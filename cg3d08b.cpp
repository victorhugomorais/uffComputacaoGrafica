#include "Graphics3D.h"
#include "bezier.h"
#include "ColorShader.h"
#include "VertexUtils.h"
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

	std::vector<Vec3Col> V(N);
	for(unsigned int i = 0; i < m; i++){
		for(unsigned int j = 0; j < n; j++){
			float u = u0 + i*du;
			float v = v0 + j*dv;

			int ij = i + j*m;
			V[ij].position = coons(u, v);
			
			float s = i/(m-1.0);
			float t = j/(n-1.0);
			V[ij].color = bilerp(s, t, red, blue, green, yellow);
		}
	}

	std::vector<unsigned int> indices;
	for(unsigned int i = 0; i < m-1; i++){
		for(unsigned int j = 0; j < n-1; j++){	
			unsigned int ij = i + j*m;
			indices.insert(indices.end(), {
				ij, ij+1, ij+m,
				ij+m+1, ij+m, ij+1
			});
		}
	}
	Elements<Triangles> T{indices};

	int w = 600, h = 600;
	Graphics3D G{w, h};
	mat4 View = lookAt({5, 5 ,1}, {0, 0, 0}, {0, 0, 1});
	float a = w/(float)h;
	mat4 Projection = perspective(50, a, 0.1, 50);

	int nframes = 30;
	for(int k = 0; k < nframes; ++k){
		G.clear();
		G.initZBuffer();

		float theta = k*2*M_PI/nframes;
		mat4 Model = rotate_z(theta);

		ColorShader shader;
		shader.M = Projection*View*Model;

		G.draw(V, T, shader);

		char filename[30];
		sprintf(filename, "anim/output%03d.png", k);
		puts(filename);
		G.savePNG(filename);
	}
}
