#include "Colors.h"
#include "Vector3.h"
#include <vector>

Colors::Colors(void) {
	colorIndex = 0;
	colorsVector.resize(3);
	colorsVector[0] = Vector3(1, 0, 0);
	colorsVector[1] = Vector3(0, 1, 0); 
	colorsVector[2] = Vector3(0, 0, 1);
}

Colors::~Colors(void) {
}

Vector3& Colors::next() {
	if(colorIndex == 3) {
		colorIndex = 0;
	}
	Vector3 next = colorsVector[colorIndex];
	colorIndex++;

	return next;
}
