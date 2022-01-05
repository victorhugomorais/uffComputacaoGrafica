#ifndef MIX_COLOR_SHADER_H
#define MIX_COLOR_SHADER_H

struct MixColorShader{
	struct Varying{
		vec4 position;
		vec3 color;
	};
	friend Varying operator*(float t, Varying V){
		return {t*V.position, t*V.color};
	}
	friend Varying operator+(Varying U, Varying V){
		return {U.position + V.position, U.color + V.color};
	}

	mat4 M;
	vec3 pmin, pmax;
	std::array<Color, 8> C;
	
	template<typename Vertex>
	void vertexShader(Vertex in, Varying& out){
		vec4 pos = getPosition(in);
		out.position = M*pos;

		vec3 p = toVec3(pos);
		vec3 d = (p-pmin)/(pmax - pmin);
		float dx = d(0);
		float dy = d(1);
		float dz = d(2);

		Color C1 = bilerp(dx, dz, C[0], C[1], C[2], C[3]);
		Color C2 = bilerp(dx, dz, C[4], C[5], C[6], C[7]);
		out.color = toVec3(lerp(dy, C1, C2));
	}

	void fragmentShader(Varying V, Color& FragColor){
		FragColor = toColor(V.color);
	}
};

#endif
