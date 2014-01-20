#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vec3.h"

class Camera {

protected:
	Vec3d  eye;       // POSITION OF THE CAMERA
	Vec3d  lookat;    // POINT CAMERA IS LOOKING AT
	Vec3d  up;        // UP VECTOR
	double fovy;      // FIELD OF VIEW (half opening angle in degrees of viewing frustum in y direction)

public:
	Camera() { };
   Camera(const Vec3d Eye, const Vec3d LookAt, const Vec3d Up, const double FOVy)
		{ eye=Eye; lookat=LookAt; up=Up; fovy=FOVy; }

	// FUNCTIONS TO QUERY STATE
	Vec3d Eye()    { return eye; }
	Vec3d LookAt() { return lookat; }
	Vec3d Up()     { return up;  }
	double FOVy()  { return fovy; }

	// FUNCTIONS TO SET STATE
	void Eye(const Vec3d Eye)       { eye=Eye; }
	void LookAt(const Vec3d LookAt) { lookat=LookAt; }
	void Up(const Vec3d Up)         { up=Up;   }
	void FOVy(const double FOVy)    { fovy=FOVy; }
};

#endif
