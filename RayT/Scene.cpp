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
	mAmbientLight = new Light(vec3(0, 0, 0), vec4(1.0, 0.0, 0.0, 0.0), false);
}

Light* Scene::getAmbientLight()
{
	return mAmbientLight;
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

vec3 Scene::textureObject(Hit hitObj)
{
	if (hitObj.obj->getObjectTexture()) {
		TexCoordCalculator* tCalc = TexCoordCalculator::getTexCoordCalculator(hitObj.obj);

		vec3 objSpaceCoord = tCalc->getObjectSpaceCoords(hitObj.intersectPoint);
		vec2 UV = tCalc->calcTexCoord(objSpaceCoord);
	
		vec3 texCol = hitObj.obj->getObjectTexture()->getColor(UV);
		return texCol;
		
	} else {
		return vec3(1.0, 1.0, 1.0);
	}
}

vec4 Scene::lightScene(Hit hitObj)
{
	vec4 objCol = hitObj.obj->getObjectColor();
	vec3 normal = glm::normalize(hitObj.obj->getNormal(hitObj.intersectPoint));
	vec4 resultantColor;	
	
	

	// todo: add object's material properties here!
	for (int i = 0; i < mLightList.size(); i++) {
		double NdotL = glm::dot(glm::normalize(mLightList[i]->getLightPosition() - hitObj.intersectPoint), normal);
						
		// TODO: Add some ambient component
		//resultantColor *= mAmbientLight->getLightColor();
		double maxNdotL = glm::max(NdotL, 0.0);

		if (hitObj.obj->getObjectTexture()) { // Texturing enabled
			vec3 texCol = textureObject(hitObj);
			resultantColor += (mLightList[i]->getLightColor().g * maxNdotL * vec4(texCol.x / 255.0, texCol.y / 255.0, texCol.z / 255.0, 1.0));
		} else {
			resultantColor += vec4(mLightList[i]->getLightColor().r * maxNdotL * hitObj.obj->getObjectColor().r,
						mLightList[i]->getLightColor().g * maxNdotL * hitObj.obj->getObjectColor().g, 
						mLightList[i]->getLightColor().b * maxNdotL * hitObj.obj->getObjectColor().b, 
						0.0);	
		}
		
#ifdef _DEBUG_SCENE	
		if (hitObj.obj->getObjectType() == 1) {
			std::cout << "\nInterP: " << hitObj.intersectPoint.x << ","<< hitObj.intersectPoint.y <<","<< hitObj.intersectPoint.z;
			std::cout << "\nNdotL  = " << NdotL;
			std::cout << "\nmaxNdotL = " << maxNdotL;
			getchar();
		}		
#endif									   		   							  
	}	
	
	double intersectD = NO_INTERSECTION;
	for (int i = 0; i < mLightList.size(); i++) {
		vec3 tempRay = glm::normalize(mLightList[i]->getLightPosition() - hitObj.intersectPoint); 
		Ray* shadowRay = Ray::getRay(hitObj.intersectPoint, tempRay);	 // TODO: Write Ray types.
																		 // TODO: Check for leaks!						
		for (int j = 0; j < mObjectList.size(); j++) {
			intersectD = mObjectList[j]->intersectObject(shadowRay);				
		}									
	}

	if (hitObj.obj->getObjectType() == 1 || intersectD == NO_INTERSECTION)
		return resultantColor;
	else
		return vec4(0.0, 0.0, 0.0, 0.0);							
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


