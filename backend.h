#ifndef BACKEND_H
#define BACKEND_H 1

#include <vector>
#include <stdexcept>
#include <cmath>
#include "parse.h"
#include "space_point.h"
#include "constants.h"
#include "Graph_lib_additions.h"

using namespace CONSTS;

class CalcFunction
{
private:
	func F;
	Range R;
	double error_rate = STEP.f/2;

public:
	CalcFunction(func FF, Range rr)
		: F{FF}, R{rr} 
	{}

	std::vector<double> calc(const SpacePoint* p);
	SpacePoint put_to_nan(const SpacePoint* p, double arg);
};


class GraphLine
{
private:
	CalcFunction F;
	Range R;
	SpacePoint fix_arg;
	Graph_lib::Curve line;

public:
	GraphLine(CalcFunction FF, Range rr, SpacePoint&& fa)
		: F{FF}, R{rr}, fix_arg{fa}
	{ calc_line(); }

	void calc_line();
	Graph_lib::Curve& get_curve() { return line; }
};


class Graph
{
private:
	CalcFunction F;
	Range R;
	std::vector <GraphLine*> figures;

public:
	Graph(CalcFunction FF, Range rr);

	std::vector <GraphLine*>& get_figures() { return figures; }
	void clear();
	~Graph();
};

#endif
