#include "TexCoordCalc.h"
#include "SphereTexCoordCalc.h"

TexCoordCalculator* TexCoordCalculator::getTexCoordCalculator(Object* o)
{
	switch ( o->getObjectType() ) {
		case OBJ_SPHERE: {	
			return new SphereTexCoordCalculator((Sphere*)o); // TODO: Is this ok?
			break;
		}

		case OBJ_PLANE: {
			return NULL;		
		}
		
		default: {
			std::cout <<"\n An object needed!";
			return NULL;
			break;
		}
	}
}


