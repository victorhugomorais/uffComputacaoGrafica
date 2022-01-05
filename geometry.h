#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vec.h"

inline float triArea(vec2 a, vec2 b, vec2 c){
	float aux;
	 aux = (((c(0) - a(0)) * (b(1) - a(1)))/2) - (((b(0) - a(0)) * (c(1) - a(1)))/2);
	return aux;
}

template<class Tri>
vec3 barycentric(vec2 p, const Tri& P){

	float aux1 = triArea(p,P[1],P[2]) / triArea(P[0],P[1],P[2]);

	float aux2 = triArea(P[0],p,P[2]) / triArea(P[0],P[1],P[2]);

	float aux3 = triArea(P[0],P[1],p) / triArea(P[0],P[1],P[2]);

	return {aux1, aux2, aux3};
}

template<class Tri>
bool is_inside(vec2 v, const Tri& P){
	float aT = triArea(P[0], P[1], P[2]);

	if(fabs(aT) < 1e-3){
		float M[] = {
			norm(P[0]-P[1]),
			norm(P[1]-P[2]),
			norm(P[2]-P[0])
		};

		float maxM = M[0];
		int i = 0, j = 1;

		if(M[1] > maxM){
			i = 1;
			j = 2;
			maxM = M[1];
		}

		if(M[2] > maxM){
			i = 2;
			j = 0;
			maxM = M[2];
		}

		return fabs(norm(v - P[i]) + norm(v - P[j]) - maxM) < 1e-3;
		
	}

	vec3 b = barycentric(v, P);
	return b(0) >= 0 && b(1) >= 0 && b(2) >= 0;
}

#endif
