#ifndef LUTIL_H
#define LUTIL_H

#include "Headers.h"

//Screen Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int POINT_SIZE=2;
int X0,Y0, radius;

const int coords[][3] ={{0, 0, 6},
             {2, 3, 6},
            }; 

bool initGL();

void update();

void render();

void y_axis();

void x_axis();

void selectCenter(int option);

vector<pair<int, int>> Midpoint();

#endif
