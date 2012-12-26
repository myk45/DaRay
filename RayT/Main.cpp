#include <cstdio>
#include <ctime>
#include <cmath>
#include "Ray.h"
#include "Camera.h"
#include "Window.h"
#include "Common.h"
#include "Sphere.h"
#include "Light.h"
#include "Scene.h"
#include "Plane.h"
#include <GL/glut.h>

//#undef __CPP__11__


#ifdef __CPP__11__
	#include <thread>
	#include <chrono>
#endif	


#define _DEBUG_MAIN
#undef  _DEUBG_MAIN

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
	glutCreateWindow("Da Ray");	
	glutDisplayFunc(draw);	
	glutMainLoop();	
}

// Passing local copies of data so as to have thread safety. Passing pointers would lead to 
// unsafe function
void fillPixels(int winWidth, int winHeight, int winWStart, int winHStart,
				Camera mainCamera, Scene scene)
{		
	for (int i = winHStart; i < (winHStart+winHeight); i++) {
		for (int j = winWStart; j < (winWStart+winWidth); j++) {						
			Ray *currRay = Ray::getRay(vec2(j, i), &mainCamera);
			
			std::vector<Hit>& hitList = scene.getHitList(currRay);
			vec4 colAtPix = scene.processHitListAndGetColor(); // maybe we could give in a light here!			
						
			colorBuffer[i][j][0] = (colAtPix.r / 1.0) * 255;
			colorBuffer[i][j][1] = (colAtPix.g / 1.0) * 255;
			colorBuffer[i][j][2] = (colAtPix.b / 1.0) * 255;						
			
			scene.clearHitList();					
		}
	}
}

void addSceneObjects(Scene* scene)
{	
	scene->addObject( new Plane( vec3(0, 1, 0), vec3(0, -1, 10), vec4(0.0, 1.0, 1.0, 0.0) ) );
	scene->addObject( new Plane( vec3(1, 0, 0), vec3(-5, 0, 10), vec4(0.2, 0.5, 0.7, 0.0) ) );	
	scene->addObject( new Plane( vec3(0, 0,-1), vec3(0, 0, 1000), vec4(1.0, 1.0, 0.0, 0.0) ) );	
	
	
	Texture *tex = new Texture();
	tex->createTexture("texture.bmp");
	
	Sphere* sObj = new Sphere( vec3(0, 1.5, 10), 3.5, vec4(1.0, 0.0, 0.0, 0.0) );
	sObj->setObjectTexture(tex);
	
	scene->addObject(sObj);
	scene->addLight( new Light( vec3(10, 10, 5), vec4(1.0, 1.0, 1.0, 0.0),  false) );
	scene->addLight( new Light( vec3(-10, -10, 10), vec4(1.0, 1.0, 1.0, 0.0), false) );
}

int main(int argc, char* argv[])
{	
	//std::thread t = std::thread(foo);
	
	Camera *mainCamera = new Camera(POS, LOOK, UP, 1.0, 90.0);
	Scene* scene = new Scene();	
			
	// Add some objects and lights	
	addSceneObjects(scene);
	

#ifdef __CPP__11__							
	auto begin = std::chrono::system_clock::now();
#else
	clock_t begin = clock();	
#endif		
	  
	// Fill the color buffer	
#ifndef __CPP__11__	
	fillPixels(Window::mWindowWidth, Window::mWindowHeight, 0, 0, *mainCamera, *scene);
#else
	std::thread workerThreads[NUM_THREADS];
	
	workerThreads[0] = std::thread(fillPixels, 250, 250, 0,   0,   *mainCamera, *scene);
	workerThreads[1] = std::thread(fillPixels, 250, 250, 250, 0,   *mainCamera, *scene); 
	workerThreads[2] = std::thread(fillPixels, 250, 250, 250, 250, *mainCamera, *scene); 
	workerThreads[3] = std::thread(fillPixels, 250, 250, 0,   250, *mainCamera, *scene);  
	
	for (int i = 0; i < 4; i++) {
		workerThreads[i].join();
	}
#endif
		

#ifdef __CPP__11__							
	auto end = std::chrono::system_clock::now();
	std::cout << "\nTime for tracing this scene: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
	getchar();
#else	
	clock_t end = clock();	
	double traceTime = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "\nTime for tracing this scene: " << traceTime << "\nEnter to continue";						
	getchar();
#endif	

	initialiseGLUT(argc, argv);		
	return 0;
}
