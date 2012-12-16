#ifndef _SCENE_
#define _SCENE_

#include <vector>
#include "Common.h"
#include "Object.h"
#include "Light.h"
#include "Ray.h"

struct Hit {	
	Object* obj;
	double intersectDis;
	vec3 intersectPoint; // point where the intersection happened.
	
	Hit() {}
	Hit(Object *o, double i, vec3 p) { obj = o; intersectDis = i; intersectPoint = p; }
};

class Scene {
	private:
			std::vector<Object*> mObjectList;
			std::vector<Light*> mLightList;
			std::vector<Hit> mHitList;
			
	public:
			Scene();
			void addObject(Object*);
			void addLight(Light*);
			
			std::vector<Hit>& getHitList(Ray*);
			vec4 processHitListAndGetColor();
			vec4 lightScene(Hit);
			
			void clearHitList() { mHitList.clear(); }					

};

#endif

