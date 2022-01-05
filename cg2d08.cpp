#include "Graphics2D_v1.h"
#include "bezier.h"

int main(){
	std::vector<vec2> P = {
		{107, 278},
		{166, 83},
		{567, 29},
		{674, 359}
	};
	LineStrip LP{4};

	std::vector<vec2> Q = sample_cubic_bezier(P.data(), 50);
	LineStrip LQ{50};
	
	Graphics2D G(800, 400);
	G.clear();
	G.draw(P, LP, red);
	G.draw(Q, LQ, blue);
	G.savePNG("saidas/cg2d08.cpp.png");
}
