#include "Graphics3D.h"
#include "TextureShader.h"
#include "ObjMesh.h"
#include "transforms.h"

class Mesh{
	std::vector<ObjMesh::Vertex> tris;
	std::vector<MaterialRange> materials;
	std::map<std::string, Image> texture_map;
	public:
	mat4 Model;

	Mesh(std::string obj_file, mat4 _Model, std::string default_texture = ""){
		ObjMesh mesh{obj_file};
		tris = mesh.getTriangles();

		MaterialInfo std_mat;
		std_mat.map_Kd = default_texture;

		materials = mesh.getMaterials(std_mat);

		for(MaterialRange range: materials)
			load_texture(mesh.path, range.mat.map_Kd);

		Model = _Model;
	}
	
	void load_texture(std::string path, std::string file){			
		if(file != "" && texture_map.find(file) == texture_map.end()){
			std::string img = path + file;
			std::cout << "read image " << img << '\n';
			texture_map[file] = Image{img};
		}
	}

	void get_texture(std::string file, Image& img) const{
		auto it = texture_map.find(file);
		img = (it != texture_map.end())? it->second: Image{};
	}

	void draw(Graphics3D& G, TextureShader& shader) const{
		for(MaterialRange range: materials){
			get_texture(range.mat.map_Kd, shader.texture.img);
			TrianglesRange T{range.first, range.count};
			G.draw(tris, T, shader);
		}
	}
};

int main(){
	Mesh mesh{
		"modelos/Wood Table/Old Wood Table.obj",
		loadIdentity()
	};
	
	int w = 800, h = 600;
	Graphics3D G{w, h};
	
	TextureShader shader;
	shader.texture.filter = BILINEAR;
	shader.texture.wrapX = REPEAT;
	shader.texture.wrapY = REPEAT;
	
	mat4 View = lookAt({10, 10, 10}, {0, 1, 0}, {0, 1, 0});
	float a = w/(float)h;
	mat4 Projection = perspective(45, a, 0.1, 1000);

	int nframes = 40;
	for(int k = 0; k < nframes; k++){
		G.clear();
		G.initZBuffer();
		
		float theta = k*2*M_PI/(nframes-1);
		mat4 Model = rotate_y(theta);
		shader.M = Projection*View*Model;

		mesh.draw(G, shader);
		
		char filename[30];
		sprintf(filename, "anim/output%03d.png", k);
		puts(filename);
		G.savePNG(filename);
	}
}
