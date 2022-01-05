#include "Graphics2D_v1.h"
#include "bezier.h"
#include "matrix.h"

int main(){
	std::vector<vec2> CP = loadCurve("borboleta.txt");
	std::vector<vec2> P = sample_cubic_bezier_spline(CP, 30);

	float t = 0.5;
	mat2 Rot = {
		cos(t), -sin(t),
		sin(t), cos(t)
	};
	mat2 Cis = {
		1, 1.2,
		0, 1
	};
	std::vector<vec2> Q = (Rot*Cis)*P;

	LineStrip L{P.size()};
	
	Graphics2D G(800, 600);
	G.clear();
	G.draw(P, L, red);
	G.draw(Q, L, blue);
	G.savePNG("saidas/cg2d11g.cpp.png");
}
