#pragma once
#include "shader.h"

VERTEX CartesionToScreen(VERTEX vert) {
	VERTEX noob = vert;

	noob.x = floor((noob.x + 1) * (screen_width / 2));
	noob.y = floor((1 - noob.y) * (screen_height / 2));

	return noob;
}

void DrawPixel(float newx, float newy, float newz, unsigned int color) {

	unsigned int pos = ((unsigned int)newy * screen_width) + (unsigned int)newx;

	if (pos < (sizeof(screenArray) / sizeof(*screenArray))) {
		if (newz < z[pos]) {
			screenArray[pos] = color;
			z[pos] = newz;
		}
	}
}

unsigned int TwoDOneD(unsigned int x, unsigned int y, unsigned int width) {
	return (x * width) + y;
}

unsigned int ColorConverter(unsigned int ogColor) {
	unsigned int blue = (ogColor & 0xff000000) >> 24;
	unsigned int red = (ogColor & 0x0000ff00) << 8;
	unsigned int green = (ogColor & 0x00ff0000) >> 8;
	unsigned int alpha = (ogColor & 0x000000ff) << 24;

	ogColor = blue | red | green | alpha;

	return ogColor;
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
		float currZ = Lerp(a.z, b.z, ratio);
		DrawPixel(currX, currY, currZ, color);
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

void DrawTexture(const unsigned int* image, unsigned int image_width, unsigned int image_height, Triangle dest, Triangle sourceImage) {
	// Get copies of the screen and image vertices
	VERTEX desA = dest.a;
	VERTEX desB = dest.b;
	VERTEX desC = dest.c;

	VERTEX selA = sourceImage.a;
	VERTEX selB = sourceImage.b;
	VERTEX selC = sourceImage.c;

	if (Vertex_Shader) {
		Vertex_Shader(desA);
		Vertex_Shader(desB);
		Vertex_Shader(desC);
	}

	desA = CartesionToScreen(desA);
	desB = CartesionToScreen(desB);
	desC = CartesionToScreen(desC);

	selA = CartesionToScreen(selA);
	selB = CartesionToScreen(selB);
	selC = CartesionToScreen(selC);

	// Destination
	float desStartX = min(desB.x, desA.x);
	desStartX = min(desStartX, desC.x);
	float desStartY = min(desB.y, desA.y);
	desStartY = min(desStartY, desC.y);
	float desEndX = max(desB.x, desA.x);
	desEndX = max(desEndX, desC.x);
	float desEndY = max(desB.y, desA.y);
	desEndY = max(desEndY, desC.y);

	// Selection Triangle
	float selStartX = min(selB.x, selA.x);
	selStartX = min(selStartX, selC.x);
	float selStartY = min(selB.y, selA.y);
	selStartY = min(selStartY, selC.y);
	float selEndX = max(selB.x, selA.x);
	selEndX = max(selEndX, selC.x);
	float selEndY = max(selB.y, selA.y);
	selEndY = max(selEndY, selC.y);

	float currSelY = selStartY;

	for (int i = desStartY; i <= desEndY; i++) {
		float currSelX = selStartX;

		for (int j = desStartX; j <= desEndX; j++) {
			VERTEX currDes = { j, i, 0, 0, 0, 0 };
			VERTEX currSel = { currSelX, currSelY, 0,0,0,0 };

			VERTEX byaDes = BarycentricCoordinates(desA, desB, desC, currDes);
			VERTEX byaSel = BarycentricCoordinates(selA, selB, selC, currSel);

			// Checks if the curr Destination point is in the Destination triangle
			if (byaDes.x >= 0 && byaDes.x <= 1 &&
				byaDes.y >= 0 && byaDes.y <= 1 &&
				byaDes.z >= 0 && byaDes.z <= 1) {


				float tu = BERP(selA.u, selB.u, selC.u, byaDes);
				int u = (tu * image_width);
				float tv = BERP(selA.v, selB.v, selC.v, byaDes);
				int v = (tv * image_height);
				float currZ = BERP(desA.z, desB.z, desC.z, byaDes);

				int index = TwoDOneD(u, v, image_width);
				unsigned int color = ColorConverter(image[index]);


				DrawPixel(currDes.x, currDes.y, currZ, color);
			}

			currSelX++;
		}

		currSelY++;
	}

}

void BetterBrute(VERTEX a, VERTEX b, VERTEX c, unsigned int color) {

	VERTEX copyA = a;
	VERTEX copyB = b;
	VERTEX copyC = c;

	if (Vertex_Shader) {
		Vertex_Shader(copyB);
		Vertex_Shader(copyC);
		Vertex_Shader(copyA);
	}

	copyA = CartesionToScreen(copyA);
	copyB = CartesionToScreen(copyB);
	copyC = CartesionToScreen(copyC);

	float startX = min(copyB.x, copyA.x);
	startX = min(startX, copyC.x);
	float startY = min(copyB.y, copyA.y);
	startY = min(startY, copyC.y);
	float endX = max(copyB.x, copyA.x);
	endX = max(endX, copyC.x);
	float endY = max(copyB.y, copyA.y);
	endY = max(endY, copyC.y);

	for (int i = startY; i <= endY; i++) {
		for (int j = startX; j <= endX; j++) {
			VERTEX curr = { j, i, 0, 0, 0, 0 };
			VERTEX bya = BarycentricCoordinates(copyA, copyB, copyC, curr);

			if (bya.x >= 0 && bya.x <= 1 &&
				bya.y >= 0 && bya.y <= 1 &&
				bya.z >= 0 && bya.z <= 1) {

				float currZ = BERP(copyA.z, copyB.z, copyC.z, bya);
				DrawPixel(curr.x, curr.y, currZ, color);
			}
		}
	}

}

void ClearBuffer() {
	for (int i = 0; i < (sizeof(screenArray) / sizeof(*screenArray)); i++) {
		screenArray[i] = 0x00000000;
		z[i] = 1;
	}
}