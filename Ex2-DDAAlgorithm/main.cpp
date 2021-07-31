#include "Helpers.h"

void runMainLoop(int val);

int main( int argc, char* args[] ){

	glutInit( &argc, args );

	glutInitContextVersion( 2, 1 );

	glutInitDisplayMode( GLUT_SINGLE|GLUT_RGB );
	glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	glutCreateWindow( "OpenGL" );

	int option=0;
	cout<<"Choose octant: (1 to 8 both inclusive): ";
	cin>>option;

	selectOctant(option);
	cout<<"Start point: ("<<X0<<", "<<Y0<<")"<<endl;
	cout<<"End point: ("<<Xn<<", "<<Yn<<")"<<endl;

	if( !initGL() )
	{
		printf( "Unable to initialize graphics library!\n" );
		return 1;
	}

	vector<pair<int, int>> points = DDA();
	int count=0;
	cout<<"Points plotted: "<<endl;
	for(pair<int, int> p: points){
        cout<<"("<<p.first<<", "<<p.second<<")"<<" ";
        count++;
        if(count==4){
        	count=0;
        	cout<<endl;
        }
    }

	glutDisplayFunc( render );

	glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, 0 );

	glutMainLoop();

	return 0;
}

void runMainLoop( int val ){
    update();
    render();

    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, val );
}