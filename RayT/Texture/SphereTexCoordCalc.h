#ifndef _SPHERE_TEX_COORD_CALC
#define _SPHERE_TEX_COORD_CALC

#include "Common.h"
#include "Sphere.h"
#include "TexCoordCalc.h"


class SphereTexCoordCalculator : public TexCoordCalculator {
		Sphere* mObj;
		
	public:
		SphereTexCoordCalculator(Sphere* o)  { mObjType = OBJ_SPHERE; mObj = o; }
		~SphereTexCoordCalculator() {}

		virtual vec2 calcTexCoord(vec3);
		virtual vec3 getObjectSpaceCoords(vec3);
};

#endif
