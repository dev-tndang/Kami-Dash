#include "raylib.h"

int main()
{
    // Window Properties
    const int windowWidth = 1280;
    const int windowHeight = 720;

    InitWindow(windowWidth, windowHeight, "Kami Dash");
    SetTargetFPS(60);

    // Set Character
    Texture2D kami = LoadTexture("textures/running_knight_girl.png");
    Rectangle kamiRectangle;
    Vector2 kamiPosition;

    // Gravity Properties
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

        // Ground Check
        if (positionY >= windowHeight - radius)
        {
            // Player is on the Ground
            velocity = 0;
            inTheAir = false;
        }
        else
        {
            // Player is in the Air, apply Gravity
            velocity += gravity;
            inTheAir = true;
        }

        // Player Jumps at Velocity
        if(IsKeyPressed(KEY_SPACE) && !inTheAir)
        {
            velocity += jumpVelocity;
        }
        
        // Update Position
        positionY += velocity;

        EndDrawing();
    }

    CloseWindow();
}