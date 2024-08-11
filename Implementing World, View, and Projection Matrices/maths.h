#pragma once
#include "defines.h"

struct VERTEX {
	float x, y, z, w;
	unsigned int color;
};

struct MATRIX {
	float a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p;
};

struct Line {
	VERTEX startPoint;
	VERTEX endPoint;
	unsigned int color;
};


float Lerp(float start, float end, float ratio)
{
	return (end - start) * ratio + start;
}

VERTEX PerspectiveDivide(VERTEX vert) {
	VERTEX final;
	if (vert.w != 0) {
		final.x = vert.x / vert.w;
		final.y = vert.y / vert.w;
		final.z = vert.z / vert.w;
	}
	else {
		final = vert;
	}
	return final;
}

MATRIX IDENITYMAT = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

VERTEX VecMultMatrix(VERTEX vert, MATRIX matrix) {
	VERTEX fin = vert;

	fin.x = (vert.x * matrix.a) + (vert.y * matrix.e) + (vert.z * matrix.i) + (vert.w * matrix.m);
	fin.y = (vert.x * matrix.b) + (vert.y * matrix.f) + (vert.z * matrix.j) + (vert.w * matrix.n);
	fin.z = (vert.x * matrix.c) + (vert.y * matrix.g) + (vert.z * matrix.k) + (vert.w * matrix.o);
	fin.w = (vert.x * matrix.d) + (vert.y * matrix.h) + (vert.z * matrix.l) + (vert.w * matrix.p);

	return fin;
}

MATRIX MatXMat4(MATRIX x, MATRIX y) {
	MATRIX final;

	final.a = (x.a * y.a) + (x.b * y.e) + (x.c * y.i) + (x.d * y.m);
	final.b = (x.a * y.b) + (x.b * y.f) + (x.c * y.j) + (x.d * y.n);
	final.c = (x.a * y.c) + (x.b * y.g) + (x.c * y.k) + (x.d * y.o);
	final.d = (x.a * y.d) + (x.b * y.h) + (x.c * y.l) + (x.d * y.p);

	final.e = (x.e * y.a) + (x.f * y.e) + (x.g * y.i) + (x.h * y.m);
	final.f = (x.e * y.b) + (x.f * y.f) + (x.g * y.j) + (x.h * y.n);
	final.g = (x.e * y.c) + (x.f * y.g) + (x.g * y.k) + (x.h * y.o);
	final.h = (x.e * y.d) + (x.f * y.h) + (x.g * y.l) + (x.h * y.p);

	final.i = (x.i * y.a) + (x.j * y.e) + (x.k * y.i) + (x.l * y.m);
	final.j = (x.i * y.b) + (x.j * y.f) + (x.k * y.j) + (x.l * y.n);
	final.k = (x.i * y.c) + (x.j * y.g) + (x.k * y.k) + (x.l * y.o);
	final.l = (x.i * y.d) + (x.j * y.h) + (x.k * y.l) + (x.l * y.p);

	final.m = (x.m * y.a) + (x.n * y.e) + (x.o * y.i) + (x.p * y.m);
	final.n = (x.m * y.b) + (x.n * y.f) + (x.o * y.j) + (x.p * y.n);
	final.o = (x.m * y.c) + (x.n * y.g) + (x.o * y.k) + (x.p * y.o);
	final.p = (x.m * y.d) + (x.n * y.h) + (x.o * y.l) + (x.p * y.p);

	return final;

}

MATRIX InverseMatrix(MATRIX mat) {
	MATRIX final;
	float temp;

	// Moving 3x3 part
	temp = mat.e;
	mat.e = mat.b;
	mat.b = temp;

	temp = mat.i;
	mat.i = mat.c;
	mat.c = temp;

	temp = mat.g;
	mat.g = mat.j;
	mat.j = temp;

	// Multiply vertex by new 3x3
	float x = -1 * (round((mat.m * mat.a) + (mat.n * mat.e) + (mat.o * mat.i)));
	float y = -1 * (round((mat.m * mat.b) + (mat.n * mat.f) + (mat.o * mat.j)));
	float z = -1 * (round((mat.m * mat.c) + (mat.n * mat.g) + (mat.o * mat.k)));

	final = mat;
	final.m = x;
	final.n = y;
	final.o = z;

	return final;
}

MATRIX Translation(float x, float y, float z) {
	MATRIX final = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, x, y, z, 1 };
	return final;
}

MATRIX Scaling(VERTEX size) {
	MATRIX final = { size.x, 0, 0, 0, 0, size.y, 0, 0, 0, 0, size.z, 0, 0, 0, 0, 1 };
	return final;
}

MATRIX XRotation(float deg) {
	float rad = deg * (PI / 180);

	MATRIX RotX = { 1, 0, 0, 0, 0, cos(rad), -sin(rad), 0, 0, sin(rad), cos(rad), 0, 0, 0, 0, 1 };
	return RotX;
}

MATRIX YRotation(float deg) {
	float rad = deg * (PI / 180);

	MATRIX rotY = { cos(rad), 0, -sin(rad), 0, 0, 1, 0, 0, sin(rad), 0, cos(rad), 0, 0, 0, 0, 1 };
	return rotY;
}

MATRIX ZRotation(float deg) {
	float rad = deg * (PI / 180);

	MATRIX rotZ = { cos(rad), -sin(rad), 0, 0, sin(rad), cos(rad), 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	return rotZ;
}

MATRIX PerspectiveProjection(float fov, float aspec, float np, float fp) {
	float deg = fov * (PI / 180);
	float Yscale = (1 / tan(deg / 2));
	float Xscale = Yscale * aspec;

	MATRIX final = { Xscale, 0, 0, 0, 0, Yscale, 0, 0, 0, 0, fp / (fp - np), 1, 0, 0, -((fp * np) / (fp - np)), 0 };
	return final;
}

MATRIX ViewMatrix() {
	MATRIX final = InverseMatrix(MatXMat4(Translation(0, 0, -1), XRotation(-18)));
	return final;
}

