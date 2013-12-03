#include "Camera.h"
#include <iostream>

/**
 * Need to come back and think of default values for the camera
 */
Camera::Camera(void)
{
	cameraMatrix.identity();
	// computeCameraMatrix();
}

Camera::Camera(Vector3& e, Vector3& d, Vector3& up) {
	this->e = e;
	this->d = d;
	this->up = up;
	computeCameraMatrix();
}

void Camera::computeCameraMatrix(void) {
	Vector3 e_minus_d = e - d;
	Vector3 zCamera = e_minus_d.scale(1/e_minus_d.magnitude());
	Vector3 zCamera_cross_up = up.crossProduct(zCamera);
	Vector3 xCamera = zCamera_cross_up.scale(1/zCamera_cross_up.magnitude());
	//xCamera.print();
	Vector3 yCamera = zCamera.crossProduct(xCamera);
	//yCamera.print();
	cameraMatrix = Matrix4(xCamera.get(0), xCamera.get(1), xCamera.get(2), 0,
						   yCamera.get(0), yCamera.get(1), yCamera.get(2), 0,
						   zCamera.get(0), zCamera.get(1), zCamera.get(2), 0,
						   0.0, 0.0, 0.0, 1.0).multiply(
								Matrix4(1, 0, 0, -e.get(0), 0, 1, 0, -e.get(1), 0, 0, 1, -e.get(2), 0, 0, 0, 1)
						   );
}


Matrix4& Camera::getGLMatrix(void) {
	return cameraMatrix;
}


Camera::~Camera(void)
{
}
