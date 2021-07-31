#include "Signatures.h"

bool initGL()
{
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	gluOrtho2D(0.0,640.0,0.0,480.0);
	
    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    return true;
}

void update()
{

}

void render()
{
    //Clear color buffer
     glClear(GL_COLOR_BUFFER_BIT);
     glBegin(GL_POINTS);
     	glVertex2d(70,130);
     	glVertex2d(100,230);
     	glVertex2d(170,130);
     	glVertex2d(300,350);
     glEnd();
     glFlush(); 

    //Update screen
    //glutSwapBuffers();
}
