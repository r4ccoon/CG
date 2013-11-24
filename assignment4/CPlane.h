#pragma once 

class CPlane  
{
public:
	CPlane(float length, float lineLength);
	~CPlane();

	void Draw();
    void Reset();
    void Key(unsigned char key);
    float U, V, W;

private :
	float _length;
    float _lineLength;
};

