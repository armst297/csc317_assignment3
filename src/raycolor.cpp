#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

int MAX_RECURSIONS = 0;
double EPSILON_FACTOR_REFLECT = 0.1;


/*
if ray gets a hit:
    get material diffuse (kd) colour
    if material is a mirror surface:
        cast a mirror ray with the reflect function
        if mirror ray hits:
            add mirror colour (km) * returned colour
    return true
else
    return false

will need to do a recursion check so that you eventually return false for that
'if mirror ray hits' to stop infinite loop

max reflections set, somewhere around 10 shouldn't take too long to calculate
for debugging if wonky start with 0, then 1.... increase
*/


bool raycolor(
  const Ray & ray,
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
    ////////////////////////////////////////////////////////////////////////////
    // Replace with your code here:



    rgb = Eigen::Vector3d(0,0,0);
    Eigen::Vector3d rgb_phong, light_mirrored, rgb_mirrored;
    Ray reflected_ray;

    // variables needed for first_hit function
    Eigen::Vector3d n = Eigen::Vector3d::Zero();
    int hit_id = -1;
    double t = -1.0;


    if( first_hit(ray, min_t, objects, hit_id, t, n) ){
        // get colour based on blinn_phong_shading
        rgb_phong = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
        // add mirrored component IFF applicable
        light_mirrored = Eigen::Vector3d::Zero();
        if(! (objects[hit_id]->material->km == Eigen::Vector3d::Zero()) ){
            // has a reflective component, calculate the reflection
            if(num_recursive_calls < MAX_RECURSIONS){
                // need to figure out what colour to return
                reflected_ray.direction = reflect(ray.direction, n);
                reflected_ray.origin = (ray.origin + t*ray.direction) + EPSILON_FACTOR_REFLECT*n;
                raycolor(reflected_ray, 1.0, objects, lights, num_recursive_calls + 1, light_mirrored);
                rgb_mirrored = (objects[hit_id]->material->km.array() * light_mirrored.array()).matrix();
            }

        }
        // add mirror light to total
        rgb = rgb_phong + rgb_mirrored;
        return true;
    }

    return false;
    ////////////////////////////////////////////////////////////////////////////
}
