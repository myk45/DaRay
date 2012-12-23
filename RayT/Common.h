#ifndef _COMMON_
#define _COMMON_

// ===========================================================================
// Some preprocessor checks
// ===========================================================================
#ifdef __linux__
	#if __GNUC__ >= 4 && __GNUC_MINOR__ >= 6 && __GNUC_PATCHLEVEL__ >= 3 
		#define __CPP__11__
		#pragma message("C++ 11 supported")
	#else
		#undef __CPP__11__
		#pragma message("C++ 11 not supported")
	#endif	
#else 
	#if _MSC_VER > 1600
		#define __CPP__11__
		#pragma message("C++ 11 supported")
	#else 
		#undef __CPP__11__
		#pragma message("C++ 11 not supported")
	#endif			
#endif	
// ===========================================================================
// ===========================================================================

#include <cmath>
#include <cassert>
#include "glm/glm.hpp"

typedef glm::vec4 vec4;
typedef glm::vec3 vec3;
typedef glm::vec2 vec2;

#define UP   vec3(0, 1, 1)
#define POS  vec3(0, 0, 0)
#define LOOK vec3(0, 0, 1)

#define NO_INTERSECTION -1

enum OBJECT_TYPE {
	OBJ_PLANE = 0,
	OBJ_SPHERE,
	OBJ_COUNT
};


static const int NUM_THREADS = 4;

#endif
