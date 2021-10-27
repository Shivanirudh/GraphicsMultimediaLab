#ifndef LUTIL_H
#define LUTIL_H

#include "Headers.h"

//Screen Constants
const int SCREEN_WIDTH = 1362;
const int SCREEN_HEIGHT = 750;
const int SCREEN_FPS = 60;
const int POINT_SIZE=3;

typedef float MatrixDim [4][4];
MatrixDim transformation_matrix;

static GLfloat input[8][3]={
    {40,40,-50},{90,40,-50},{90,90,-50},{40,90,-50},
    {30,30,0},{80,30,0},{80,80,0},{30,80,0}

};

float output[8][3];
float tx,ty,tz;
float sx,sy,sz;
float angle;

int choice,choiceRot;

void init();

void render();

void setIdentityM(MatrixDim m);

void translate(int tx, int ty, int tz);

void scale(int sx, int sy, int sz);

void RotateX(float angle);

void RotateY(float angle);

void RotateZ(float angle);

void multiplyMatrices();

void Axes(void);

void draw(float a[8][3]);

#endif
