#include "raylib.h"
#include "raymath.h"

int main()
{
	const int windowWidth{ 960 };
	const int windowHeight{ 540 };
	float speed{ 4.0 };

	InitWindow(windowWidth, windowHeight, "Goob's Adventure");

	Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
	Vector2 mapPos{ 0.0,0.0 };

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		Vector2 direction{};
		// Movement
		if (IsKeyDown(KEY_A)) direction.x -= 1.0;
		if (IsKeyDown(KEY_D)) direction.x += 1.0;
		if (IsKeyDown(KEY_W)) direction.y -= 1.0;
		if (IsKeyDown(KEY_S)) direction.y += 1.0;

		if (Vector2Length(direction) != 0.0)
		{
			// set mapPos = mapPos - directions
			mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction),speed));
		}

		DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

		EndDrawing();
	}
	CloseWindow();
}