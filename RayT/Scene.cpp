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

void Scene::addLight(Light* light)
{
	mLightList.push_back(light);
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
		
		if (intersectD != NO_INTERSECTION) {
			vec3 intersectPoint = ray->getRayOrigin() + vec3(ray->getRayDirection().x * intersectD, 
												             ray->getRayDirection().y * intersectD,
													         ray->getRayDirection().z * intersectD);	
													         			
			mHitList.push_back( Hit(mObjectList[i], intersectD, intersectPoint) );
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

vec4 Scene::lightScene(Hit hitObj)
{
	vec4 objCol = hitObj.obj->getObjectColor();
	vec3 normal = glm::normalize(hitObj.obj->getNormal(hitObj.intersectPoint));
	vec4 resultantColor;	
	
	// todo: add object's material properties here!
	for (int i = 0; i < mLightList.size(); i++) {
		double NdotL = glm::dot(glm::normalize(mLightList[i]->getLightPosition() - hitObj.intersectPoint), normal);
	
		double maxNdotL = glm::max(NdotL, 0.0);
		resultantColor += vec4(mLightList[i]->getLightColor().r * maxNdotL * hitObj.obj->getObjectColor().r,
							   mLightList[i]->getLightColor().g * maxNdotL * hitObj.obj->getObjectColor().g, 
							   mLightList[i]->getLightColor().b * maxNdotL * hitObj.obj->getObjectColor().b, 
							   0.0);					
		
#ifdef _DEBUG_SCENE	
		if (hitObj.obj->getObjectType() == 1) {
			std::cout << "\nInterP: " << hitObj.intersectPoint.x << ","<< hitObj.intersectPoint.y <<","<< hitObj.intersectPoint.z;
			std::cout << "\nNdotL  = " << NdotL;
			std::cout << "\nmaxNdotL = " << maxNdotL;
			getchar();
		}		
#endif									   		   							  
	}	
	
	return resultantColor;
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
	Hit winHit;
	double min = 0xFFFFFFFF;
	for (int i = 0; i < mHitList.size(); i++) {
		if (mHitList[i].intersectDis < min) {
			winHit.obj = mHitList[i].obj;
			winHit.intersectDis = mHitList[i].intersectDis;
			winHit.intersectPoint = mHitList[i].intersectPoint;
			min = winHit.intersectDis;
		}				
	}	
#ifdef _DEBUG_SCENE	
	std::cout << "\nWinning object: " << OBJ_STR[winHit.obj->getObjectType()]; 
	std::cout << "\nReturning color:";
#endif	

	return lightScene(winHit);
}


