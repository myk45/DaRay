#include <cstdio>
#include <cmath>
#include "Ray.h"
#include "Camera.h"
#include <GL/glut.h>


int main(int argc, char* argv[])
{
#define M_PI 3.14 / 180.0

	const double nearPlaneDis = 1.0;
	const double fovx = 60.0 * M_PI;
	const double fovy = 60.0 * M_PI; 
	const int width  = 640;
	const int height = 480;

	const double valXAtNearPlane = tan(fovx / 2) * nearPlaneDis;
	const double valYAtNearPlane = tan(fovy / 2) * nearPlaneDis;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {			
			double xx = ((i - width  / 2.0) / (width  / 2.0)) * valXAtNearPlane;
			double yy = (((height - j)  / 2.0) / (height / 2.0)) * valYAtNearPlane;
						
			vec3 ray = glm::normalize(vec3(xx, yy, 1));						
			float t = findPlaneIntersection(ray);

			if (t != -1) {
				pixels[i][j][0] = 255;
				pixels[i][j][1] = 0;
				pixels[i][j][2] = 0;		
			} else {
				pixels[i][j][0] = 0;
				pixels[i][j][1] = 0;
				pixels[i][j][2] = 0;		
			}									
		}
	}

	//getchar();
	
	initialiseGLUT(argc, argv);		
	return 0;
}
