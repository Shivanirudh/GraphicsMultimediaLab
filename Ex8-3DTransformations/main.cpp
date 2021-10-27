#include "Helpers.h"

int main( int argc, char* args[] ){

	glutInit(&argc,args);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1362,750);
    glutInitWindowPosition(0,0);
	glutCreateWindow( "OpenGL" );

    init();

    glutDisplayFunc(render);

	glutMainLoop();

	return 0;
}