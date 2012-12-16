#ifndef _COMMON_
#define _COMMON_

#define _DEBUG 
//#undef  _DEBUG

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

#endif
