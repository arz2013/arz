#include <math.h>
#include <iostream>

#include "Matrix4.h"
#include "Vector3.h"

Matrix4::Matrix4()
{
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = 0;
    }
  }
} 

Matrix4::Matrix4(
  double m00, double m01, double m02, double m03,
  double m10, double m11, double m12, double m13,
  double m20, double m21, double m22, double m23,
  double m30, double m31, double m32, double m33 )
{
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[0][3] = m03;
  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[1][3] = m13;
  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
  m[2][3] = m23;
  m[3][0] = m30;
  m[3][1] = m31;
  m[3][2] = m32;
  m[3][3] = m33;
}

double* Matrix4::getPointer()
{
  return &m[0][0];
}

void Matrix4::identity()
{
  double ident[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
  for (int i=0; i<4; ++i)
  {
    for (int j=0; j<4; ++j)
    {
      m[i][j] = ident[i][j];
    }
  }
}

// angle in radians
void Matrix4::rotateY(double angle)
{
	m[0][0] = cos(angle);
	m[0][1] = 0;
	m[0][2] = sin(angle);
	m[0][3] = 0;
	m[1][0] = 0;
	m[1][1] = 1;
	m[1][2] = 0;
	m[1][3] = 0;
	m[2][0] = -sin(angle);
	m[2][1] = 0;
	m[2][2] = cos(angle);
	m[2][3] = 0;
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = 0;
	
	m[3][3] = 1;
}

void Matrix4::rotateZ(double angle) {
	Matrix4 rotationMatrix = this->rotateOnZAxis(angle);
	m[0][0] = rotationMatrix.get(0, 0);
	m[0][1] = rotationMatrix.get(0, 1);
	m[0][2] = rotationMatrix.get(0, 2);
	m[0][3] = rotationMatrix.get(0, 3);
	m[1][0] = rotationMatrix.get(1, 0);
	m[1][1] = rotationMatrix.get(1, 1);
	m[1][2] = rotationMatrix.get(1, 2);
	m[1][3] = rotationMatrix.get(1, 3);
	m[2][0] = rotationMatrix.get(2, 0);
	m[2][1] = rotationMatrix.get(2, 1);
	m[2][2] = rotationMatrix.get(2, 2);
	m[2][3] = rotationMatrix.get(2, 3);
	m[3][0] = rotationMatrix.get(3, 0);
	m[3][1] = rotationMatrix.get(3, 1);
	m[3][2] = rotationMatrix.get(3, 2);	
	m[3][3] = rotationMatrix.get(3, 3);
}

double Matrix4::get(int x, int y) {
	return m[x][y];
}

Matrix4 Matrix4::multiply(Matrix4& operand) {
	double temp[4][4];
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			Vector4 rowValues = this->rowValues(i);
			Vector4 columnValues = operand.columnValues(j);
			temp[i][j] = rowValues.dotProduct(columnValues);
		}
	}

	return Matrix4(temp[0][0], temp[0][1], temp[0][2], temp[0][3], 
		           temp[1][0], temp[1][1], temp[1][2], temp[1][3], 
				   temp[2][0], temp[2][1], temp[2][2], temp[2][3], 
				   temp[3][0], temp[3][1], temp[3][2], temp[3][3]); 
}

Vector4 Matrix4::multiply(Vector4& operand) {
	Vector4 rowValues0 = rowValues(0);
	Vector4 rowValues1 = rowValues(1);
	Vector4 rowValues2 = rowValues(2);
	Vector4 rowValues3 = rowValues(3);

	double coordinate0 = rowValues0.dotProduct(operand);
	double coordinate1 = rowValues1.dotProduct(operand);
	double coordinate2 = rowValues2.dotProduct(operand);
	double coordinate3 = rowValues3.dotProduct(operand);

	return Vector4(coordinate0, coordinate1, coordinate2, coordinate3);
}

Matrix4 Matrix4::add(Matrix4& operand) {
	return Matrix4(m[0][0] + operand.get(0, 0), m[0][1] + operand.get(0, 1), m[0][2] + operand.get(0, 2), m[0][3] + operand.get(0, 3), 
		           m[1][0] + operand.get(1, 0), m[1][1] + operand.get(1, 1), m[1][2] + operand.get(1, 2), m[1][3] + operand.get(1, 3), 
				   m[2][0] + operand.get(2, 0), m[2][1] + operand.get(2, 1), m[2][2] + operand.get(2, 2), m[2][3] + operand.get(2, 3), 
				   m[3][0] + operand.get(3, 0), m[3][1] + operand.get(3, 1), m[3][2] + operand.get(3, 2), m[3][3] + operand.get(3, 3));
}

Vector4 Matrix4::rowValues(int rowIndex) {
	return Vector4(get(rowIndex,0), get(rowIndex,1), get(rowIndex,2), get(rowIndex,3));
}

Vector4 Matrix4::columnValues(int columnIndex) {
	return Vector4(get(0, columnIndex), get(1, columnIndex), get(2, columnIndex), get(3, columnIndex));
}

Matrix4 Matrix4::scale(double scale) {
	return Matrix4(scale * m[0][0], scale * m[0][1], scale * m[0][2], scale * m[0][3], 
		           scale * m[1][0], scale * m[1][1], scale * m[1][2], scale * m[1][3], 
				   scale * m[2][0], scale * m[2][1], scale * m[2][2], scale * m[2][3], 
				   scale * m[3][0], scale * m[3][1], scale * m[3][2], scale * m[3][3]);
}

void Matrix4::scale(Matrix4& scaleMatrix) {
	rotate(scaleMatrix);
}


Matrix4 Matrix4::rotateOnXAxis(double degree)
{
	return rotateOnAxis(Vector3(1, 0, 0), degree);
}
	
Matrix4 Matrix4::rotateOnYAxis(double degree)
{
	return rotateOnAxis(Vector3(0, 1, 0), degree);
}

Matrix4 Matrix4::rotateOnZAxis(double degree)
{
	return rotateOnAxis(Vector3(0, 0, 1), degree);
}

/**
 * 
 */
Matrix4 Matrix4::rotateOnAxis(Vector3& vector, double degree) 
{
	// Create an identity matrix and scale it by cos(degree)
	Matrix4 identity;
	identity.identity();
	Matrix4 scaledIdentityMatrix = identity.scale(cos(degree));
	// Compute the scaled cross product of the vector
	Matrix4 crossProduct = this->crossProduct(vector);
	Matrix4 scaledCrossProduct = crossProduct.scale(sin(degree));
	// Compute the scaled tensor product of the vector
	Matrix4 tensorProduct = this->tensorProduct(vector);
	Matrix4 scaledTensorProduct = tensorProduct.scale(1 - cos(degree));
	// Need to zero out the rest of the matrix?
	Matrix4 result = scaledIdentityMatrix.add(scaledCrossProduct).add(scaledTensorProduct);	
	// Reset the very final cell to 1, since it gets scaled earlier
	result.m[3][3] = 1;

	return result;
}

Matrix4 Matrix4::crossProduct(Vector3 vector) 
{
	return Matrix4(0, -vector.get(2), vector.get(1), 0, 
		           vector.get(2), 0, -vector.get(0), 0, 
		           -vector.get(1), vector.get(0), 0, 0, 
				   0, 0, 0, 0);	
}

Matrix4 Matrix4::tensorProduct(Vector3 vector) 
{
	return Matrix4(vector.get(0) * vector.get(0), vector.get(1) * vector.get(0), vector.get(0) * vector.get(2), 0, 
		           vector.get(0) * vector.get(1), vector.get(1) * vector.get(1), vector.get(1) * vector.get(2), 0, 
		           vector.get(0) * vector.get(2), vector.get(1) * vector.get(2), vector.get(2) * vector.get(2), 0, 
				   0, 0, 0, 0);	
}

Matrix4 Matrix4::nonUniformScalingMatrix(double scalingFactorX, double scalingFactorY, double scalingFactorZ) 
{
	Matrix4 result;
	result.identity();
	result.m[0][0] = scalingFactorX;
	result.m[1][1] = scalingFactorY;
	result.m[2][2] = scalingFactorZ;

	return result;
}

/**
 * Gets applied to the Transformation Matrix
 */
void Matrix4::translate(Matrix4& translation) 
{
	Matrix4 translated = this->multiply(translation);
	m[0][0] = translated.get(0,0);
	m[0][1] = translated.get(0,1);
	m[0][2] = translated.get(0,2);
	m[0][3] = translated.get(0,3);
	m[1][0] = translated.get(1,0);
	m[1][1] = translated.get(1,1);
	m[1][2] = translated.get(1,2);
	m[1][3] = translated.get(1,3);
	m[2][0] = translated.get(2,0);
	m[2][1] = translated.get(2,1);
	m[2][2] = translated.get(2,2);
	m[2][3] = translated.get(2,3);
	m[3][0] = translated.get(3,0);
    m[3][1] = translated.get(3,1);
	m[3][2] = translated.get(3,2);
	m[3][3] = translated.get(3,3);

	std::cout << "Matrix4::translate\n";
	print();
}

Matrix4 Matrix4::translationMatrix(Vector3& translation) {
	return Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, translation.get(0), translation.get(1), translation.get(2), 1);
}

void Matrix4::rotate(Matrix4& rotation) 
{
	Matrix4 rotated = rotation.multiply(*this);
	m[0][0] = rotated.get(0,0);
	m[0][1] = rotated.get(0,1);
	m[0][2] = rotated.get(0,2);
	m[0][3] = rotated.get(0,3);
	m[1][0] = rotated.get(1,0);
	m[1][1] = rotated.get(1,1);
	m[1][2] = rotated.get(1,2);
	m[1][3] = rotated.get(1,3);
	m[2][0] = rotated.get(2,0);
	m[2][1] = rotated.get(2,1);
	m[2][2] = rotated.get(2,2);
	m[2][3] = rotated.get(2,3);
	m[3][0] = rotated.get(3,0);
    m[3][1] = rotated.get(3,1);
	m[3][2] = rotated.get(3,2);
	m[3][3] = rotated.get(3,3);
}

/**
 * This only applies to the Cube Matrix (not the Transformation matrix)
 */
void Matrix4::applyTransformation(Matrix4& transformationMatrix) {
	Matrix4 cubeMatrix = this->multiply(transformationMatrix);
	m[0][0] = cubeMatrix.get(0,0);
	m[0][1] = cubeMatrix.get(0,1);
	m[0][2] = cubeMatrix.get(0,2);
	m[0][3] = cubeMatrix.get(0,3);
	m[1][0] = cubeMatrix.get(1,0);
	m[1][1] = cubeMatrix.get(1,1);
	m[1][2] = cubeMatrix.get(1,2);
	m[1][3] = cubeMatrix.get(1,3);
	m[2][0] = cubeMatrix.get(2,0);
	m[2][1] = cubeMatrix.get(2,1);
	m[2][2] = cubeMatrix.get(2,2);
	m[2][3] = cubeMatrix.get(2,3);
	m[3][0] = cubeMatrix.get(3,0);
    m[3][1] = cubeMatrix.get(3,1);
	m[3][2] = cubeMatrix.get(3,2);
	m[3][3] = cubeMatrix.get(3,3);
}


void Matrix4::print(void) {
	std::cout << "Matrix4 contents: \n";
	std::cout << "[" << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ", " << m[0][3] << "\n";
	std::cout << " " << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ", " << m[1][3] << "\n";
	std::cout << " " << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ", " << m[2][3] << "\n";
	std::cout << " " << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3] << "]\n";
}

void Matrix4::printPosition()
{ 
	std::cout << "Matrix4 position: [" << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << "]\n";
}


Matrix4 Matrix4::transpose() {
	return Matrix4(m[0][0], m[1][0], m[2][0], m[3][0],
		           m[0][1], m[1][1], m[2][1], m[3][1],
				   m[0][2], m[1][2], m[2][2], m[3][2],
				   m[0][3], m[1][3], m[2][3], m[3][3]);
}