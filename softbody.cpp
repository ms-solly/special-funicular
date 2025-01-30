// #include "raylib.h"
// #include <math.h>
// #include "raymath.h"

// #define G_WIDTH 800
// #define G_HEIGHT 600

// #define NUM_POINTS 40
// #define BALL_RADIUS 70
// #define RIGID_RADIUS 30
// #define GROUND_Y 400
// #define GRAVITY 0.5f
// #define STIFFNESS 0.1f
// #define JUMP_FORCE -12.0f


// typedef struct 
// {
//     Vector2 position;
//     Vector2 lPosition;
// } SoftBodyPoint;

// typedef struct 
// {
//     SoftBodyPoint points[NUM_POINTS];
//     Vector2 corePosition;
//     Vector2 velocity;
// } SoftBody;

// SoftBody ball;
// bool isOnGround = false;

// // Initialize particles in a soft object

// void InitSoftBody(SoftBody *body, Vector2 startPosition)
// {
//     for (size_t i = 0; i < NUM_POINTS; i++)
//     {
//         body->corePosition = startPosition;
//         body->velocity = (Vector2){0,0};
        
//         for (size_t i = 0; i < NUM_POINTS; i++)
//         {
//             float angle = (2 * PI * i)/NUM_POINTS;
//             body->points[i].position = (Vector2)
//                                     {
//                                         startPosition.x + cos(angle) * BALL_RADIUS,
//                                         startPosition.y + sin(angle) * BALL_RADIUS
//                                     };
//             body->points[i].lPosition = body->points[i].position;
//         }
        

//     }
    
// }
// // Initialize springs connecting adjacent particles


// // Apply spring force between two particles


// // Update the particles' positions and velocities
// void updateSoftBody(SoftBody *body)
// {
//     body->velocity.y += GRAVITY;
//     body->corePosition.y += body->velocity.y;

//     if (IsKeyPressed(KEY_SPACE) && isOnGround)
//     {
//         body->velocity.y = JUMP_FORCE;
//         isOnGround = false;
//     }
    

//     for (size_t i = 0; i < NUM_POINTS; i++)
//     {
//         // constraint to follow rigid body
//         float angle = (2 * PI * i)/NUM_POINTS;
//         Vector2 target = (Vector2){
//             body->corePosition.x + cos(angle) * BALL_RADIUS,
//             body->corePosition.y + sin(angle) * BALL_RADIUS
//         };

//         // move
//         body->points[i].position.x += (target.x - body->points[i].position.x) * STIFFNESS;
//         body->points[i].position.y += (target.y - body->points[i].position.y) * STIFFNESS;

//         // ground collision
//         if (body->corePosition.y + RIGID_RADIUS > GROUND_Y)
//         {
//             body->corePosition.y = GROUND_Y - RIGID_RADIUS;
//             body->velocity.y *= -0.6f;
//             isOnGround = true;
//         }
        
//     }
    
// }

// // Render the soft body
// void DrawSoftBody(SoftBody *body)
// {
//     for (size_t i = 0; i < NUM_POINTS; i++)
//     {
//         DrawCircleV(body->points[i].position, 5 , GREEN);
//         int next = (i + 1) % NUM_POINTS;
//         DrawLineV(body->points[i].position,body->points[next].position, LIGHTGRAY);
//     }
//     DrawCircleLinesV(body->corePosition, RIGID_RADIUS, DARKGRAY);
    
// }


// int main() {
//     InitWindow(G_WIDTH, G_HEIGHT, "Soft Body");
//     SetTargetFPS(60);

//     InitSoftBody(&ball, (Vector2){400,200});

//     while (!WindowShouldClose()) {

//         // Update physics



//         // Render
//         BeginDrawing();
//         ClearBackground(RAYWHITE);

//         updateSoftBody(&ball);
//         DrawText("SOFT BODY",10,10,20,BLACK);

//         // ground
//         DrawRectangle(0,GROUND_Y,GetScreenWidth(),20,DARKBROWN);

//         DrawSoftBody(&ball);

//         EndDrawing();
//     }

//     CloseWindow();
//     return 0;
// }