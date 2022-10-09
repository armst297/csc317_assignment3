#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
    Eigen::Vector3d reflected_ray = (2*(n.dot(in))*n - in).normalized();
    return reflected_ray;
  ////////////////////////////////////////////////////////////////////////////
}
