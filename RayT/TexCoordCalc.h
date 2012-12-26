#ifndef _TEXCOORD_CALC
#define _TEXCOORD_CALC

#include "Common.h"
#include "Object.h"

// Takes a point in world space, converts to object space and then, lets you obtain a 
// (u, v) coordinate that can be used to obtain a texture's color from.
// Currently, we are only concerned with 2D textures
class TexCoordCalculator {
	protected:
		OBJECT_TYPE mObjType;
	
	public:
		//TexCoordCalculator(OBJECT_TYPE t) {} Make private??
		
		static TexCoordCalculator* getTexCoordCalculator(Object*);
		~TexCoordCalculator() {}
		
		//return a (u, v) pair															  // Somehow GCC doesn't complain!			
		virtual vec2 calcTexCoord(vec3 objSpaceCoord) { std::cout << "\nWhy am i here?";  return vec2(-1.0, -1.0); }
																						  // Somehow GCC doesn't complain!						
		virtual vec3 getObjectSpaceCoords(vec3) 	   { std::cout << "\nWhy am i here?"; return vec3(-1.0, -1.0, -1.0); }
};

#endif
