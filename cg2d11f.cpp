#include "Graphics2D_v1.h"
#include "matrix.h"
#include "bezier.h"

int main(){
	std::vector<vec2> CP = loadCurve("borboleta.txt");
	std::vector<vec2> P = sample_cubic_bezier_spline(CP, 30);

	float t = 0.6;
	mat2 M = {
		cos(t), -sin(t),
		sin(t), cos(t)
	};

	std::vector<vec2> Q = M*P;

	LineStrip L{P.size()};
	
	Graphics2D G(800, 600);
	G.clear();
	G.draw(P, L, red);
	G.draw(Q, L, blue);
	G.savePNG("saidas/cg2d11f.cpp.png");
}
