#include<iostream>
/*
#include<Windows.h>
#include<GL/freeglut.h>
#include<GL/glew.h>
*/
#include<GL/glut.h>
#include<math.h>

using namespace std;

void runMainLoop(int value);
bool ortho = true;
int state = 0;

double x_rotate = 0, y_rotate = 0;

void drawAxes(){
    glColor3d(0, 0, 1);
    glBegin(GL_LINES);

    glVertex2f(-2, 0);
    glVertex2f(2, 0);

    glVertex2f(0, -2);
    glVertex2f(0, 2);

    glEnd();
    glFlush();
}

void render(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glColor3f(1.0, 1.0, 1.0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLineWidth(3);

    glMatrixMode(GL_MODELVIEW);

    drawAxes();
    glPushMatrix();

    if(state){
        glOrtho(-2, 2, -2, 2, -2, 2);
    }
    else{
        gluPerspective(120, 1, 0.1, 50);
    }
    gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);

    glRotatef(x_rotate, 1, 0, 0);
    glRotatef(y_rotate, 0, 1, 0);

    glTranslatef(state * 0.1, state * 0.1, 0);
    glScalef(state * 0.5, 1, 1);

    glColor4f(1, 1, 1, 1);
    glutWireTeapot(0.5);

    glPopMatrix();
    glFlush();
}

void keyboardKeys(unsigned char key, int x, int y){
    key = tolower(key);

    switch(key){
        case 'w':
            x_rotate += 5;
            break;
        case 's':
            x_rotate -= 5;
            break;
        case 'a':
            y_rotate -= 5;
            break;
        case 'd':
            y_rotate -= 5;
            break;
        case 32:
            ortho = !ortho;
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("3D");

    glutDisplayFunc(render);
    glutKeyboardFunc(keyboardKeys);
    glutTimerFunc(1000, runMainLoop, 1000);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glutMainLoop();
    return 0;
}

void runMainLoop(int value){
    render();
    state = (state + 1) % 5;
    glutTimerFunc(1000, runMainLoop, 1000);
}