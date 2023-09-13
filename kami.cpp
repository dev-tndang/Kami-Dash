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
    int windowDimensions[2];
    windowDimensions[0] = 1280;
    windowDimensions[1] = 720;

    InitWindow(windowDimensions[0], windowDimensions[1], "Kami Dash");
    SetTargetFPS(60);

    // Set Character "Kami"
    Texture2D kami = LoadTexture("textures/running_knight_girl.png");
    AnimationData kamiData;

    kamiData.rectangle.width = kami.width/7;
    kamiData.rectangle.height = kami.height;
    kamiData.rectangle.x = 0.0;
    kamiData.rectangle.y = 0.0;
    kamiData.position.x = windowDimensions[0]/2 - kamiData.rectangle.width/2;
    kamiData.position.y = windowDimensions[1] - kamiData.rectangle.height;
    kamiData.updateTime = 1.0/12.0;
    kamiData.runningTime = 0;
    kamiData.frame = 0;

    // Set PowerUp
    Texture2D powerCrystal = LoadTexture("textures/power_ups/crystals/blue/blue_crystal_sprites_sheet.png");
    AnimationData powerCrystals[3]{};

    for (int i = 0; i < 3; i++)
    {
        powerCrystals[i].rectangle.x = 0.0;
        powerCrystals[i].rectangle.y = 0.0;
        powerCrystals[i].rectangle.width = powerCrystal.width/4;
        powerCrystals[i].rectangle.height = powerCrystal.height;
        powerCrystals[i].position.y = windowDimensions[1] - powerCrystal.height;
        powerCrystals[i].frame = 0;
        powerCrystals[i].runningTime = 0.0;
        powerCrystals[i].updateTime = 1.0/4.0;
    }

    powerCrystals[0].position.x = windowDimensions[0];
    powerCrystals[1].position.x = windowDimensions[0] + 300;
    powerCrystals[2].position.x = windowDimensions[0] + 600;
    
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
        powerCrystals[0].runningTime += deltaTime;
        powerCrystals[1].runningTime += deltaTime;

        BeginDrawing();
        ClearBackground(WHITE);
        
        // Render Kami
        DrawTextureRec(kami, kamiData.rectangle, kamiData.position, WHITE);

        // Render Power Crystal 1 & 2
        DrawTextureRec(powerCrystal, powerCrystals[0].rectangle, powerCrystals[0].position, WHITE);
        DrawTextureRec(powerCrystal, powerCrystals[1].rectangle, powerCrystals[1].position, WHITE);

        // Ground Check
        if (kamiData.position.y >= windowDimensions[1] - kamiData.rectangle.height)
        {
            // Player is on the Ground
            velocity = 0;
            kamiData.position.y = windowDimensions[1] - kamiData.rectangle.height;
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
        powerCrystals[0].position.x += powerCrystalVelocity * deltaTime;
        powerCrystals[1].position.x += powerCrystalVelocity * deltaTime;

        // Update Power Crystals Animation
        if (powerCrystals[0].runningTime >= powerCrystals[0].updateTime)
        {
            powerCrystals[0].rectangle.x = powerCrystals[0].frame * powerCrystals[0].rectangle.width;
            powerCrystals[0].frame++;
            if (powerCrystals[0].frame > 3)
            {
                powerCrystals[0].frame = 0;
            }
            powerCrystals[0].runningTime = 0;
        } 

        if (powerCrystals[1].runningTime >= powerCrystals[1].updateTime)
        {
            powerCrystals[1].rectangle.x = powerCrystals[1].frame * powerCrystals[1].rectangle.width;
            powerCrystals[1].frame++;
            if (powerCrystals[1].frame > 3)
            {
                powerCrystals[1].frame = 0;
            }
            powerCrystals[1].runningTime = 0;
        } 

        EndDrawing();
    }

    UnloadTexture(kami);
    UnloadTexture(powerCrystal);
    CloseWindow();
}