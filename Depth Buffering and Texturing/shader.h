#pragma once
#include "maths.h"

void(*Vertex_Shader)(VERTEX& v) = 0;

MATRIX WORLD, VIEW, PROJ;

void VS_WORLD(VERTEX& v) {
	v = VecMultMatrix(v, WORLD);
	v = VecMultMatrix(v, VIEW);
	v = VecMultMatrix(v, PROJ);

	v.x /= v.w;
	v.y /= v.w;
	v.z /= v.w;
}