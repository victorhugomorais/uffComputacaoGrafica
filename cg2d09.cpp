#include "Graphics2D_v1.h"
#include "bezier.h"
#include "matrix.h"
int main(){
	std::vector<vec2> P = {
		{107, 278},
		{166, 83},
		{567, 29},
		{674, 359},
		{500, 581},
		{325, 418},
		{485, 380},
	};
	std::vector<vec2> Q = sample_cubic_bezier_spline(P, 50);
	
	LineStrip LP{P.size()};
	LineStrip LQ{Q.size()};

	Graphics2D G(800, 600);
	G.clear();
	G.draw(P, LP, blue);
	G.draw(Q, LQ, red);
	G.savePNG("saidas/cg2d09.cpp.png");
}
