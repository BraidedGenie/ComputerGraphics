#pragma once
#include "shader.h"

VERTEX CartesionToScreen(VERTEX vert) {
	VERTEX noob = vert;

	noob.x = floor((noob.x + 1) * (screen_width / 2));
	noob.y = floor((1 - noob.y) * (screen_height / 2));

	return noob;
}

void DrawPixel(float newx, float newy, unsigned int color) {

	unsigned int pos = ((unsigned int)newy * screen_width) + (unsigned int)newx;

	if (pos < (sizeof(screenArray) / sizeof(*screenArray))) {
		screenArray[pos] = color;
	}
}

unsigned int TwoDOneD(unsigned int x, unsigned int y, unsigned int width) {
	return (x * width) + y;
}

void Parametric(VERTEX a, VERTEX b, unsigned int color) {

	float deltaX = abs(b.x - a.x);
	float deltaY = abs(b.y - a.y);
	float total = (deltaX > deltaY) ? deltaX : deltaY;

	for (int i = 0; i < total; i++)
	{
		float ratio = (float)i / total;
		float currX = Lerp(a.x, b.x, ratio);
		float currY = Lerp(a.y, b.y, ratio);
		DrawPixel(currX, currY, color);
	}
}


void DrawLine(Line line) {

	VERTEX copyA = line.startPoint;
	VERTEX copyB = line.endPoint;

	if (Vertex_Shader) {
		Vertex_Shader(copyA);
		Vertex_Shader(copyB);
	}

	copyA = CartesionToScreen(copyA);
	copyB = CartesionToScreen(copyB);

	Parametric(copyA, copyB, line.color);
}

void ClearBuffer() {
	for (int i = 0; i < (sizeof(screenArray) / sizeof(*screenArray)); i++) {
		screenArray[i] = 0x00000000;
	}
}