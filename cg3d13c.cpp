#include "Graphics3D.h"
#include "TextureShader.h"
#include "ObjMesh.h"
#include "transforms.h"

int main(){
	std::string path = "modelos/train-toy-cartoon/";
	ObjMesh mesh{path+"train-toy-cartoon.obj"};
	auto mesh_triangles = mesh.getTriangles();

	int w = 800, h = 600;
	Graphics3D G{w, h};
	G.clear();
	G.initZBuffer();

	float a = w/(float)h;
	mat4 Projection = perspective(45, a, 0.1, 100);
	mat4 View = lookAt({1, 1, 1}, 30*mesh.center(), {0, 1, 0});
	mat4 Model = rotate_y(.2)*scale(30, 30, 30);

	TextureShader shader;
	shader.M = Projection*View*Model;
	shader.texture.filter = BILINEAR;
	
	for(auto range: mesh.getMaterials()){
		shader.texture.img = Image{path + range.mat.map_Kd};
		TrianglesRange T{range.first, range.count};
		G.draw(mesh_triangles, T, shader);
	}

	G.savePNG("output.png");
}
