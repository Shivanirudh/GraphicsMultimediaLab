#ifndef LUTIL_H
#define LUTIL_H

#include "Headers.h"

//Screen Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int POINT_SIZE=2;
int X0,Y0,Xn,Yn;

const int coords[][4] ={{2, 1, 8, 3},
             {2, 1, 10, 12},
             {-2, 1, -8, 3},
             {-2, 1, -4, 6},
             {-2, -1, -8, -3},
             {-2, -1, -4, -6},
             {2, -1, 8, -3},
             {2, -1, 4, -6},
            }; 

bool initGL();

void update();

void render();

void selectOctant(int option);

vector<pair<int, int>> Bresenham();

#endif
