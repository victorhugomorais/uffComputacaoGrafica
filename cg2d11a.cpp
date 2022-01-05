#include "Graphics2D_v1.h"
#include "bezier.h"

int main(){
	std::vector<vec2> CP = loadCurve("borboleta.txt");
	std::vector<vec2> P = sample_cubic_bezier_spline(CP, 30);

	LineStrip L{P.size()};

	Graphics2D G(800, 600);
	G.clear();
	G.draw(P, L, red);
	G.savePNG("saidas/cg2d11a.cpp.png");
}
