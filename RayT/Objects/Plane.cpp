#include "Plane.h"

#define _DEBUG_PLANE
#undef _DEBUG_PLANE

Plane::Plane()
{
}

Plane::Plane(vec3 norm, vec3 point, vec4 col)
{
	mTexture = NULL;
	mObjType = OBJ_PLANE;
	mColor = col;
	mNormal = norm;
	mPointInPlane = point;
}


double Plane::intersectObject(Ray *ray)
{	
	mNormal = glm::normalize(mNormal);
	
	// (A - P) . N = 0
	double t = (glm::dot(mPointInPlane, mNormal) - (glm::dot(ray->getRayOrigin(), mNormal))) / 
			   (glm::dot(glm::normalize(ray->getRayDirection()), mNormal));
			   		
#ifdef _DEBUG_PLANE		
	if (t != 0 && glm::dot(ray->getRayDirection(), mNormal) != 0) {
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
		std::cout << "\nFrom: " << __FILE__;
		std::cout << "\nT = " << t;
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
		getchar();
	}
#endif
	
	if (glm::dot(ray->getRayDirection(), mNormal) == 0)	 return -1.0;
	if (glm::dot (mNormal, ray->getRayDirection()) == 0) return -1.0;
	if (glm::dot(glm::normalize(ray->getRayDirection()), mNormal) == 0) return -1.0;
	if (t == 0)									  	     return -1.0;			
	if (t < 0)											 return -1.0;		
			
	return t;
}
