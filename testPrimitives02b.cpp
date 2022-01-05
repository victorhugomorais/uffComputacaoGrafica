#include "Primitives.h"
#include "rasterization.h"
#include "Image.h"

int main(){
	Image Img(500, 400);
	Img.fill(white);

	std::vector<vec2> P = {
		{193, 66},
		{259, 139},
		{340, 54},		
		{176, 220},
		{336, 212},
		{261, 311}
	};

	std::vector<unsigned int> indices = {
		0, 3, 1,  1, 3, 4,  1, 4, 2,  3, 5, 4
	};
	
	Elements<Triangles> T{indices};

	for(Triangle<vec2> triangle: assemble(T, P))
		for(Pixel p: rasterizeTriangle(triangle))
			Img(p.x,p.y) = blue;
	
	Img.savePNG("saidas/testPrimitives02b.cpp.png");
}
