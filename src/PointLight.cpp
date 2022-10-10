#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  // return the direction vector towards the light source based on the given q
  d = (this->p) - q;
  // distance is the max_t
  max_t = d.norm();
  d.normalize(); // normalized direction
  return;
  ////////////////////////////////////////////////////////////////////////////
}
