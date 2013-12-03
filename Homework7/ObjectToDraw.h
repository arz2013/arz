#pragma once
#include <vector>
#include "Matrix4.h"
#include "Vector3.h"
#include "Colors.h"

class ObjectToDraw
{
private:
	int nVerts;
	float *vertices;
	float *normals;
	float *texcoords;
	int nIndices;
	int *indices;
	std::vector<Vector3> vertexes;
	std::vector<Vector3> myIndices;
	Colors colors;

	// 
	Matrix4 translationMatrix;
	Matrix4 scalingMatrix;
	Matrix4 normalizationScalingMatrix;
	Matrix4 transformationMatrix;

public:
	ObjectToDraw(char* fileName);
	ObjectToDraw(void);
	void draw(void);
	Matrix4& getTransformationMatrix();
	Matrix4& getTranslationMatrix();
	void performFullScreenCalculation(void);
	~ObjectToDraw(void);
};

