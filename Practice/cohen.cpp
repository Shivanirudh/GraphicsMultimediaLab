#include<iostream>
#include<GL/glut.h>

/*
#include<windows.h>
#include<GL/freeglut.h>
#include<GL/glew.h>
#include<iostream>
*/

using namespace std;

void runMainLoop(int val);

void render(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glFlush();
    glBegin(GL_POINTS);
    glVertex2d(100, 100);
    glVertex2d(200, 200);
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GL_DOUBLE | GL_RGBA | GL_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cohen Sutherland");

    gluOrtho2D(-800, 800, -600, 600);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glutDisplayFunc(render);
    glutTimerFunc(1000, runMainLoop, 0);
    glutMainLoop();
}

void runMainLoop(int value){
    render();
    glutTimerFunc(1000, runMainLoop, 0);
}