#include<iostream>
#include<GL/glut.h>
/*
#include<Windows.h>
#include<GL/freeglut.h>
#include<GL/glew.h>
#include<iostream>
*/

using namespace std;

void runMainLoop(int val);

void Circle(int X0, int Y0, int radius)
{
    int x = radius;
    int y = 0;
    int p = 1- radius;
    glBegin(GL_POINTS);
    int point_x = x+X0;
    int point_y = y+Y0;
    glVertex2d(point_x, point_y);
    if(radius<0){
        point_x = x + X0;point_y = -y + Y0;glVertex2d(point_x, point_y);
        point_x = y + X0;point_y = x + Y0;glVertex2d(point_x, point_y);
        point_x = -y + X0;point_y = x + Y0;glVertex2d(point_x, point_y);
    }
    while(x>y){
        y++;
        if(p<=0){
            p += ((2*y) + 1);
        }
        else{
            x--;
            p += ((2*y) - (2*x) + 1);
        }
        if(x<y)
            break;
        point_x = x + X0;point_y = y + Y0;glVertex2d(point_x, point_y);
        point_x = x + X0;point_y = -y + Y0;glVertex2d(point_x, point_y);
        point_x = -x + X0;point_y = y + Y0;glVertex2d(point_x, point_y);
        point_x = -x + X0;point_y = -y + Y0;glVertex2d(point_x, point_y);
        if(x!=y){
            point_x = y + X0;point_y = x + Y0;glVertex2d(point_x, point_y);
            point_x = -y + X0;point_y = x + Y0;glVertex2d(point_x, point_y);
            // point_x = y + X0;point_y = -x + Y0;glVertex2d(point_x, point_y);
            // point_x = -y + X0;point_y = -x + Y0;glVertex2d(point_x, point_y);
        }
    }
    glEnd();
    glFlush();
}



void render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
    glBegin(GL_POINTS);
    Circle(0, 0, 400);
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Vanakkam");

    gluOrtho2D(-800, 800, -600, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glutDisplayFunc(render);
    glutTimerFunc(1000, runMainLoop, 0);
    glutMainLoop();
    return 0;
}

void runMainLoop(int val){
    render();
    glutTimerFunc(1000, runMainLoop, 0);
}