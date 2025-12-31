#pragma once
#include <raylib.h>
#include <ctime>

class Clock {
public:
	Clock(int size, Vector2 position) :size(size), position(position), hour(0), minute(0), second(0) {};
	void Draw() const;
	void Update(); // update time

private:
	int size; // radius
	Vector2 position; // center point
	int hour;
	int minute;
	int second;

	void DrawFace() const;
	void DrawHourMarks() const;
	void DrawHourLabels() const;

	void DrawHourHand(int hour, int minute) const;
	void DrawMinuteHand(int minute) const;
	void DrawSecondHand(int second) const;

	void DrawHand(float handWidth, float handLength, int angle, Color color, int offset) const;
};