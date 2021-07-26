#ifndef LUTIL_H
#define LUTIL_H

#include "LOpenGL.h"
#include <stdio.h>

//Screen Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

bool initGL();

void update();

void render();

void building();

void roof();

void door();

void window();

void chimney();

void line(int x1, int y1, int x2, int y2);

void lineloop(int x1, int y1, int x2, int y2);

void triangle(int x1, int y1, int x2, int y2, int x3, int y3);

void quad(int x1, int y1, int x2, int y2); 


#endif
