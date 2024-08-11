#include "RasterSurface.h"
#include "Assets.h"

#pragma region Asset Position Settings
// Initalizing arrays
Position treePostion[11];
Rect TeleportFrames[64];

void BuildTrees() {
	// Set Positions
	treePostion[0] = { 24, 31 };
	treePostion[1] = { 93, 76 };
	treePostion[2] = { 210, 82 };
	treePostion[3] = { 272, 29 };
	treePostion[4] = { 389, 21 };

	treePostion[5] = { 24, 401 };
	treePostion[6] = { 152, 373 };
	treePostion[7] = { 210, 422 };
	treePostion[8] = { 338, 422 };

	treePostion[9] = { 24, 130 };
	treePostion[10] = { 22, 301 };

	// Draw
	for (int i = 0; i < 11; i++) {
		TreeSprite(treePostion[i].x, treePostion[i].y);
	}
}
void BuildBuilding() {
	DungeonSprite(120, 210);
}
void BuildBox() {
	MailboxSprite(400, 150);
}
void BuildTeleporterFrames() {
	unsigned int currPos = 0;

	for (int currX = 0; currX < teleporter_hit_width; currX += 128) {
		for (int currY = 0; currY < teleporter_hit_height; currY += 128) {
			Rect teleportFrame = {currY, currX, currX + 128, currY + 128};

			TeleportFrames[currPos] = teleportFrame;
			currPos++;

			if (currPos > 64) {
				return;
			}

		}
	}
}

void AnimateTeleportor() {

}
#pragma endregion


int main() {
	RS_Initialize("Jaimee Beard", screen_width, screen_height);
	BuildTeleporterFrames();
	unsigned int pos = 0;
	float counter = 0;
	XTime timer;
	timer.Restart();

	do {

		ClearBuffer();
		LoadGround();
		timer.Signal();
		counter += timer.Delta();

		BuildTrees();
		BuildBuilding();
		BuildBox();

		if (counter >= (1 / 30.f)) {
			counter = 0;
			pos++;

			if (pos > 64) {
				pos = 0;
			}
		}

		BLIT(teleporter_hit_pixels, teleporter_hit_width, teleporter_hit_height, 230, 200, TeleportFrames[pos]);

	} while (RS_Update(screenArray, screen_height * screen_width));

	RS_Shutdown();
}