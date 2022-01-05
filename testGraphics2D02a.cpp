#include "Graphics2D_v1.h"

int main(){
	std::vector<vec2> P = {
		{ 60, 105},
		{229, 114},
		{145, 270},
		{364, 208},
		{283, 333},
		{471, 298}
	};

	Triangles T{P.size()};
//	TriangleStrip T{P.size()};

	Graphics2D G(500, 400);
	G.clear();
	G.draw(P, T, blue);
	G.savePNG("output.png");
}


