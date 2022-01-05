#include "Image.h"
#include "rasterization.h"

int main(){
	Image Img(600, 600);
	Img.fill(white);

	vec2 T[] = { {20, 50}, {524, 100}, {205, 567} };

	for(Pixel p : rasterizeTriangle(T))
		Img(p.x, p.y) = blue;

	Img.savePNG("saidas/testRasterization01.cpp.png");
}


