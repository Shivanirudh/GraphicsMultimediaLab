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

double transform1[3][3];
double transform2[3][3];

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

vector<vector<double>> matrix_multiplication(double points[][3], int pr);

void drawPolygon();

void applyTransforms();

void drawTransfomedPolygon();

void setTranslateMatrix(double x, double y, int transform_number);

void setRotateMatrix(double angle_radians, double x, double y, int transform_number);

void setScaleMatrix(double x, double y, double xf, double yf, int transform_number);

void setReflectMatrix(double angle_radians, double intercept, int transform_number);

void setShearMatrix(double shx, double shy, int transform_number);

#endif
