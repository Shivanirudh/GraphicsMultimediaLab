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
    vector<pair<int, int>> points = Bresenham();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glBegin(GL_POINTS);
        for(pair<int, int> p: points){
            glVertex2d(p.first, p.second);
        }
    glEnd();
    glFlush(); 
}

void selectOctant(int option){
    X0 = coords[option-1][0];
    Y0 = coords[option-1][1];
    Xn = coords[option-1][2];
    Yn = coords[option-1][3];
}

int sign(int val){
	if(val<0){
		return -1;
	}
	else if(val>0){
		return 1;
	}
	else{
		return 0;
	}
}

vector<pair<int, int>> Bresenham(){
	
	int x=X0;
	int y=Y0;

	int dx=abs(Xn-X0);
	int dy=abs(Yn-Y0);

	int sign_x = sign(Xn-X0);
	int sign_y = sign(Yn-Y0);

	int swap=-1;

	//Swap x and y if slope > 1, and acknowledge swap.
	if(dy>dx){
		int temp = dx;
		dx = dy;
		dy = temp;
		swap=1;
	}
	else{
		swap=0;
	}

	int p = (2*dy) - dx;
	int faca = 2*dy;
	int facb = (2*dy)-(2*dx);

	vector<pair<int, int>> points;

	points.push_back(pair<int, int>(x, y));

	for(int i=1;i<=dx;i++){
		if(p<0){
			if(swap==1){
				y += sign_y;
			}
			else{
				x += sign_x; 
			}
			p = p + faca;
		}
		else{
			y += sign_y;
			x += sign_x;
			p += facb;
		}
		points.push_back(pair<int, int>(x, y));
	}
	return points;
}
