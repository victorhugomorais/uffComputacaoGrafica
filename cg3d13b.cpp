#include "Graphics3D.h"
#include "ObjMesh.h"
#include "TextureShader.h"
#include "transforms.h"

int main(){
	ObjMesh mesh{"modelos/teapot.obj"};
	auto mesh_triangles = mesh.getTriangles();
	Triangles T{mesh_triangles.size()};

	TextureShader shader;
	shader.texture.img = Image{"bob.jpg"};
	shader.texture.filter = BILINEAR;
	shader.texture.wrapX = REPEAT;
	shader.texture.wrapY = REPEAT;
	
	int w = 1280, h = 720;
	Graphics3D G{w, h};
	
	mat4 View = lookAt({25, 25, 23}, {0.2, 8, 0}, {0, 1, 0});
	float a = w/(float)h;
	mat4 Projection = perspective(45, a, 0.1, 100);

	int nframes = 40;
	for(int k = 0; k < nframes; k++){
		G.clear();
		G.initZBuffer();
		
		float theta = k*2*M_PI/(nframes-1);
		mat4 Model = rotate_y(theta)*rotate_x(-M_PI/2);

		shader.M = Projection*View*Model;

		G.draw(mesh_triangles, T, shader);
		
		char filename[30];
		sprintf(filename, "anim/output%03d.png", k);
		puts(filename);
		G.savePNG(filename);
	}
}
