#pragma once
#include "Vector3.h"

class Vector4
{
public:
	Vector4(double coordinate0, double coordinate1, double coordinate2);
	Vector4(double coordinate0, double coordinate1, double coordinate2, double wArg);
	Vector4(void);
	~Vector4(void);
	void set(int coordinateIndex, double newCoordinateValue);
	double get(int coordinateIndex);
	double operator[](int coordinateIndex);
	Vector4 add(Vector4& operand);
	Vector4 operator+(Vector4& operand);
	Vector4 subtract(Vector4& operand);
	Vector4 operator-(Vector4& operand);
	double dotProduct(Vector4& operand);
	Vector4 dehomogenize();
	void print(void);
private:
	Vector3 xyz;
	double w; // What's the default value of this?
};

