#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAX_BALLS 15 // Tweak Here
#define K_VAL 10 // Tweak Here

static int redBallCount = 0;
static int blueBallCount = 0;

typedef struct pointBlock {
    double dist;
    char * color;
} pointBlock;

double getDistance(Vector2 a, Vector2 b) {

    double diff_x = a.x - b.x;
    double diff_y =  a.y - b.y;

    double dist = sqrt((diff_x * diff_x) + (diff_y * diff_y));
    return dist;

}

void swapPointBlock(pointBlock * a, pointBlock * b) {
    pointBlock temp = * a;
    * a = * b;
    * b = temp;
}

void sortPointBlockDist(pointBlock dist[]) {
    for(int i = 0; i < 2*MAX_BALLS - 1; ++i) {
        for(int j = 0; j < 2*MAX_BALLS - i - 1; ++j) {
            if(dist[j].dist > dist[j+1].dist) {
                swapPointBlock(&dist[j], &dist[j+1]);
            }
        }
    }
}

int main() {

    int width = 1024;
    int height = width/2;

    InitWindow(width, height, "WINDOW");
    SetTargetFPS(60);

    Vector2 redPoints[MAX_BALLS];
    Vector2 bluePoints[MAX_BALLS];

    Vector2 greyPoint = {
        .x = (double) width/2.2 + GetRandomValue(10, 100),
        .y = (double) height/2.2 + GetRandomValue(100, 10),
    };

    double pointDist[2*MAX_BALLS];
    pointBlock pointBlockDist[2*MAX_BALLS];

    for(size_t i = 0; i < MAX_BALLS; ++i) {

        redPoints[i].x = (double) width/2 + GetRandomValue(100, 10);
        redPoints[i].y = (double) height/2 + GetRandomValue(10, 100);

        bluePoints[i].x = (double) width/2.7 + GetRandomValue(10, 100);
        bluePoints[i].y = (double) height/2.7 + GetRandomValue(100, 10);

    }

    while(!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(greyPoint, 5, BLACK);

        for(size_t i = 0; i < MAX_BALLS; ++i) {
            DrawCircleV(redPoints[i], 5, RED);
            DrawCircleV(bluePoints[i], 5, BLUE);

            pointDist[i] = getDistance(greyPoint, redPoints[i]);
            pointDist[i+MAX_BALLS] = getDistance(greyPoint, bluePoints[i]);

            pointBlockDist[i].dist = getDistance(greyPoint, redPoints[i]);
            pointBlockDist[i].color = "R";
            pointBlockDist[i + MAX_BALLS].dist = getDistance(greyPoint, bluePoints[i]);
            pointBlockDist[i + MAX_BALLS].color = "B";
        }


        EndDrawing();


    }

    sortPointBlockDist(pointBlockDist);

    printf("-----------------------------\n");

    for(int i = 0; i < 2*MAX_BALLS; ++i) {
        printf("%.2f\t%s\n", pointBlockDist[i].dist, pointBlockDist[i].color);
    }

    printf("-----------------------------\n");

    for(int i = 0; i < K_VAL; ++i) {
        if(strcmp(pointBlockDist[i].color, "R") == 0) {
            redBallCount++;
        } else {
            blueBallCount++;
        }
    }

    printf("R\tB\n");
    printf("%d\t%d\n", redBallCount, blueBallCount);

    if(redBallCount > blueBallCount) {
        printf("It's Red!!\n");
    } else {
        printf("It's Blue!!\n");
    }

    CloseWindow();

    return 0;

}
