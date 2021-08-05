#ifndef LUTIL_H
#define LUTIL_H

#include "Headers.h"

//Screen Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int POINT_SIZE=2;

bool initGL();

void update();

void render();


void circle(int X0, int Y0, int radius);

void line(int x1, int y1, int x2, int y2);

void lineloop(int x1, int y1, int x2, int y2);

void solidQuad(int x1, int y1, int x2, int y2);

void platform();

void human();

void head();

void body();

void brush();

void canvas();

void art();

void base();

void snowman();

#endif
