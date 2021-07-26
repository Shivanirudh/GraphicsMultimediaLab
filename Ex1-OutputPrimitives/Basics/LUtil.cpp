/*This source code copyrighted by Lazy Foo' Productions (2004-2013)
and may not be redistributed without written permission.*/
//Version: 001

#include "LUtil.h"

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

/*
void render()
{
    //Clear color buffer
     glClear(GL_COLOR_BUFFER_BIT);
     glBegin(GL_LINES);
        glVertex2d(70,130);
        glVertex2d(100,230);
        glVertex2d(170,130);
        glVertex2d(300,350);
     glEnd();
     glFlush(); 

    //Update screen
    //glutSwapBuffers();
}

void render()
{
    //Clear color buffer
     glClear(GL_COLOR_BUFFER_BIT);
     glBegin(GL_LINE_STRIP);
        glVertex2d(70,130);
        glVertex2d(100,230);
        glVertex2d(170,130);
        glVertex2d(300,350);
     glEnd();
     glFlush(); 

    //Update screen
    //glutSwapBuffers();
}

void render()
{
    //Clear color buffer
     glClear(GL_COLOR_BUFFER_BIT);
     glBegin(GL_LINE_LOOP);
        glVertex2d(70,130);
        glVertex2d(100,230);
        glVertex2d(170,130);
        glVertex2d(300,350);
     glEnd();
     glFlush(); 

    //Update screen
    //glutSwapBuffers();
}

void render()
{
    //Clear color buffer
     glClear(GL_COLOR_BUFFER_BIT);
     glBegin(GL_TRIANGLES);
        glVertex2d(70,130);
        glVertex2d(100,230);
        glVertex2d(170,130);
        glVertex2d(300,350);
     glEnd();
     glFlush(); 

    //Update screen
    //glutSwapBuffers();
}

void render()
{
    //Clear color buffer
     glClear(GL_COLOR_BUFFER_BIT);
     glBegin(GL_QUADS);
        glVertex2d(70,130);
        glVertex2d(100,230);
        glVertex2d(170,130);
        glVertex2d(300,350);
     glEnd();
     glFlush(); 

    //Update screen
    //glutSwapBuffers();
}

void render()
{
    //Clear color buffer
     glClear(GL_COLOR_BUFFER_BIT);
     glBegin(GL_QUAD_STRIP);
        glVertex2d(70,130);
        glVertex2d(100,230);
        glVertex2d(170,130);
        glVertex2d(300,350);
     glEnd();
     glFlush(); 

    //Update screen
    //glutSwapBuffers();
}

void render()
{
    //Clear color buffer
     glClear(GL_COLOR_BUFFER_BIT);
     glBegin(GL_POLYGON);
        glVertex2d(70,130);
        glVertex2d(100,230);
        glVertex2d(170,130);
        glVertex2d(300,350);
     glEnd();
     glFlush(); 

    //Update screen
    //glutSwapBuffers();
}
*/