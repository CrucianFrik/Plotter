#include <vector>
#include <cmath>


struct MyExeption
{
	std::string m_error = "";
	MyExeption(std::string error)
	: m_error(error) {}

	const char* get_error() { return m_error.c_str();}
};

struct Steps
{
	double l;  //Шаг между линиями
	double p;  //Шаг между точками на линии
	double f;  //Шаг для перебора значений третей переменной 
					//при имеющихся двух для нахождения x3 по f(x1, x2)

	Steps(double ll, double pp, double ff)
		:l{ll}, p{pp}, f{ff} 
	{}
};

const Steps step(1, 1, 1);

struct ScreenPoint
{
	double x;
	double y;

	ScreenPoint(double x1, double x2)
		:x{x1}, y{x2} {}
};

struct Point
{
	double x;
	double y;
	double z;

	Point()
		:x{NAN}, y{NAN}, z{NAN} 
	{}

	Point(double x1, double x2, double x3)
		: x{x1}, y{x2}, z{x3} 
	{}

};


struct Range
{
	double start;
	double end;

	Range(double s, double e)
		: start{s}, end{e}{}
};

struct function
{
	function(){}

	double operator()(Point p)
	{
		return pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2) - 25;
	}

	double operator()(double x, double y, double z)
	{
		return pow(x, 2) + pow(y, 2) + pow(z, 2) - 25;
	}
};

class CalcFunction
{
private:
	function F;
	Range R;
	double error_rate = step.f/2;

public:
	CalcFunction(function FF, Range rr)
		: F{FF}, R{rr} {}

	bool check_point(const Point* p)
	{
		if ((p->x && p->y && (!p->z)) || (p->y && p->z && (!p->x)) || (p->x && p->z && (!p->y)))
			return false;
		return true;
	}	

	Point put_to_nan(const Point* p, double arg)
	{
		if (!p->x)
			return Point(arg, p->y, p->z);
		if (!p->y)
			return Point(p->x, arg, p->z);
		if (!p->z)
			return Point(p->x, p->y, arg);
	}

	std::vector<double> calc(const Point* p)
	{
		if (!check_point(p))
			throw MyExeption("incorrect Point in CalcFunction.calc");

		std::vector<double> third_coord;
		for (double arg = R.start; arg < R.end; arg += step.f)
		{
			if (F(put_to_nan(p, arg)) <= error_rate)
				third_coord.push_back(arg);
		}
		return third_coord;
	}		
	
};

const ScreenPoint* get_projection(Point p);

class Line
{
private:
	CalcFunction F;
	Range R;
	Point fix_arg;
	std::vector<const ScreenPoint *> line;

public:
	Line(CalcFunction FF, Range rr, Point&& fa)
		: F{FF}, R{rr}, fix_arg{fa} //?? вынести эту красивую строчку за после if?
	{ 
		if (!check_point(&fix_arg))
			throw MyExeption("incorrect Point in Line constructor");

		calculate(); 
	}

	bool check_point(const Point* p)
	{
		if ((p->x && p->y) || (p->y && p->z) || (p->x && p->z) || (p->x && p->y && p->z))
			return false;
		return true;
	}

	void calculate()
	{
		for (double arg = R.start; arg < R.end; arg += step.p)
		{
			Point p;
			std::vector<double> third_coord;
			if (fix_arg.x)
			{
				p.x = fix_arg.x;
				p.y = arg;
				third_coord = F.calc(&p);
				for (double tc : third_coord)
					p.z = tc;
					line.push_back(get_projection(p));
			}

			else if (fix_arg.y)
			{
				p.y = fix_arg.y;
				p.z = arg;	
				third_coord = F.calc(&p);
				for (double tc : third_coord)
					p.x = tc;
					line.push_back(get_projection(p));
			}

			else if (fix_arg.z)
			{
				p.z = fix_arg.z;
				p.x = arg;
				third_coord = F.calc(&p);
				for (double tc : third_coord)
					p.y = tc;
					line.push_back(get_projection(p));
			}		
		}
	}

	const std::vector<const ScreenPoint*>& get_line() { return line; }

	~Line()
	{
		for (int p = 0; p < line.size(); ++p)
			delete line[p];
	}
};


class Graph
{
private:
	CalcFunction F;
	Range R;
	std::vector <const Line*> graph;

public:
	Graph(function FF, Range rr)
		: F{CalcFunction(FF, rr)}, R{rr}
	{
		for (double x = R.start; x < R.end; x += step.l)
			graph.push_back(new Line(F, R, Point(x, NAN, NAN)));

		for (double y = R.start; y < R.end; y += step.l)
			graph.push_back(new Line(F, R, Point(NAN, y, NAN)));

		for (double z = R.start; z < R.end; z += step.l)
			graph.push_back(new Line(F, R, Point(NAN, NAN, z)));
	}

	std::vector <const Line*>& get_graph() { return graph; }

	//объекты по указателям лежат в динамической памяти
	~Graph()
	{
		for (int l = 0; l < graph.size(); ++l)
			delete graph[l];
	}
};


