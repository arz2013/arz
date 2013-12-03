#pragma once
class Vector3
{
public:
	Vector3(void);
	Vector3(double coord0, double coord1, double coord2);
	~Vector3(void);
	void set(int coordinateIndex, double newCoordValue);
	double get(int coordinateIndex);
	double operator[](int coordinateIndex);
	Vector3 add(Vector3& operand);
	Vector3 operator+(Vector3& operand);
	Vector3 subtract(Vector3& operand);
	Vector3 operator-(Vector3& operand);
	Vector3 negate();
	/**
	 * Returns a new Vector containing the scaled values
	 */
	Vector3 scale(double scaleValue);
	double dotProduct(Vector3& operand);
	/**
	 * Returns a new Vector containing the cross product of "this" and "operand"
	 */
	Vector3 crossProduct(Vector3& operand);
	double magnitude(void);
	Vector3 normalize(void);
	void print(void);

	/**
	 */
	bool isXAxisCoordinate();
	bool isYAxisCoordinate();
	bool isZAxisCoordinate();
	bool isAllZeroes();
private:
	double coordinate0;
	double coordinate1;
	double coordinate2;
};



