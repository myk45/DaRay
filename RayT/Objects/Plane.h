#ifndef _PLANE_
#define _PLANE_

#include "Common.h"
#include "Object.h"
#include "Ray.h"

class Plane : public Object {
	private:
			vec3 mNormal;
			vec3 mPointInPlane;
			double mDistance;	
			
			
	public:
			inline vec3   getNormal()   { return mNormal;   }
			inline double getDistance() { return mDistance; }
			virtual vec3 getNormal(vec3 pos) { return mNormal; }			
			
			Plane();
			Plane(vec3, vec3, vec4);
			virtual double intersectObject(Ray *);				
			
};

#endif


