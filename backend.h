#include <vector>
#include <cmath>
#define DEBUG_OUT(x) std::cout <<__LINE__<<": "<< (#x) <<" = "<< (x) << std::endl

const Steps step(1, 0.1, 0.1);

struct SpacePoint
{
	double x;
	double y;
	double z;

	SpacePoint()
		:x{NAN}, y{NAN}, z{NAN} 
	{}

	SpacePoint(double x1, double x2, double x3)
		: x{x1}, y{x2}, z{x3} 
	{}

	SpacePoint(const SpacePoint& p)
		:x{p.x}, y{p.y}, z{p.z} 
	{}

};


struct func
{
	func(){}

	double operator()(SpacePoint p)
	{
		return pow(p.x, 2)/16 + pow(p.y, 2)/25 - pow(p.z, 2)/13;
		//return pow(x, 2) + pow(y, 2) + pow(z, 2) - 25;
	}

	double operator()(double x, double y, double z)
	{
		return pow(x, 2)/16 + pow(y, 2)/25 - pow(z, 2)/13;
		//return pow(x, 2) + pow(y, 2) + pow(z, 2) - 25;
	}
};

class CalcFunction
{
private:
	func F;
	Range R;
	double error_rate = step.f/10;

public:
	CalcFunction(func FF, Range rr)
		: F{FF}, R{rr} {}

	/*bool check_point(const SpacePoint* p)
	{
		if ((p->x && p->y && (isnan(p->z))) || (p->y && p->z && (isnan(p->x))) || (p->x && p->z && (isnan(p->y))))
			return false;
		return true;
	}*/ //DEBUG comment	

	SpacePoint put_to_nan(const SpacePoint* p, double arg)
	{
		if (isnan(p->x))
			return SpacePoint(arg, p->y, p->z);
		if (isnan(p->y))
			return SpacePoint(p->x, arg, p->z);
		if (isnan(p->z))
			return SpacePoint(p->x, p->y, arg);
		throw std::runtime_error("invalid argumenst in CalcFunction::put_to_nan");
	}

	std::vector<double> calc(const Point* p)
	{
		std::vector<double> third_coord;
		for (double arg = R.start; arg < R.end; arg += step.f)
		{
			if (-error_rate <= F(put_to_nan(p, arg)) && F(put_to_nan(p, arg)) <= error_rate)
				third_coord.push_back(arg);

		}
		return third_coord;
	}		
	
};


class Line
{
private:
	CalcFunction F;
	Range R;
	SpacePoint fix_arg;
	Graph_lib::Open_polyline line;

public:
	std::vector<const SpacePoint *> line_real_points; //DEBUG

	Line(CalcFunction FF, Range rr, SpacePoint&& fa)
		: F{FF}, R{rr}, fix_arg{fa}
	{ calculate(); }

	void calculate()
	{
		for (double arg = R.start; arg < R.end; arg += step.p)
		{
			SpacePoint p;
			std::vector<double> third_coord;
			if (!isnan(fix_arg.x))
			{
				p.x = fix_arg.x;
				p.y = arg;
				third_coord = F.calc(&p);
				for (double tc : third_coord)
				{
					p.z = tc;
					line_real_points.push_back(new SpacePoint(p)); //DEBUG
					line.add(Screen::get_projection(p));
				}
			}

			else if (!isnan(fix_arg.y))
			{
				p.y = fix_arg.y;
				p.z = arg;	
				third_coord = F.calc(&p);
				for (double tc : third_coord)
				{
					p.x = tc;
					line_real_points.push_back(new SpacePoint(p)); //DEBUG
					line.add(Screen::get_projection(p));
				}
			}

			else if (!isnan(fix_arg.z))
			{
				p.z = fix_arg.z;
				p.x = arg;
				third_coord = F.calc(&p);
				for (double tc : third_coord)
				{
					p.y = tc;
					line_real_points.push_back(new SpacePoint(p)); //DEBUG
					line.add(get_projection(p));
				}
			}		
		}
	}

	const Graph_lib::Open_polyline& get_polyline() { return line; }

	~Line()		//DEBUG
	{
		for (int p = 0; p < line_real_points.size(); ++p)
			delete line_real_points[p];
	}
};


class Graph
{
private:
	CalcFunction F;
	Range R;
	std::vector <const Line*> figure;

public:
	Graph(func FF, Range rr)
		: F{CalcFunction(FF, rr)}, R{rr}
	{
		for (double x = R.start; x < R.end; x += step.l)
			figure.push_back(new Line(F, R, SpacePoint(x, NAN, NAN)));

		for (double y = R.start; y < R.end; y += step.l)
			figure.push_back(new Line(F, R, SpacePoint(NAN, y, NAN)));

		for (double z = R.start; z < R.end; z += step.l)
			figure.push_back(new Line(F, R, SpacePoint(NAN, NAN, z)));
	}

	std::vector <const Line*>& get_figure() { return figure; }

	void print()  //DEBUG
	{
		for (int nl = 0; nl < figure.size(); ++nl)
		{
			for(int np = 0; np < figure[nl]->line_real_points.size(); ++np)
			{
				std::cout << "SpacePoint: (" << figure[nl]->line_real_points[np]->x \
				<< ", "<<figure[nl]->line_real_points[np]->y\
				<<", "<<figure[nl]->line_real_points[np]->z << ")"<<std::endl;
			}
		}
	}

	//объекты по указателям лежат в динамической памяти
	~Graph()
	{
		for (int l = 0; l < figure.size(); ++l)
			delete figure[l];
	}
};