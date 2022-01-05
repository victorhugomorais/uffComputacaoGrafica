#include "Graphics3D.h"
#include "bezier.h"
#include "SimpleShader.h"
#include "transforms.h"

vec3 c0(float t){
	vec3 P[4] = {
		{ 1,0,0},
		{ 1,0,1},
		{ 0,0,1},
		{ 0,0,0},
	};
	return cubic_bezier(P, t);
}

vec3 c1(float t){
	vec3 P[4] = {
		{ 1,2,-2},
		{ 1,1,-2},
		{ 0,1,-2},
		{ 0,2,-2},
	};
	return cubic_bezier(P, t);
}

vec3 d0(float t){
	vec3 P[4] = {
		{ 1, 0, 0},
		{ 1, 1, 0},
		{ 1,2,-1},
		{ 1,2,-2},
	};
	return cubic_bezier(P, t);
}

vec3 d1(float t){
	vec3 P[4] = {
		{ 0, 0, 0},
		{ 0, 1, 0},
		{ 0, 2, -1},
		{ 0, 2, -2},
	};
	return cubic_bezier(P, t);
}

vec3 coons(float s, float t){
	vec3 Lc = lerp(t, c0(s), c1(s));
	vec3 Ld = lerp(s, d0(t), d1(t));
	vec3 B = bilerp(s, t, c0(0), c0(1), c1(0), c1(1));
	return Lc + Ld - B;
}

int main(){
	unsigned int m = 20, n = 20, N = m*n;

	float u0 = 0, u1 = 1, du = (u1-u0)/(m-1),
              v0 = 0, v1 = 1, dv = (v1-v0)/(n-1);

	std::vector<vec3> V(N);
	for(unsigned int i = 0; i < m; i++){
		for(unsigned int j = 0; j < n; j++){
			float u = u0 + i*du;
			float v = v0 + j*dv;

			unsigned int ij = i + j*m;
			V[ij] = coons(u, v);
		}
	}

	std::vector<unsigned int> indices;
	for(unsigned int i = 0; i < m; i++){
		for(unsigned int j = 0; j < n; j++){	
			unsigned int ij = i + j*m;
			if(i < m-1){
				indices.push_back(ij);
				indices.push_back(ij+1);
			}
			
			if(j < n-1){
				indices.push_back(ij);
				indices.push_back(ij+m);
			}
		}
	}
	Elements<Lines> L{indices};

	int w = 600, h = 600;
	Graphics3D G{w, h};
	mat4 View = lookAt({5, 5 ,1}, {0, 0, 0}, {0, 0, 1});
	float a = w/(float)h;
	mat4 Projection = perspective(50, a, 0.1, 50);

	SimpleShader shader;
	shader.C = blue;

	int nframes = 30;
	for(int k = 0; k < nframes; ++k){
		G.clear();
		G.initZBuffer();

		float theta = k*2*M_PI/nframes;
		mat4 Model = rotate_z(theta);

		shader.M = Projection*View*Model;

		G.draw(V, L, shader);

		char filename[30];
		sprintf(filename, "anim/output%03d.png", k);
		puts(filename);
		G.savePNG(filename);
	}
}
