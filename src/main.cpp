#include "raylib.h"
#include <iostream>
#include <string>

const int screenWidth = 800;
const int screenHeight = 450;
const std::string gameTitle = "PONG";
int leftScore = 0, rightScore = 0, bounceCount = 0, frameCounter = 0, baseBallSpeed = 3, basePaddleSpeed = 5;
bool isPaused = true;

/*Structs*/

struct Ball {
    int X, Y, XVel, YVel, radius; // X and Y from center
};

struct Paddle {
    int X, Y, Height, Width, Velocity; // X and Y from top left
};

/*Drawing functions*/

void DrawBackground() {
    DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
    DrawRectangle(0, screenHeight / 2 - 5, screenWidth, 15, DARKBLUE);
    DrawRectangle(screenWidth / 2 - 5, 0, 15, screenHeight, DARKBLUE);
    DrawCircle(screenWidth / 2, screenHeight / 2, 60, DARKBLUE);
    DrawCircle(screenWidth / 2, screenHeight / 2, 45, BLUE);
}

void DrawPaddle(Paddle paddle) {
    DrawRectangle(paddle.X, paddle.Y, paddle.Width, paddle.Height, BLACK);
}

void DrawBall(Ball b) {
    DrawCircle(b.X, b.Y, b.radius, BLACK);
}

/*Logic Functions*/

void ResetBall(Ball* b) {
    b->X = screenWidth / 2; b->Y = screenHeight / 2;
    b->XVel = baseBallSpeed; b->YVel = baseBallSpeed;
}
void BallUpdate(Ball *b) {
    if (bounceCount == 4) {
        b->XVel = baseBallSpeed+1;
        if (b->YVel > 0) {
            b->YVel = baseBallSpeed+1;
        }
        else {
            b->YVel = -1 * (baseBallSpeed+1);
        }
    }
    else if (bounceCount == 8) {
        b->XVel = baseBallSpeed+2;
        if (b->YVel > 0) {
            b->YVel = baseBallSpeed+2;
        }
        else {
            b->YVel = -1*(baseBallSpeed + 2);
        }
    }
    else if (bounceCount == 12) {
        b->XVel = baseBallSpeed+3;
        if (b->YVel > 0) {
            b->YVel = baseBallSpeed+3;
        }
        else {
            b->YVel = -1*(baseBallSpeed + 3);
        }
    }
    else if (bounceCount == 16) {
        b->XVel = baseBallSpeed+4;
        if (b->YVel > 0) {
            b->YVel = baseBallSpeed+4;
        }
        else {
            b->YVel = -1*(baseBallSpeed+4);
        }
    }
    b->X += b->XVel;
    b->Y += b->YVel;
    if (b->Y >= screenHeight - b-> radius / 2 || b->Y <= 0 + b->radius / 2) {
        b->YVel *= -1;
    }
    if (b->X >= screenWidth + b->radius*2) { //Score point for LeftPaddle
        leftScore++;
        ResetBall(b);
        bounceCount = 0;
        frameCounter = 0;
    }
    if (b->X <= 0 - b->radius*2) { // Score point for RightPaddle
        rightScore++;
        ResetBall(b);
        bounceCount = 0;
        frameCounter = 0;
    }
}

void DetectBallPaddleCollision(Ball* b, Paddle* p1, Paddle* p2) {
    if (frameCounter > 60 && CheckCollisionCircleRec(Vector2{ float(b->X),float(b->Y) }, float(b->radius), Rectangle{ float(p1->X), float(p1->Y), float(p1->Width), float(p1->Height) })) {
        b->XVel *= -1;
        bounceCount++;
        frameCounter = 0;
    }
    else if (frameCounter > 60 && CheckCollisionCircleRec(Vector2{ float(b->X),float(b->Y) }, float(b->radius), Rectangle{ float(p2->X), float(p2->Y), float(p2->Width), float(p2->Height) })) {
        b->XVel *= -1;
        bounceCount++;
        frameCounter = 0;
    }
}

void PaddleUpdate(Paddle* paddle, int upKey, int downKey) {
    if (IsKeyDown(upKey) && paddle->Y > 0) {
        paddle->Y -= paddle->Velocity;
    }
    if (IsKeyDown(downKey) && paddle->Y < screenHeight - paddle->Height) {
        paddle->Y += paddle->Velocity;
    }
}

void DetectPauseAndStart() {
    if (IsKeyPressed(KEY_SPACE)) {
        isPaused = !isPaused;
    }
}

void UpdatePaddleSetting(Paddle *p1, Paddle *p2) {
    if (IsKeyPressed(KEY_ONE)) {
        p1->Velocity = 1;
        p2->Velocity = 1;
    }
    else if (IsKeyPressed(KEY_TWO)) {
        p1->Velocity = 2;
        p2->Velocity = 2;
    }
    else if (IsKeyPressed(KEY_THREE)) {
        p1->Velocity = 3;
        p2->Velocity = 3;
    }
    else if (IsKeyPressed(KEY_FOUR)) {
        p1->Velocity = 4;
        p2->Velocity = 4;
    }
    else if (IsKeyPressed(KEY_FIVE)) {
        p1->Velocity = 5;
        p2->Velocity = 5;
    }
    else if (IsKeyPressed(KEY_SIX)) {
        p1->Velocity = 6;
        p2->Velocity = 6;
    }
    else if (IsKeyPressed(KEY_SEVEN)) {
        p1->Velocity = 7;
        p2->Velocity = 7;
    }
    else if (IsKeyPressed(KEY_EIGHT)) {
        p1->Velocity = 8;
        p2->Velocity = 8;
    }
    else if (IsKeyPressed(KEY_NINE)) {
        p1->Velocity = 9;
        p2->Velocity = 9;
    }
}
void UpdateReset() {
    if (IsKeyPressed(KEY_R)) {
        leftScore = 0;
        rightScore = 0;
    }
}

/*Main Function*/

int main()
{

    InitWindow(screenWidth, screenHeight, gameTitle.c_str());

    Ball ball;
    Paddle leftPaddle, rightPaddle;


    ball.X = screenWidth / 2; ball.Y = screenHeight / 2;
    ball.XVel = baseBallSpeed; ball.YVel = baseBallSpeed; ball.radius = 10;

    leftPaddle.Width = 15; leftPaddle.Height = 60, leftPaddle.Velocity = basePaddleSpeed;
    leftPaddle.X = 1; leftPaddle.Y = screenHeight / 2 - leftPaddle.Height / 2;

    rightPaddle.Width = 15; rightPaddle.Height = 60, rightPaddle.Velocity = basePaddleSpeed;
    rightPaddle.X = screenWidth - 1 - rightPaddle.Width; rightPaddle.Y = screenHeight / 2 - rightPaddle.Height / 2;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update Logic
        DetectPauseAndStart();
        if (!isPaused) {
            frameCounter++;
            DetectBallPaddleCollision(&ball, &leftPaddle, &rightPaddle);
            BallUpdate(&ball);
            PaddleUpdate(&leftPaddle, KEY_W, KEY_S);
            PaddleUpdate(&rightPaddle, KEY_UP, KEY_DOWN);
        }
        else {
            UpdatePaddleSetting(&leftPaddle, &rightPaddle);
            UpdateReset();
        }
        // Draw
        BeginDrawing();

        ClearBackground(BLUE);

        DrawBackground();
        DrawPaddle(leftPaddle);
        DrawPaddle(rightPaddle);
        DrawBall(ball);
        DrawText(TextFormat("%i", leftScore), screenWidth / 4 - 20, 10, 40, WHITE);
        DrawText(TextFormat("%i", rightScore), 3 * screenWidth / 4 - 20, 10, 40, WHITE);

        if(isPaused){
            DrawText("Press Space to play", screenWidth / 4, 65, 40, WHITE);
            DrawText("1-9 to change paddle speed", screenWidth / 6, 110, 40, WHITE);
            DrawText("R to reset score", screenWidth / 3, 160, 30, WHITE);
        }
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}