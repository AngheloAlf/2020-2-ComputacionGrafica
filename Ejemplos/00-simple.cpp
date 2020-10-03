//	Program simple.c
//	Ed Angel
//	Interactive Computer Graphics - A Top-down Approach with OpenGL

#include <GL/glut.h>

void mydisplay(void)
{	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POLYGON);
		glVertex2f(-0.5, -0.5);
		glVertex2f(-0.5,  0.5);
		glVertex2f( 0.5,  0.5);
		glVertex2f( 0.5, -0.5);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{	glutInit(&argc, argv);
    glutCreateWindow("simple.c");
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
