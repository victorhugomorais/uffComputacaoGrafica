#include "Graphics3D.h"
#include "ColorShader.h"
#include "SimpleShader.h"
#include "VertexUtils.h"
#include "transforms.h"

int main(){
	Color darkred = {70, 50, 50};
	std::vector<Vec3Col> V1 = {
		{{0, 0, 0}, red},
		{{1, 0, 0}, red},
		{{1, 1, 0}, red},
		{{0, 1, 0}, red},
		{{0, 0, 1}, darkred},
		{{1, 0, 1}, darkred},
		{{1, 1, 1}, darkred},
		{{0, 1, 1}, darkred},
	};
	std::vector<Vec3Col> V2 = V1;
	std::vector<Vec3Col> V3 = V1;

	Color darkgreen = {50, 70, 50};
	Color darkblue = {50, 50, 70};
	for(int i = 0; i < 8; i++){
		if(i < 4){
			V2[i].color = green;
			V3[i].color = blue;
		}else{
			V2[i].color = darkgreen;
			V3[i].color = darkblue;
		}
	}
	
	std::vector<unsigned int> indices = {
		0, 2, 1,	0, 3, 2, // back
 		4, 5, 7,	5, 6, 7, // front
		5, 1, 6,	1, 2, 6, // right
		0, 4, 3,	4, 7, 3, // left
		0, 1, 4,	1, 5, 4, // down
		2, 3, 6,	3, 7, 6  // up
	};
	Elements<Triangles> Te{indices};

	int w = 1280, h = 720;
	Graphics3D G{w, h};
	
	// Model Matrix
	mat4 Model1 = translate(-1, 0, 0);
	mat4 Model2 = translate(1, 0, -1)*rotate_y(0.4);
	mat4 Model3 = translate(1, 0, 1)*rotate_y(-0.3)*scale(0.3, 1.8, 1);
	
	// Projection Matrix
	mat4 Projection = perspective(50, w/(float)h, .1, 10);

	int nframes = 60;
	for(int k = 0; k < nframes; ++k){
		G.clear();
		G.initZBuffer();

		// View Matrix
		float theta = k*2*M_PI/nframes;
		vec3 pos = {4*cos(theta), 3, 4*sin(theta)};
		mat4 View = lookAt(pos, {0, 0, 0}, {0, 1, 0});

		ColorShader shader;
		shader.M = Projection*View*Model1;
		G.draw(V1, Te, shader);
		
		shader.M = Projection*View*Model2;
		G.draw(V2, Te, shader);

		shader.M = Projection*View*Model3;
		G.draw(V3, Te, shader);

		char filename[20];
		sprintf(filename, "anim/output%03d.png", k);
		puts(filename);
		G.savePNG(filename);
	}
}
