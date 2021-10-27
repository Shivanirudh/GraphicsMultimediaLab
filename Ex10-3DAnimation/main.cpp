#include "Helpers.h"

void reshape(int w, int h);
void runMainLoop();


int main(int argc, char *args[])
{

	glutInit( &argc, args );

	glutInitContextVersion( 2, 1 );

	glutInitDisplayMode( GLUT_SINGLE|GLUT_RGB );
	glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
	glutCreateWindow( "OpenGL" );

	initGL();
    glutDisplayFunc(runMainLoop);
    glutReshapeFunc(reshape);

	glutMainLoop();

	return 0;
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(75, 1, 1, 20);
    glMatrixMode(GL_MODELVIEW);
}
void runMainLoop() {
    
    glutTimerFunc(1000 / 60, render, 0);
}