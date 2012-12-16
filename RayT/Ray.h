#ifndef _RAY_
#define _RAY_

#include "glm/glm.hpp"
#include "Camera.h"
#include <cstdio>
#include <iostream>

typedef glm::vec3 vec3;

class Ray {
	private:
			vec3 mOrigin;
			vec3 mDirection;
			
	public:
			Ray();
			Ray(vec3 o, vec3 d); 
			
			~Ray();
			
			inline vec3 getRayOrigin()    { return mOrigin;    }
			inline vec3 getRayDirection() { return mDirection; }
			
			// Like a factory for rays! haha! how come?!
			static Ray* getRay(glm::vec2 pixelPos, Camera* cam);

};
#endif
