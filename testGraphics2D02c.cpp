#include "Graphics2D_v1.h"

int main(){
	std::vector<vec2> P = {
		{193, 66},  {259, 139},
		{340, 54},  {176, 220},
		{336, 212}, {261, 311}
	};
	std::vector<unsigned int> indices = {
		0, 3, 1,   1, 3, 4, 
		1, 4, 2,   3, 5, 4
	};
	Elements<Triangles> T{indices};

	Graphics2D G(500, 400);
	G.clear();
	G.draw(P, T, blue);
	G.savePNG("output.png");
}



