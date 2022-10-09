#include "first_hit.h"

bool first_hit(
  const Ray & ray,
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id,
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  int size = objects.size();
  double t_temp = 0;
  bool first_hit = true;
  Eigen::Vector3d n_temp = Eigen::Vector3d::Zero();
  for (int i = 0; i < size; ++i){
    if(objects[i]->intersect(ray, min_t, t_temp, n_temp)){
        if(first_hit){
            t = t_temp;
            n = n_temp;
            hit_id = i;
            first_hit = false;
        } else if(t_temp < t){
            // is closer
            t = t_temp;
            n = n_temp;
            hit_id = i;
        }
    }
  }
  if(first_hit){
      //no hits found
      return false;
  }

  return true;
  ////////////////////////////////////////////////////////////////////////////
}
