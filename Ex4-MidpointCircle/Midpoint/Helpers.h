#include "Signatures.h"

bool initGL(){
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	gluOrtho2D(0.0,640.0,0.0,480.0);
	
    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    glTranslatef( SCREEN_WIDTH / 3.f, SCREEN_HEIGHT / 3.f, 0.f );

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
    vector<pair<int, int>> points = Midpoint();
    y_axis();
    x_axis();
    // glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glBegin(GL_POINTS);
        for(pair<int, int> p: points){
            glVertex2d(p.first, p.second);
        }
    glEnd();
    glFlush(); 
}

void y_axis(){
	// glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
		glVertex2d(0, -480.0);
		glVertex2d(0, 480.0);
	glEnd();
	glFlush();
}

void x_axis(){
	// glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
		glVertex2d(-640.0, 0);
		glVertex2d(640.0, 0);
	glEnd();
	glFlush();
}

void selectCenter(int option){
    X0 = coords[option-1][0]*20;
    Y0 = coords[option-1][1]*20;
    radius = coords[option-1][2]*10;
}

vector<pair<int, int>> Midpoint(){
	
	int x = radius;
	int y = 0;

	int p = 1 - radius;

	int point_x = x + X0;
	int point_y = y + Y0;
	

	vector<pair<int, int>> points;

	points.push_back(pair<int, int>(point_x, point_y));

	if( radius<0){
		point_x = x + X0; point_y = -y + Y0;
		points.push_back(pair<int, int>(point_x, point_y));
		
		point_x = y + X0; point_y = x + Y0;
		points.push_back(pair<int, int>(point_x, point_y));
		
		point_x = -y + X0; point_y = x + Y0;
		points.push_back(pair<int, int>(point_x, point_y));		
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
		points.push_back(pair<int, int>(point_x, point_y));	

		point_x = -x + X0; point_y = y + Y0;
		points.push_back(pair<int, int>(point_x, point_y));	

		point_x = x + X0; point_y = -y + Y0;
		points.push_back(pair<int, int>(point_x, point_y));	
		
		point_x = -x + X0; point_y = -y + Y0;
		points.push_back(pair<int, int>(point_x, point_y));	
		
		if( x != y ){
			point_x = y + X0; point_y = x + Y0;
			points.push_back(pair<int, int>(point_x, point_y));	

			point_x = -y + X0; point_y = x + Y0;
			points.push_back(pair<int, int>(point_x, point_y));	

			point_x = y + X0; point_y = -x + Y0;
			points.push_back(pair<int, int>(point_x, point_y));	
			
			point_x = -y + X0; point_y = -x + Y0;
			points.push_back(pair<int, int>(point_x, point_y));	
		}
	}
	return points;
}