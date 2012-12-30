#include "Ray.h"
#include "Window.h"
#include "Camera.h"
#include "Common.h"

#define  _DEBUG_RAY
#undef   _DEBUG_RAY

Ray::Ray()
{

}


Ray::Ray(vec3 o, vec3 d)
{ 
	mOrigin = o; 
	mDirection = d; 

#ifdef  _DEBUG_RAY	
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	std::cout << "\nFrom: " << __FILE__;
	std::cout << "\nRay: Origin:(" << mOrigin.x << ", " << mOrigin.y << ", " << mOrigin.z << ")";
	std::cout << "\nRay: Direction:(" << mDirection.x << ", " << mDirection.y << ", " << mDirection.z << ")";	
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
#endif
	
}

Ray* Ray::getRay(glm::vec2 pixelPos, Camera* cam)
{
	double rayX = (pixelPos.x / Window::mWindowWidth) * Camera::mNearPlaneWidth;
	double rayY = (pixelPos.y / Window::mWindowHeight) * Camera::mNearPlaneWidth;
	
	vec3 screenCenter(cam->getLookAt().x * cam->getNearPlaneDis(),
					  cam->getLookAt().y * cam->getNearPlaneDis(),
					  cam->getLookAt().z * cam->getNearPlaneDis());

#ifdef  _DEBUG_RAY	
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	std::cout << "\nFrom: " << __FILE__;
	std::cout << "\nNear Plane width = " << Camera::mNearPlaneWidth;
	std::cout << "\nScreen center:(" << screenCenter.x << ", " << screenCenter.y << ", " << screenCenter.z << ")";
	std::cout << "\nPixelPos:(" << pixelPos.x << ", " << pixelPos.y << ")";
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
#endif					   
	
	double origx = (screenCenter.x) - (Camera::mNearPlaneWidth / 2.0);
	double origy = (screenCenter.y) - (Camera::mNearPlaneWidth / 2.0);
	vec3 origPlane(origx, origy, cam->getNearPlaneDis()); // TODO: maybe different? check
	vec3 actualRay(rayX, rayY, cam->getNearPlaneDis());
	
	actualRay = origPlane + actualRay;
	actualRay.z = cam->getNearPlaneDis();
	
#ifdef  _DEBUG_RAY	
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	std::cout << "\nActual Ray:(" << actualRay.x << ", " << actualRay.y << ", " << actualRay.z << ")";
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
#endif	
	
	vec3 rayDir = actualRay - cam->getCameraPos();
	
	return new Ray(cam->getCameraPos(), rayDir);
}
