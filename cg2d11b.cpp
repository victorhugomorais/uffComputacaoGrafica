#include "Graphics2D.h"
#include "bezier.h"

int main(){
	std::vector<vec2> CP = loadCurve("borboleta.txt");
	std::vector<vec2> P = sample_cubic_bezier_spline(CP, 30);

	vec2 v = {220, 150};

	std::vector<vec2> Q(P.size());
	for(unsigned int i = 0; i < P.size(); i++)
		Q[i] = P[i] + v;
	
	LineStrip L{P.size()};
	
	Graphics2D G(800, 600);
	G.clear();
	G.draw(P, L, red);
	G.draw(Q, L, blue);
	G.savePNG("saidas/cg2d11b.cpp.png");
}
