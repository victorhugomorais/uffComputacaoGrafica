#include "Graphics3D.h"
#include "SimpleShader.h"
#include "bezier.h"
#include "transforms.h"

int main(){
	vec3 CP[4] = {
		{0, 0, 0}, 	{1, 0, 0}, 
		{1, 1, 1}, 	{0, 0, 1}
	};
	unsigned int N = 50;
	std::vector<vec3> P = sample_cubic_bezier(CP, N);
	LineStrip L{N};
	
	SimpleShader shader;
	shader.C = blue;

	int w = 600, h = 600;
	Graphics3D G{w, h};
	mat4 View = lookAt({4,0,1}, {0, 0, 0}, {0, 0, 1});
	float a = w/(float)h;
	mat4 Projection = perspective(50, a, 0.1, 50);

	int nframes = 30;
	for(int k = 0; k < nframes; ++k){
		G.clear();
		G.initZBuffer();
	
		float theta = k*2*M_PI/nframes;
		mat4 Model = rotate_z(theta);
		shader.M = Projection*View*Model;
		G.draw(P, L, shader);

		char filename[50];
		sprintf(filename, "anim/output%03d.png", k);
		puts(filename);
		G.savePNG(filename);
	}
}
