#include "raylib.h"

struct AnimationData
{
    Rectangle rectangle;
    Vector2 position;
    int frame;
    float updateTime;
    float runningTime;
    float positionYOffset;
};

struct BackgroundData
{
    Texture2D texture;
    Vector2 position;
    Vector2 followingPosition;
    Rectangle rectangle;
    float scale;
    float xLocation;
};


bool isOnGround(AnimationData data, int windowHeight, float positionOffset)
{
    return data.position.y >= windowHeight - (data.rectangle.height + positionOffset);
}

float setBackgroundLayerSpeed(float scrollingXLocation, float scrollingSpeed, float deltaTime, int layerLocation)
{
    scrollingXLocation -= (scrollingSpeed * layerLocation) * deltaTime;
    return scrollingXLocation;
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

BackgroundData updateLevelData(BackgroundData data, float deltaTime)
{
    // Reset Background Texture Positions
    if (data.xLocation <= -data.rectangle.width * data.scale)
    {
        data.xLocation = 0.0;
    }

    data.position.x = data.xLocation;
    data.followingPosition.x = data.xLocation + data.texture.width * data.scale;
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
    const int amountOfBGTextures = 10;
    float backgroundScollingSpeed = 10.0;
    BackgroundData levelData[amountOfBGTextures]{};

    levelData[0].texture = LoadTexture("textures/dark_pixel_forest/Layer_0011_0.png");
    levelData[1].texture = LoadTexture("textures/dark_pixel_forest/Layer_0010_1.png");
    levelData[2].texture = LoadTexture("textures/dark_pixel_forest/Layer_0009_2.png");
    levelData[3].texture = LoadTexture("textures/dark_pixel_forest/Layer_0008_3.png");
    levelData[4].texture = LoadTexture("textures/dark_pixel_forest/Layer_0007_Lights.png");
    levelData[5].texture = LoadTexture("textures/dark_pixel_forest/Layer_0006_4.png");
    levelData[6].texture = LoadTexture("textures/dark_pixel_forest/Layer_0005_5.png");
    levelData[7].texture = LoadTexture("textures/dark_pixel_forest/Layer_0004_Lights.png");
    levelData[8].texture = LoadTexture("textures/dark_pixel_forest/Layer_0003_6.png");
    levelData[9].texture = LoadTexture("textures/dark_pixel_forest/Layer_0001_8.png");

    for (int i = 0; i < amountOfBGTextures; i++)
    {
        levelData[i].position.x = 0.0;
        levelData[i].position.y = -levelData[i].texture.height / 2 - 60.0;
        levelData[i].followingPosition.x = levelData[i].position.x + levelData[i].texture.width;
        levelData[i].followingPosition.y = -levelData[i].texture.height / 2 - 60.0;
        levelData[i].rectangle.x = 0.0;
        levelData[i].rectangle.y = 0.0;
        levelData[i].rectangle.height = levelData[i].texture.height;
        levelData[i].rectangle.width = levelData[i].texture.width;
        levelData[i].scale = 1.5;
        levelData[i].xLocation = 0.0;
    }

    // Set Level Foreground
    const int amountOfFGTextures = 2;
    float foregroundScrollingSpeed = 100.0;
    BackgroundData foregroundData[amountOfFGTextures]{};

    foregroundData[0].texture = LoadTexture("textures/dark_pixel_forest/Layer_0002_7.png");
    foregroundData[1].texture = LoadTexture("textures/dark_pixel_forest/Layer_0000_9.png");
    
    for (int i = 0; i < amountOfFGTextures; i++)
    {
        foregroundData[i].position.x = 0.0;
        foregroundData[i].position.y = -foregroundData[i].texture.height / 2 - 60.0;
        foregroundData[i].followingPosition.x = foregroundData[i].position.x + foregroundData[i].texture.width;
        foregroundData[i].followingPosition.y = -foregroundData[i].texture.height / 2 - 60.0;
        foregroundData[i].rectangle.x = 0.0;
        foregroundData[i].rectangle.y = 0.0;
        foregroundData[i].rectangle.height = foregroundData[i].texture.height;
        foregroundData[i].rectangle.width = foregroundData[i].texture.width;
        foregroundData[i].scale = 1.5;
        foregroundData[i].xLocation = 0.0;
    }

    // Set Character "Kami"
    Texture2D kami = LoadTexture("textures/running_knight_girl.png");
    AnimationData kamiData;

    kamiData.rectangle.width = kami.width/7;
    kamiData.rectangle.height = kami.height;
    kamiData.rectangle.x = 0.0;
    kamiData.rectangle.y = 0.0;
    kamiData.position.x = windowDimensions[0]/2 - kami.width/1.5;
    kamiData.position.y = windowDimensions[1] + kami.height;
    kamiData.updateTime = 1.0/12.0;
    kamiData.runningTime = 0;
    kamiData.frame = 0;
    kamiData.positionYOffset = 70.0;

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
        powerCrystals[i].positionYOffset = 75.0;
        powerCrystals[i].position.x = windowDimensions[0] + (i * 300);
        powerCrystals[i].position.y = windowDimensions[1] - (powerCrystal.height + powerCrystals[i].positionYOffset);
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

        BeginDrawing();
        ClearBackground(WHITE);
        
        // Update Background Data
        for (int i = 0; i < amountOfBGTextures; i++)
        {
            // Render the Background
            DrawTextureEx(levelData[i].texture, levelData[i].position, 0.0, levelData[i].scale, WHITE);
            DrawTextureEx(levelData[i].texture, levelData[i].followingPosition, 0.0, levelData[i].scale, WHITE);

            // Update the Background Texture Positions
            levelData[i].xLocation = setBackgroundLayerSpeed(levelData[i].xLocation, backgroundScollingSpeed, deltaTime, i);

            // Update Background Positions
            levelData[i] = updateLevelData(levelData[i], deltaTime);
        }

        // Render Kami
        DrawTextureRec(kami, kamiData.rectangle, kamiData.position, WHITE);

        // Ground Check
        if (isOnGround(kamiData, windowDimensions[1], kamiData.positionYOffset))
        {
            // Player is on the Ground
            velocity = 0;
            kamiData.position.y = windowDimensions[1] - (kamiData.rectangle.height + kamiData.positionYOffset);
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

                // Update Foreground Data
        for (int i = 0; i < amountOfFGTextures; i++)
        {
            // Render the Background
            DrawTextureEx(foregroundData[i].texture, foregroundData[i].position, 0.0, foregroundData[i].scale, WHITE);
            DrawTextureEx(foregroundData[i].texture, foregroundData[i].followingPosition, 0.0, foregroundData[i].scale, WHITE);

            // Update the Background Texture Positions
            foregroundData[i].xLocation = setBackgroundLayerSpeed(foregroundData[i].xLocation, foregroundScrollingSpeed, deltaTime, i);

            // Update Background Positions
            foregroundData[i] = updateLevelData(foregroundData[i], deltaTime);
        }

        EndDrawing();
    }

    UnloadTexture(kami);
    UnloadTexture(powerCrystal);
    for (int i = 0; i < amountOfBGTextures; i++)
    {
        UnloadTexture(levelData[i].texture);
    }  
    for (int i = 0; i < amountOfBGTextures; i++)
    {
        UnloadTexture(foregroundData[i].texture);
    }  
    CloseWindow();
}