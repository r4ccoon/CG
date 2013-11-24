#pragma once

#include "vec3.h" 

class CCoordinate 
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

