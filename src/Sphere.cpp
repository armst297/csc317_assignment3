#include "Sphere.h"
#include "Ray.h"
#include <cmath>
#include <Eigen/Geometry>


// only take the smallest POSITIVE real number
// sphere normal
// if you know intersection of ray w circle, at point p
// you want from center to p, so p-c is the vector
// DONT FORGET TO MAKE N A UNIT VECTOR

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // equation of a circle (implicit)
  // (x - x_center)^2 + (y - y_center)^2 +(z - z_center)^2 - radius^2 = 0
  // vector form inserting our ray
  // (d.dot(d))*t^2 + 2*d.dot(e - center)*t + (e - c).dot(e - c) - radius^2 = 0

  //first determine how many solutions there are
  // A*t^2 + B*t + C = 0
  double a = ray.direction.dot(ray.direction);
  double b = 2*ray.direction.dot(ray.origin - this->center);
  Eigen::Vector3d temp = ray.origin - this->center;
  double c = temp.dot(temp) - (this->radius)*(this->radius);

  // check which case this is
  double discrim = b*b - 4.0*a*c;
  if (discrim < 0){
      //no real solutions
      return false;
  }
  if (discrim == 0){
      // one real solution, at a single point
      double t_temp = -1.0*b/(2*a);
      if (t_temp >= min_t){
          //actually found a spot!
          t = t_temp;
          //calculate normal of spot
          Eigen::Vector3d location = (ray.origin + t*ray.direction);
          n = (location - this->center)/(this->radius);
          return true;
      }
      return false;
  } else {
      // 2 solutions take the smallest one
      double t_temp1 = (-1.0*b + sqrt(discrim))/(2*a);
      double t_temp2 = (-1.0*b - sqrt(discrim))/(2*a);
      if(t_temp1 < min_t && t_temp2 < min_t){
          //no solutions visible
          return false;
      } else if (t_temp1 < min_t || t_temp2 < t_temp1){
          //only t_temp2 is valid or t_temp2 < t_temp1
          t = t_temp2;
          //calculate normal of spot
          Eigen::Vector3d location = (ray.origin + t*ray.direction);
          n = (location - this->center)/(this->radius);
          return true;
      } else if (t_temp2 < min_t || t_temp1 < t_temp2){
          //only t_temp1 is valid or t_temp1 < t_temp2
          t = t_temp1;
          //calculate normal of spot
          Eigen::Vector3d location = (ray.origin + t*ray.direction);
          n = (location - this->center)/(this->radius);
          return true;
      }

  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
