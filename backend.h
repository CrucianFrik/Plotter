#ifndef BACKEND_H
#define BACKEND_H 1

#include <vector>
#include <cmath>

#include "gui.h"

class CalcFunction
{
private:
	func F;
	Range R;
	double error_rate = step.f/10;

public:
	CalcFunction(func FF, Range rr)
		: F{FF}, R{rr} {}

	std::vector<double> calc(const Point* p);
	SpacePoint put_to_nan(const SpacePoint* p, double arg);
};


class Line
{
private:
	CalcFunction F;
	Range R;
	SpacePoint fix_arg;
	Graph_lib::Open_polyline line;

public:
	Line(CalcFunction FF, Range rr, SpacePoint&& fa)
		: F{FF}, R{rr}, fix_arg{fa}
	{ calc_line(); }

	void calc_line();
	const Graph_lib::Open_polyline& get_polyline() { return line; }
};


class Graph
{
private:
	CalcFunction F;
	Range R;
	std::vector <const Line*> figures;

public:
	Graph(func FF, Range rr);

	std::vector <const Line*>& get_figure() { return figures; }
	~Graph();
};

#endif
