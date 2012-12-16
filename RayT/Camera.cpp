#include <cmath>
#include "Camera.h"

double Camera::mNearPlaneWidth = 0.0;			

const double PI = 3.14;

Camera::Camera(vec3 pos, vec3 lookAt, vec3 up, double near=1.0, double fov=90.0)	
{
	mCamPos = pos;
	mUp = glm::normalize(up);
	mLookAt = glm::normalize(mCamPos - lookAt);
	mRight = glm::cross(mLookAt, mUp);
	mNearPlaneDis = near;
	mFOV = fov;
	
	init(); // Some initial calculations. This gives some constants that can be used later
}


void Camera::init()
{
	double ang = (mFOV / 2.0 ) * (PI / 180.0);
	
	double nearPlaneRight = tan(ang) * mNearPlaneDis;
	mNearPlaneWidth = 2 * nearPlaneRight;
}
	
