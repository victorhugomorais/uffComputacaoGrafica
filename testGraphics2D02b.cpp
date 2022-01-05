#include "Graphics2D_v1.h"

int main(){
	std::vector<vec2> P = {
		{222, 139},
		{80, 59},
		{117, 279},
		{245, 313},
		{388, 192},
		{354, 32}
	};

	TriangleFan T{P.size()};

	Graphics2D G(500, 400);
	G.clear();
	G.draw(P, T, blue);
	G.savePNG("output.png");
}


