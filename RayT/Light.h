#ifndef _LIGHT_
#define _LIGHT_

#include "Common.h"

class Light {
	private:
			vec3 mLightPos;
			vec4 mLightColor;
			bool mLightType;  // 0 -> directional. 1 -> point
			
	public:
			Light();
			Light(vec3, vec4, bool);	
			
			inline vec4 getLightColor()      { return mLightColor; }
			inline vec3 getLightPosition()   { return mLightPos; 	  }			
};

#endif
