#ifndef SPACE_POINT_H
#define SPACE_POINT_H 1

#include <cmath>

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

struct Vec3d
{
	double x;
	double y;
	double z;

  Vec3d (double x_, double y_, double z_)
    : x {x_}, y {y_}, z {z_} {}

  Vec3d (SpacePoint& p)
    : x {p.x}, y {p.y}, z {p.z} {}
};

double abs(Vec3d);
Vec3d operator+ (const Vec3d, const Vec3d);
Vec3d operator- (const Vec3d, const Vec3d);
Vec3d operator* (double, const Vec3d);
Vec3d operator* (const Vec3d, double);
Vec3d operator/ (const Vec3d, double);

double dot (const Vec3d, const Vec3d);

#endif // SPACE_POINT_H
