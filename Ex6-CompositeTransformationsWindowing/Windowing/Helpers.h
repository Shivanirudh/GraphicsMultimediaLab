#include "Signatures.h"

bool initGL(){
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	gluOrtho2D(0.0,640.0,0.0,480.0);
	
    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // glTranslatef( SCREEN_WIDTH / 3.f, SCREEN_HEIGHT / 3.f, 0.f );

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    glPointSize(POINT_SIZE);
    glEnable(GL_POINT_SMOOTH);

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    return true;
}

void update(){

}

void render(){
    drawWindow();
    drawWindowFigure();
    drawViewport();

    computeScaleFactor();
    computeTransformedPoints();

    drawViewportFigure();

    glFlush(); 
}

void setEdgeCount(int option){
    if(option == 0){
        cout<<"Invalid"<<endl;
    }
    else if(option == 1 || option == 2){
        edge_count = 2;
    }
    else{
        edge_count = option;
    }
}

void lineloop(double x1, double y1, double x2, double y2) {  

    glBegin(GL_LINE_LOOP);         
   
    glVertex2d(x1,y1);         
    glVertex2d(x2,y1);         
    glVertex2d(x2,y2);      
    glVertex2d(x1,y2);     
   
    glEnd();         
}      

void drawWindow(){
    glColor3f(1.0,1.0,1.0);
    lineloop(window_x_dims.first, window_y_dims.first, window_x_dims.second, window_y_dims.second);
}

void drawWindowFigure(){
    glColor3f(1.0,1.0,1.0);
    if(edge_count==2)
        glBegin(GL_LINES);
    else
        glBegin(GL_POLYGON);
    
    for (int i = 0; i < edge_count; i++){
        glVertex2d(original_points[i].first, original_points[i].second);
    }
    glEnd();
    glFlush();
}

void drawViewport(){
    glColor3f(0.0,1.0,0.0);
    lineloop(viewport_x_dims.first, viewport_y_dims.first, viewport_x_dims.second, viewport_y_dims.second);
}

void drawViewportFigure(){
    glColor3f(0.0,1.0,0.0);
    if(edge_count==2)
        glBegin(GL_LINES);
    else
        glBegin(GL_POLYGON);
    
    for (int i = 0; i < edge_count; i++){
        glVertex2d(transformed_points[i].first, transformed_points[i].second);
    }
    glEnd();
    glFlush();
}

void computeScaleFactor(){

    double xNr = viewport_x_dims.second - viewport_x_dims.first;
    double xDr = window_x_dims.second - window_x_dims.first;

    Sx = xNr/xDr;

    double yNr = viewport_y_dims.second - viewport_y_dims.first;
    double yDr = window_y_dims.second - window_y_dims.first;

    Sy = yNr/yDr;
}

void computeTransformedPoints(){
    for(int i=0;i<edge_count;i++){
        pair<double, double> p = original_points[i];
        double xw = p.first;
        double yw = p.second;

        double xv = viewport_x_dims.first + (xw - window_x_dims.first) * Sx;
        double yv = viewport_y_dims.first + (yw - window_y_dims.first) * Sy;

        transformed_points.push_back(pair<double, double>(xv, yv));
    }
}