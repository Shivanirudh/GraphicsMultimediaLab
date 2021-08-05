#include "Helpers.h"

void runMainLoop(int val);

int main( int argc, char* args[] ){

	glutInit( &argc, args );

	glutInitContextVersion( 2, 1 );

	glutInitDisplayMode( GLUT_SINGLE|GLUT_RGB );
	glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	glutCreateWindow( "OpenGL" );

	int option=0;
	cout<<"Choose center: (1 for origin, 2 for elsewhere): ";
	cin>>option;

	selectCenter(option);
	cout<<"Center: ("<<X0<<", "<<Y0<<")"<<endl;
	cout<<"Radius: "<<radius<<endl;

	if( !initGL() )
	{
		printf( "Unable to initialize graphics library!\n" );
		return 1;
	}

	vector<pair<int, int>> points = Midpoint();
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