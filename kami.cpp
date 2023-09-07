#include "raylib.h"

int main()
{
    // Window Properties
    const int windowWidth = 1280;
    const int windowHeight = 720;

    InitWindow(windowWidth, windowHeight, "Kami Dash");
    SetTargetFPS(60);

    // Set Character "Kami"
    Texture2D kami = LoadTexture("textures/running_knight_girl.png");
    Rectangle kamiRectangle;
    Vector2 kamiPosition;

    kamiRectangle.width = kami.width/7;
    kamiRectangle.height = kami.height;
    kamiRectangle.x = 0;
    kamiRectangle.y = 0;

    kamiPosition.x = windowWidth/2 - kamiRectangle.width/2;
    kamiPosition.y = windowHeight - kamiRectangle.height;

    // Set PowerUp
    Texture2D powerCrystal = LoadTexture("textures/power_ups/crystals/blue/blue_crystal_sprites_sheet.png");
    Rectangle powerCrystalRectangle;
    Vector2 powerCrystalPosition;

    powerCrystalRectangle.width = powerCrystal.width/4;
    powerCrystalRectangle.height = powerCrystal.height;
    powerCrystalRectangle.x = 0;
    powerCrystalRectangle.y = 0;

    powerCrystalPosition.x = windowWidth;
    powerCrystalPosition.y = windowHeight - powerCrystalRectangle.height;

    // Kami's Running Animation
    const float updateTime = 1.0/12.0;
    float runningTime = 0;
    int kamiRunningFrame = 0;

    // Power Crystal Movement
    int powerCrystalVelocity = -600;

    // Gravity Properties (pixels/s)
    const int gravity = 1600;
    const int jumpVelocity = -800;
    int velocity = 0;
    int inTheAir = false;

    // The Main Game
    while (!WindowShouldClose())
    {
        // Delta Time
        const float deltaTime = GetFrameTime();
        runningTime += deltaTime;

        BeginDrawing();
        ClearBackground(WHITE);
        
        // Render Kami
        DrawTextureRec(kami, kamiRectangle, kamiPosition, WHITE);

        // Render Power Crystal
        DrawTextureRec(powerCrystal, powerCrystalRectangle, powerCrystalPosition, WHITE);

        // Ground Check
        if (kamiPosition.y >= windowHeight - kamiRectangle.height)
        {
            // Player is on the Ground
            velocity = 0;
            kamiPosition.y = windowHeight - kamiRectangle.height;
            inTheAir = false;

            // Update Animation Frame
            if (runningTime >= updateTime)
            {
                kamiRectangle.x = kamiRunningFrame * kamiRectangle.width;
                kamiRunningFrame++;
                if (kamiRunningFrame > 6)
                {
                    kamiRunningFrame = 0;
                }
                runningTime = 0;
            }
        }
        else
        {
            // Player is in the Air, apply Gravity
            velocity += gravity * deltaTime;
            inTheAir = true;
        }

        // Player Jumps at Velocity
        if(IsKeyPressed(KEY_SPACE) && !inTheAir)
        {
            velocity += jumpVelocity;
        }
        
        // Update Kami's Position
        kamiPosition.y += velocity * deltaTime;

        // Update Power Crystal's Position
        powerCrystalPosition.x += powerCrystalVelocity * deltaTime;

        EndDrawing();
    }

    UnloadTexture(kami);
    UnloadTexture(powerCrystal);
    CloseWindow();
}