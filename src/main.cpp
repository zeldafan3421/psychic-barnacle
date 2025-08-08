#include "raylib.h"
#include "log.h"

constexpr int width = 1280;
constexpr int height = 720;
const char* title = "app";
constexpr Color background_color = WHITE;

int main()
{
	SetTraceLogCallback(CustomLog);

	InitWindow(width, height, title);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(background_color);
		EndDrawing();
	}

	CloseWindow();
}
