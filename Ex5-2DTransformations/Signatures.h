#ifndef LUTIL_H
#define LUTIL_H

#include "Headers.h"

//Screen Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int POINT_SIZE=3;
vector<int> X_points;
vector<int> Y_points;

vector<pair<double, double>> transforms;

int edge_count;
int transformation; 
double factor_x, factor_y;
double angle_radians;

bool initGL();

void update();

void render();

void y_axis();

void x_axis();

void setEdgeCount(int option);

vector<vector<double>> matrix_multiplication(double points[][3], double matrix[][3], int r1, int c1, int r2, int c2);

void drawPolygon();

void drawTranslatedPolygon(double x, double y);

void drawRotatedPolygon(double angle_radians, double x, double y);

void drawScaledPolygon(double x, double y, double xf, double yf);

void drawReflectedPolygon(double angle_radians, double intercept);

void drawShearedPolygon(double shx, double shy);

#endif
