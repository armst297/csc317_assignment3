#include "viewing_ray.h"

// first function, generate rays (perspective)
// given pixel index i, j
// remember camera coordinate system
// ^V
// |
// |
// |______>u
// think of matrix way, index from top left down
// (i, j) --> (x, y) physical image distance
// x = (-1/2)*width_camera + (i + 0.5)*width_pixel
// y = (1/2)*height_camera - (j + 0.5)*height_pixel
// width_pixel = (width_camera/width_image)
// heigh_pixel = (height_camera/height_image)
// .5 is to hit the center of each pixel
//                         __
// i,j is int coordinate, |
// x, y is double |
//                |___
//
// need to transform again to get our 3d space (u,v,w)
// r (ray vector) = x*u +y*v - d*w
// d is the distance relative to the camera eye

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  double x = (-0.5)*camera.width + (j + 0.5)*camera.width/width;
  double y = (0.5)*camera.height - (i + 0.5)*camera.height/height;

  ray.origin = camera.e;
  ray.direction = x*camera.u + y*camera.v - camera.d*camera.w;
  // ray.direction.normalize();

  ////////////////////////////////////////////////////////////////////////////
}
