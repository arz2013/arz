#pragma once
#include <GL/glut.h>
#include "cube.h"

class WaveObjLoader
{
public:
	WaveObjLoader(void);
	int loadObject(const char* filename, Cube cubeForObject);
	~WaveObjLoader(void);
};

