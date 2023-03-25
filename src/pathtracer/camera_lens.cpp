#include "camera.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "CGL/misc.h"
#include "CGL/vector2D.h"
#include "CGL/vector3D.h"

using std::cout;
using std::endl;
using std::max;
using std::min;
using std::ifstream;
using std::ofstream;

namespace CGL {

using Collada::CameraInfo;

Ray Camera::generate_ray_for_thin_lens(double x, double y, double rndR, double rndTheta) const {

  // TODO Project 3-2: Part 4
  // compute position and direction of ray from the input sensor sample coordinate.
  // Note: use rndR and rndTheta to uniformly sample a unit disk.

	double c_spc_x = x * 2 * tan(0.5 * hFov * PI / 180) - tan(0.5 * hFov * PI / 180);
	double c_spc_y = y * 2 * tan(0.5 * vFov * PI / 180) - tan(0.5 * vFov * PI / 180);

	Vector3D red_seg_dir(c_spc_x, c_spc_y, -1);
	Vector3D pLens(lensRadius * sqrt(rndR) * cos(rndTheta), lensRadius * sqrt(rndR) * sin(rndTheta), 0);
	Vector3D pFocus(-focalDistance / red_seg_dir.z * red_seg_dir.x, -focalDistance / red_seg_dir.z * red_seg_dir.y, -focalDistance);
	Vector3D blue_seg_dir_norm = (pFocus - pLens).unit();

	Ray w_spc_ray(c2w * pLens + pos, c2w * blue_seg_dir_norm);
	w_spc_ray.min_t = nClip;
	w_spc_ray.max_t = fClip;

	return w_spc_ray;
}


} // namespace CGL
