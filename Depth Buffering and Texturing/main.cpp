#include <Windows.h>
#include "RasterSurface.h"
#include "Rasterization_Functions.h"

#pragma region Objects

Line GridLines[22];
Line Cube[12];
Triangle color[12];

// Grid
void BuildGrid() {

	// Horizontal Lines
	float startX = -.5;
	float endX = .5;
	int arrPos = 0;
	float currZ = -.5;

	for (int i = 0; i < 11; i++) {
		VERTEX startpoint = { startX, 0, currZ, 1 };
		VERTEX endpoint = { endX, 0, currZ, 1 };

		Line currLine = { startpoint, endpoint, 0xffffffff };
		Line copy = currLine;

		GridLines[arrPos] = currLine;

		// Move along
		arrPos++;
		currZ += .1;
	}

	// Verical Lines
	float startZ = -.5;
	float endZ = .5;
	arrPos = 11;
	float currX = -.5;

	for (int i = 11; i < 22; i++) {
		VERTEX startpoint = { currX, 0, startZ, 1 };
		VERTEX endpoint = { currX, 0, endZ, 1 };

		Line currLine = { startpoint, endpoint, 0xffffffff };
		Line copy = currLine;

		GridLines[arrPos] = currLine;

		arrPos++;
		currX += .1;
	}
}
void DrawGrid() {
	for (int i = 0; i < 22; i++)
	{
		DrawLine(GridLines[i]);
	}
}

// Cube
void BuildCube() {
	VERTEX startpoint;
	VERTEX endpoint;
	Line currLine;

	// Front Top
	startpoint = { -.25, .25, -.25, 1 };
	endpoint = { 0.25, .25, -.25, 1 };

	currLine = { startpoint, endpoint, 0x00ff00ff };
	Cube[0] = currLine;

	// Front Bottom
	startpoint = { -.25, -.25, -.25, 1 };
	endpoint = { .25, -.25, -.25, 1 };

	currLine = { startpoint, endpoint, 0x00ff00ff };
	Cube[1] = currLine;

	// Front Left
	startpoint = { -.25, -.25, -.25, 1 };
	endpoint = { -.25, .25, -.25, 1 };

	currLine = { startpoint, endpoint, 0x00ff00ff };
	Cube[2] = currLine;

	// Front Right
	startpoint = { .25, -.25, -.25, 1 };
	endpoint = { .25, .25, -.25, 1 };

	currLine = { startpoint, endpoint, 0x00ff00ff };
	Cube[3] = currLine;

	// Left Bottom
	startpoint = { -.25, -.25, -.25, 1 };
	endpoint = { -.25, -.25, .25, 1 };

	currLine = { startpoint, endpoint, 0x00ff00ff };
	Cube[4] = currLine;

	// Right Bottom
	startpoint = { .25, -.25, -.25, 1 };
	endpoint = { .25, -.25, .25, 1 };

	currLine = { startpoint, endpoint, 0x00ff00ff };
	Cube[5] = currLine;

	// Left Top
	startpoint = { -.25, .25, -.25, 1 };
	endpoint = { -.25, .25, .25, 1 };

	currLine = { startpoint, endpoint, 0x00ff00ff };
	Cube[6] = currLine;

	// Right Top
	startpoint = { .25, .25, -.25, 1 };
	endpoint = { .25, .25, .25, 1 };

	currLine = { startpoint, endpoint, 0x00ff00ff };
	Cube[7] = currLine;

	// Back Right
	startpoint = { .25, -.25, .25, 1 };

	endpoint = { .25, .25, .25, 1 };

	currLine = { startpoint, endpoint, 0x00ff00ff };
	Cube[8] = currLine;

	// Back Left
	startpoint = { -.25, -.25, .25, 1 };
	endpoint = { -.25, .25, .25, 1 };

	currLine = { startpoint, endpoint, 0x00ff00ff };
	Cube[9] = currLine;

	// Back Top
	startpoint = { -.25, .25, .25, 1 };
	endpoint = { .25, .25, .25, 1 };

	currLine = { startpoint, endpoint, 0x00ff00ff };
	Cube[10] = currLine;

	// Back Bottom
	startpoint = { -.25, -.25, .25, 1 };
	endpoint = { 0.25, -.25, .25, 1 };

	currLine = { startpoint, endpoint, 0x00ff00ff };
	Cube[11] = currLine;
}
void DrawCube() {
	for (int i = 0; i < sizeof(Cube) / sizeof(*Cube); i++) {
		DrawLine(Cube[i]);
	}
}


VERTEX OneselA = { 1, 0, 1, 1, 1, 0 };
VERTEX OneselB = { 0, 1, 1, 1, 0, 1 };
VERTEX OneselC = { 1, 0, 1, 1, 1, 1 };
Triangle selecOne = { OneselA, OneselB, OneselC };

VERTEX TwoselA = { 0, 1, 1, 1, 0, 1 };
VERTEX TwoselB = { 1, 0, 1, 1, 1, 0 };
VERTEX TwoselC = { 0, 0, 1, 1, 0, 0 };
Triangle selecTwo = { TwoselA, TwoselB, TwoselC };

void ColorGenerator() {
	// Front Triangles
	VERTEX a = { .25, -.25, -.25, 1 };
	VERTEX b = { -.25, .25, -.25, 1 };
	VERTEX c = { -.25, -.25, -.25, 1 };

	color[0] = { a, b, c, 0x00ff00ff };

	a = { -.25, .25, -.25, 1 };
	b = { .25, -.25, -.25, 1 };
	c = { .25, .25, -.25, 1 };

	color[1] = { a, b, c, 0x00ff00ff };

	// Left Triangles
	a = { -.25, -.25, .25, 1 };
	b = { -.25, .25, -.25, 1 };
	c = { -.25, -.25, -.25, 1 };

	color[2] = { a, b, c, 0x0000ffff };

	a = { -.25, .25, -.25, 1 };
	b = { -.25, -.25, .25, 1 };
	c = { -.25, .25, .25, 1 };

	color[3] = { a, b, c, 0x0000ffff };

	// Right Triangles
	a = { .25, -.25, .25, 1 };
	b = { .25, .25, -.25, 1 };
	c = { .25, -.25, -.25, 1 };

	color[4] = { a, b, c, 0xff0000ff };

	a = { .25, .25, -.25, 1 };
	b = { .25, -.25, .25, 1 };
	c = { .25, .25, .25, 1 };

	color[5] = { a, b, c, 0xff0000ff };

	//Bottom Triangles
	a = { .25, -.25, -.25, 1 };
	b = { -.25, -.25, .25, 1 };
	c = { -.25, -.25, -.25, 1 };

	color[6] = { a, b, c, 0x00ffffff };

	a = { -.25, -.25, .25, 1 };
	b = { .25, -.25, -.25, 1 };
	c = { .25, -.25, .25, 1 };

	color[7] = { a, b, c, 0x00ffffff };

	// Top Triangles
	a = { .25, .25, -.25, 1 };
	b = { -.25, .25, .25, 1 };
	c = { -.25, .25, -.25, 1 };

	color[8] = { a, b, c, 0x0000ff00 };

	a = { -.25, .25, .25, 1 };
	b = { .25, .25, -.25, 1 };
	c = { .25, .25, .25, 1 };

	color[9] = { a, b, c, 0x0000ff00 };

	// Back Triangles
	a = { .25, -.25, .25, 1 };
	b = { -.25, .25, .25, 1 };
	c = { -.25, -.25, .25, 1 };

	color[10] = { a, b, c, 0x00ff0000 };

	a = { -.25, .25, .25,1 };
	b = { .25, -.25, .25, 1 };
	c = { .25, .25, .25, 1 };

	color[11] = { a, b, c, 0x00ff0000 };
}

#pragma endregion


int main() {
	RS_Initialize("Jaimee Beard", screen_width, screen_height);
	BuildGrid();
	BuildCube();
	ColorGenerator();

	float RotAngle = 0;

	do {
		ClearBuffer();

		RotAngle += .1;
		Vertex_Shader = VS_WORLD;
		WORLD = IDENITYMAT;
		VIEW = ViewMatrix();
		PROJ = PerspectiveProjection(90, (float)screen_height / screen_width, .1, 10);
		DrawGrid();

		WORLD = MatXMat4(YRotation(RotAngle), Translation(0, .25, 0));

		// Draawing Texture 
		for (int i = 0; i < sizeof(color) / sizeof(*color); i += 2) {
			Triangle bottomTri = { color[i].a, color[i].b, color[i].c };
			Triangle topTri = { color[i + 1].a, color[i + 1].b, color[i + 1].c };
			DrawTexture(flower_pixels, flower_width, flower_height, bottomTri, selecOne);
			DrawTexture(flower_pixels, flower_width, flower_height, topTri, selecTwo);
		}

	} while (RS_Update(screenArray, screen_width * screen_height));

	RS_Shutdown();
}