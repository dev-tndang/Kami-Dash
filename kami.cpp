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
    Rectangle powerCrystal2Rectangle;
    Vector2 powerCrystal2Position;

    powerCrystalRectangle.width = powerCrystal.width/4;
    powerCrystalRectangle.height = powerCrystal.height;
    powerCrystalRectangle.x = 0;
    powerCrystalRectangle.y = 0;

    powerCrystal2Rectangle.width = powerCrystal.width/4;
    powerCrystal2Rectangle.height = powerCrystal.height;
    powerCrystal2Rectangle.x = 0;
    powerCrystal2Rectangle.y = 0;

    powerCrystalPosition.x = windowWidth;
    powerCrystalPosition.y = windowHeight - powerCrystalRectangle.height;

    powerCrystal2Position.x = windowWidth + 300;
    powerCrystal2Position.y = windowHeight - powerCrystalRectangle.height;

    // Kami's Running Animation
    const float updateTime = 1.0/12.0;
    float runningTime = 0;
    int kamiRunningFrame = 0;

    // Power Crystal's Animation
    const float powerCrystalUpdateTime = 1.0/4.0;
    float powerCrystalRunningTime = 0;
    int powerCrystalFrame = 0;

    const float powerCrystal2UpdateTime = 1.0/6.0;
    float powerCrystal2RunningTime = 0;
    int powerCrystal2Frame = 0;

    int powerCrystalVelocity = -200;

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

        // Update Running Times with Delta Time
        runningTime += deltaTime;
        powerCrystalRunningTime += deltaTime;
        powerCrystal2RunningTime += deltaTime;

        BeginDrawing();
        ClearBackground(WHITE);
        
        // Render Kami
        DrawTextureRec(kami, kamiRectangle, kamiPosition, WHITE);

        // Render Power Crystal
        DrawTextureRec(powerCrystal, powerCrystalRectangle, powerCrystalPosition, WHITE);

        // Render Power Crystal 2
        DrawTextureRec(powerCrystal, powerCrystal2Rectangle, powerCrystal2Position, WHITE);

        // Ground Check
        if (kamiPosition.y >= windowHeight - kamiRectangle.height)
        {
            // Player is on the Ground
            velocity = 0;
            kamiPosition.y = windowHeight - kamiRectangle.height;
            inTheAir = false;

            // Update Kami's Animation Frame
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
        powerCrystal2Position.x += powerCrystalVelocity * deltaTime;

        // Update Power Crystal's Animation
        if (powerCrystalRunningTime >= powerCrystalUpdateTime)
        {
            powerCrystalRectangle.x = powerCrystalFrame * powerCrystalRectangle.width;
            powerCrystalFrame++;
            if (powerCrystalFrame > 3)
            {
                powerCrystalFrame = 0;
            }
            powerCrystalRunningTime = 0;
        } 

        if (powerCrystal2RunningTime >= powerCrystal2UpdateTime)
        {
            powerCrystal2Rectangle.x = powerCrystal2Frame * powerCrystal2Rectangle.width;
            powerCrystal2Frame++;
            if (powerCrystal2Frame > 3)
            {
                powerCrystal2Frame = 0;
            }
            powerCrystal2RunningTime = 0;
        } 

        EndDrawing();
    }

    UnloadTexture(kami);
    UnloadTexture(powerCrystal);
    CloseWindow();
}