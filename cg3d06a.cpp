#include "Graphics3D.h"
#include "SimpleShader.h"
#include "transforms.h"

int main(){
	unsigned int N = 150;
	float t0 = -20, t1 = 20;
	float dt = (t1-t0)/(N-1);

	std::vector<vec3> V(N);
	for(unsigned int i = 0; i < N; i++){
		float t = t0 + i*dt;
		V[i] = {cos(t), sin(t), t};
	}
	LineStrip L{N};
	
	int w = 600, h = 600;

	mat4 Model = scale(1, 1, 0.2);
	mat4 View = lookAt({10,0,3}, {0, 0, 0}, {0, 0, 1});
	float a = w/(float)h;
	mat4 Projection = perspective(50, a, 0.1, 50);

	SimpleShader shader;
	shader.M = Projection*View*Model;
	shader.C = blue;
	
	Graphics3D G{w, h};
	G.clear();
	G.initZBuffer();
	G.draw(V, L, shader);
	G.savePNG("output.png");
}

