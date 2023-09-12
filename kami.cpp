#include "raylib.h"

struct AnimationData
{
    Rectangle rectangle;
    Vector2 position;
    int frame;
    float updateTime;
    float runningTime;
};


int main()
{
    // Window Properties
    const int windowWidth = 1280;
    const int windowHeight = 720;

    InitWindow(windowWidth, windowHeight, "Kami Dash");
    SetTargetFPS(60);

    // Set Character "Kami"
    Texture2D kami = LoadTexture("textures/running_knight_girl.png");
    AnimationData kamiData;

    kamiData.rectangle.width = kami.width/7;
    kamiData.rectangle.height = kami.height;
    kamiData.rectangle.x = 0.0;
    kamiData.rectangle.y = 0.0;
    kamiData.position.x = windowWidth/2 - kamiData.rectangle.width/2;
    kamiData.position.y = windowHeight - kamiData.rectangle.height;
    kamiData.updateTime = 1.0/12.0;
    kamiData.runningTime = 0;
    kamiData.frame = 0;

    // Set PowerUp
    Texture2D powerCrystal = LoadTexture("textures/power_ups/crystals/blue/blue_crystal_sprites_sheet.png");
    AnimationData powerCrystal1Data;
    AnimationData powerCrystal2Data;

    powerCrystal1Data.rectangle.width = powerCrystal.width/4;
    powerCrystal1Data.rectangle.height = powerCrystal.height;
    powerCrystal1Data.rectangle.x = 0;
    powerCrystal1Data.rectangle.y = 0;
    powerCrystal1Data.position.x = windowWidth;
    powerCrystal1Data.position.y = windowHeight - powerCrystal1Data.rectangle.height;
    powerCrystal1Data.updateTime = 1.0/4.0;
    powerCrystal1Data.runningTime = 0;
    powerCrystal1Data.frame = 0;

    powerCrystal2Data.rectangle.width = powerCrystal.width/4;
    powerCrystal2Data.rectangle.height = powerCrystal.height;
    powerCrystal2Data.rectangle.x = 0;
    powerCrystal2Data.rectangle.y = 0;
    powerCrystal2Data.position.x = windowWidth + 300;
    powerCrystal2Data.position.y = windowHeight - powerCrystal2Data.rectangle.height;
    powerCrystal2Data.updateTime = 1.0/6.0;
    powerCrystal2Data.runningTime = 0;
    powerCrystal2Data.frame = 0;

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
        kamiData.runningTime += deltaTime;
        powerCrystal1Data.runningTime += deltaTime;
        powerCrystal2Data.runningTime += deltaTime;

        BeginDrawing();
        ClearBackground(WHITE);
        
        // Render Kami
        DrawTextureRec(kami, kamiData.rectangle, kamiData.position, WHITE);

        // Render Power Crystal 1 & 2
        DrawTextureRec(powerCrystal, powerCrystal1Data.rectangle, powerCrystal1Data.position, WHITE);
        DrawTextureRec(powerCrystal, powerCrystal2Data.rectangle, powerCrystal2Data.position, WHITE);

        // Ground Check
        if (kamiData.position.y >= windowHeight - kamiData.rectangle.height)
        {
            // Player is on the Ground
            velocity = 0;
            kamiData.position.y = windowHeight - kamiData.rectangle.height;
            inTheAir = false;

            // Update Kami's Animation Frame
            if (kamiData.runningTime >= kamiData.updateTime)
            {
                kamiData.rectangle.x = kamiData.frame * kamiData.rectangle.width;
                kamiData.frame++;
                if (kamiData.frame > 6)
                {
                    kamiData.frame = 0;
                }
                kamiData.runningTime = 0;
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
        kamiData.position.y += velocity * deltaTime;

        // Update Power Crystals Position
        powerCrystal1Data.position.x += powerCrystalVelocity * deltaTime;
        powerCrystal2Data.position.x += powerCrystalVelocity * deltaTime;

        // Update Power Crystals Animation
        if (powerCrystal1Data.runningTime >= powerCrystal1Data.updateTime)
        {
            powerCrystal1Data.rectangle.x = powerCrystal1Data.frame * powerCrystal1Data.rectangle.width;
            powerCrystal1Data.frame++;
            if (powerCrystal1Data.frame > 3)
            {
                powerCrystal1Data.frame = 0;
            }
            powerCrystal1Data.runningTime = 0;
        } 

        if (powerCrystal2Data.runningTime >= powerCrystal2Data.updateTime)
        {
            powerCrystal2Data.rectangle.x = powerCrystal2Data.frame * powerCrystal2Data.rectangle.width;
            powerCrystal2Data.frame++;
            if (powerCrystal2Data.frame > 3)
            {
                powerCrystal2Data.frame = 0;
            }
            powerCrystal2Data.runningTime = 0;
        } 

        EndDrawing();
    }

    UnloadTexture(kami);
    UnloadTexture(powerCrystal);
    CloseWindow();
}