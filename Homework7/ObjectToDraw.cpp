#include "ObjectToDraw.h"
#include "objReader.h"
#include <iostream>
#include <GL/glut.h>
#include <vector>
#include "Vector3.h"
#include "Colors.h"
#include <algorithm>

static double UNIVERSAL_SCALING_FACTOR = 25.0;

ObjectToDraw::ObjectToDraw(char* fileName) 
{
	nVerts = 0;
	nIndices = 0;
	ObjReader::readObj(fileName, nVerts, &vertices, &normals, &texcoords, nIndices, &indices);
	translationMatrix.identity();
	transformationMatrix.identity();
}
	

void ObjectToDraw::draw(void) 
{
	for(int i = 0; i < nIndices; i++) {
		Vector3 nextColor = colors.next();
		glColor3f(nextColor.get(0), nextColor.get(1), nextColor.get(1));
		glVertex3f(vertices[3 * indices[i]], vertices[3 * indices[i]+1], vertices[3 * indices[i]+2]);
	}
}

Matrix4& ObjectToDraw::getTranslationMatrix() {
	return translationMatrix;
}

Matrix4& ObjectToDraw::getTransformationMatrix() {
	return transformationMatrix;
}

void ObjectToDraw::performFullScreenCalculation(void) {
	double maxXValue = vertices[0];
	double minXValue = vertices[0];
	double maxYValue = vertices[1];
	double minYValue = vertices[1];
	double maxZValue = vertices[2];
	double minZValue = vertices[2];

	for(int i = 0; i < nIndices; i++) {
		double x = vertices[3 * indices[i]];
		if(x > maxXValue) {
			maxXValue = x;
		} else if(x < minXValue) {
			minXValue = x;
		}
		double y = vertices[3 * indices[i] + 1];
		if(y > maxYValue) {
			maxYValue = y;
		} else if(y < minYValue) {
			minYValue = y;
		}
		double z = vertices[3 * indices[i] + 2];
		if(z > maxZValue) {
			maxZValue = z;
		} else if(z < minZValue) {
			minZValue = z;
		}
	}

	std::cout << "Max X Value: " << maxXValue << "\n";
	std::cout << "Min X Value: " << minXValue << "\n";
	std::cout << "Max Y Value: " << maxYValue << "\n";
	std::cout << "Min Y Value: " << minYValue << "\n";
	std::cout << "Max Z Value: " << maxZValue << "\n";
	std::cout << "Min Z Value: " << minZValue << "\n";

	double midPointX = (maxXValue + minXValue)/2.0;
	double midPointY = (maxYValue + minYValue)/2.0;
	double midPointZ = (maxZValue + minZValue)/2.0;

	translationMatrix = Matrix4(1.0, 0.0, 0.0, -midPointX, 
								0.0, 1.0, 0.0, -midPointY, 
								0.0, 0.0, 1.0, -midPointZ, 
								0, 0, 0 , 1);
	std::cout << "\nTranslation Matrix for the full-screen/centering: " << "\n";
	translationMatrix.print();

	double distanceFromCenterX = maxXValue - minXValue;
	double distanceFromCenterY = maxYValue - minYValue;
	double distanceFromCenterZ = maxZValue - minZValue;

	double maxOfDistanceFromCenter = std::max(distanceFromCenterX, distanceFromCenterY);
	maxOfDistanceFromCenter = std::max(maxOfDistanceFromCenter, distanceFromCenterZ);
	std::cout << "\nMax of Distance From Center: " << maxOfDistanceFromCenter << "\n";

	normalizationScalingMatrix = translationMatrix.nonUniformScalingMatrix(1/maxOfDistanceFromCenter, 1/maxOfDistanceFromCenter, 1/maxOfDistanceFromCenter);

	std::cout << "\nScaling Matrix: " << "\n";
	normalizationScalingMatrix.print();

	scalingMatrix = translationMatrix.nonUniformScalingMatrix(UNIVERSAL_SCALING_FACTOR, UNIVERSAL_SCALING_FACTOR, UNIVERSAL_SCALING_FACTOR); 

	transformationMatrix.identity();
	transformationMatrix = getTranslationMatrix().transpose().multiply(normalizationScalingMatrix.multiply(scalingMatrix).multiply(transformationMatrix));

}

ObjectToDraw::ObjectToDraw(void)
{
}


ObjectToDraw::~ObjectToDraw(void)
{
}
