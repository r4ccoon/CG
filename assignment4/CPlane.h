#pragma once
#include "CDrawableObject.h"

class CPlane :
	public CDrawableObject
{
public:
	CPlane(float length);
	~CPlane();

	void Draw( );

private :
	float _length;
};

