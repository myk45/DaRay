#ifndef _OBJECT_
#define _OBJECT_

#include "Common.h"
#include "Ray.h"
	
	
// abstract base class for all Scene objects	
class Object {
	protected:
			OBJECT_TYPE mObjType;
			vec4 mColor;	
	
	public:			
			OBJECT_TYPE getObjectType() { return mObjType; }
			vec4 getObjectColor() 		{ return mColor;   }
			virtual double intersectObject(Ray *) = 0;									
			
};

#endif
