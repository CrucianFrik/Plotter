#include <vector>


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
};

const Steps step(1, 1, 1);

struct ScreenPoint
{
	double x;
	double y;

	ScreenPoint(double x1, double x2)
		:x{x1}, y{x2} {}
}

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

	const ScreenPoint* get_projection(/*...*/);
	{}
};


struct Range
{
	double start;
	double end;

	Range(double s, double e)
		: start{s}, end{e}{}
};


class Line
{
private:
	CalcFunction F;
	Range r;
	Point fix_arg;
	vector<const ScreenPoint const*> line;

public:
	Line(CalcFunction FF, Range rr, Point& fa)
		: F{FF, rr}, r{rr}, fix_arg{fa} //?? вынести эту красивую строчку за после if?
	{ 
		if (!check_point(fix_arg))
			throw MyExeption("incorrect Point in Line constructor");

		calculate(); 
	}

	bool check_point(Point* p)
	{
		if ((p.x && p.y) || (p.y && p.z) || (p.x && p.z) || (p.x && p.y && p.z))
			return false;
		return true;
	}

	void calculate()
	{
		for (double arg = r.start; arg < r.end; arg += step.p)
		{
			Point p Point();
			if (fix_arg.x)
			{
				p.x = fix_arg.x;
				p.y = arg;
				p.z = F.calc(p);
			}

			else if (fix_arg.y)
			{
				p.y = fix_arg.y;
				p.z = arg;	
				p.x = F.calc(p);
			}

			else if (fix_arg.z)
			{
				p.z = fix_arg.z;
				p.x = arg;
				p.y = F.calc(p);
			}		

			//объекты по указателям лежат в динамической памяти
			line.push_back(p.get_projection());
		}
	}

	const vector<const ScreenPoint const*>& get_line() { return line; }

	~Line()
	{
		for (int i = 0; i < line.size(); ++i)
			delete line[i];
	}
};


class Graph
{
private:
	CalcFunction F;
	Range r;
	vector <const vector<const ScreenPoint *const> const*> lines;

public:
	Graph(function FF, Range rr)
		: F{CalcFunction(FF, rr)}, r{rr}
	{
		for (double x = r.start; x < r.end; x += step.l)
			lines.push_back(new Line(F, r, Point(x, NAN, NAN)));

		for (double y = r.start; y < r.end; y += step.l)
			lines.push_back(new Line(F, r, Point(NAN, y, NAN)));

		for (double z = r.start; z < r.end; z += step.l)
			lines.push_back(new Line(F, r, Point(NAN, NAN, z)));
	}

	~Graph()
	{
		for (int l = 0; l < lines.size(); ++l)
			delete l;
	}
};


class CalcFunction
{
private:
	function F;
	Range r;

public:
	CalcFunction(function FF, Range rr)
		: F{FF}, r{rr} {}

	bool check_point(Point* p)
	{
		if ((p.x && p.y && (!p.z)) || (p.y && p.z && (!p.x)) || (p.x && p.z && (!p.y)))
			return false;
		return true;
	}	

	double calc(Point* p)
	{
		if (!check_point(p))
			throw MyExeption("incorrect Point in CalcFunction.calc");

		for ... arg += step.f
		///
	}		
	
};