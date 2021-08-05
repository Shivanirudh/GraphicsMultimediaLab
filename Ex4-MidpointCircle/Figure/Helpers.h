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
    
    glClear(GL_COLOR_BUFFER_BIT);
    platform();
    human();
    canvas();
    art();
    glFlush();
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
 
void solidQuad(int x1, int y1, int x2, int y2) {         

    glBegin(GL_QUADS);         
   
    glVertex2d(x1,y1);         
    glVertex2d(x2,y1);         
    glVertex2d(x2,y2);      
    glVertex2d(x1,y2);    
           
    glEnd();         
}     

void circle(int X0, int Y0, int radius){
	int x = radius;
	int y = 0;

	int p = 1 - radius;

	int point_x = x + X0;
	int point_y = y + Y0;
	

	glBegin(GL_POINTS);

	glVertex2d(point_x, point_y);

	if( radius<0){
		point_x = x + X0; point_y = -y + Y0;
		glVertex2d(point_x, point_y);
		
		point_x = y + X0; point_y = x + Y0;
		glVertex2d(point_x, point_y);
		
		point_x = -y + X0; point_y = x + Y0;
		glVertex2d(point_x, point_y);		
	}

	while(x > y){
		y++;
		if(p <=0){
			p += ((2*y) + 1);
		}
		else{
			x--;
			p += ((2*y) - (2*x) + 1);
		}
		if(x < y)
			break;

		point_x = x + X0; point_y = y + Y0;
		glVertex2d(point_x, point_y);	

		point_x = -x + X0; point_y = y + Y0;
		glVertex2d(point_x, point_y);	

		point_x = x + X0; point_y = -y + Y0;
		glVertex2d(point_x, point_y);	
		
		point_x = -x + X0; point_y = -y + Y0;
		glVertex2d(point_x, point_y);	
		
		if( x != y ){
			point_x = y + X0; point_y = x + Y0;
			glVertex2d(point_x, point_y);	

			point_x = -y + X0; point_y = x + Y0;
			glVertex2d(point_x, point_y);	

			point_x = y + X0; point_y = -x + Y0;
			glVertex2d(point_x, point_y);	
			
			point_x = -y + X0; point_y = -x + Y0;
			glVertex2d(point_x, point_y);	
		}
	}
	glEnd();
}


void platform(){
	solidQuad(100, 50, 600, 100);
}

void human(){
	head();	
	body();
	brush();
}

void head(){
	circle(300, 300, 20);
}

void body(){
	//torso
	line(300, 280, 300, 175);

	//arm
	line(300, 260, 275, 235);
	line(275, 235, 310, 190);

	line(300, 260, 325, 235);
	line(325, 235, 360, 250);

	//legs
	line(300, 175, 325, 100);
	line(300, 175, 275, 100);
}

void brush(){
	line(345, 258, 385, 230);
	line(346, 259, 386, 231);
	line(347, 260, 387, 232);

	line(345, 258, 347, 260);
	line(385, 230, 387, 232);

	//bristles
	line(385, 230, 388, 228);
	line(387, 232, 388, 228);
}


void canvas(){
	lineloop(375, 150, 575, 340);

	line(475, 150, 445, 100);
	line(475, 150, 505, 100);
}

void art(){
	base();
	snowman();
}

void base(){
	line(395, 170, 555, 170);
}

void snowman(){
	//body
	circle(475, 210, 40);
	circle(475, 215, 2);
	circle(475, 225, 2);
	circle(475, 235, 2);

	line(512, 220, 550, 218);
	line(532, 219, 549, 208);
	line(532, 219, 549, 228);

	line(438, 220, 400, 218);
	line(418, 219, 401, 208);
	line(418, 219, 401, 228);	

	//head
	circle(475, 270, 20);

	//eyes
	circle(467, 275, 4);
	circle(483, 275, 4); 
	
	// circle(475, 265, 2);

	//mouth
	for(int x=465, y=260; x<475; x+=3, y-=1){
		circle(x, y, 0);
	}
	for(int x=485, y=260; x>475; x-=3, y-=1){
		circle(x, y, 0);
	}


}