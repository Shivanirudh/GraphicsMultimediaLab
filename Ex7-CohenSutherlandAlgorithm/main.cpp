#include "Helpers.h"

void runMainLoop(int val);

int main( int argc, char* args[] ){

	glutInit( &argc, args );

	glutInitContextVersion( 2, 1 );

	glutInitDisplayMode( GLUT_SINGLE|GLUT_RGB );
	glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	glutCreateWindow( "OpenGL" );

	cout<<"Enter window dimensions: "<<endl;
	cout<<"Enter minimum X value: "; cin>>window_x_dims.first;
	cout<<"Enter maximum X value: "; cin>>window_x_dims.second;
	cout<<"Enter minimum Y value: "; cin>>window_y_dims.first;
	cout<<"Enter maximum Y value: "; cin>>window_y_dims.second;

	cout<<"Enter vertices: "<<endl;
	cout<<"Vertex "<<1<<" (x y): ";
	cin>>original_point1.first>>original_point1.second;
	
	cout<<"Vertex "<<2<<" (x y): ";
	cin>>original_point2.first>>original_point2.second;	

	drawOriginalLine();


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