#include "House.h"
#include <iostream>
#include <array>

House::House(void)
{
	int noOfVertices = 42;

	// These are the x,y,z coordinates of the vertices of the triangles
	float verticesInit[] = {  
			-4,-4,4, 4,-4,4, 4,4,4, -4,4,4,     // front face
			-4,-4,-4, -4,-4,4, -4,4,4, -4,4,-4, // left face
			4,-4,-4,-4,-4,-4, -4,4,-4, 4,4,-4,  // back face
			4,-4,4, 4,-4,-4, 4,4,-4, 4,4,4,     // right face
			4,4,4, 4,4,-4, -4,4,-4, -4,4,4,     // top face
			-4,-4,4, -4,-4,-4, 4,-4,-4, 4,-4,4, // bottom face

			-20,-4,20, 20,-4,20, 20,-4,-20, -20,-4,-20, // grass
			-4,4,4, 4,4,4, 0,8,4,                       // front attic wall
			4,4,4, 4,4,-4, 0,8,-4, 0,8,4,               // left slope
			-4,4,4, 0,8,4, 0,8,-4, -4,4,-4,             // right slope
			4,4,-4, -4,4,-4, 0,8,-4};                   // rear attic wall
  
   vertices.resize(noOfVertices);
   int noOfCreatedVertices = 0;
   for(int i = 0; i < noOfVertices * 3; i = i + 3) {
	   vertices[noOfCreatedVertices] = Vector3(verticesInit[i], verticesInit[i + 1], verticesInit[i + 2]);
	   noOfCreatedVertices++;
   }

  // These are the RGB colors corresponding to the vertices, in the same order
  float colorsInit[] = { 
			1,0,0, 1,0,0, 1,0,0, 1,0,0,  // front is red
			0,1,0, 0,1,0, 0,1,0, 0,1,0,  // left is green
			1,0,0, 1,0,0, 1,0,0, 1,0,0,  // back is red
			0,1,0, 0,1,0, 0,1,0, 0,1,0,  // right is green
			0,0,1, 0,0,1, 0,0,1, 0,0,1,  // top is blue
			0,0,1, 0,0,1, 0,0,1, 0,0,1,  // bottom is blue
  
			0,0.5,0, 0,0.5,0, 0,0.5,0, 0,0.5,0, // grass is dark green
			0,0,1, 0,0,1, 0,0,1,                // front attic wall is blue
			1,0,0, 1,0,0, 1,0,0, 1,0,0,         // left slope is green
			0,1,0, 0,1,0, 0,1,0, 0,1,0,         // right slope is red
			0,0,1, 0,0,1, 0,0,1,};              // rear attic wall is red

  colors.resize(noOfVertices);
  noOfCreatedVertices = 0;
  for(int i = 0; i < noOfVertices * 3; i = i + 3) {
	   colors[noOfCreatedVertices] = Vector3(colorsInit[i], colorsInit[i + 1], colorsInit[i + 2]);
	   noOfCreatedVertices++;
  }

  // The index data stores the connectivity of the triangles; 
  // index 0 refers to the first triangle defined above
  float indicesInit[] = {
			0,2,3,    0,1,2,      // front face
			4,6,7,    4,5,6,      // left face
			8,10,11,  8,9,10,     // back face
			12,14,15, 12,13,14,   // right face
			16,18,19, 16,17,18,   // top face
			20,22,23, 20,21,22,   // bottom face
				   
			24,26,27, 24,25,26,   // grass
			28,29,30,             // front attic wall
			31,33,34, 31,32,33,   // left slope
			35,37,38, 35,36,37,   // right slope
			39,40,41};            // rear attic wall
  
  indices.resize(20);
  noOfCreatedVertices = 0;
  for(int i = 0; i < 60; i = i + 3) {
	  indices[noOfCreatedVertices] = Vector3(indicesInit[i], indicesInit[i + 1], indicesInit[i + 2]);
	  noOfCreatedVertices++;
  }
}

std::vector<Vector3> House::getIndices() {
	return indices;
}

Vector3& House::getVertice(int index) {
	return vertices[index];
}

Vector3& House::getColor(int index) {
	return colors[index];
}


House::~House(void)
{
}
