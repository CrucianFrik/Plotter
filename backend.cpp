#include "backend.h"

bool isnan(double n)
{
  return (n != n);
}

SpacePoint CalcFunction::put_to_nan(const SpacePoint* p, double arg)
	{
		if (isnan(p->x))
			return SpacePoint(arg, p->y, p->z);
		if (isnan(p->y))
			return SpacePoint(p->x, arg, p->z);
		if (isnan(p->z))
			return SpacePoint(p->x, p->y, arg);
		throw std::runtime_error("invalid argumenst in CalcFunction::put_to_nan");
	}


std::vector<double> CalcFunction::calc(const Point* p)
	{
		std::vector<double> third_coord;
		for (double arg = R.start; arg < R.end; arg += step.f)
			if (-error_rate <= F(put_to_nan(p, arg)) && F(put_to_nan(p, arg)) <= error_rate)
				third_coord.push_back(arg);

		return third_coord;
	}


void Line::calc_line()
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
				line.add(get_projection(p));
			}
		}		
	}
}

Graph::Graph(CalcFunction FF, Range rr)
	: F{FF}, R{rr}
{
	for (double x = R.start; x < R.end; x += step.l)
		figures.push_back(new Line(F, R, SpacePoint(x, NAN, NAN)));

	for (double y = R.start; y < R.end; y += step.l)
		figures.push_back(new Line(F, R, SpacePoint(NAN, y, NAN)));

	for (double z = R.start; z < R.end; z += step.l)
		figures.push_back(new Line(F, R, SpacePoint(NAN, NAN, z)));
}

Graph::~Graph()
{
	for (int l = 0; l < figures.size(); ++l)
		delete figures[l];
}