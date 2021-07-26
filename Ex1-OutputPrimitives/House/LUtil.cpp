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
    
    building();
    roof();
    door();
    window();
    chimney();
    
    glFlush(); 

    //Update screen
    //glutSwapBuffers();
}


void line(int x1, int y1, int x2, int y2) {       

    glBegin(GL_LINES);         
    
    glVertex2d(x1,y1); 
    glVertex2d(x2,y2);

    glEnd();         
}      

void lineloop(int x1, int y1, int x2, int y2) {  

    glBegin(GL_LINE_LOOP);         
   
    glVertex2d(x1,y1);         
    glVertex2d(x2,y1);         
    glVertex2d(x2,y2);      
    glVertex2d(x1,y2);     
   
    glEnd();         
}      

void triangle(int x1, int y1, int x2, int y2, int x3, int y3) {       

    glBegin(GL_TRIANGLES);         
   
    glVertex2d(x1,y1);     
    glVertex2d(x2,y2);      
    glVertex2d(x3,y3);   
   
    glEnd();         
}      

void quad(int x1, int y1, int x2, int y2) {         

    glBegin(GL_QUADS);         
   
    glVertex2d(x1,y1);         
    glVertex2d(x2,y1);         
    glVertex2d(x2,y2);      
    glVertex2d(x1,y2);    
           
    glEnd();         
}     

void building() {
    lineloop(250,100, 330,250); 

    lineloop(330,100, 530,250);
}

void roof() {
    triangle(250,250, 330,250, 290,300);
    line(290,300, 490,300);
    line(490,300, 530,250);

}

void door(){
    quad(280,100, 283,160);
    quad(280,158, 300,160);
    quad(297,100, 300,160);
}
 
void window(){
    quad(418,155, 420,167);
    quad(418,165, 442,167);
    quad(418,153, 442,155);
    quad(440,155, 442,167);
    line(430,155, 430,165);
    line(420,160, 440,160);
}

void chimney(){
    quad(500,260, 515,310);
}
