#include <GL/glut.h>

class Textures
{
private:
	GLuint texture[3];
public:
	Textures(void);
	unsigned char* loadPPM(const char* filename, int& width, int& height);
	void load();
	void enableTextureNumber(int textureNumber);
	~Textures(void);
};

