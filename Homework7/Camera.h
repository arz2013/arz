#pragma once

#include "Matrix4.h"
#include "Vector3.h"

class Camera
{
private:
	Vector3 e;
	Vector3 d;
	Vector3 up;
	Matrix4 cameraMatrix;
	void computeCameraMatrix(void);
public:
	Camera(void);
	Camera(Vector3& e, Vector3& d, Vector3& up);
	Matrix4& getGLMatrix(void);
	~Camera(void);
};

