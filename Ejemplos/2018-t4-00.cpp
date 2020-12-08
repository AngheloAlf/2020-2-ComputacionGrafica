//	Universidad Tecnica Federico Santa Maria
//	Departamento de Informatica
//	INF342 Computacion Grafica
//	Prof. Hubert Hoffmann
//
//	Segundo Semestre 2018
//	Tarea 4

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <windows.h>

#include <GL/glut.h>

using namespace std;

typedef float point[4];

//	Initial tetrahedron
point v[]={{0.0, 0.0, 1.0}, {0.0, 0.9428, -0.3333},
          {-0.8164, -0.4714, -0.3333}, {0.8164, -0.4714, -0.3333}};

int n=5;
GLfloat light0Position[] = {-1.0, -1.0, 1.0, 0.0};
GLfloat light1Position[] = {1.0,  1.0, 1.0, 0.0};

//	Display one triangle using three normals for interpolative shading
void triangle(point a, point b, point c)
{	glBegin(GL_POLYGON);
		glNormal3fv(a);
   		glVertex3fv(a);
   		glNormal3fv(b);
   		glVertex3fv(b);
   		glNormal3fv(c);
   		glVertex3fv(c);
	glEnd();
}

// Normalize a vector
void normal(point p)
{	//double sqrt();
	double d = 0.0;
	int i;
	for(i=0; i<3; i++) d += p[i]*p[i];
	d = sqrt(d);
	if(d > 0.0) for(i=0; i<3; i++) p[i] /= d;
}

//	Triangle subdivision using vertex numbers
//	righthand rule applied to create outward pointing faces
void divideTriangle(point a, point b, point c, int m)
{	point v1, v2, v3;
	int j;
	if(m > 0)
	{	for(j=0; j<3; j++) v1[j]=a[j]+b[j];
		normal(v1);
		for(j=0; j<3; j++) v2[j]=a[j]+c[j];
		normal(v2);
		for(j=0; j<3; j++) v3[j]=b[j]+c[j];
		normal(v3);
		divideTriangle(a, v1, v2, m-1);
		divideTriangle(c, v2, v3, m-1);
		divideTriangle(b, v3, v1, m-1);
		divideTriangle(v1, v3, v2, m-1);
	}
	else(triangle(a,b,c)); //	Draw triangle at end of recursion
}

//	Apply triangle subdivision to faces of tetrahedron
void tetrahedron(int m)
{	divideTriangle(v[0], v[1], v[2], m);
	divideTriangle(v[3], v[2], v[1], m);
	divideTriangle(v[0], v[3], v[1], m);
	divideTriangle(v[0], v[2], v[3], m);
}

//	Display tetrahedron
void display(void)
{	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	tetrahedron(n);
	glFlush();
}

void teclado(unsigned char key, int x, int y)
{	if(key == 27) exit(0);
	if(key == '1') glEnable(GL_LIGHT0);		//	Enable light 0
	if(key == '0') glDisable(GL_LIGHT0);	//	Disable light 0
	if(key == '3') glEnable(GL_LIGHT1);		//	Enable light 1
	if(key == '2') glDisable(GL_LIGHT1);	//	Disable light 1
	if(key == 'x') light0Position[0]-= 0.5;
	if(key == 'X') light0Position[0]+= 0.5;
	if(key == 'y') light0Position[1]-= 0.5;
	if(key == 'Y') light0Position[1]+= 0.5;
	if(key == 'z') light0Position[2]-= 0.5;
	if(key == 'Z') light0Position[2]+= 0.5;
	glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
	if(key == 'a') light1Position[0]-= 0.5;
	if(key == 'A') light1Position[0]+= 0.5;
	if(key == 'b') light1Position[1]-= 0.5;
	if(key == 'B') light1Position[1]+= 0.5;
	if(key == 'c') light1Position[2]-= 0.5;
	if(key == 'C') light1Position[2]+= 0.5;
	glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
	display();
}

void myReshape(int w, int h)
{	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w <= h)
		glOrtho(-4.0,4.0,-4.0*(GLfloat)h/(GLfloat)w,
      			+4.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	else
   		glOrtho(-4.0*(GLfloat)w/(GLfloat)h,
      			+4.0*(GLfloat)w/(GLfloat)h,-4.0,4.0,-10.0,10.0);
	glMatrixMode(GL_MODELVIEW);
	display();
}

void myinit(void)
{ 	GLfloat mat_specular[]=  {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_diffuse[]=   {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_ambient[]=   {1.0, 1.0, 1.0, 1.0};
	GLfloat mat_shininess=   {100.0};

	GLfloat light0Ambient[]= {0.0, 0.0, 0.0, 1.0};
	GLfloat light0Diffuse[]= {1.0, 0.0, 0.0, 1.0};
	GLfloat light0Specular[]={1.0, 1.0, 1.0, 1.0};

	GLfloat light1Ambient[]= {0.0, 0.0, 0.0, 1.0};
	GLfloat light1Diffuse[]= {0.0, 0.0, 1.0, 1.0};
	GLfloat light1Specular[]={1.0, 1.0, 1.0, 1.0};

//	Set up ambient, diffuse, and specular components for light 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR,light0Specular);

//	Set up ambient, diffuse, and specular components for light 1
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR,light1Specular);

//	Define material proerties for front face of all polygons
	glMaterialfv(GL_FRONT,GL_SPECULAR,	mat_specular);
	glMaterialfv(GL_FRONT,GL_AMBIENT,	mat_ambient);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,	mat_diffuse);
	glMaterialf(GL_FRONT, GL_SHININESS,mat_shininess);
	glEnable(GL_SMOOTH);		//	Enable smooth shading
	glEnable(GL_LIGHTING);		//	Enable lighting
	glEnable(GL_DEPTH_TEST);	//	Enable z buffer
	glClearColor(0.0, 0.4, 0.4, 1.0);
	glColor3f(0.0, 0.0, 0.0);

	cout << endl << endl;
	cout << "  USO DE TECLAS" << endl << endl;
	cout << "  Fuentes de Luz" << endl << endl;
	cout << "  0: Apagar   Fuente de Luz 0 (roja)" << endl;
	cout << "  1: Encender Fuente de Luz 0 (roja)" << endl;
	cout << "  2: Apagar   Fuente de Luz 1 (azul)" << endl;
	cout << "  3: Encender Fuente de Luz 1 (azul)" << endl << endl;
	cout << "  Movimientos de las Fuentes de Luz" << endl;
	cout << "  x: Mover Luz 0 -x  y  X: Mover Luz 0 +x" << endl;
	cout << "  y: Mover Luz 0 -y  y  Y: Mover Luz 0 +y" << endl;
	cout << "  z: Mover Luz 0 -z  y  Z: Mover Luz 0 +z" << endl << endl;
	cout << "  a: Mover Luz 1 -x  y  A: Mover Luz 1 +x" << endl;
	cout << "  b: Mover Luz 1 -y  y  B: Mover Luz 1 +y" << endl;
	cout << "  c: Mover Luz 1 -z  y  X: Mover Luz 1 +z" << endl << endl;
	cout << "  ESC = Quit" << endl;
}

int main(int argc, char **argv)
{	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(600,400);
	glutCreateWindow("Computacion Grafica - Tarea 4");
	myinit();
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(teclado);
	glutMainLoop();
}
