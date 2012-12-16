#include <cstdio>
#include <cmath>
#include "Ray.h"
#include "Camera.h"
#include "Window.h"
#include "Common.h"
#include "Sphere.h"
#include "Scene.h"
#include "Plane.h"
#include <GL/glut.h>

unsigned char colorBuffer[500][500][3];

void draw()
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawPixels(500, 500, GL_RGB, GL_UNSIGNED_BYTE, colorBuffer);
	glutSwapBuffers();
}

void initialiseGLUT(int argc, char **argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(Window::mWindowWidth, Window::mWindowHeight);
	glutCreateWindow("Ray tracer");	
	glutDisplayFunc(draw);	
	glutMainLoop();	
}

int main(int argc, char* argv[])
{	
	Camera *mainCamera = new Camera(POS, LOOK, UP, 1.0, 90.0);
	Scene* scene = new Scene();
			
	scene->addObject( new Plane( vec3(0, 1, 0), vec3(0, -1, 10), vec4(0.0, 0.2, 0.2, 0.0) ) );
	scene->addObject( new Sphere( vec3(0, 3.4, 10), 3.5, vec4(1.0, 0.0, 0.0, 0.0) ) );
	
	for (int i = 0; i < Window::mWindowHeight; i++) {
		for (int j = 0; j < Window::mWindowWidth; j++) {			
			Ray *currRay = Ray::getRay(vec2(j, i), mainCamera);
			
			std::vector<Hit>& hitList = scene->getHitList(currRay);
			vec4 colAtPix = scene->processHitListAndGetColor(); // maybe we could give in a light here!
			
			colorBuffer[i][j][0] = (colAtPix.r / 1.0) * 255;
			colorBuffer[i][j][1] = (colAtPix.g / 1.0) * 255;
			colorBuffer[i][j][2] = (colAtPix.b / 1.0) * 255;
			
			scene->clearHitList();
			

#ifdef _DEBUG
	//getchar();								
#endif			
		}
	}

	initialiseGLUT(argc, argv);		
	return 0;
}
