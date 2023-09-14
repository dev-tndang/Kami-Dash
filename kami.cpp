#include "raylib.h"

struct AnimationData
{
    Rectangle rectangle;
    Vector2 position;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimationData data, int windowHeight)
{
    return data.position.y >= windowHeight - data.rectangle.height;
}

AnimationData updateAnimationData(AnimationData data, float deltaTime, int maxFrame)
{
    // Update Running Time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        // Update Animation Frame
        data.rectangle.x = data.frame * data.rectangle.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
        data.runningTime = 0;
    }
    return data;
}

int main()
{
    // Window Properties
    int windowDimensions[2];
    windowDimensions[0] = 1280;
    windowDimensions[1] = 720;

    InitWindow(windowDimensions[0], windowDimensions[1], "Kami Dash");
    SetTargetFPS(60);

    // Set Level Background
    Texture2D levelBackground = LoadTexture("textures/dark_pixel_forest/Layer_0011_0.png");
    Vector2 backgroundPosition;
    float backgroundX = 0.0;

    backgroundPosition.x = 0.0;
    backgroundPosition.y = 0.0;

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

    // Set PowerUp Crystals
    Texture2D powerCrystal = LoadTexture("textures/power_ups/crystals/blue/blue_crystal_sprites_sheet.png");

    const int amountOfCrystals = 6;
    AnimationData powerCrystals[amountOfCrystals]{};

    for (int i = 0; i < amountOfCrystals; i++)
    {
        powerCrystals[i].rectangle.x = 0.0;
        powerCrystals[i].rectangle.y = 0.0;
        powerCrystals[i].rectangle.width = powerCrystal.width/4;
        powerCrystals[i].rectangle.height = powerCrystal.height;
        powerCrystals[i].position.x = windowDimensions[0] + (i * 300);
        powerCrystals[i].position.y = windowDimensions[1] - powerCrystal.height;
        powerCrystals[i].frame = 0;
        powerCrystals[i].runningTime = 0.0;
        powerCrystals[i].updateTime = 1.0/4.0;
    }
    
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

        // Update Background Position
        backgroundX -= 20 * deltaTime;
        backgroundPosition.x = backgroundX;

        BeginDrawing();
        ClearBackground(WHITE);

        // Render the Background
        DrawTextureEx(levelBackground, backgroundPosition, 0.0, 1.5, WHITE);
        
        // Render Kami
        DrawTextureRec(kami, kamiData.rectangle, kamiData.position, WHITE);

        // Ground Check
        if (isOnGround(kamiData, windowDimensions[1]))
        {
            // Player is on the Ground
            velocity = 0;
            kamiData.position.y = windowDimensions[1] - kamiData.rectangle.height;
            inTheAir = false;

            // Update Kami's Animation Frame
            kamiData = updateAnimationData(kamiData, deltaTime, 6);
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

        // Render & Update Power Crystal's Values
        for (int i = 0; i < amountOfCrystals; i++)
        {
            // Render the Power Crystals
            DrawTextureRec(powerCrystal, powerCrystals[i].rectangle, powerCrystals[i].position, WHITE);

            // Update the Power Crystals Position
            powerCrystals[i].position.x += powerCrystalVelocity * deltaTime;

            // Update the Power Crystals Animation
            powerCrystals[i] = updateAnimationData(powerCrystals[i], deltaTime, 3);
        }

        EndDrawing();
    }

    UnloadTexture(kami);
    UnloadTexture(powerCrystal);
    UnloadTexture(levelBackground);
    CloseWindow();
}