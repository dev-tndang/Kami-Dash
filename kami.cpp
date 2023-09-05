#include "raylib.h"

int main()
{
    // Window Properties
    const int windowWidth = 1280;
    const int windowHeight = 720;

    InitWindow(windowWidth, windowHeight, "Kami Dash");
    SetTargetFPS(60);

    // Placeholder Circle Properties
    const int radius = 20;
    int positionY = windowHeight - radius;
    int velocity = 0;

    // The Main Game
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        DrawCircle(windowWidth/2, positionY, radius, GREEN);
        positionY += velocity;

        if(IsKeyPressed(KEY_SPACE))
        {
            velocity -= 10;
        }

        EndDrawing();
    }

    CloseWindow();
}