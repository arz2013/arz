#include "Vector3.h"
#include <math.h>
#include <iostream>
#include <stdexcept>

Vector3::Vector3() 
{
	coordinate0 = 0;
	coordinate1 = 0;
	coordinate2 = 0;
}

Vector3::Vector3(double coord0, double coord1, double coord2)
{
	coordinate0 = coord0;
	coordinate1 = coord1;
	coordinate2 = coord2;
}

void Vector3::set(int coordinateIndex, double newCoordValue) 
{
	if(coordinateIndex == 0) {
		coordinate0 = newCoordValue;
	} else if(coordinateIndex == 1) {
		coordinate1 = newCoordValue;
	} else if(coordinateIndex == 2) {
		coordinate2 = newCoordValue;
	} else {
		throw std::invalid_argument("Invalid coordinateIndex value: " + coordinateIndex);
	}
}

double Vector3::get(int coordinateIndex) {
	if(coordinateIndex == 0) {
		return coordinate0;
	} else if(coordinateIndex == 1) {
		return coordinate1;
	} else if(coordinateIndex == 2) {
		return coordinate2;
	} else {
		throw std::invalid_argument("Invalid coordinateIndex value: " + coordinateIndex);
	}
}

double Vector3::operator[](int coordinateIndex) {
	return get(coordinateIndex);
}

Vector3 Vector3::add(Vector3& operand) {
	return Vector3(coordinate0 + operand.get(0), coordinate1 + operand.get(1), coordinate2 + operand.get(2));
}

Vector3 Vector3::operator+(Vector3& operand) {
	return add(operand);
}

Vector3 Vector3::subtract(Vector3& operand) {
	return Vector3(coordinate0 - operand.get(0), coordinate1 - operand.get(1), coordinate2 - operand.get(2));	
}

Vector3 Vector3::operator-(Vector3& operand) {
	return subtract(operand);
}

Vector3 Vector3::negate() {
	return scale(-1);
}

Vector3 Vector3::scale(double scaleValue) {
	return Vector3(coordinate0 * scaleValue, coordinate1 * scaleValue, coordinate2 * scaleValue); 
}

/**
 * Check for NULL
 */
double Vector3::dotProduct(Vector3& operand) {
	return (coordinate0 * operand.get(0)) + (coordinate1 * operand.get(1)) + (coordinate2 * operand.get(2));
}

Vector3 Vector3::crossProduct(Vector3& operand) {
	return Vector3((coordinate1 * operand.get(2)) - (coordinate2 * operand.get(1)), 
				   (coordinate2 * operand.get(0)) - (coordinate0 * operand.get(2)), 
				   (coordinate0 * operand.get(1)) - (coordinate1 * operand.get(0)));
}

double Vector3::magnitude() {
	return sqrt((coordinate0 * coordinate0) + (coordinate1 * coordinate1) + (coordinate2 * coordinate2));
}

Vector3 Vector3::normalize() {
	double magnitude = this->magnitude();
	return Vector3(coordinate0/magnitude, coordinate1/magnitude, coordinate2/magnitude);
}

void Vector3::print() {
	std::cout << "Vector3 coordinates: (" << coordinate0 << ", " << coordinate1 << ", " << coordinate2 << ")\n"; 
}

bool Vector3::isXAxisCoordinate() {
	return coordinate0 != 0 && coordinate1 == 0 && coordinate2 == 0;
}

bool Vector3::isYAxisCoordinate() {
	return coordinate0 == 0 && coordinate1 != 0 && coordinate2 == 0;
}

bool Vector3::isZAxisCoordinate() {
	return coordinate0 == 0 && coordinate1 == 0 && coordinate2 != 0;
}

bool Vector3::isAllZeroes() {
	return coordinate0 == 0 && coordinate1 == 0 && coordinate2 == 0;
}

Vector3::~Vector3(void)
{
}
