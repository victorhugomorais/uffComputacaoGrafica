#ifndef RASTERIZATION_H
#define RASTERIZATION_H

#include <algorithm>
#include <cmath>
#include "vec.h"
#include "geometry.h"

//////////////////////////////////////////////////////////////////////////////

struct Pixel{
	int x, y;
};

inline Pixel toPixel(vec2 u){
	return { (int)round(u(0)), (int)round(u(1)) };
}

inline vec2 toVec2(Pixel p){
	return {(float)p.x, (float)p.y};
}

//////////////////////////////////////////////////////////////////////////////

template<class Line>
std::vector<Pixel> rasterizeLine(const Line& P){
	//return simple(P[0], P[1]);

	return dda(P[0], P[1]);

	//return bresenham(toPixel(P[0]), toPixel(P[1]));
}

//////////////////////////////////////////////////////////////////////////////

inline std::vector<Pixel> simple(vec2 A, vec2 B){
	std::vector<Pixel> out;
	vec2 d = B - A;
	float m = d(1)/d(0);
	float b = A(1) - m*A(0);

	int x0 = std::round(A(0));
	int x1 = std::round(B(0));

	for(int x=x0; x <= x1; x++){
		int y = round(m*x + b);
		out.push_back({x, y});
	}
	return out;
}

//////////////////////////////////////////////////////////////////////////////

inline std::vector<Pixel> dda(vec2 A, vec2 B){
	vec2 dif = B - A;
	float delta = std::max(fabs(dif(0)), fabs(dif(1)));

	vec2 d = (1/delta)*dif;
	vec2 p = A;

	std::vector<Pixel> out;
	for(int i = 0; i <= delta; i++){
		out.push_back(toPixel(p));
		p = p + d;
	}
	return out;
}

//////////////////////////////////////////////////////////////////////////////

inline std::vector<Pixel> bresenham_base(int dx, int dy){
	std::vector<Pixel> out;

	int D = 2*dy - dx; 
	int y = 0;
	for(int x = 0; x <= dx; x++){
		out.push_back({x, y});
		if(D > 0){
			y++;
			D -= 2*dx;
		}
		D += 2*dy;
	}
	return out;
}

inline std::vector<Pixel> bresenham(int dx, int dy){
	std::vector<Pixel> out;

	if(dx >= dy){
		out = bresenham_base(dx, dy);
	}else{
		out = bresenham_base(dy, dx);
		for(Pixel& p: out)
			p = {p.y, p.x};
	}
	return out;
}

inline std::vector<Pixel> bresenham(Pixel p0, Pixel p1){
	if(p0.x > p1.x)
		std::swap(p0, p1);

	std::vector<Pixel> out = bresenham(p1.x - p0.x, abs(p1.y - p0.y));

	int s = (p0.y <= p1.y)? 1: -1;

	for(Pixel& p: out)
		p = {p0.x + p.x, p0.y + s*p.y};

	return out;
}

//////////////////////////////////////////////////////////////////////////////

template<class Tri>
std::vector<Pixel> rasterizeTriangle(const Tri& P){
	//return simple_rasterize_triangle(P);
	return scanline(P);
}

//////////////////////////////////////////////////////////////////////////////
template<class Tri>
std::vector<Pixel> simple_rasterize_triangle(const Tri& P){
	vec2 A = P[0];
	vec2 B = P[1];
	vec2 C = P[2];

	int xmin =  ceil(std::min({A(0), B(0), C(0)}));
	int xmax = floor(std::max({A(0), B(0), C(0)}));
	int ymin =  ceil(std::min({A(1), B(1), C(1)}));
	int ymax = floor(std::max({A(1), B(1), C(1)}));

	std::vector<Pixel> out;
	Pixel p;
	for(p.y = ymin; p.y <= ymax; p.y++)
		for(p.x = xmin; p.x <= xmax; p.x++)
			if(is_inside(toVec2(p), P))
				out.push_back(p);
	return out;
}

//////////////////////////////////////////////////////////////////////////////
// template<class Tri>
// std::vector<Pixel> scanline(const Tri& P){
// 	/* TAREFA */

// vec2 A = P[0];
// vec2 B = P[1];
// vec2 C = P[2];

// int j = 0;
// float x1 = 0;
// float x2 = 0;
// float x3 = 0;
// Pixel p;

// //pegamos os intervalos entre os maior x e o menor x usando teto e base 
// 	int xmin =  ceil(std::min({A(0), B(0), C(0)}));
// 	int xmax = floor(std::max({A(0), B(0), C(0)}));
// //pegamos os intervalos entre os maior y e o menor y usando teto e base 
// 	int ymin =  ceil(std::min({A(1), B(1), C(1)}));
// 	int ymax = floor(std::max({A(1), B(1), C(1)}));

// 	std::vector<Pixel> out;


// //usamos um for pra percorrer cada linha e utilizamos a equação da reta para calcular os x1 a x3 que seriam as interseçõies entre as linhas do scanline e o triangulo
// for( j = ymin; j <=ymax ; j++){
// x1 = (j - A(1)) * ( B(0) - A(0) ) / ( B(1) - A(1)) + A(0);
	
// x2 = (j - B(1)) * ( C(0) - B(0) ) / ( C(1) - B(1)) + B(0);
	
// x3 = (j - C(1)) * ( A(0) - C(0) ) / ( A(1) - C(1)) + C(0); 


// //se x1 e x2 estiverem dentro do intervalo
// if (ceil(x1) >= xmin && floor(x1) <= xmax && ceil(x2) >= xmin && floor(x2) <= xmax)
// {
// 	if(x1 > x2)
// 	{
// 		std::swap(x1, x2);
// 	}
// 	for(int x = ceil(x1); x <= floor(x2); x++)
// 		out.push_back({x,j});
// }

// //se x1 e x3 estiverem dentro do intervalo
// if (ceil(x1) >= xmin && floor(x1) <= xmax && ceil(x3) >= xmin && floor(x3) <= xmax)
// {
// 	if(x1 > x3){
// 		std::swap(x1, x3);
// 	}
// 	for(int x = ceil(x1); x <= floor(x3); x++)
// 		out.push_back({x,j});
// }

// //se x2 e x3 estiverem dentro do intervalo
// if(ceil(x2) >= xmin && floor(x2) <= xmax && ceil(x3) >= xmin && floor(x3) <= xmax)
// {
// 	if(x2 > x3){
// 		std::swap(x2, x3);
// 	}
// 	for(int x = ceil(x2); x <= floor(x3); x++)
// 		out.push_back({x,j});
// }

// 	return out;

// 	}

// }

template<class Tri>
std::vector<Pixel> scanline(const Tri& P){
	vec2 A = P[0];
	vec2 B = P[1];
	vec2 C = P[2];

	int xmin =  ceil(std::min({A(0), B(0), C(0)}));
	int xmax = floor(std::max({A(0), B(0), C(0)}));
	int ymin =  ceil(std::min({A(1), B(1), C(1)}));
	int ymax = floor(std::max({A(1), B(1), C(1)}));
	std::vector<Pixel> out;

	for (int i = ymin; i <= ymax; i++)
	{
		float x1 = (i - A(1)) * (B(0) - A(0)) / (B(1) - A(1)) + A(0);
		float x2 = (i - B(1)) * (C(0) - B(0)) / (C(1) - B(1)) + B(0);
		float x3 = (i - C(1)) * (A(0) - C(0)) / (A(1) - C(1)) + C(0);

		if (floor(x1) <= xmax && ceil(x1) >= xmin && floor(x2) <= xmax && ceil(x2) >= xmin)
		{
			if(x1 > x2){
				std::swap(x1,x2);
			}
			for (int k = ceil(x1); k <= floor(x2); k++)
			{
				out.push_back({k,i});
			}
			
		}
		if (floor(x1) <= xmax && ceil(x1) >= xmin && floor(x3) <= xmax && ceil(x3) >= xmin)
		{
			if(x1 > x3){
				std::swap(x1,x3);
			}
			for (int k = ceil(x1); k <= floor(x3); k++)
			{
				out.push_back({k,i});
			}
			
		}
		if (floor(x2) <= xmax && ceil(x2) >= xmin && floor(x3) <= xmax && ceil(x3) >= xmin)
		{
			if(x2 > x3){
				std::swap(x2,x3);
			}
			for (int k = ceil(x2); k <= floor(x3); k++)
			{
				out.push_back({k,i});
			}
			
		}
		
	}
	return out;
}

#endif
