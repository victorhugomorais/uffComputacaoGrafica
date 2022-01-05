#include "Image.h"
#include "rasterization.h"

int main(){
	Image Img(600, 600);
	Img.fill(white);

	int n = 20;
	for(int i = 0; i < n; i++){
		float angle = i*2*M_PI/n;
		
		vec2 c = {300, 300};
		vec2 d = {cos(angle), sin(angle)};
		vec2 L[2] = { c+50*d, c+200*d };

		for(Pixel p : rasterizeLine(L))
			Img(p.x, p.y) = blue;
	}
	Img.savePNG("saidas/cg2d02.cpp.png");
}
