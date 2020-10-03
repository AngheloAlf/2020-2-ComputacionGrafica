// Universidad Tecnica Federico Santa Maria
// Departamento de Informatica
// INF342 Computación Grafica
// Fabián Fernández
// Anghelo Carvajal
// T1 
// Grupo 08
// g++ 2020-t1-08.cpp -o 2020-t1-08 -lGL -lglut -lGLU -Wall -Wextra


#include <GL/glut.h>


void my_init() {
	/// Setear color blanco como clearColor
    glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}


void cuadradoRojo(void){
	/// Color rojo
    glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
		// Vertice inferior izquierda
		glVertex2f(-0.5, -0.5);
		// Vertice superior izquierda
		glVertex2f(-0.5,  0.5);
		// Vertice superior derecha
		glVertex2f( 0.5,  0.5);
		// Vertice inferior derecha
		glVertex2f( 0.5, -0.5);
	glEnd();
}

void cuadradoAzul(void){
	/// Color azul
    glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
		// Vertice izquierda
		glVertex2f(-0.5,  0.0);
		// Vertice inferior
		glVertex2f( 0.0, -0.5);
		// Vertice derecha
		glVertex2f( 0.5,  0.0);
		// Vertice superior
		glVertex2f( 0.0,  0.5);
	glEnd();
}

void cuadradoVerde(void){
	/// Color verde
    glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
		// Vertice inferior izquierda
		glVertex2f(-0.25, -0.25);
		// Vertice superior izquierda
		glVertex2f(-0.25,  0.25);
		// Vertice superior derecha
		glVertex2f( 0.25,  0.25);
		// Vertice inferior derecha
		glVertex2f( 0.25, -0.25);
	glEnd();
}

void mydisplay(void){	
	glClear(GL_COLOR_BUFFER_BIT);
	// dibujamos los cuadrados
    cuadradoRojo();
    cuadradoAzul();
    cuadradoVerde();
	glFlush();
}

int main(int argc, char** argv)
{	
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(400, 400);
    //glutInitWindowPosition(0, 0);
    glutCreateWindow("Grupo 08 - T1");
    my_init();
	glutDisplayFunc(mydisplay);
	glutMainLoop();
}
