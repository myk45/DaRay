#ifndef _TEXTURE_
#define _TEXTURE_


#include "Common.h"

// Responsible for: Reading of texture images, obtaining colors for a textcoord
class Texture {
	private:
			static int mTexID[MAX_TEXTURE_COUNT]; 
			static int mTexCount;
			unsigned char mTexelData[TEX_WIDTH][TEX_HEIGHT][3];
			 
	public:
			Texture();

			void createTexture(const char* filename); // C stle IO used. So, const char* makes sense :D
			vec3 getColor(const vec2 UV); // get Color for a UV texCoord. Returns an RGB vector
};

#endif
