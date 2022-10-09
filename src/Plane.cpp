#include "Plane.h"
#include "Ray.h"
#include <cmath>
#include <Eigen/Geometry>

//

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // My code here
  // ax + by + cz = d -> Equation of a plane
  // <a,b,c> = normal -> Normal vector to the plane
  // d=ax0 + by0 + cz0
  // <x0, y0, z0> = point -> Point on the plane
  double a = this->normal(0);
  double b = this->normal(1);
  double c = this->normal(2);
  double x0 = this->point(0);
  double y0 = this->point(1);
  double z0 = this->point(2);
  double d = a * x0 + b * y0 + c * z0;

  /*
  origin + t * direction -> equation of the ray
  break into components x, y, z and solve for intersection with the plane
  x = x_origin + t * x_direction
  y = y_origin + t * y_direction
  z = z_origin + t * z_direction

  Check to see if the viewing line is parallel to the plane
  Calculate dot product of the plane normal and the direction
  If parallel then
    check if viewing line is on the plane (ie. origin is on the plane)
  else
    only one solution for intersection;

  */

    if (this->normal.dot(ray.direction) == 0) {
        // Parallel to plane
        // if (a*ray.origin(0) + b*ray.origin(1) + c*ray.origin(2) == d) {
        //     // On the plane
        //     t = min_t;
        //     n = normal;
        //     return true;
        // }
        return false;
    }
    double t_temp = -1.0*(a*ray.origin(0) + b*ray.origin(1) + c*ray.origin(2) - d)
                    / (a*ray.direction(0) + b*ray.direction(1) + c*ray.direction(2));
    if (t_temp < min_t) {
        // Not in our camera view
        return false;
    }

    // In our field of view
    t = t_temp;
    n = this->normal;
    return true;
  ////////////////////////////////////////////////////////////////////////////
}
