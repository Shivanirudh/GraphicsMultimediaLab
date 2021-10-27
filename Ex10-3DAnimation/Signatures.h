#ifndef LUTIL_H
#define LUTIL_H

#include "Headers.h"

//Screen Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int POINT_SIZE=2;

int INC = 1;

void initGL();

void render(int state);

void keyboardKeys(unsigned char key, int x, int y);

void drawAxes();


#endif
