#include "raylib.h"
#include <iostream>

#define BACKGROUND (Color){84,194,249,255}
#define FLAPPY_COLOR (Color){73,53,222,255}
#define TUBE_COLOR (Color){190,237,17,255}
#define FLAPPY_SIZE 30
#define MAX_TUBES 100

using namespace std;

typedef struct Flappy
{
    Color color;
    int radius;
    Vector2 position;
}Flappy;

typedef struct Tubes
{
    Color color;
    Rectangle rec;
    bool active;
}Tubes;

static int screenWidth = 800;
static int screenHeight = 450;
static Flappy flappy = {0};

static Tubes tubes[MAX_TUBES*2] = {0};
static Vector2 tubesPos[MAX_TUBES] = {0};
static int tubeVel = 2;

static int score = 0;
static int hScore = 0;
static bool gameOver = false;
static bool pause = false;

static void InitGame(void);
static void DrawGame(void);
static void UpdateGame(void);

int main(void)
{
    InitWindow(screenWidth, screenHeight, "Flappy Bird");
    InitGame();
    SetTargetFPS(60);

    while(WindowShouldClose() == false)
    {
        DrawGame();
        UpdateGame();
    }

    CloseWindow();
    return 0;
}

void InitGame(void)
{
    score = 0;
    gameOver = false;
    pause = false;
    flappy.radius = FLAPPY_SIZE;

    flappy.position = {100,screenHeight/2 - flappy.radius};

    for(int i = 0; i < MAX_TUBES; i++)
    {
        tubesPos[i] =(Vector2) {500 + 210*i, -GetRandomValue(0,120)};
        tubes[i].active = true;
        tubes[i+1].active = true;
    }
    for(int i = 0; i < MAX_TUBES*2; i+=2)
    {
        tubes[i].rec.x = tubesPos[i/2].x;
        tubes[i].rec.y =  tubesPos[i/2].y;
        tubes[i].rec.width = 80;
        tubes[i].rec.height = 300;

        tubes[i+1].rec.x = tubesPos[i/2].x;
        tubes[i+1].rec.y =  650 + tubesPos[i/2].y -250;
        tubes[i+1].rec.width = 80;
        tubes[i+1].rec.height = 300;
    }
}

void DrawGame(void)
{
        BeginDrawing();
        ClearBackground(BACKGROUND);
        if(!gameOver && !pause)
        {
            DrawCircle(flappy.position.x, flappy.position.y, flappy.radius, FLAPPY_COLOR);

            for(int i = 0; i < MAX_TUBES*2; i+=2)
            {
                DrawRectangle(tubes[i].rec.x, tubes[i].rec.y, tubes[i].rec.width, tubes[i].rec.height, TUBE_COLOR);
                DrawRectangle(tubes[i+1].rec.x, tubes[i+1].rec.y, tubes[i+1].rec.width, tubes[i+1].rec.height, TUBE_COLOR);
            }
            DrawText(TextFormat("Score: %i", score), 10 , 10 , 20, (Color){255,255,255,255});
            DrawText(TextFormat("High Score: %i",hScore), 10 , 25 , 20, (Color){255,255,255,255});
        }
        else if(gameOver)
        {
            DrawText("Game Over", screenWidth/2 -120 , screenHeight/2 -60, 50, (Color){255,255,255,255});
            DrawText("Press [ENTER] to Restart", screenWidth/2 -200, screenHeight/2 , 35, (Color){255,255,255,255});
        }
        else if(pause)
        {
            DrawText("PAUSED", screenWidth/2 -110 , screenHeight/2 - 45, 50, (Color){255,255,255,255});
        }


        EndDrawing();
}

void UpdateGame(void)
{
    if(!gameOver && !pause)
    {
        if(IsKeyDown(KEY_SPACE))
        {
            flappy.position.y -= 2;
        }
        else
        {
            flappy.position.y += 1 ;
        }

        for(int i = 0; i < MAX_TUBES; i++)
        {
            tubesPos[i].x -= tubeVel;
        }
        for(int i = 0; i < MAX_TUBES*2;i++)
        {
            tubes[i].rec.x = tubesPos[i/2].x;
            tubes[i+1].rec.x = tubesPos[i/2].x;
        }

        for(int i = 0; i < MAX_TUBES*2; i+=2)
        {
            bool collision = CheckCollisionCircleRec(flappy.position, flappy.radius, tubes[i].rec) || CheckCollisionCircleRec(flappy.position, flappy.radius, tubes[i+1].rec);
            if(collision)
            {
                gameOver = true;
            }
            else if((tubesPos[i/2].x < flappy.position.x) && (tubes[i].active))
            {
                score += 100;
                hScore = (score > hScore)? score : hScore;
                tubes[i].active = false;
            }
        }

        gameOver = (flappy.position.y < 0 || flappy.position.y > 450)? !gameOver: gameOver;
        if(IsKeyPressed(KEY_P))
        {
            pause = !pause;
        }

    }
    else if(pause)
    {
        if(IsKeyPressed(KEY_P))
        {
            pause = !pause;
        }
    }
    else if(gameOver)
    {
        if(IsKeyPressed(KEY_ENTER))
        {
            gameOver = false;
            InitGame();
        }

    }
}

