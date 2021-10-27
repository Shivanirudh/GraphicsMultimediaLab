#include "Signatures.h"



void render(){
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    //Translucency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Line width
    glLineWidth(3);

    //Apply the transformations & drawing on the model view matrix
    glMatrixMode(GL_MODELVIEW);

    //Draw the X and Y axis
    drawAxes();

    //Transform only the drawn object, so use the matrix stack accordingly
    glPushMatrix();

    if(isOrthoProjection){
        //Parallel Projection
        glOrtho(-2, 2, -2, 2, -2, 2);
    } else{
        //Perspective Projection
        gluPerspective(120, 1, 0.1, 50); //FoVy = 120, Aspect Ratio = 1
    }

    gluLookAt(0, 0, 1, 0, 0, 0, 0, 1, 0);   //Camera, Center & Up Vector
    glRotatef(x_rotate, 1, 0, 0);   //Keyboard based rotations
    glRotatef(y_rotate, 0, 1, 0);

    glColor4f(1, 1, 1, 0.3);    //Draw the object
    glutWireTeapot(0.5);

    glPopMatrix();  //Pop the matrix back into the model view stack

    glFlush();
}

void drawAxes(){
    //To draw X and Y axis

    glColor3d(0, 1, 1);

    glBegin(GL_LINES);

    glVertex2f(-2, 0);
    glVertex2f(2, 0);

    glVertex2f(0, -2);
    glVertex2f(0, 2);

    glEnd();
    glFlush();
}

void keyboardKeys(unsigned char key, int x, int y){
    //Callback function for keyboard interactivity

    key = tolower(key);

    switch(key){
        case 'w':{
            x_rotate += 5;
            break;
        }
        case 's':{
            x_rotate -= 5;
            break;
        }
        case 'd':{
            y_rotate += 5;
            break;
        }
        case 'a':{
            y_rotate -= 5;
            break;
        }
        case 32:{
            //Spacebar for changing projections
            isOrthoProjection = !isOrthoProjection;
            break;
        }
    }

    //Update the display
    glutPostRedisplay();
}