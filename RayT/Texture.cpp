#include "Texture.h"


#define _DEBUG_TEX
#undef  _DEBUG_TEX

int Texture::mTexID[MAX_TEXTURE_COUNT]; 
int Texture::mTexCount = 0;
			 
			 
Texture::Texture()
{
	mTexID[mTexCount] = mTexCount;
	mTexCount++;
}

void Texture::createTexture(const char* filename)
{
	FILE* texFile;
	unsigned char arr[54];
	
	if ( (texFile = fopen(filename, "rb")) == NULL ) {
		std::cout << "\nError: Cannot open file for texture!";
	} else {
		std::cout << "\nFile: " << filename << " Opened!";
		fread(arr, 1, 54, texFile);
		fread(mTexelData, 1, TEX_WIDTH * TEX_HEIGHT * 3, texFile);
		fclose(texFile);
	}	
}

vec3 Texture::getColor(const vec2 UV)
{
	int j = UV.x * (double)TEX_WIDTH;
	int i = UV.y * (double)TEX_HEIGHT;
		
#ifdef _DEBUG_TEX
	std::cout << "From: " << __FILE__;
	std::cout << "\n (i, j) = (" << i << ", " << j << ")";
	std::cout << "\n Col: " << (int)mTexelData[i][j][0] << "," << (int)mTexelData[i][j][1] << "," << (int)mTexelData[i][j][2];
	getchar();	
#endif	

	// TODO: "Check" not really needed. Check why the check is needed! :D
	if (i > 0 && i <= 256 && j > 0 && j <= 256) {
		vec3 col(mTexelData[i][j][2], mTexelData[i][j][1], mTexelData[i][j][0]);
		return col;
	}

	return vec3(1.0, 1.0, 1.0);
}




