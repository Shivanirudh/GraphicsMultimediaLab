#include "Helpers.h"

void runMainLoop(int val);

int main( int argc, char* args[] ){

	glutInit( &argc, args );

	glutInitContextVersion( 2, 1 );

	glutInitDisplayMode( GLUT_SINGLE|GLUT_RGB );
	glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	glutCreateWindow( "OpenGL" );

	int option=0;
	cout<<"Choose number of edges: (1 for line, 3 and upwards for polygon): ";
	cin>>option;

	setEdgeCount(option);
	cout<<"Enter vertices: "<<endl;
	for(int i=0;i<edge_count;i++){
		cout<<"Vertex "<<i+1<<" (x,y): ";
		int x,y;
		cin>>x>>y;
		X_points.push_back(x);
		Y_points.push_back(y);

	}

	drawPolygon();
	cout<<"Number of edges: "<<edge_count<<endl;

	if( !initGL() )
	{
		printf( "Unable to initialize graphics library!\n" );
		return 1;
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
