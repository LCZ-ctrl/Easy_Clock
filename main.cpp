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

	// Main loop
	while (WindowShouldClose() == false) {
		// 1. Event Handling

		// 2. Updating
		clock.Update();

		// 3. Drawing
		BeginDrawing();
		//ClearBackground(LIGHT_BLUE);
		ClearBackground(BLACK);
		clock.Draw();
		EndDrawing();
	}

	CloseWindow();
}