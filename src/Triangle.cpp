#include "Triangle.h"
#include "Ray.h"
#include <cmath>
#include <Eigen/Geometry>
#include <Eigen/Dense>

// will be the hardest one
// alpha + beta < 1
// alpha > 0
// beta > 0
// constrict you to a Triangle
//equate with point on a ray
// [t1, t2, -d][alpha]
//             |beta |
//             [  t  ]
// eigen linear library has linear solvers, allowed to use those
// eigen documentation super sucks according to ta
// no solutions, dont touch
// linearly dep, many solutions, catch it on an edge of the Triangle

// computing normals (clockwise normal) not ccw,
// right hand rule based on corners a, b, c

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  /*
  My code here
  Check if viewing ray is parallel to the plane containing the triangle
  use right hand rule and the triangle points to calculate the normal vector
  */
  Eigen::Vector3d v1 = std::get<1>(this->corners) - std::get<0>(this->corners);
  Eigen::Vector3d v2 = std::get<2>(this->corners) - std::get<0>(this->corners);
  Eigen::Vector3d normal = v1.cross(v2);
  normal.normalize();

  // ax + by + cz = d -> Equation of a plane
  // <a,b,c> = normal -> Normal vector to the plane
  // d=ax0 + by0 + cz0
  // <x0, y0, z0> = point -> Point on the plane
  double a = normal(0);
  double b = normal(1);
  double c = normal(2);
  double x0 = (std::get<0>(this->corners))(0);
  double y0 = (std::get<0>(this->corners))(1);
  double z0 = (std::get<0>(this->corners))(2);
  double d = a * x0 + b * y0 + c * z0;

  if (normal.dot(ray.direction) == 0) {
      // Parallel to plane
      // Don't rend
      return false;
  }

  // Solve equation to determine if intersection with triangle
  // e + t*d = a + B(b-a) + G(c-a); B=Beta, G=Gamma
  //
  Eigen::Matrix3d A;
  Eigen::Vector3d B;
  Eigen::Vector3d x;

  A << (std::get<0>(this->corners))(0) - (std::get<1>(this->corners))(0), (std::get<0>(this->corners))(0) - (std::get<2>(this->corners))(0), ray.direction(0),
       (std::get<0>(this->corners))(1) - (std::get<1>(this->corners))(1), (std::get<0>(this->corners))(1) - (std::get<2>(this->corners))(1), ray.direction(1),
       (std::get<0>(this->corners))(2) - (std::get<1>(this->corners))(2), (std::get<0>(this->corners))(2) - (std::get<2>(this->corners))(2), ray.direction(2);
  B << (std::get<0>(this->corners))(0) - ray.origin(0),
       (std::get<0>(this->corners))(1) - ray.origin(1),
       (std::get<0>(this->corners))(2) - ray.origin(2);

  // X vector in order of Beta, Gamma, t
  x = A.colPivHouseholderQr().solve(B);
  double beta = x(0);
  double gamma = x(1);
  double t_temp = x(2);

  if (t_temp >= min_t && gamma >= 0 && gamma <= 1 && beta >= 0 && beta <= (1.0 - gamma)) {
      t = t_temp;
      n = normal;
      return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
