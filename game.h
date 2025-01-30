#ifndef GAME_H
#define GAME_H

#include <raylib.h>

extern int score;
extern int level;
extern int continuousScore;
extern bool levelUpScreenVisible;
extern float levelScreenTimer;

typedef struct {
    float x, y;
    int speed_x, speed_y;
    int radius;
} Ball;

typedef struct {
    float x, y;
    float width, height;
    int speed;
} Paddle;

extern Ball ball;
extern Paddle player, wall;

void initGame();
void showLevelScreen();
void checkLevelUp();
void updateLevelLogic();

#endif
