#ifndef LUTIL_H
#define LUTIL_H

#include "Headers.h"

//Screen Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int POINT_SIZE=2;

//pairs of the form (min, max)
pair<double, double> window_x_dims, window_y_dims;

pair<double, double> original_point1, new_point1;
pair<double, double> original_point2, new_point2;

int region_code1[4] = {0, 0, 0, 0},
	region_code2[4] = {0, 0, 0, 0};

bool initGL();

void update();

void render();

void lineloop(double x1, double y1, double x2, double y2);

void drawWindow();

void drawOriginalLine();

void computeRegionCode1();

void computeRegionCode2();

bool trivial_accept();

bool trivial_reject();

void drawClippedLine();

void CohenSutherland();

#endif
