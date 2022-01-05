#include "Primitives.h"
#include "rasterization.h"
#include "Image.h"

int main(){
	Image Img(500, 400);
	Img.fill(white);

	std::vector<vec2> P = {
		{ 60, 105},
		{229, 114},
		{145, 270},
		{364, 208},
		{283, 333},
		{471, 298}
	};

	Triangles T{P.size()};
	//TriangleStrip T{P.size()};

	for(Triangle<vec2> triangle: assemble(T, P))
		for(Pixel p: rasterizeTriangle(triangle))
			Img(p.x,p.y) = blue;
	
	Img.savePNG("saidas/testPrimitives02a.cpp.png");
}

