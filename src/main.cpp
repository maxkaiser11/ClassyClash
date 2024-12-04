#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Vector2 getWorldPos() { return worldPos; }

private:
    Texture2D texture;
    Texture2D idle;
    Texture2D run;
    Vector2 screenPos;
    Vector2 worldPos;
    float rightLeft = 1.f;
    // animation variales
    float runningTime = 0;
    int frame = 0;
    const int maxFrames = 6;
    const float updateTime = 1.f / 12.f;
};

int main()
{
    const int windowWidth = 384;
    const int windowHeight = 384;
    InitWindow(windowWidth, windowHeight, "Classy Clash");

    Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 mapPos = {0.0f, 0.0f};
    float speed = 4.0f;

    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
    Vector2 knightPos = {
        (float)windowWidth / 2.0f - 4.0f * (0.5f * (float)knight.width / 6.0f),
        (float)windowHeight / 2.0f - 4.0f * (0.5f * (float)knight.height)};
    // 1. facing right, -1. facing left

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction = {};
        if (IsKeyDown(KEY_A))
            direction.x -= 1.0f;
        if (IsKeyDown(KEY_D))
            direction.x += 1.0f;
        if (IsKeyDown(KEY_W))
            direction.y -= 1.0f;
        if (IsKeyDown(KEY_S))
            direction.y += 1.0f;
        if (Vector2Length(direction) != 0.0f)
        {
            // set map pos = mapPos - direction
            mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            knight = knight_run;
        }
        else
        {
            knight = knight_idle;
        }

        DrawTextureEx(map, mapPos, 0.0f, 4.0f, WHITE);

        // update animation frame
        runningTime += GetFrameTime();
        if (runningTime >= updateTime)
        {
            frame++;
            runningTime = 0.f;
            if (frame > maxFrames)
                frame = 0;
        }

        // draw the knight
        Rectangle source = {frame * (float)knight.width / 6.f, 0.f, rightLeft * (float)knight.width / 6.f, (float)knight.height};
        Rectangle dest = {knightPos.x, knightPos.y, 4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height};

        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}