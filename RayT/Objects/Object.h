#ifndef _OBJECT_
#define _OBJECT_

#include "Common.h"
#include "Ray.h"
#include "Texture.h"
	
	
// abstract base class for all Scene objects	
class Object {
	protected:
			OBJECT_TYPE mObjType;
			vec4 mColor;	
			Texture* mTexture;						
	
	public:			
			OBJECT_TYPE getObjectType() { return mObjType; }
			vec4 getObjectColor() 		{ return mColor;   }
			virtual double intersectObject(Ray *) = 0;		
			virtual vec3 getNormal(vec3) = 0;								
			
			void setObjectTexture(Texture* t)     { mTexture = t;     }
			Texture* getObjectTexture()           { return mTexture; }
};

#endif
