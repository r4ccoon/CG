#pragma once
#include "CDrawableObject.h"

class CPlane :
	public CDrawableObject
{
public:
	CPlane(float length);
	~CPlane();

	void Draw();
    void Reset();
    void Key(unsigned char key);
    float U, V, W;

private :
	float _length;
    float _lambda1, _lambda2;
};

