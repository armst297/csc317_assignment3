#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <limits>
#include <cmath>

// gobal definitions
double AMBIENT_FACTOR = 0.1;
double EPSILON_FACTOR = 0.0001;


/*
Gives you the material diffused colour

colour <= ambient colour * 0.1
//do all lighting contributions (i.e for each light)
for light conditions:
    throw ray at light
    check if "shadow ray" hits, i.e. does the light hit that point of the material
    if not shadow:
        // add blin shadding contribution
        diffuse*light_brightness*(l_direction*normal_of_surface)
            + specular*light_brightness(n*h)^p
        // material phong exponent
        //h is the halfway vector (l - v) normalized // assuming ray into object
        // no distance attenuation, therefore normalize the l vector
        // careful where the v is pointing for the sign (-v into object, +v out of object)

more on shadows
point light
directed light
max_t
if length of the ray is > max_t then no shadow ONLY for point lights
directional lights ALWAYS cast shadows

*/

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id,
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
    // set up any variables needed for calculations
    // object at hit_id is the one we need to compute the colour for
    // Object & obj = objects[hit_id];
    Ray shadow_ray;
    Eigen::Vector3d rgb, dir_light, shadow_obj_normal, rgb_diffused, rgb_specular, rgb_ambient, rgb_phong, hit_normal, halfvect;
    double max_t, shadow_hit_t;
    int shadow_hit_id;
    bool hit_obj;
    Eigen::Vector3d object_hit_location = ray.origin + t*ray.direction;
    int num_of_lights = lights.size();

    shadow_ray.origin = object_hit_location + EPSILON_FACTOR*n;

    // get the ambient colour (pre any actual light sources)
    rgb_ambient = AMBIENT_FACTOR*(objects[hit_id]->material->ka);
    rgb_phong = Eigen::Vector3d::Zero();
    // calculate the colour impact for each light source
    for(int i = 0; i < num_of_lights; ++i){
        // get the direction of the light and the distance
        // find the direction and distance of the light
        lights[i]->direction(object_hit_location, dir_light, max_t);
        shadow_ray.direction = dir_light;

        // add check for if shadow ray hits here, for now just fix diffuse & Specular
        rgb_diffused = Eigen::Vector3d::Zero();
        rgb_specular = Eigen::Vector3d::Zero();

        hit_obj = first_hit(shadow_ray, 0.0, objects, shadow_hit_id, shadow_hit_t, shadow_obj_normal);
        if(
            (max_t == std::numeric_limits<double>::infinity()) ||
            !hit_obj ||
            (hit_obj && (shadow_hit_t > max_t))
        ) {

            // get diffused light
            double n_dot_l = n.dot(dir_light);
            double max_angle_factor = std::max(0.0, n_dot_l);
            rgb_diffused = ((objects[hit_id]->material->kd).array() * (lights[i]->I).array()).matrix() * max_angle_factor;

            // get specular light
            halfvect = (dir_light - ray.direction.normalized()).normalized();
            double n_dot_h = n.dot(halfvect);
            double max_angle_phong = std::pow(std::max(0.0, n_dot_h), objects[hit_id]->material->phong_exponent);
            rgb_specular = ((objects[hit_id]->material->ks).array() * (lights[i]->I).array()).matrix() * max_angle_phong;

        }

        rgb_phong += rgb_diffused + rgb_specular;

    }

    rgb = rgb_ambient + rgb_phong;
    return rgb;
  ////////////////////////////////////////////////////////////////////////////
}
