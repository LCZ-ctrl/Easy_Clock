#include "clock.h"
#include <cmath>
#include <chrono>
using namespace std;

Color DARK_GREY = { 45,45,45,255 };
Color LIGHT_GREY = { 229,229,229,255 };

void Clock::Draw() const {
	DrawFace();
	DrawHourMarks();
	DrawHourLabels();
	DrawHourHand(hour, minute);
	DrawMinuteHand(minute);
	DrawSecondHand(second);
	DrawCircleV(position, 15, DARK_GREY);
}

void Clock::Update() {
	time_t t = time(0);
	tm now;

	localtime_s(&now, &t); // get local time

	hour = now.tm_hour % 12;
	minute = now.tm_min;
	second = now.tm_sec;
}

void Clock::DrawFace() const {
	DrawCircleV(position, size, DARK_GREY); 
	DrawCircleV(position, size - 30, LIGHT_GREY);
	DrawCircleV(position, size - 40, RAYWHITE);
}

void Clock::DrawHourMarks() const {
	float rectWidth = 10;
	float rectHeight = size;

	Rectangle rect = { position.x, position.y, rectWidth, rectHeight };
	for (int i = 0; i < 12; i++) {
		DrawRectanglePro(rect, { rectWidth / 2, rectHeight }, i * 30, DARK_GREY);
	}

	// Inner face, in order to "hide" part of the rectangle to create hour marks
	DrawCircleV(position, size - 50, RAYWHITE);
}

void Clock::DrawMinuteHand(int minute) const {
	float handWidth = 10;
	float handLength = size * 0.66;
	int angle = minute * 6;

	DrawHand(handWidth, handLength, angle, DARK_GREY, 0);
}

void Clock::DrawHourHand(int hour, int minute) const {
	float handWidth = 12.5;
	float handLength = size * 0.44;
	int angle = 30 * hour + (minute / 60.0) * 30; // to make hour hand move within an hour

	DrawHand(handWidth, handLength, angle, DARK_GREY, 0);
}

void Clock::DrawSecondHand(int second) const {
	float handWidth = 5;
	float handLength = size * 1.05;
	int angle = second * 6;

	DrawHand(handWidth, handLength, angle, RED, 55); // 55px offset to create a "tail" in second hand
}

void Clock::DrawHand(float handWidth, float handLength, int angle, Color color, int offset) const {
	Rectangle handrect = { position.x, position.y, handWidth, handLength };
	DrawRectanglePro(handrect, { handWidth / 2, handLength - offset }, angle, color);

	float tipLength = handWidth * 1.0f;
	Vector2 tipBase = { 
		position.x + (handLength - offset) * sinf(DEG2RAD * angle), 
		position.y - (handLength - offset) * cosf(DEG2RAD * angle) 
	};
	Vector2 tipLeft = { 
		tipBase.x - (handWidth / 2) * cosf(DEG2RAD * angle), 
		tipBase.y - (handWidth / 2) * sinf(DEG2RAD * angle) 
	};
	Vector2 tipRight = { 
		tipBase.x + (handWidth / 2) * cosf(DEG2RAD * angle), 
		tipBase.y + (handWidth / 2) * sinf(DEG2RAD * angle) 
	};
	Vector2 tipPoint = { 
		tipBase.x + tipLength * sinf(DEG2RAD * angle), 
		tipBase.y - tipLength * cosf(DEG2RAD * angle) 
	};
	DrawTriangle(tipLeft, tipRight, tipPoint, color);

	Rectangle shadowRect = { position.x + 2 * cosf(DEG2RAD * angle), position.y + 2 * sinf(DEG2RAD * angle), handWidth, handLength };
	DrawRectanglePro(shadowRect, { handWidth / 2, handLength - offset }, angle, ColorAlpha(DARK_GREY, 0.3f));
}

void Clock::DrawHourLabels() const {
	int fontSize = 38;
	const char* labels[4] = { "3", "6", "9", "12" };
	int hours[4] = { 3, 6, 9, 12 };
	float textRadius = size - 70;

	for (int i = 0; i < 4; i++) {
		int h = hours[i];
		float theta_deg = 90 - (h * 30);
		float theta_rad = theta_deg * DEG2RAD; // convert degrees to radians
		float x = position.x + textRadius * cos(theta_rad);
		float y = position.y - textRadius * sin(theta_rad);

		const char* text = labels[i];
		int textWidth = MeasureText(text, fontSize);
		int textHeight = fontSize;

		DrawText(text, x - textWidth / 2, y - textHeight / 2, fontSize, DARK_GREY);
	}
}

