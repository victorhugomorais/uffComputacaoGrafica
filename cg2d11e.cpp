#include "Graphics2D_v1.h"
#include "bezier.h"
#include "matrix.h"

int main(){
	std::vector<vec2> CP = loadCurve("borboleta.txt");
	std::vector<vec2> P = sample_cubic_bezier_spline(CP, 30);

	mat2 M = {
		-1.0, 0.0,
		 0.0, 1.0
	};	
	vec2 v = {800, 0};

	int n = P.size();
	std::vector<vec2> Q(n);
	for(int i = 0; i < n; i++)
		Q[i] = M*P[i] + v;

	LineStrip L{P.size()};
	
	Graphics2D G(800, 600);
	G.clear();
	G.draw(P, L, red);
	G.draw(Q, L, blue);
	G.savePNG("saidas/cg2d11e.cpp.png");
}
