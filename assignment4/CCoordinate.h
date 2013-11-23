#pragma once

#include "vec3.h"
#include "CDrawableObject.h"

class CCoordinate :	public CDrawableObject
{
public:
	CCoordinate(float length);	
	~CCoordinate();

	virtual void Draw();

private:
	float _length;
	float _size;
	Vec3f colorX, colorY, colorZ;
};

