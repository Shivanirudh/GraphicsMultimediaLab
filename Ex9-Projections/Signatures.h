#ifndef LUTIL_H
#define LUTIL_H

#include "Headers.h"

//Screen Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int POINT_SIZE=2;

const double X_MIN = -500;
const double X_MAX = 500;
const double Y_MIN = -500;
const double Y_MAX = 500;

double x_rotate = 0;
double y_rotate = 0;

bool isOrthoProjection = true;

void render();

void keyboardKeys(unsigned char key, int x, int y);

void drawAxes();


#endif
