#include "Light.h"

Light::Light()
{

}

Light::Light(vec3 pos, vec4 col, bool type)
{
	mLightColor = col;
	mLightPos   = pos;
	mLightType  = type;
}


