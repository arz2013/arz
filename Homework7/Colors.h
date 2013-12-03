#pragma once
#include "Vector3.h"
#include <vector>

class Colors
{
private:
	int colorIndex;
	std::vector<Vector3> colorsVector;
public:
	Colors(void);
	~Colors(void);
	Vector3& next();
};

