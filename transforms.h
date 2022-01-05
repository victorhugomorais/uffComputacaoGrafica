#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "matrix.h"
#include "vec.h"

inline mat4 loadIdentity(){
    return Id<4>();
}

inline mat4 translate(vec3 u){
	return {
		1, 0, 0, u(0),
		0, 1, 0, u(1),
		0, 0, 1, u(2),
		0, 0, 0,    1
	};
}

inline mat4 translate(float x, float y, float z){
    return translate(vec3{x, y, z});
}

inline mat4 scale(float x, float y, float z){
	return {
		x, 0, 0, 0,
		0, y, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1
	};
}

inline mat4 rotate_x(float angle){
	float c = cos(angle);
	float s = sin(angle);

	return {
		1, 0,  0, 0,
		0, c, -s, 0,
		0, s,  c, 0,
		0, 0,  0, 1
	};
}

inline mat4 rotate_y(float angle){
	float c = cos(angle);
	float s = sin(angle);

	return {
		 c, 0, s, 0,
		 0, 1, 0, 0,
		-s, 0, c, 0,
		 0, 0, 0, 1
	};
}

inline mat4 rotate_z(float angle){
	float c = cos(angle);
	float s = sin(angle);

	return {
		c, -s, 0, 0,
		s,  c, 0, 0,
		0,  0, 1, 0,
		0,  0, 0, 1
	};
}

// inline mat4 rotate(vec3 n, float theta){
// 	/* TAREFA - aula 10 */
// 	return loadIdentity();
// }

inline mat4 rotate(vec3 n, float theta)
{
	//Normalizando vetor n;
	n = normalize(n);

	//Fórmula de rotação
	vec3 R0 = ((1 - cos(theta)) * dot((vec3){1, 0, 0}, n) * n + (cos(theta) * (vec3){1, 0, 0}) + (sin(theta) * cross(n, (vec3){1, 0, 0})));

	vec3 R1 = ((1 - cos(theta)) * dot((vec3){0, 1, 0}, n) * n) + (cos(theta) * (vec3){0, 1, 0}) + (sin(theta) * cross(n, (vec3){0, 1, 0}));

	vec3 R2 = ((1 - cos(theta)) * dot((vec3){0, 0, 1}, n) * n) + (cos(theta) * (vec3){0, 0, 1}) + (sin(theta) * cross(n, (vec3){0, 0, 1}));

	mat4 R = {
		R0(0), R1(0), R2(0), 0,
		R0(1), R1(1), R2(1), 0,
		R0(2), R1(2), R2(2), 0,
		0, 0, 0, 1};

	return R;
}

// inline mat4 lookAt(vec3 eye, vec3 center, vec3 up){
// 	/* TAREFA - AULA 11 */
// 	return loadIdentity();
// }

inline mat4 lookAt(vec3 O, vec3 C, vec3 Up)
{
	//Normalizando vetor Up
	Up = normalize(Up);

	//Criando vetor unitário f = CO / ||CO||
	vec3 CO = (C - O);
	vec3 f = {CO(0) / norm(CO), CO(1) / norm(CO), CO(2) / norm(CO)};

	//Guardando produto vetorial numa variável para facilitar a divisão
	vec3 FcrossUp = cross(f, Up);
	vec3 s = {FcrossUp(0) / norm(FcrossUp), FcrossUp(1) / norm(FcrossUp), FcrossUp(2) / norm(FcrossUp)};

	//Vetor u = sXf
	vec3 u = cross(s, f);


	//Matriz ortogonal
	mat4 m1 = {
		s(0), s(1), s(2), 0,
		u(0), u(1), u(2), 0,
		-f(0), -f(1), -f(2), 0,
		0, 0, 0, 1};

	//Matriz translação
	mat4 m2 = {
		1, 0, 0, -(O(0)),
		0, 1, 0, -(O(1)),
		0, 0, 1, -(O(2)),
		0, 0, 0, 1};

	return (m1 * m2);
}



inline mat4 orthogonal(float l, float r, float b, float t, float n, float f){
	return {
		2/(r-l),      0,     0,      (l+r)/(l-r),
			0,  2/(t-b),     0,      (b+t)/(b-t),
			0,        0, -2/(f-n),   (n+f)/(n-f),
			0,        0,      0,               1
	};	
}

inline mat4 frustum(float l, float r, float b, float t, float n, float f){
	mat4 Persp = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0,-(n+f)/n, -f,
		0, 0, -1/n, 0
	};
	mat4 Volume = {
		2/(r-l),      0,     0,      (l+r)/(l-r),
			0,  2/(t-b),     0,      (b+t)/(b-t),
			0,        0, 2/(f-n),    (n+f)/(n-f),
			0,        0,      0,               1
	};	
	return Volume*Persp;
}

inline mat4 perspective(float fovy, float aspect, float Near, float Far){
	/* TAREFA - AULA 12*/

//CONVERTER P RADIANO
	float anguloR = (fovy * M_PI) / 180; 

	//VOLUME DE VISAO EM PERSPECTIVA DADA NO SLIDE
	float top = fabs(Near) * tan(anguloR / 2);
	float bot = -top;

	//RAZÃO DE ASPECTO
	float right = top * aspect;
	float left = -right;

	return frustum(left, right, bot, top, Near, Far);

}

#endif