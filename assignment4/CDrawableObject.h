#pragma once
class CDrawableObject
{
public:
	CDrawableObject();

	virtual void Draw() = 0;

	~CDrawableObject();
};

