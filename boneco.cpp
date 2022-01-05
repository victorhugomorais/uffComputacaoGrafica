#include "Image.h"

float G(float x, float y, float cx, float cy, float s){
	float dx = x - cx;
	float dy = y - cy;
	return 100*exp(-(dx*dx + dy*dy)/(s*s));
}

float F(float x, float y){ //
	return 50 
    - G (x - 100, y,    205, 310, 60)  //barriga
    - G ( x - 100, y,   310, 220, 60)  //perna d
    - G ( x - 100, y,   100, 220, 60)  //perna e
    - G ( x-100, y-120, 200, 300, 60)  //torax
    - G ( x + 100, y -  100, 200 , 320 , 40) 
	//mao esquerda
    - G ( x - 200 , y - 100, 200, 300, 40) 
	//cotovelo direito
    - G ( x , y - 100,  190 , 300 , 45) 
	//cotovelo esquerdo
    - G ( x -280 , y -  100 , 200 , 320 , 40) 
	//mao direita
    - G ( x - 100, y -  225 , 200 , 320 , 60 );
	//cabeça;
}

int main(){
	Image img(600, 600);
	img.fill(white);
	for(int y = 0; y < 600; y++)
		for(int x = 0; x < 600; x++)
			if(F(x,y) <= 0)
				img(x,y) = red;
		

	img.savePNG("output.png");
}
