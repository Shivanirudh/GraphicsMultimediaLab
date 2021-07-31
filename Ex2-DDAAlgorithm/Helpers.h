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
    // cout<<X0<<" "<<Y0<<" "<<Xn<<" "<<Yn<<endl;
    vector<pair<int, int>> points = DDA();


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
    X0 = coords[option-1][0]*20;
    Y0 = coords[option-1][1]*20;
    Xn = coords[option-1][2]*20;
    Yn = coords[option-1][3]*20;
}

double round_value(double v){
  return floor(v + 0.5);
}
vector<pair<int, int>> DDA(void){

  double dx=(Xn-X0);
  double dy=(Yn-Y0);
  double steps;
  double xInc,yInc,x=X0,y=Y0;
  
  steps=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
  xInc=dx/(double)steps;
  yInc=dy/(double)steps;

  vector<pair<int, int>> points;
  
  points.push_back(pair<int, int>(x, y));
  
  int k;
  for(k=0;k<steps;k++)
  {
    x+=xInc;
    y+=yInc;
    
    points.push_back(pair<int, int>(round_value(x), round_value(y)));
  }
  return points;
}