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
    drawOriginalLine();

    CohenSutherland();

    glFlush(); 
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

void drawOriginalLine(){
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_LINES);
       
    glVertex2d(original_point1.first, original_point1.second);
    glVertex2d(original_point2.first, original_point2.second);
    
    glEnd();
    glFlush();
}

void computeRegionCode1(){
    if(new_point1.second > window_y_dims.second){
        region_code1[0] = 1;
    }
    if(new_point1.second < window_y_dims.first){
        region_code1[1] = 1;
    }
    if(new_point1.first > window_x_dims.second){
        region_code1[2] = 1;
    }
    if(new_point1.first < window_x_dims.first){
        region_code1[3] = 1;
    }
}

void computeRegionCode2(){
    if(new_point2.second > window_y_dims.second){
        region_code2[0] = 1;
    }
    if(new_point2.second < window_y_dims.first){
        region_code2[1] = 1;
    }
    if(new_point2.first > window_x_dims.second){
        region_code2[2] = 1;
    }
    if(new_point2.first < window_x_dims.first){
        region_code2[3] = 1;
    }
}

bool trivial_accept(){
    computeRegionCode1();computeRegionCode2();

    int sum=0;
    for(int i=0;i<4;i++){
        sum += (region_code1[i]+region_code2[i]);
    }   

    return (sum == 0)?true:false;
}

bool trivial_reject(){
    computeRegionCode1();computeRegionCode2();

    int sum=0;
    for(int i=0;i<4;i++){
        sum += (region_code1[i]*region_code2[i]);
    }   

    return (sum >= 1)?true:false;
}

void drawClippedLine(){
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_LINES);
       
    glVertex2d(new_point1.first, new_point1.second);
    glVertex2d(new_point2.first, new_point2.second);
    
    glEnd();
    glFlush();
}

void CohenSutherland(){
    new_point1 = original_point1;
    new_point2 = original_point2;
    for(int iteration=0; iteration<5; iteration++){
        if(trivial_accept()){
            cout<<"Trivially accepted"<<endl;
            cout<<"New points are : ("
                <<new_point1.first<<", "<<new_point1.second
                <<") and ("
                <<new_point2.first<<", "<<new_point2.second
                <<")"<<endl;

            sleep(2);
            drawClippedLine();
            sleep(3);
            break;
        }
        if(trivial_reject()){
            cout<<"Trivially rejected"<<endl;
            sleep(3);
            break;
        }

        double slope = (new_point2.second - new_point1.second)/(new_point2.first - new_point1.first);
        //Point 1
        if(region_code1[0] == 1){
            new_point1.second = window_y_dims.second;
            new_point1.first = new_point2.first + (new_point1.second - new_point2.second)/slope;
        }
        if(region_code1[1] == 1){
            new_point1.second = window_y_dims.first;
            new_point1.first = new_point2.first + (new_point1.second - new_point2.second)/slope;
        }
        if(region_code1[2] == 1){
            new_point1.first = window_x_dims.second;
            new_point1.second = new_point2.second + (new_point1.first - new_point2.first)*slope;
        }
        if(region_code1[3] == 1){
            new_point1.first = window_x_dims.first;
            new_point1.second = new_point2.second + (new_point1.first - new_point2.first)*slope;
        }


        //Point 2
        if(region_code2[0] == 1){
            new_point2.second = window_y_dims.second;
            new_point2.first = new_point1.first + (new_point2.second - new_point1.second)/slope;
        }
        if(region_code2[1] == 1){
            new_point2.second = window_y_dims.first;
            new_point2.first = new_point1.first + (new_point2.second - new_point1.second)/slope;
        }
        if(region_code2[2] == 1){
            new_point2.first = window_x_dims.second;
            new_point2.second = new_point1.second + (new_point2.first - new_point1.first)*slope;
        }
        if(region_code2[3] == 1){
            new_point2.first = window_x_dims.first;
            new_point2.second = new_point1.second + (new_point2.first - new_point1.first)*slope;
        }

        drawClippedLine();
        cout<<"New points are : ("
                <<new_point1.first<<", "<<new_point1.second
                <<") and ("
                <<new_point2.first<<", "<<new_point2.second
                <<")"<<endl;
        sleep(1);
    }
}