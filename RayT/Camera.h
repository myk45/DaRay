#ifndef _CAMERA_
#define _CAMERA_

#include <iostream>
#include "glm/glm.hpp"

typedef glm::vec3 vec3;

class Camera {
	private:
			glm::vec4 mLRTB; // L, R, T, B of near plane
			double mFOV;	 // FOV_X = FOV_Y now
			double mNearPlaneDis;
			
			vec3 mUp;
			vec3 mRight;
			vec3 mLookAt;
			vec3 mCamPos;			
			void init();
	
	public:
			Camera();
			Camera(vec3 pos, vec3 lookAt, vec3 up, double near, double fov);
			
			
			inline vec3 getLookAt()	   { return mLookAt;}
			inline vec3 getUp()    	   { return mUp;    }
			inline vec3 getRight() 	   { return mRight; }
			inline vec3 getCameraPos() { return mCamPos; }
			
			inline double getNearPlaneDis() { return mNearPlaneDis; }
			
			static double mNearPlaneWidth;							

};

#endif

