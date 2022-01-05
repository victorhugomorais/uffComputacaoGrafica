#include "Graphics3D.h"

struct Shader{
    using Varying = vec2;

    void vertexShader(vec2 v, Varying& out){
	    out = v;
	};

    void fragmentShader(Varying, Color& fragColor){
        fragColor = blue;
    }
};

int main(){
    Shader shader;

	std::vector<vec2> V= {
		{-0.8, -0.6}, {-0.6,  0.8}, {-0.2, -0.6},
		{ 0.0,  0.0}, { 0.6,  0.8},	{ 0.8, -0.8},
	};
    Triangles T{V.size()};
  
    Graphics3D G{500, 500};
    G.clear();
    G.draw(V, T, shader);
	G.savePNG("output.png");
}
