#include "GLee.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include "cube.h"
#include "Matrix4.h"
#include "ObjectToDraw.h"
#include "Camera.h"
#include "House.h"
#include "Textures.h"

using namespace std;

static Cube cube;
static Cube cubeForObject;
static ObjectToDraw objectToDraw;
static Camera camera;
static Camera cameraForCube; // For Room
static House house;

static Textures textures;

static double MOVEMENT_SIZE = 2.0; // Controls the "small movement" for "x", "X", "y", "Y", "z", "Z"
static double Z_AXIS_ROTATION = 20; // Start with 20 degrees
static double SMALL_SCALE_SIZE = 0.8;
static double BIG_SCALE_SIZE = 1.2;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here

static bool showCube = true;
static bool showObject = false;
static bool showHouse = false;

static ObjectToDraw statue;

static int statueInteger;

// Camera And Light
static Vector3 cameraPosition(0.0f, 0.0f, 1.0f);
// static Vector3 lightPosition(-2.0f, 3.0f, -15.0f); // FarZ + 10
// static Vector3 lightPosition(-4.0f, -4.0f, -7.5f); // Previous
// static Vector3 lightPosition(0.0f, -4.0f, -25.0f);
static Vector3 lightPosition(2.0f, 3.0f,-2.0f); // From tutorial

// Light Matrixes
static Matrix4 lightProjectionMatrix;
static Matrix4 lightViewMatrix;


void Window::show_cube(void) {
	glDisable(GL_LIGHTING);

	showCube = true;
	showObject = false;
	showHouse = false;
}

void Window::show_object(void) {
	glDisable(GL_LIGHTING);

	showCube = false;
	showObject = true;
	showHouse = false;
}

void Window::show_house(void) {
	glDisable(GL_LIGHTING);

	showCube = false;
	showObject = false;
	showHouse = true;
}


//----------------------------------------------------------------------------
// Callback method called when a keyboard key is pressed
void Window::processNormalKeys(unsigned char key, int x, int y) 
{
	if(key == 27) { // Escape key
		glutReshapeWindow(512, 512);        
		glutPositionWindow(0,0);
		// reshapeCallback(512, 512);
	}
}

void Window::drawObject(void)
{
	glLoadMatrixd(cubeForObject.getMatrix().getPointer());
	glBegin(GL_TRIANGLES);
	objectToDraw.draw();
	glEnd();
}

void Window::drawHouse(void)
{
  glLoadMatrixd(camera.getGLMatrix().transpose().getPointer());
  glBegin(GL_TRIANGLES);

  std::vector<Vector3> indices = house.getIndices();
  for(int i = 0; i < indices.size(); i++) {
	  Vector3 indice = indices[i];
	  Vector3 color = house.getColor(indice.get(0));
	  glColor3f(color.get(0), color.get(1), color.get(2));
	  Vector3 firstVertice = house.getVertice(indice.get(0));
	  glVertex3f(firstVertice.get(0), firstVertice.get(1), firstVertice.get(2));
	  Vector3 secondVertice = house.getVertice(indice.get(1));
	  glVertex3f(secondVertice.get(0), secondVertice.get(1), secondVertice.get(2));
	  Vector3 thirdVertice = house.getVertice(indice.get(2));
	  glVertex3f(thirdVertice.get(0), thirdVertice.get(1), thirdVertice.get(2));
  }
  
  glEnd();

}


void drawSmallerCube() {

}

void Window::drawCube(bool blendTexture) 
{
	// Matrix4 transformationMatrix = cameraForCube.getGLMatrix().multiply(cube.getMatrix().transpose());
	// glLoadMatrixd(transformationMatrix.transpose().getPointer());
	float farZ = -25.0;

	if(blendTexture) {
		textures.enableTextureNumber(1);
	}
    // Draw sides of cube in object coordinate system:
    glBegin(GL_QUADS);
    glColor3f(1.0, 0.0, 0.0);

    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);   
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0, -5.0,  5.0);
    glVertex3f(-5.0, -5.0,  5.0);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0,  -3.0, farZ + 20);
    glVertex3f( 1.0,  -3.0, farZ + 20);
    glVertex3f( 1.0, -5.0, farZ + 20);
    glVertex3f(-1.0, -5.0, farZ + 20);
    
    // Draw left side:
	glColor3f(1.0, 1.0, 1.0);
    glNormal3f(-1.0, 0.0, 0.0);
	if(blendTexture) {
		glTexCoord2f(0, 0);
	}
    glVertex3f(-5.0,  5.0,  5.0);
	if(blendTexture) {
		glTexCoord2f(1, 0);
	}
    glVertex3f(-5.0,  5.0, farZ); //
	if(blendTexture) {
		glTexCoord2f(0, 1);
	}
    glVertex3f(-5.0, -5.0, farZ); // 
	if(blendTexture) {
		glTexCoord2f(1, 1);
	}
    glVertex3f(-5.0, -5.0,  5.0);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 0.0, 0.0);
    glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-1.0,  -3.0, farZ + 20);
	glVertex3f(-1.0,  -3.0, farZ + 15);
	glVertex3f(-1.0,  -5.0, farZ + 15);
	glVertex3f(-1.0,  -5.0, farZ + 20);
	glEnd();

	if(blendTexture) {
		textures.enableTextureNumber(0);
	}
	glBegin(GL_QUADS);
    // Draw right side:
	glColor3f(1.0, 0.0, 0.0);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0, farZ); //
    glVertex3f( 5.0, -5.0, farZ); // 
    glVertex3f( 5.0, -5.0,  5.0);

	glColor3f(1.0, 0.0, 0.0);
    glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(1.0,  -3.0, farZ + 20);
	glVertex3f(1.0,  -3.0, farZ + 15);
	glVertex3f(1.0,  -5.0, farZ + 15);
	glVertex3f(1.0,  -5.0, farZ + 20);
    
	glColor3f(1.0, 1.0, 1.0);

    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(-5.0,  5.0, farZ);
    glVertex3f( 5.0,  5.0, farZ);
    glVertex3f( 5.0, -5.0, farZ);
    glVertex3f(-5.0, -5.0, farZ);

	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-1.0,  -3.0, farZ + 15);
    glVertex3f( 1.0,  -3.0, farZ + 15);
    glVertex3f( 1.0, -5.0, farZ + 15);
    glVertex3f(-1.0, -5.0, farZ + 15);
	
  
    // Draw top side:
	glColor3f(1.0, 1.0, 1.0);
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(-5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0,  5.0);
    glVertex3f( 5.0,  5.0, farZ);
    glVertex3f(-5.0,  5.0, farZ);

	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-1.0,  -3.0, farZ + 15);
    glVertex3f( 1.0,  -3.0, farZ + 15);
    glVertex3f( 1.0, -3.0, farZ + 20);
    glVertex3f(-1.0, -3.0, farZ + 20);
	
    
	glColor3f(1.0, 1.0, 1.0);
    // Draw bottom side:
    glNormal3f(0.0, -1.0, 0.0);
	if(blendTexture) {
		glTexCoord2f(0, 0);
	}
    glVertex3f(-5.0, -5.0, farZ);
	if(blendTexture) {
		glTexCoord2f(1, 0);
	}
    glVertex3f( 5.0, -5.0, farZ);
	if(blendTexture) {
		glTexCoord2f(0, 1);
	}
    glVertex3f( 5.0, -5.0,  5.0);
	if(blendTexture) {
		glTexCoord2f(1, 1);
	}
    glVertex3f(-5.0, -5.0,  5.0);

	glEnd();
}


//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback(void)
{
	if(!showHouse) {
		if(showObject) {
			cubeForObject.spin(cubeForObject.getCurrentRotationDegree());
			cubeForObject.getMatrix().applyTransformation(objectToDraw.getTransformationMatrix());
		}

		if(showCube) {
			cube.getMatrix().applyTransformation(cube.getTransformationMatrix());
		}
	}
	displayCallback();  // call display routine to re-draw cube
}

//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Window::reshapeCallback(int w, int h)
{
  double ratio = 0.5; // Added while playing around for final project, you can set it back to 1 if you want to
  // double ratio = 1.0;
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  // glFrustum(-10.0 * ratio, 10.0 * ratio, -10.0 * ratio, 10.0 * ratio, 10, 1000.0); // set perspective projection viewing frustum // Play around with the second to last value 10 to 5 or something like that
  glFrustum(-10.0 * ratio, 10.0 * ratio, -10.0 * ratio, 10.0 * ratio, 10, 1000.0); // set perspective projection viewing frustum // Play around with the second to last value 10 to 5 or something like that
  glTranslatef(0, 0, -20 * ratio);
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
/**
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);
  if(showCube) {
    drawCube();
  } else if(showObject) {
	drawObject();
  } else if(showHouse) {
	drawHouse();
  }
  glFlush();  
  glutSwapBuffers();
*/

void Window::displayCallback(void)
{
	int shadowMapSize = 512;

  	//First pass - from light's point of view
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(lightProjectionMatrix.getPointer());

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(lightViewMatrix.getPointer());

	//Use viewport the same size as the shadow map
	glViewport(0, 0, shadowMapSize, shadowMapSize);

	//Draw back faces into the shadow map
	glCullFace(GL_FRONT);

	//Disable color writes, and use flat shading for speed
	glShadeModel(GL_FLAT);
	glColorMask(0, 0, 0, 0);
	
	//Draw the scene
	drawCube(false);

	//Read the depth buffer into the shadow map texture
	textures.enableTextureNumber(2);
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowMapSize, shadowMapSize);

	//restore states
	glCullFace(GL_BACK);
	glShadeModel(GL_SMOOTH);
	glColorMask(1, 1, 1, 1);

	//2nd pass - Draw from camera's point of view
	glClear(GL_DEPTH_BUFFER_BIT);
	
	// Does not seem right
	double ratio = 0.5;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-10.0 * ratio, 10.0 * ratio, -10.0 * ratio, 10.0 * ratio, 10, 1000.0); 
	glTranslatef(0, 0, -20 * ratio);
 	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // Added by Roger
	glLoadMatrixd(cameraForCube.getGLMatrix().transpose().getPointer());

	glViewport(0, 0, width, height);

	//Use dim light to represent shadowed areas
	float lightPos[4] = {lightPosition[0], lightPosition[1], lightPosition[2], 1.0};
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	
	float whiteColPointTwo[4] = {0.2f, 0.2f, 0.2f, 0.2f};
	glLightfv(GL_LIGHT1, GL_AMBIENT, whiteColPointTwo);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteColPointTwo);
	float blackCol[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	glLightfv(GL_LIGHT1, GL_SPECULAR, blackCol);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
	
	drawCube(false);
	
	//3rd pass
	//Draw with bright light

	float whiteCol[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteCol);
	glLightfv(GL_LIGHT1, GL_SPECULAR, whiteCol);
	glLightfv(GL_LIGHT1, GL_AMBIENT, whiteCol);

	//Calculate texture matrix for projection
	//This matrix takes us from eye space to the light's clip space
	//It is postmultiplied by the inverse of the current view matrix when specifying texgen
	Matrix4 biasMatrix(0.5f, 0.0f, 0.0f, 0.0f,
					   0.0f, 0.5f, 0.0f, 0.0f,
					   0.0f, 0.0f, 0.5f, 0.0f,
					   0.5f, 0.5f, 0.5f, 1.0f);	//bias from [-1, 1] to [0, 1]

	Matrix4 textureMatrix = lightProjectionMatrix.transpose().multiply(lightViewMatrix.transpose());
	textureMatrix = biasMatrix.transpose().multiply(textureMatrix);
	// textureMatrix = textureMatrix.transpose();

	//Set up texture coordinate generation.
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	Vector4 rowValues = textureMatrix.rowValues(0);
	float rv[4] = {rowValues[0], rowValues[1], rowValues[2], rowValues[3]};
	glTexGenfv(GL_S, GL_EYE_PLANE, rv);
	glEnable(GL_TEXTURE_GEN_S);

	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	rowValues = textureMatrix.rowValues(1);
	float rv1[4] =  {rowValues[0], rowValues[1], rowValues[2], rowValues[3]};
	glTexGenfv(GL_T, GL_EYE_PLANE, rv1);
	glEnable(GL_TEXTURE_GEN_T);

	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	rowValues = textureMatrix.rowValues(2);
	float rv2[4] =  {rowValues[0], rowValues[1], rowValues[2], rowValues[3]};
	glTexGenfv(GL_R, GL_EYE_PLANE, rv2);
	glEnable(GL_TEXTURE_GEN_R);

	glTexGeni(GL_Q, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
	rowValues = textureMatrix.rowValues(3);
	float rv3[4] =  {rowValues[0], rowValues[1], rowValues[2], rowValues[3]};
	glTexGenfv(GL_Q, GL_EYE_PLANE, rv3);
	glEnable(GL_TEXTURE_GEN_Q);
	
	//Bind & enable shadow map texture
	textures.enableTextureNumber(2);
	glEnable(GL_TEXTURE_2D);
	
	//Enable shadow comparison
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);

	//Shadow comparison should be true (ie not in shadow) if r<=texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

	//Shadow comparison should generate an INTENSITY result
	glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

	//Set alpha test to discard false comparisons
	glAlphaFunc(GL_GEQUAL, 0.99f);
	glEnable(GL_ALPHA_TEST);
	
	drawCube(false);

	//Disable textures and texgen
	glDisable(GL_TEXTURE_2D);

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_GEN_Q);

	//Restore other states
	glDisable(GL_LIGHTING);
	glDisable(GL_ALPHA_TEST);
	
	glFinish();
	glutSwapBuffers();
	glutPostRedisplay();
}

Cube::Cube()
{
  angle = 0.0;
  rotationDegree = 0.01;
  transformationMatrix.identity();
  r = 0.0;
  g = 1.0;
  b = 0.0;
  spinY = true;
}

Matrix4& Cube::getMatrix()
{
  return matrix;
}

Matrix4& Cube::getTransformationMatrix(void)
{
	return transformationMatrix;
}

void Cube::spin(double deg)
{
  angle += deg;
  if (angle > 360.0 || angle < -360.0) angle = 0.0;
  if(showCube) {
	if(isSpinY()) {
		matrix.rotateY(angle);
	} else {
		matrix.rotateZ(angle);
	}
  } else if(showObject) {
	if(isSpinY()) {
		cubeForObject.getMatrix().rotateY(angle);
	} else {
		cubeForObject.getMatrix().rotateZ(angle);
	}
  }
}

bool Cube::isSpinY()
{
	return spinY;
}

void Cube::setSpinY(bool newValue) 
{
	spinY = newValue;
}

double Cube::getR() 
{
	return r;
}

double Cube::getG()
{ 
	return g;
}
	
double Cube::getB()
{
	return b;
}
	
void Cube::setRGB(double rVal, double gVal, double bVal) {
	r = rVal;
	g = gVal;
	b = bVal;
}

double Cube::getCurrentRotationDegree(void) {
	return rotationDegree;
}

void Cube::flipSpinDirection(void) 
{
	angle = 0.0;
	rotationDegree = -rotationDegree;
}

void Cube::spinCounterclockwise(void)
{
	rotationDegree = abs(rotationDegree);
}

void Cube::spinClockwise(void)
{
	rotationDegree = -abs(rotationDegree);
}

void initializeLightMatrices(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 2.0f, 8.0f);
	// gluPerspective(45.0f, 1.0f, 0.0f, 7.0f);
	// glTranslatef(-10.0, 0, 0);
	// gluPerspective(10.0f, 5.1f, 5.0f, 8.0f);
	GLfloat proj[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, proj);
	lightProjectionMatrix = Matrix4(proj[0], proj[1], proj[2], proj[3],
								    proj[4], proj[5], proj[6], proj[7],
								    proj[8], proj[9], proj[10], proj[11],
									proj[12], proj[13], proj[14], proj[15]);
	
	glLoadIdentity();
	/*gluLookAt( lightPosition[0], lightPosition[1], lightPosition[2],
			   1.0f, -4.0f, -7.5f, // From -17.5
	           0.0f, 1.0f, 0.0f);
	*/
	gluLookAt(	lightPosition[0], lightPosition[1], lightPosition[2],
				0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f);
	GLfloat view[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, view);
	lightViewMatrix = Matrix4(view[0], view[1], view[2], view[3],
							  view[4], view[5], view[6], view[7],
							  view[8], view[9], view[10], view[11],
							  view[12], view[13], view[14], view[15]);

	glPopMatrix();

	/*
	Camera lightCamera = Camera(lightPosition, Vector3(1, -3, -17.5), Vector3(0, 1, 0));
	lightViewMatrix = lightCamera.getGLMatrix();
	*/
	

	// Restore 
	glMatrixMode(GL_PROJECTION); 
}

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {16.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
  
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("OpenGL Cube for CSE167");    	      // open window and set window title

  // Depth states
  glClearDepth(1.0f);						  // Shadow mapping tutorial
  glDepthFunc(GL_LEQUAL);					  // Shadow mapping tutorial

  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glDisable(GL_CULL_FACE);     // disable backface culling to render both sides of polygons
  // glEnable(GL_CULL_FACE);
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Added from shadow mapping tutorial
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Added from shadow mapping tutorial
  glMatrixMode(GL_PROJECTION); 

  // Texture
  glEnable(GL_TEXTURE_2D);   // enable texture mapping

  // Normalize
  glEnable(GL_NORMALIZE);
  
  // Generate material properties:
  // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  // glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

  glEnable(GL_COLOR_MATERIAL);
  
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);

  // Some more initialization
  if(!GLEE_ARB_depth_texture || !GLEE_ARB_shadow) {
	  std::cout << "ARB_depth_texture and ARB_shadow extensions required!!!\n";
  }

  initializeLightMatrices();
  
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);
  glutKeyboardFunc(Window::processNormalKeys); 

  // Full Screen
  glutFullScreen();  
    
  // Initialize cube matrix:
  cube.getMatrix().identity();
  // Initialize cube for object
  cubeForObject.getMatrix().identity();

  // Camera For the Room
  cameraForCube = Camera(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

  // Load Textures
  textures.load();

  // Object to draw statue
  // statue = ObjectToDraw("statue.obj");
  // statueInteger = loadObject("statue.obj");

  glutMainLoop();

  return 0;
}

