#include "Graphics2D_v1.h"
#include "bezier.h"
#include "matrix.h"

int main(){
	std::vector<vec2> CP = loadCurve("borboleta.txt");
	std::vector<vec2> P = sample_cubic_bezier_spline(CP, 30);

	vec2 v = {400, 300};
	mat3 T = {
		1.0, 0.0, v(0),
		0.0, 1.0, v(1),
		0.0, 0.0, 1.0
	};
	
	mat3 Ti = {
		1.0, 0.0, -v(0),
		0.0, 1.0, -v(1),
		0.0, 0.0, 1.0
	};
	
	float t = 3.5;
	mat3 R = {
		cos(t), -sin(t), 0.0,
		sin(t),  cos(t), 0.0,
		   0.0,     0.0, 1.0
	};

	LineStrip L{P.size()};
	
	Graphics2D G(800, 600);
	G.clear();
	G.draw(P, L, red);
	G.draw((T*R*Ti)*P, L, blue);
	G.savePNG("saidas/cg2d13g.cpp.png");
}
