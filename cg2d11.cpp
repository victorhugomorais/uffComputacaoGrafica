#include "Graphics2D_v1.h"
#include "bezier.h"

int main(){
	std::vector<vec2> P = {
		{11, 218},
		{184, 10},
		{54, 344},
		{315, 369},
		{228, 281},
		{349, 180},
	};
	std::vector<vec2> Q = sample_bezier(P, 100);

	LineStrip LP{P.size()};
	LineStrip LQ{Q.size()};
	
	Graphics2D G(800, 600);
	G.clear();
	G.draw(P, LP, red);
	G.draw(Q, LQ, blue);
	G.savePNG("saidas/cg2d11.cpp.png");
}
