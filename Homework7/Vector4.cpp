#include "Vector4.h"

#include <iostream>
#include <stdexcept>

Vector4::Vector4() 
{
	xyz = Vector3();
}

Vector4::Vector4(double coordinate0, double coordinate1, double coordinate2)
{
	xyz = Vector3(coordinate0, coordinate1, coordinate2);
}


Vector4::Vector4(double coordinate0, double coordinate1, double coordinate2, double wArg)
{
	xyz = Vector3(coordinate0, coordinate1, coordinate2);
	w = wArg;
}

/**
 * Should we throw an exception here?
 */
double Vector4::get(int coordinateIndex) {
	if(coordinateIndex >=0 && coordinateIndex <=2) {
		return xyz.get(coordinateIndex);
	} else if(coordinateIndex == 3) {
		return w;
	} else {
		throw std::invalid_argument("Invalid coordinateIndex value: " + coordinateIndex);
	}
}

/**
 * Should we throw an exception here?
 */
void Vector4::set(int coordinateIndex, double newCoordinateValue) {
	if(coordinateIndex >=0 && coordinateIndex <=2) {
		xyz.set(coordinateIndex, newCoordinateValue);
	} else if(coordinateIndex == 3) {
		w = newCoordinateValue;
	}
}

double Vector4::operator[](int coordinateIndex) {
	return get(coordinateIndex);
}

/**
 * Should we check for NULL here?
 */
Vector4 Vector4::add(Vector4& operand) {
	return Vector4(xyz.get(0) + operand.get(0), xyz.get(1) + operand.get(1), xyz.get(2) + operand.get(2), w + operand.get(3));
}

Vector4 Vector4::operator+(Vector4& operand) {
	return add(operand);
}

Vector4 Vector4::subtract(Vector4& operand) {
	return Vector4(xyz.get(0) - operand.get(0), xyz.get(1) - operand.get(1), xyz.get(2) - operand.get(2), w - operand.get(3));
}
	
Vector4 Vector4::operator-(Vector4& operand) {
	return subtract(operand);
}
	
Vector4 Vector4::dehomogenize() {
	return Vector4(xyz.get(0)/w, xyz.get(1)/w, xyz.get(2)/w, 1);
}

double Vector4::dotProduct(Vector4& operand) {
	return get(0) * operand.get(0) + get(1) * operand.get(1) + get(2) * operand.get(2) + get(3) * operand.get(3);
}

void Vector4::print(void) {
	std::cout << "Vector4 coordinates: (" << xyz.get(0) << ", " << xyz.get(1) << ", " << xyz.get(2) << ", " << w << ")\n"; 
}

Vector4::~Vector4(void) {
}