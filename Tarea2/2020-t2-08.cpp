// Universidad Tecnica Federico Santa Maria
// Departamento de Informatica
// INF342 Computación Grafica
// Fabián Fernández
// Anghelo Carvajal
// T2
// Grupo 08
// g++ 2020-t2-08.cpp -o 2020-t2-08 -lGL -lglut -lGLU -Wall -Wextra


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

//Seteo de angulos

GLfloat angulo_1 = 0;
GLfloat angulo_2 = 0;

void mydisplay(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// dibujamos los cuadrados

	// Rotamos a la izquierda
	glRotatef(angulo_1, 0.0, 0.0, 1.0);
    cuadradoRojo();

	// Rotamos a la derecha
	glRotatef(-angulo_2, 0.0, 0.0, 1.0);
    cuadradoAzul();

	// Cargar el sistema de coordenadas "normal"
	glLoadIdentity();
    cuadradoVerde();

	glFlush();
	glutSwapBuffers();
}

void spinCube(void){	
	angulo_1 += 0.05;
	if(angulo_1 > 360){
		angulo_1 -= 360;
	}
	angulo_2 += 0.45;
	if(angulo_2 > 360){
		angulo_2 -= 360;
	}
	//se dibujan los cuadros con el angulo actualizado
	mydisplay();
}

void keys(unsigned char key, int x, int y){
	// Cerrar el programa cuando se apreta ESC.
	if(key ==  27) exit(0);
}


int main(int argc, char** argv)
{	
    glutInit(&argc, argv);
	//Glut_Double importante.....
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Grupo 08 - T2");
    my_init();
	glutDisplayFunc(mydisplay);
	glutIdleFunc(spinCube);
	// Registra el teclado
	glutKeyboardFunc(keys);
	glutMainLoop();
}
