#include "Scene.h"

#define _DEBUG_SCENE
#undef  _DEBUG_SCENE

#ifdef _DEBUG_SCENE
std::string OBJ_STR[10] =
				  {
				   "PLANE",
				   "SPHERE"
				  };
#endif

Scene::Scene()
{

}


void Scene::addObject(Object* obj)
{
	mObjectList.push_back(obj);
}

std::vector<Hit>& Scene::getHitList(Ray* ray)
{
#ifdef _DEBUG_SCENE	
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
	std::cout << "\nFrom: " << __FILE__;
	std::cout << "trying to get hit list\n";
	std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
#endif	
	
	// interect all objects and check if there is an intersection and store result in hit list
	for (int i = 0; i < mObjectList.size(); i++) {
		double intersectD = mObjectList[i]->intersectObject(ray);
		
		//std::cout << "Intersect dis= " << intersectD << "\n";
		//getchar();
		
		if (intersectD != NO_INTERSECTION) {
			mHitList.push_back( Hit(mObjectList[i], intersectD) );
		} else {
		
#ifdef _DEBUG_SCENE	
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
		std::cout << "\nFrom: " << __FILE__;
		std::cout << "\nObject: " << OBJ_STR[mObjectList[i]->getObjectType()] << " does not intersect!";
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
#endif			
		}
		
	}
	
	return mHitList;
}


vec4 Scene::processHitListAndGetColor()
{
#ifdef _DEBUG_SCENE	
	if (mHitList.size() == 0) {
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
		std::cout << "\nFrom: " << __FILE__;
		std::cout << "\n HitList is zero!";
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
    }
#endif
	if (mHitList.size() == 0)
		return vec4(0.5, 0.5, 0.5, 0.0);
	
	// TODO: Do some calculations and get a color
	Hit winHit(mHitList[0].obj, mHitList[0].intersectDis);
	double max = 0;
	for (int i = 0; i < mHitList.size(); i++) {
		if (mHitList[i].intersectDis > max) {
			winHit.obj = mHitList[i].obj;
			winHit.intersectDis = mHitList[i].intersectDis;
			max = winHit.intersectDis;
		}				
	}	
#ifdef _DEBUG_SCENE	
	std::cout << "\nWinning object: " << OBJ_STR[winHit.obj->getObjectType()]; 
	std::cout << "\nReturning color:";
#endif	

	return winHit.obj->getObjectColor();
}


