#include <iostream>
#include <raylib.h>
#include "clock.h"

int main() {
	const int WINDOW_WIDTH = 600;
	const int WINDOW_HEIGHT = 600;

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Clock");
	Image icon = LoadImage("Graphics/clock.png");
	SetWindowIcon(icon);
	UnloadImage(icon);

	SetExitKey(0);
	SetTargetFPS(30);

	Clock clock{ 250, {300, 300} }; // initialize the clock

	while (WindowShouldClose() == false) {
		clock.Update();
		BeginDrawing();
		ClearBackground(BLACK);
		clock.Draw();
		EndDrawing();
	}

	CloseWindow();
}