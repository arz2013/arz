#ifndef _CUBE_H_
#define _CUBE_H_

#include "Matrix4.h"
#include "Vector3.h"

class Cube
{
  private:
	double rotationDegree;
	Matrix4 transformationMatrix;
	double r;
	double g;
	double b;
	bool spinY;

  protected:
    Matrix4 matrix;                 // model matrix
    double angle;                   // rotation angle [degrees]

  public:
    Cube();   // Constructor
    Matrix4& getMatrix();
	Matrix4& getTransformationMatrix(void);
    void spin(double);      // spin cube [degrees]
	double getCurrentRotationDegree(void);
	void flipSpinDirection(void);
	double getR();
	double getG();
	double getB();
	void setRGB(double r, double g, double b);
	bool isSpinY();
	void setSpinY(bool newValue);
	void spinCounterclockwise(void);
	void spinClockwise(void);
};

class Window	  // output window related routines
{
  private:
	static void drawCube(bool blendTexture);
	static void drawObject(void);
	static void drawHouse(void);
	static void show_cube(void);
	static void show_object(void);
	static void show_house(void);
  public:
    static int width, height; 	            // window size
	static void processNormalKeys(unsigned char key, int x, int y);
	static void processSpecialKeys(int key, int x, int y);
	static void processSpecialKeys();
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
};

#endif

