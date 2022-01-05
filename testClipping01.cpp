#include "Graphics2D.h"
#include "bezier.h"

int main(){
	ClipRectangle R = {100, 200, 500, 400};

	std::vector<Vec2Col> P = {
		{{26, 168}, red},
		{{176, 245}, green},
		{{140, 122}, blue},
		{{340, 145}, red},
		{{576, 451}, yellow},
		{{300, 300}, cyan},
		{{124, 357}, green},
		{{154, 457}, black}
	};

	LineStrip L{P.size()};

	std::vector<vec2> RP = {
		{R.x0, R.y0},  {R.x1, R.y0}, 
		{R.x1, R.y1},  {R.x0, R.y1}, 
	};
	LineLoop LR{4};

	
	Graphics2D G(800, 600);
	G.clear();
	G.draw(RP, LR, blue);
	
	//for(Line<Vec2Col> line: assemble(L, P))
	for(Line<Vec2Col> line: clip(assemble(L, P), R))
		G.drawPrimitive(line);

	G.savePNG("saidas/testClipping01.cpp.png");
}
