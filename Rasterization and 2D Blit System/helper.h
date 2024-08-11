#pragma once
#include "defines.h"

struct Rect {
	unsigned top, left, right, bottom;
};

struct Position {
	unsigned int x, y;
};

unsigned int TwoDto1D(unsigned int x, unsigned int y, unsigned int width) {
	return (x * width) + y;
}

unsigned int Lerp(unsigned int a, unsigned int b, float ratio) {
	return ((int)b - (int)a)*ratio + a;
}

// A is the new color and B is the original
unsigned int Perp(unsigned int a, unsigned int b) {
	//Store colors
	unsigned int newBlue = a & 0x000000ff;
	unsigned int newRed = (a & 0x00ff0000) >> 16;
	unsigned int newGreen = (a & 0x0000ff00) >> 8;
	unsigned int newAlpha = (a & 0xff000000) >> 24;

	unsigned int oldBlue = (b & 0x000000ff) ;
	unsigned int oldRed = (b & 0x00ff0000) >> 16;
	unsigned int oldGreen = (b & 0x0000ff00) >> 8;
	unsigned int oldAlpha = (b & 0xff000000) >> 24;

	// Lerp colors
	float ratio = (float)newAlpha / (0xff000000 >> 24);

	unsigned int finBlue = Lerp(oldBlue, newBlue, ratio);
	unsigned int finGreen = Lerp(oldGreen, newGreen, ratio);
	unsigned int finRed = Lerp(oldRed, newRed, ratio);
	unsigned int finAlpha = Lerp(oldAlpha, newAlpha, ratio);

	// Merge channels
	unsigned final = finBlue  | (finGreen << 8) | (finRed << 16) | (finAlpha << 24);

	return final;
};

unsigned int ColorConverter(unsigned int ogColor) {
	unsigned int blue = (ogColor & 0xff000000) >> 24;
	unsigned int red = (ogColor & 0x0000ff00) << 8;
	unsigned int green = (ogColor & 0x00ff0000) >> 8;
	unsigned int alpha = (ogColor & 0x000000ff) << 24;

	ogColor = blue | red | green | alpha;

	return ogColor;
}

void DrawPixel(unsigned int pos, unsigned int color) {
	if (pos < screen_height * screen_width) {
		//if ((color & 0x000000ff) == 255) {
			screenArray[pos] = Perp(ColorConverter(color), screenArray[pos]);
		//}
	}
}

void BLIT(const unsigned int* source, unsigned int source_width, unsigned int source_height, unsigned int desX, unsigned int desY, Rect sourceSprite) {

	unsigned int spritewidth = sourceSprite.right - sourceSprite.left;
	unsigned int spriteheight = sourceSprite.bottom - sourceSprite.top;

	unsigned int finalY = desY;
	unsigned int currY = sourceSprite.left;

	while (currY < sourceSprite.right) {
		unsigned int currX = sourceSprite.top;
		unsigned int finalX = desX;

		while (currX < sourceSprite.bottom) {

			DrawPixel(TwoDto1D(finalX, finalY, screen_width), source[TwoDto1D(currX, currY, source_width)]);

			finalX++;
			currX++;
		}

		finalY++;
		currY++;
	}
}


void ClearBuffer() {
	for (int i = 0; i < (screen_height * screen_width); i++) {
		screenArray[i] = 0x00000000;
	}
}