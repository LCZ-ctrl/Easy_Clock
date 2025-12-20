#include <iostream>
#include <raylib.h>
#include "clock.h"

int main() {
	const int WINDOW_WIDTH = 600;
	const int WINDOW_HEIGHT = 600;
	Color LIGHT_BLUE = { 225, 239, 240, 255 };

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Clock");
	Image icon = LoadImage("Graphics/clock.png");
	SetWindowIcon(icon);
	UnloadImage(icon);

	SetTargetFPS(15);

	Clock clock{ 250, {300, 300} };

	while (WindowShouldClose() == false) {
		clock.Update();
		BeginDrawing();
		//ClearBackground(LIGHT_BLUE);
		ClearBackground(BLACK);
		clock.Draw();
		EndDrawing();
	}

	CloseWindow();
}