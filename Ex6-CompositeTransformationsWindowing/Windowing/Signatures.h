#ifndef LUTIL_H
#define LUTIL_H

#include "Headers.h"

//Screen Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int POINT_SIZE=2;

double Sx, Sy;

//pairs of the form (min, max)
pair<double, double> window_x_dims, window_y_dims;
pair<double, double> viewport_x_dims, viewport_y_dims;

int edge_count;

vector<pair<double, double>> original_points, transformed_points;

bool initGL();

void update();

void render();

void lineloop(double x1, double y1, double x2, double y2);

void setEdgeCount(int option);

void computeScaleFactor();

void computeTransformedPoints();

void drawWindow();

void drawWindowFigure();

void drawViewport();

void drawViewportFigure();

#endif
