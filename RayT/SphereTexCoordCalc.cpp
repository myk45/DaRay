#include "SphereTexCoordCalc.h"

#define DEBUG_SPH_TEX_CC
#undef  DEBUG_SPH_TEX_CC

vec2 SphereTexCoordCalculator::calcTexCoord(vec3 objSpaceCoord)
{
//	x = rsinAcosB
	
	double thetaY = acos(objSpaceCoord.z / mObj->getRadius());
	thetaY *= (180.0 / PI);
	
	
	double thetaX = acos( (objSpaceCoord.x) / (mObj->getRadius() * sin(thetaY * PI / 180.0)) );
	thetaX *= (180.0 / PI);
	
	vec2 UV;
	UV.y = (thetaY / 180.0); 
	UV.x = (thetaX / 360.0); 
	
#ifdef DEBUG_SPH_TEX_CC
	std::cout << "\nFrom: " << __FILE__;
	std::cout << "\n val = " << (objSpaceCoord.x) / (mObj->getRadius() * sin(thetaY));
	std::cout << "\n\nOBJ_COORD:(" << objSpaceCoord.x << "," << objSpaceCoord.y << "," << objSpaceCoord.z << ")";
	std::cout << "\nTHETA X = " << thetaX;
	std::cout << "  THETA y = " << thetaY;
	std::cout << "\nUV( " << UV.x << "," << UV.y << ")";
	getchar();
#endif	

	return UV;
}

vec3 SphereTexCoordCalculator::getObjectSpaceCoords(vec3 worldSpaceCoord)
{
	vec3 objSpaceCoord(worldSpaceCoord.x - mObj->getPos().x, 
					   worldSpaceCoord.y - mObj->getPos().y, 
					   worldSpaceCoord.z - mObj->getPos().z);
					   
	return 	objSpaceCoord;				   
}
