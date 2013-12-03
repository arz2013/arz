#include "GLee.h"
#include <stdlib.h>
#include <iostream>

#include "Textures.h"

static const int shadowMapSize = 512;

Textures::Textures(void)
{
}

unsigned char* Textures::loadPPM(const char* filename, int& width, int& height) {
	const int BUFSIZE = 128;
	FILE* fp;
	unsigned int read;
	unsigned char* rawData;
	char buf[3][BUFSIZE];
	char* retval_fgets;
	size_t retval_sscanf;

	if ( (fp=fopen(filename, "rb")) == NULL)
	{
		std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
		width = 0;
		height = 0;
		return 0;
	}

	// Read magic number:
	retval_fgets = fgets(buf[0], BUFSIZE, fp);

	// Read width and height:
	do
	{
		retval_fgets=fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');
	retval_sscanf=sscanf(buf[0], "%s %s", buf[1], buf[2]);
	width = atoi(buf[1]);
	height = atoi(buf[2]);

	// Read maxval:
	do
	{
		retval_fgets=fgets(buf[0], BUFSIZE, fp);
	} while (buf[0][0] == '#');

	// Read image data:
	rawData = new unsigned char[width * height * 3];
	read = fread(rawData, width * height * 3, 1, fp);
	fclose(fp);
	if (read != 1)
	{
		std::cerr << "error parsing ppm file, incomplete data" << std::endl;
		delete[] rawData;
		width = 0;
		height = 0;

		return 0;
	}

	return rawData;
}

void Textures::enableTextureNumber(int textureNumber) { // Texture Number should start from zero
	glBindTexture(GL_TEXTURE_2D, texture[textureNumber]);
}

void Textures::load() {  
  char* textureFileNames[2] = {"woodenfloor.PPM", "walltexture.PPM"};

  // Create IDs for normal texture
  glGenTextures(3, &texture[0]);  

  for(int i = 0; i < 2; i++) {
	  int twidth, theight;   // texture width/height [pixels]
	  unsigned char* tdata;  // texture pixel data

	  tdata = loadPPM(textureFileNames[i], twidth, theight);
	  if (tdata==NULL) return;
	  // Set this texture to be the one we are working with
	  glBindTexture(GL_TEXTURE_2D, texture[i]);
	  // Make sure no bytes are padded:
	  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	  // Select GL_MODULATE to mix texture with quad color for shading:
	  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	  // Generate the texture
	  glTexImage2D(GL_TEXTURE_2D, 0, 3, twidth, theight, 0, GL_RGB, GL_UNSIGNED_BYTE, tdata);
	  // Set bi-linear filtering for both minification and magnification
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	  delete(tdata);
  }

  // Handle Shadow Map Texture separately
  glBindTexture(GL_TEXTURE_2D, texture[2]);
  glTexImage2D( GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapSize, shadowMapSize, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL); // Generate Shadow Map Texture
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}




Textures::~Textures(void)
{
}
