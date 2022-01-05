#include "Graphics2D_v1.h"
#include "bezier.h"
#include "matrix.h"

int main(){
	std::vector<vec2> CP = loadCurve("borboleta.txt");
	std::vector<vec2> P = sample_cubic_bezier_spline(CP, 30);

	mat3 M = {
		-1.0, 0.0, 800,
		 0.0, 1.0, 0.0,
		 0.0, 0.0, 1.0
	};

	LineStrip L{P.size()};
	
	Graphics2D G(800, 600);
	G.clear();
	G.draw(P, L, red);
	G.draw(M*P, L, blue);
	G.savePNG("saidas/cg2d13d.cpp.png");
}
