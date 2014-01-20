#ifndef _RAY_H_
#define _RAY_H_

#include "vec3.h"

class Ray {

protected:
	Vec3d pos;  // POINT ON RAY
	Vec3d dir;  // DIRECTION

public:
	Ray() { pos=Vec3d::ZERO; dir=Vec3d::ZERO; }
	Ray(const Vec3d p, const Vec3d d) { pos=p; dir=d; }

	Vec3d Pos() { return pos; }
	Vec3d Dir() { return dir; }

	void Pos(const Vec3d p) { pos = p; }
	void Dir(const Vec3d d) { dir = d; }

	void Print() { pos.Print(); dir.Print(); }
};

#endif