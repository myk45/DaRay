#ifndef _SCENE_
#define _SCENE_

#include <vector>
#include "Common.h"
#include "Object.h"
#include "Ray.h"

struct Hit {	
	Object* obj;
	double intersectDis;
	
	Hit(Object *o, double i) { obj = o; intersectDis = i; }
};

class Scene {
	private:
			std::vector<Object*> mObjectList;
			std::vector<Hit> mHitList;
			
	public:
			Scene();
			void addObject(Object*);
			
			std::vector<Hit>& getHitList(Ray*);
			vec4 processHitListAndGetColor();
			
			void clearHitList() { mHitList.clear(); }					

};

#endif

