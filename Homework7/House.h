#pragma once
#include "Vector3.h"
#include <vector>

class House
{
private:
	std::vector<Vector3> vertices;
	std::vector<Vector3> colors;
	std::vector<Vector3> indices;
public:
	House(void);
	std::vector<Vector3> getIndices();
	Vector3& getVertice(int index);
	Vector3& getColor(int index);
	~House(void);
};

