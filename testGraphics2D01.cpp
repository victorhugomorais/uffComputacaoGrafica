#include "Graphics2D_v1.h"

int main(){
	std::vector<vec2> P = {
		{20, 20},
		{80, 60},
		{220, 30},
		{350, 90},
		{70, 300},
		{320, 150}
	};

	std::vector<unsigned int> indices = {0, 4, 5, 3, 2, 1};

	Elements<Lines> L{indices};
	//Elements<LineStrip> L{indices};
	//Elements<LineLoop> L{indices};
	//LineLoop L{P.size()};

	Graphics2D G(500, 400);
	G.clear();
	G.draw(P, L, red);
	G.savePNG("output.png");
}


