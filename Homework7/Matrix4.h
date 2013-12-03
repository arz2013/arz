#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "Vector3.h"
#include "Vector4.h"


class Matrix4
{
  private:
	Vector4 columnValues(int columnIndex);
	Matrix4 tensorProduct(Vector3 vector);
	Matrix4 crossProduct(Vector3 vector);

  protected:
    double m[4][4];   // matrix elements
    
  public:
    Matrix4();        // constructor
    Matrix4(double, double, double, double, double, double, double, double, double, double, double, double, double, double, double, double);
    double* getPointer();  // return pointer to matrix elements
    void identity();  // create identity matrix
    void rotateY(double); // rotation about y axis
	void rotateZ(double); // rotation about z axis
	// Some more common operations
	Matrix4 add(Matrix4& operand);
	// Addition for assignment
	double get(int x, int y);
	Matrix4 multiply(Matrix4& operand);
	Vector4 multiply(Vector4& operand);
	Matrix4 rotateOnXAxis(double degree);
	Matrix4 rotateOnYAxis(double degree);
	Matrix4 rotateOnZAxis(double degree);
	Matrix4 rotateOnAxis(Vector3& vector, double degree);
	Matrix4 nonUniformScalingMatrix(double scalingFactorX, double scalingFactorY, double scalingFactorZ);
	Vector4 rowValues(int rowIndex);
	// Scale using a scalar
	Matrix4 scale(double scale);
	// Scale using a matrix
	void scale(Matrix4& scaleMatrix);
	// Perform translation
	void translate(Matrix4& translation);
	// Generate a translation matrix
	Matrix4 translationMatrix(Vector3& translation);
	void rotate(Matrix4& rotation);
	void print(void);
	void printPosition();
	Matrix4 transpose();
	void applyTransformation(Matrix4& transformationMatrix);
};

#endif