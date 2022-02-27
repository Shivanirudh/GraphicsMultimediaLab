#include<iostream>
#include<math.h>
#include<GL/glut.h>
/*
#include<Windows.h>
#include<GL/freeglut.h>
#include<GL/glew.h>
*/

using namespace std;

void runMainLoop(int value);
int state = 0;
int counter = 0;

int Xn = 100, X0 = 10;
int Yn = 150, Y0 = 50;
int radius = 100;

int tx = 50, ty = 50;
double angle = 60;
double radians = angle * 3.1416 / 180;
double sx = 2, sy = 2;
double intercept = 0, ref_angle = 90;
double ref_radians = ref_angle * 3.1416 / 180;
double shx = 3, shy = 3;

//DDA
int round_val(double val){
    return floor(val + 0.5);
}

void DDA(){
    double dx = (Xn - X0);
    double dy = (Yn - Y0);

    double steps, xinc, yinc;
    double px = X0, py = Y0;

    steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    xinc = dx / (double)steps;
    yinc = dy / (double)steps;

    glVertex2d(round_val(px), round(py));
    for (int i = 0; i < steps; i++)
    {
        px += xinc;py += yinc;
        glVertex2d(round_val(px), round_val(py));
    }
}

//BRESENHAM
int sign(int val){
    int s = 0;
    if (val < 0){
        s = -1;
    }
    else if(val > 0){
        s = 1;
    }
    else{
        s = 0;
    }
    return s;
}

void Bresenham(){
    int px = -X0, py = -Y0;
    int dx = abs((-Xn) - (-X0)), dy = abs((-Yn) - (-Y0));
    int sign_x = sign((-Xn) - (-X0)), sign_y = sign((-Yn) - (-Y0));

    int swap = -1;
    if(dy>dx){
        int tmp = dx;
        dx = dy;
        dy = tmp;
        swap = 1;
    }
    else{
        swap = 0;
    }

    int p = (2 * dy) - dx;
    int faca = (2 * dy), facb = (2 * dy) - (2 * dx);

    glVertex2d(px, py);
    for (int i = 0; i < dx; i++)
    {
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
            py += sign_y;
            px += sign_x;
            p += facb;
        }
        glVertex2d(px, py);
    }
}

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
        if(x<y)
            break;
        
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

        if(x!=y){
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
void translate2D(int *x, int *y){
    int point[3][1] = {{*x}, {*y}, {1}};
    int matrix[3][3] = {{1, 0, tx}, {0, 1, ty}, {0, 0, 1}};

    int ans[3][1] = {{0}, {0}, {0}};
    for (int i = 0; i < 3;i++){
        for (int j = 0; j < 1;j++){
            for (int k = 0; k < 3;k++){
                ans[i][j] += (matrix[i][k] * point[k][j]);
            }
        }
    }
    *x = ans[0][0];
    *y = ans[1][0];
}

void rotate2D(int *x, int *y){
    int point[3][1] = {{*x}, {*y}, {1}};
    double matrix[3][3] = {{cos(30), -sin(30), 0}, {sin(30), cos(30), 0}, {0, 0, 1}};

    int ans[3][1] = {{0}, {0}, {0}};
    for (int i = 0; i < 3;i++){
        for (int j = 0; j < 1;j++){
            for (int k = 0; k < 3;k++){
                ans[i][j] += (matrix[i][k] * point[k][j]);
            }
        }
    }
    *x = ans[0][0];
    *y = ans[1][0];
}

void scale2D(int *x, int *y){
    int point[3][1] = {{*x}, {*y}, {1}};
    double matrix[3][3] = {{sx, 0, 0}, {0, sy, 0}, {0, 0, 1}};

    int ans[3][1] = {{0}, {0}, {0}};
    for (int i = 0; i < 3;i++){
        for (int j = 0; j < 1;j++){
            for (int k = 0; k < 3;k++){
                ans[i][j] += (matrix[i][k] * point[k][j]);
            }
        }
    }
    *x = ans[0][0];
    *y = ans[1][0];
}

void reflect2D(int *x, int *y){
    int point[3][1] = {{*x}, {*y}, {1}};
    double matrix[3][3] = {{1, 0, 0}, {0, -1, 0}, {0, 0, 1}};

    int ans[3][1] = {{0}, {0}, {0}};
    for (int i = 0; i < 3;i++){
        for (int j = 0; j < 1;j++){
            for (int k = 0; k < 3;k++){
                ans[i][j] += (matrix[i][k] * point[k][j]);
            }
        }
    }
    *x = ans[0][0];
    *y = ans[1][0];
}

void shear2D(int *x, int *y){
    int point[3][1] = {{*x}, {*y}, {1}};
    double matrix[3][3] = {{1, shy, 0}, {shx, 1, 0}, {0, 0, 1}};

    int ans[3][1] = {{0}, {0}, {0}};
    for (int i = 0; i < 3;i++){
        for (int j = 0; j < 1;j++){
            for (int k = 0; k < 3;k++){
                ans[i][j] += (matrix[i][k] * point[k][j]);
            }
        }
    }
    *x = ans[0][0];
    *y = ans[1][0];
}

void ModifiedBresenham(){
    int px = -X0, py = -Y0;
    int dx = abs((-Xn) - (-X0)), dy = abs((-Yn) - (-Y0));
    int sign_x = sign((-Xn) - (-X0)), sign_y = sign((-Yn) - (-Y0));

    int swap = -1;
    if(dy>dx){
        int tmp = dx;
        dx = dy;
        dy = tmp;
        swap = 1;
    }
    else{
        swap = 0;
    }

    int p = (2 * dy) - dx;
    int faca = (2 * dy), facb = (2 * dy) - (2 * dx);

    int pxt = px, pyt = py;
    int pxr = px, pyr = py;
    int pxs = px, pys = py;
    int pxf = px, pyf = py;
    int pxh = px, pyh = py;
    
    translate2D(&pxt, &pyt);
    rotate2D(&pxr, &pyr);
    scale2D(&pxs, &pys);
    reflect2D(&pxf, &pyf);
    shear2D(&pxh, &pyh);
    glVertex2d(pxt, pyt);
    glVertex2d(pxr, pyr);
    glVertex2d(pxs, pys);
    glVertex2d(pxf, pyf);
    glVertex2d(pxh, pyh);
    for (int i = 0; i < dx; i++)
    {
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
            py += sign_y;
            px += sign_x;
            p += facb;
        }
        pxt = px;
        pyt = py;
        pxr = px;
        pyr = py;
        pxs = px;
        pys = py;
        pxf = px;
        pyf = py;
        pxh = px;
        pyh = py;

        translate2D(&pxt, &pyt);
        rotate2D(&pxr, &pyr);
        scale2D(&pxs, &pys);
        reflect2D(&pxf, &pyf);
        shear2D(&pxh, &pyf);
        glVertex2d(pxt, pyt);
        glVertex2d(pxr, pyr);
        glVertex2d(pxs, pys);
        glVertex2d(pxf, pyf);
        glVertex2d(pxh, pyh);
    }
}

void render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
    glColor3f(1, 1, 1);
    glBegin(GL_POINTS);
    glVertex2d(50*counter, 50*counter);
    glVertex2d(0, 0);
    glVertex2d(-50*counter, -50*counter);
    
    glColor3f(0, 1, 0);
    DDA();

    glColor3f(1, 0, 0);
    Bresenham();

    glColor3f(0, 0, 1);
    Midpoint();

    glColor3f(1, 1, 0);
    ModifiedBresenham();
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char *argv[]){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Revision");

    gluOrtho2D(-800, 800, -600, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // int x = X0, y = Y0;
    // cout << x << " " << y << endl;
    // rotate2D(&x, &y);
    // cout<< x << " " << y << endl;

    glutDisplayFunc(render);
    glutTimerFunc(1000, runMainLoop,state);
    glutMainLoop();

    return 0;
}

void runMainLoop(int value){
    render();
    if(counter == 5){
        state = 1;
    }
    if(counter == 0){
        state = 0;
    }
    counter = (state == 0) ? counter + 1 : counter - 1;
    glutTimerFunc(1000, runMainLoop, state);
}