#include "Graphics3D.h"
#include "SimpleShader.h"
#include "transforms.h"

int main(){
	std::vector<vec3> V = {
		{0, 0, 0},
		{1, 0, 0},
		{1, 1, 0},
		{0, 1, 0},
		{0, 0, 1},
		{1, 0, 1},
		{1, 1, 1},
		{0, 1, 1},
	};
	std::vector<unsigned int> indices = {
		0, 1,	1, 2,	2, 3,	3, 0,	4, 5,	5, 6,
		6, 7,	7, 4,	0, 4,	1, 5,	2, 6,	3, 7
	};
	Elements<Lines> Le{indices};
	
	mat4 Model = rotate_y(0.2)*rotate_x(0.1)*translate(-0.5, -0.5, -0.5);
	mat4 View = lookAt({0, 0, 2}, {0, 0, 0}, {0, 1, 0});
	mat4 Projection = orthogonal(-1, 1, -1, 1, 1, 10);

	SimpleShader shader;
	shader.M = Projection*View*Model;
	shader.C = blue;

	Graphics3D G{500, 500};
	G.clear();	
	G.draw(V, Le, shader);
	G.savePNG("output.png");
}
