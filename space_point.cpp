#include "space_point.h"
#include <cmath>

double abs (Vec3d v)
{
  return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

Vec3d operator+ (const Vec3d v1, const Vec3d v2)
{
  return Vec3d { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vec3d operator- (const Vec3d v1, const Vec3d v2)
{
  return Vec3d { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

Vec3d operator* (double d, const Vec3d v)
{
  return Vec3d { d*v.x, d*v.y, d*v.z };
}

Vec3d operator* (const Vec3d, double d)
{
  return d*v;
}

Vec3d operator/ (const Vec3d, double d)
{
  return 1/d * v;
}

double dot (const Vec3d v1, const Vec3d v2)
{
  return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}

