#include "Graphics3D.h"
#include "SimpleShader.h"
#include "transforms.h"

int main(){
	int m = 50, n = 50, N = m*n;

	float u0 = -5, u1 = 5, du = (u1-u0)/(m-1),
              v0 = -5, v1 = 5, dv = (v1-v0)/(n-1);

	std::vector<vec3> P(N);
	for(int i = 0; i < m; i++){
		for(int j = 0; j < n; j++){
			float u = u0 + i*du;
			float v = v0 + j*dv;

			int ij = i + j*m;
			P[ij] = {u, v, sin(u*v/4)};
		}
	}

	std::vector<unsigned int> indices;
	for(int i = 0; i < m-1; i++){
		for(int j = 0; j < n-1; j++){	
			unsigned int ij = i + j*m;
			indices.insert(indices.end(), {
				ij, ij+1, ij+m,
				ij+m+1, ij+m, ij+1
			});
		}
	}
	TriLines<Elements<Triangles>> L{indices};

	SimpleShader shader;
	shader.C = blue;

	int w = 800, h = 600;
	Graphics3D G{w, h};
	mat4 View = lookAt({10,10,10}, {0, 0, 0}, {0, 0, 1});
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
