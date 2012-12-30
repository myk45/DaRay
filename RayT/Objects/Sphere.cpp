#include "Sphere.h"

#define _DEBUG_SPHERE
#undef  _DEBUG_SPHERE

Sphere::Sphere()
{
}

Sphere::Sphere(vec3 pos, double rad, vec4 col)
{
	mTexture = NULL;
	mObjType = OBJ_SPHERE;	
	mColor = col;
	mPosition = pos;
	mRadius   = rad;
}

vec3 Sphere::getNormal(vec3 pos)
{
	return (pos - mPosition);	
}

double Sphere::intersectObject(Ray* ray)
{
#ifdef _DEBUG_SPHERE	
//std::cout << "\nray:( "<< ray->getRayOrigin().x << ", " << ray->getRayOrigin().y << ", " << ray->getRayOrigin().z;
//std::cout <<"\nrayD:( "<< ray->getRayDirection().x<< ", "<< ray->getRayDirection().y << ", "<< ray->getRayDirection().z;
#endif	

	vec3 raoYMinusC = ray->getRayOrigin() - mPosition;
	
	double rayD_DotRayD = glm::dot(ray->getRayDirection(), ray->getRayDirection());
	double rayO_DotRayO = glm::dot(raoYMinusC, raoYMinusC);
	double RHS = (rayO_DotRayO - (mRadius * mRadius));
	double rayOrginDotP_1 = 2 * glm::dot(ray->getRayDirection(), raoYMinusC);
	
	double A = rayD_DotRayD;
	double B = rayOrginDotP_1;
	double C = RHS;
	
	{
		double det = (B * B) - (4 * A * C);		

		if (det < 0.0)
			return -1.0;
							
#ifdef _DEBUG_SPHERE	
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
		std::cout << "\ndet : " << det;
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
#endif			

		//t2 + trayD2Times = RHS
		double root1 = (-B + sqrt(det)) / (2 * A);		
		double root2 = (-B - sqrt(det)) / (2 * A);

#ifdef _DEBUG_SPHERE		
		getchar();
#endif
		
		if (root1 == root2) return -1.0;
		if (root1 < 0) return root2;
		if (root2 < 0) return root1;
		
#ifdef _DEBUG_SPHERE	
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
		std::cout << "\nFrom: " << __FILE__;
		std::cout << "\nRoot1, Root2: ( " << root1 << ", " << root2 << " )";
		std::cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n";
#endif					   
	
			
		return (root1 > root2) ? (root2) : (root1);
	}
	
	return -1.0;
}



