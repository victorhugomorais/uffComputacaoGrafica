#include "Graphics2D.h"
#include "matrix.h"
#include "transforms.h"

int main(){
	int w = 600, h = 600;

	mat4 Model = rotate_y(0.1)*translate(-0.5, -0.5, -0.5);
	mat4 View = lookAt({0, 1, 2}, {0, 0, 0}, {0, 1, 0});
	mat4 Projection = orthogonal(-1.2, 1.2, -1.2, 1.2, 2, 10);
	//mat4 Projection = frustum(-0.7, 0.7, -0.7, 0.7, 2, 10);
	mat4 Screen = {
		w/2.0f,      0,   0, (w-1)/2.0f,
		     0, h/2.0f,   0, (h-1)/2.0f,
		     0,      0,   1,          0,
		     0,      0,   0,          1
	};
	mat4 M = Screen*Projection*View*Model;

	std::vector<vec3> V = {
		{0, 0, 0}, {1, 0, 0}, {1, 1, 0}, {0, 1, 0},
		{0, 0, 1}, {1, 0, 1}, {1, 1, 1}, {0, 1, 1},
	};

	std::vector<vec2> P(V.size());
	for(unsigned int i = 0; i < V.size(); i++){
		vec4 v = M*toVec4(V[i], 1);
		P[i] = {v(0)/v(3), v(1)/v(3)};
	}
	
	std::vector<unsigned int> indices = {
		0, 1,	1, 2,	2, 3,	3, 0,	4, 5,	5, 6,
		6, 7,	7, 4,	0, 4,	1, 5,	2, 6,	3, 7
	};
	Elements<Lines> L{indices};
	
	Graphics2D G(w, h);
	G.clear();
	G.draw(P, L, red);
	G.savePNG("saidas/test3d03.cpp.png");
}
