#ifndef GRAPHICS2D_H
#define GRAPHICS2D_H

#include <vector>
#include "geometry.h"
#include "Image.h"
#include "VertexUtils.h"
#include "Primitives.h"
#include "rasterization.h"
#include "Clip2D.h"
	
class Graphics2D{
	Image img;

	public:
	Graphics2D(int w, int h) : img{w, h}{}

	void clear(Color col = white){
		img.fill(col);
	}
	
	void savePNG(std::string filename){
		img.savePNG(filename);	
	}
	
	template<class Prims>
	void draw(const std::vector<vec2>& V, const Prims& P, Color color){
		std::vector<Vec2Col> VC;
		for(vec2 v: V)
			VC.push_back({v, color});
		draw(VC, P);
	}

	template<class Prims>
	void draw(const std::vector<Vec2Col>& V, const Prims& P){
		ClipRectangle R = {-0.5f, -0.5f, img.width-0.5f, img.height-0.5f};
		for(auto primitive: clip(assemble(P, V), R))
			drawPrimitive(primitive);
	}

	void paint(Pixel p, Color c){
		if(p.x >= 0 && p.y >= 0 && p.x < img.width && p.y < img.height)
			img(p.x,p.y) = c;
	}

	void drawPrimitive(Line<Vec2Col> line){
		vec2  L[] = { line[0].position, line[1].position };
		Color C[] = { line[0].color,    line[1].color    };

		for(Pixel p: rasterizeLine(L)){
			float t = find_mix_param(toVec2(p), L[0], L[1]);
			Color color = lerp(t, C[0], C[1]);
			paint(p, color);
		};
	}


	void drawPrimitive(Triangle<Vec2Col> tri){
        vec2 L[] = {tri[0].position,  tri[1].position, tri[2].position};
        Color C[] = {tri[0].color,tri[1].color,tri[2].color};
        //Convertendo cores em vec3
        vec3 vs0 = toVec3(C[0]),vs1 = toVec3(C[1]),vs2 = toVec3(C[2]);    
        //convertendo para matriz para realizar os calculos mais abaixo
        mat3x3 A = toMat(vs0,vs1,vs2); 
        //Rasterizando o triangulo
        for (Pixel i : rasterizeTriangle(L))
        {    
            // Coordenadas baricêntricas
            vec3 x = barycentric(toVec2(i),L);
            // fazendo operações com cores em vec3 * mat3x3
            Color cor = toColor(A * x);
            paint(i,cor);
        }        
    }
	
	
};

#endif
