#include "Graphics2D.h"
#include "bezier.h"

int main(){
	ClipRectangle R = {100, 200, 500, 400};

	std::vector<Vec2Col> P = {
		{{26, 168}, red},
		{{176, 245}, green},
		{{140, 122}, blue},
		{{340, 145}, red},
		{{576, 451}, orange},
		{{300, 300}, brown},
		{{124, 357}, magenta},
		{{154, 457}, black}
	};

	P = clip(P, R);

	LineLoop L{P.size()};

	std::vector<vec2> RP = {
		{R.x0, R.y0},  {R.x1, R.y0}, 
		{R.x1, R.y1},  {R.x0, R.y1}, 
	};
	LineLoop LR{4};

	Graphics2D G(600, 600);
	G.clear();
	G.draw(RP, LR, Color{220, 220, 220});
	G.draw(P, L);
	
	G.savePNG("saidas/testClipping02.cpp.png");
}
