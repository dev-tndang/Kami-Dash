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

    kamiRectangle.width = kami.width/7;
    kamiRectangle.height = kami.height;
    kamiRectangle.x = 0;
    kamiRectangle.y = 0;

    kamiPosition.x = windowWidth/2 - kamiRectangle.width/2;
    kamiPosition.y = windowHeight - kamiRectangle.height;

    // Gravity Properties
    const int gravity = 1;
    const int jumpVelocity = -20;
    int velocity = 0;
    int inTheAir = false;

    // The Main Game
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        
        DrawTextureRec(kami, kamiRectangle, kamiPosition, WHITE);

        // Ground Check
        if (kamiPosition.y >= windowHeight - kamiRectangle.height)
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
        kamiPosition.y += velocity;

        EndDrawing();
    }

    UnloadTexture(kami);
    CloseWindow();
}