#include "raylib.h"

int main()
{
    // Window Properties
    const int windowWidth = 1280;
    const int windowHeight = 720;

    InitWindow(windowWidth, windowHeight, "Kami Dash");
    SetTargetFPS(60);

    // Gravity
    const int gravity = 1;
    const int jumpVelocity = -20;

    // Placeholder Circle Properties
    const int radius = 20;
    int positionY = windowHeight - radius;
    int velocity = 0;
    int inTheAir = false;

    // The Main Game
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        DrawCircle(windowWidth/2, positionY, radius, GREEN);

        // Ground check
        if (positionY >= windowHeight - radius)
        {
            // Player is on the ground
            velocity = 0;
            inTheAir = false;
        }
        else
        {
            // Player is in the air, apply gravity
            velocity += gravity;
            inTheAir = true;
        }

        // Player jumps at velocity
        if(IsKeyPressed(KEY_SPACE) && !inTheAir)
        {
            velocity += jumpVelocity;
        }
        
        // Update position
        positionY += velocity;

        EndDrawing();
    }

    CloseWindow();
}