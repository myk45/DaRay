#ifndef _SPHERE_
#define _SPHERE_

#include "Object.h"
#include "Common.h"

class Sphere : public Object {
	private:
			double mRadius;
			vec3 mPosition;
	
	public:
			Sphere();
			Sphere(vec3 pos, double rad, vec4 col);
			
			inline double getRadius() { return mRadius;   }
			inline vec3   getPos()	  { return mPosition; }
			
			virtual double intersectObject(Ray *);
			vec3 getNormalAt(vec2 pixelPos); 

};


#endif


