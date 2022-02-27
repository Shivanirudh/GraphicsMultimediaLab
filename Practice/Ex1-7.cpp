#include<iostream>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>


/*
#include<Windows.h>
#include<GL/glew.h>
#include<GL/freeglut.h>
*/

using namespace std;
int state = 0;

void runMainLoop(int value);

double Xn = 100, X0 = 10, Yn = 150, Y0 = 15;
int rounded_val(double v);
void DDA();
int sign(int v);
void Bresenham();

double radius = 100;
void Midpoint();

int transform = 0;
void plot_point(int x, int y);

int tr_x = 50, tr_y = 50;
void translate2D(int *x, int *y);

double angle = 60;
double radians = (angle * 3.1416) / 180;
void rotate2D(int *x, int *y);

double sc_x = 2.5, sc_y = 2.5;
void scale2D(int *x, int *y);

void reflect2D(int *x, int *y);

double sh_x = 3, sh_y = 3;
void shear2D(int *x, int *y);

int xmin = -100, xmax = 100;
int ymin = -100, ymax = 100;
int X1 = -120, Y1 = -70;
int rc1[4] = {0, 0, 0, 0};
int x2 = 70, y2 = 120;
int rc2[4] = {0, 0, 0, 0};
void lineloop(int xmin, int ymin, int xmax, int ymax);
void computeRegionCodes();
bool trivial_accept();
bool trivial_reject();
void drawline(int x1, int y1, int x2, int y2);
void CohenSutherland();

//DDA
int rounded_val(double v){
    return floor(v + 0.5);
}

void DDA(){
    double dx = Xn - X0;
    double dy = Yn - Y0;

    double px = X0, py = Y0;
    double steps = (abs(dx) > abs(dy))? abs(dx) : abs(dy);
    double xinc = dx / steps, yinc = dy / steps;

    glVertex2d(rounded_val(px), rounded_val(py));
    for (int i = 0; i < steps;i++){
        px += xinc;
        py += yinc;
        glVertex2d(rounded_val(px), rounded_val(py));
    }
}

//Bresenham
int sign(int v){
    if(v > 0){
        return 1;
    }
    else if(v<0){
        return -1;
    }
    else{
        return 0;
    }
}

void Bresenham(){
    int px = X0, py = Y0;
    px *= -1;
    py *= -1;

    int dx = abs((-Xn) - (-X0)), dy = abs((-Yn) - (-Y0));
    int sign_x = sign((-Xn) - (-X0)), sign_y = sign((-Yn) - (-Y0));

    int swap = -1;
    if(dy > dx){
        int tmp = dx;
        dx = dy;
        dy = tmp;
        swap = 1;
    }
    else{
        swap = 0;
    }

    int p = (2 * dy) - dx;
    int faca = 2 * dy, facb = (2 * dy) - (2 * dx);

    plot_point(px, py);
    for (int i = 0; i < dx;i++){
        if(p<0){
            if(swap == 1){
                py += sign_y;
            }
            else{
                px += sign_x;
            }
            p += faca;
        }
        else{
            px += sign_x;
            py += sign_y;
            p += facb;
        }
        plot_point(px, py);
    }
}


//Midpoint
void Midpoint(){
    int x = radius, y = 0;
    int p = 1 - radius;

    int px = x + X0, py = y + Y0;
    glVertex2d(px, py);
    if(radius < 0){
        px = x + X0;
        py = -y + Y0;
        glVertex2d(px, py);

        px = y + X0;
        py = x + Y0;
        glVertex2d(px, py);

        px = -y + X0;
        py = x + Y0;
        glVertex2d(px, py);
    }

    while(x>y){
        y++;
        if(p<=0){
            p += ((2 * y) + 1);
        }
        else{
            x--;
            p += ((2 * y) - (2 * x) + 1);
        }
        if(x<y){
            break;
        }

        px = x + X0;
        py = y + Y0;
        glVertex2d(px, py);

        px = x + X0;
        py = -y + Y0;
        glVertex2d(px, py);

        px = -x + X0;
        py = y + Y0;
        glVertex2d(px, py);

        px = -x + X0;
        py = -y + Y0;
        glVertex2d(px, py);

        if(x != y){
            px = y + X0;
            py = x + Y0;
            glVertex2d(px, py);

            px = y + X0;
            py = -x + Y0;
            glVertex2d(px, py);

            px = -y + X0;
            py = x + Y0;
            glVertex2d(px, py);

            px = -y + X0;
            py = -x + Y0;
            glVertex2d(px, py);
        }
    }
}

//Transforms
void plot_point(int x, int y){
    switch(transform){
        case 1:
            translate2D(&x, &y);
            break;
        case 2:
            rotate2D(&x, &y);
            break;
        case 3:
            scale2D(&x, &y);
            break;
        case 4:
            reflect2D(&x, &y);
            break;
        case 5:
            shear2D(&x, &y);
            break;
        }
        glVertex2d(x, y);
}

//Translation

void translate2D(int *x, int *y){
    int point[3][1] = {{*x}, {*y}, 1};
    int matrix[3][3] = {{1, 0, tr_x}, {0, 1, tr_y}, {0, 0, 1}};

    int ans[3][1] = {{0}, {0}, {0}};
    for (int i = 0;i < 3; i++){
        for (int j = 0; j < 1; j++){
            for (int k = 0; k < 3;k++){
                ans[i][j] += (matrix[i][k] * point[k][j]);
            }
        }
    }
    *x = ans[0][0];
    *y = ans[0][1];
}

//Rotation

void rotate2D(int *x, int *y){
    int point[3][1] = {{*x}, {*y}, 1};
    int matrix[3][3] = {{cos(radians), -sin(radians), 0}, {sin(radians), cos(radians), 0}, {0, 0, 1}};

    int ans[3][1] = {{0}, {0}, {0}};
    for (int i = 0;i < 3; i++){
        for (int j = 0; j < 1; j++){
            for (int k = 0; k < 3;k++){
                ans[i][j] += (matrix[i][k] * point[k][j]);
            }
        }
    }
    *x = ans[0][0];
    *y = ans[0][1];
}

//Scaling

void scale2D(int *x, int *y){
    int point[3][1] = {{*x}, {*y}, 1};
    int matrix[3][3] = {{sc_x, 0, 0}, {0, sc_y, 0}, {0, 0, 1}};

    int ans[3][1] = {{0}, {0}, {0}};
    for (int i = 0;i < 3; i++){
        for (int j = 0; j < 1; j++){
            for (int k = 0; k < 3;k++){
                ans[i][j] += (matrix[i][k] * point[k][j]);
            }
        }
    }
    *x = ans[0][0];
    *y = ans[0][1];
}

//Reflection

void reflect2D(int *x, int *y){
    int point[3][1] = {{*x}, {*y}, 1};
    int matrix[3][3] = {{1, 0, 0}, {0, -1, 0}, {0, 0, 1}};

    int ans[3][1] = {{0}, {0}, {0}};
    for (int i = 0;i < 3; i++){
        for (int j = 0; j < 1; j++){
            for (int k = 0; k < 3;k++){
                ans[i][j] += (matrix[i][k] * point[k][j]);
            }
        }
    }
    *x = ans[0][0];
    *y = ans[0][1];
}

//Shearing

void shear2D(int *x, int *y){
    int point[3][1] = {{*x}, {*y}, 1};
    int matrix[3][3] = {{1, sh_y, 0}, {sh_x, 1, 0}, {0, 0, 1}};

    int ans[3][1] = {{0}, {0}, {0}};
    for (int i = 0;i < 3; i++){
        for (int j = 0; j < 1; j++){
            for (int k = 0; k < 3;k++){
                ans[i][j] += (matrix[i][k] * point[k][j]);
            }
        }
    }
    *x = ans[0][0];
    *y = ans[0][1];
}

//Cohen Sutherland

void lineloop(int xmin, int ymin, int xmax, int ymax){
    glBegin(GL_LINE_LOOP);
    glVertex2d(xmin, ymin);
    glVertex2d(xmin, ymax);
    glVertex2d(xmax, ymax);
    glVertex2d(xmin, ymax);
    glEnd();
}

void computeRegionCodes(){
    //point 1
    if(Y1 > ymax)
        rc1[0] = 1;
    if(Y1<ymin)
        rc1[1] = 1;
    if(X1<xmin)
        rc1[2] = 1;
    if(X1>xmax)
        rc1[3] = 1;
    
    //point 2
    if(y2 > ymax)
        rc2[0] = 1;
    if(y2<ymin)
        rc2[1] = 1;
    if(x2<xmin)
        rc2[2] = 1;
    if(x2>xmax)
        rc2[3] = 1;
}
bool trivial_accept(){
    computeRegionCodes();
    int sum = 0;
    for (int i = 0; i < 4;i++){
        sum += (rc1[i] + rc2[i]);
    }
    return (sum == 0) ? true : false;
}
bool trivial_reject(){
    computeRegionCodes();
    int sum = 0;
    for (int i = 0; i < 4;i++){
        sum += (rc1[i] * rc2[i]);
    }   
    return (sum > 0) ? true : false;
}

void drawline(int x1, int y1, int x2, int y2){
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}

void CohenSutherland(){
    lineloop(xmin, ymin, xmax, ymax);
    glColor3f(1.0, 0.0, 0.0);
    drawline(X1, Y1, x2, y2);

    int nx1 = X1, ny1 = Y1;
    int nx2 = x2, ny2 = y2;

    for (int i = 0; i < 5;i++){
        if (trivial_accept())
        {
            cout << "Trivially accepted" << endl;
            glColor3f(0.0, 1.0, 0.0);
            drawline(nx1, ny1, nx2, ny2);
            break;
            // Sleep(3);
        }
        if(trivial_reject()){
            cout << "Trivially accepted" << endl;
            // Sleep(3);
            break;
        }
        double slope = (y2 - Y1)/(x2 - X1);

        //Point 1
        if(rc1[0] == 1){
            ny1 = ymax;
            nx1 = X1 + (ymax - Y1) / slope;
        }
        if(rc1[1] == 1){
            ny1 = ymin;
            nx1 = X1 + (ymin - Y1) / slope;
        }
        if(rc1[2] == 1){
            nx1 = xmax;
            ny1 = Y1 + (xmax - X1) * slope;
        }
        if(rc1[3] == 1){
            nx1 = xmin;
            ny1 = Y1 + (xmin - X1) * slope;
        }

        //Point 2
        if(rc2[0] == 1){
            ny2 = ymax;
            nx2 = x2 + (ymax - y2) / slope;
        }
        if(rc2[1] == 1){
            ny2 = ymin;
            nx2 = x2 + (ymin - y2) / slope;
        }
        if(rc2[2] == 1){
            nx2 = xmax;
            ny2 = y2 + (xmax - x2) * slope;
        }
        if(rc2[3] == 1){
            nx2 = xmin;
            ny2 = y2 + (xmin - x2) * slope;
        }
        glColor3f(0.0, 1.0, 0.0);
        drawline(nx1, ny1, nx2, ny2);
    }
}

void render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
    glColor3f(1, 1, 1);
    glBegin(GL_POINTS);
    if(state == 1){
        DDA();
    }
    else if (state == 2){
        Bresenham();
    }
    else if(state == 3){
        Midpoint();
    }
    else if(state == 4){
        CohenSutherland();
    }
    else{
        glVertex2d(X0, Y0);
        glVertex2d(Xn, Yn);
    }
    glEnd();
    glutSwapBuffers();
}


int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Basics");

    gluOrtho2D(-800, 800, -600, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glutDisplayFunc(render);
    glutTimerFunc(1000, runMainLoop, state);
    glutMainLoop();

    return 0;
}

void runMainLoop(int value){
    render();

    state = (state+1) % 5;
    if(state == 0){
        transform = (transform + 1) % 6;
    }
    glutTimerFunc(1000, runMainLoop, state);
}