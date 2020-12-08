// Universidad Tecnica Federico Santa Maria
// Departamento de Informatica
// INF342 Computación Grafica
// Fabián Fernández
// Anghelo Carvajal
// T2
// Grupo 08
// g++ 2020-t3-08.cpp -o 2020-t3-08 -lGL -lglut -lGLU -Wall -Wextra


#include <stdio.h>
#include <GL/glut.h>

double radio = 1.5;
float esferaRojax= -2.5;
float esferaAzulx= 2.5;
GLfloat light0Position[] = {-1.0, -1.0, 1.0, 0.0};
GLfloat light1Position[] = {1.0,  1.0, 1.0, 0.0};

const GLfloat RGBA_RED[]   = {1.0, 0.0, 0.0, 1.0};
const GLfloat RGBA_GREEN[] = {0.0, 1.0, 0.0, 1.0};
const GLfloat RGBA_BLUE[]  = {0.0, 0.0, 1.0, 1.0};

void esfera(double radio, float pos_x, const GLfloat *color){
    glLoadIdentity();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
    glTranslatef(pos_x, 0, 0);
    glutSolidSphere(radio, 50, 50);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    esfera(radio, esferaRojax, RGBA_RED);
    esfera(radio, esferaAzulx, RGBA_BLUE);

    glFlush();
    glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y){
    switch (key){
    case 27:
        exit(0);
        break;
    case '0':
        glDisable(GL_LIGHT0);
        break;
    case '1':
        glEnable(GL_LIGHT0);
        break;
    case '2':
        glDisable(GL_LIGHT1);
        break;
    case '3':
        glEnable(GL_LIGHT1);
        break;

    case 'x':
        light0Position[0]-= 0.5;
        break;
    case 'X':
        light0Position[0]+= 0.5;
        break;
    case 'y':
        light0Position[1]-= 0.5;
        break;
    case 'Y':
        light0Position[1]+= 0.5;
        break;
    case 'z':
        light0Position[2]-= 0.5;
        break;
    case 'Z':
        light0Position[2]+= 0.5;
        break;

    case 'a':
        light1Position[0]-= 0.5;
        break;
    case 'A':
        light1Position[0]+= 0.5;
        break;
    case 'b':
        light1Position[1]-= 0.5;
        break;
    case 'B':
        light1Position[1]+= 0.5;
        break;
    case 'c':
        light1Position[2]-= 0.5;
        break;
    case 'C':
        light1Position[2]+= 0.5;
        break;

    default:
        break;
    }

    glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1Position);
    display();
}

void myReshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat ratio = (GLfloat)h/(GLfloat)w;
    GLdouble left   = -4.0 / (w <= h ? 1 : ratio);
    GLdouble right  =  4.0 / (w <= h ? 1 : ratio);
    GLdouble bottom = -4.0 * (w <= h ? ratio : 1);
    GLdouble top    =  4.0 * (w <= h ? ratio : 1);
    glOrtho(left, right, bottom, top, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    display();
}

void myinit(void){
    GLfloat mat_specular[] =   {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess  =   {124.0};

    GLfloat light0Ambient[] =  {0.0, 0.0, 0.0, 1.0};
    GLfloat light0Diffuse[] =  {1.0, 0.0, 0.0, 1.0};
    GLfloat light0Specular[] = {1.0, 1.0, 1.0, 1.0};

    GLfloat light1Ambient[] =  {0.0, 0.0, 0.0, 1.0};
    GLfloat light1Diffuse[] =  {0.0, 0.0, 1.0, 1.0};
    GLfloat light1Specular[] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR,light0Specular);

    glLightfv(GL_LIGHT1, GL_AMBIENT, light1Ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1Diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR,light1Specular);

    glMaterialfv(GL_FRONT,GL_SPECULAR,    mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, RGBA_RED);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    glEnable(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.4, 0.4, 1.0);
    glColor3f(0.0, 0.0, 0.0);
}

void help(){
    printf("USO DE TECLAS\n");
    printf("\n");
    printf("Fuentes de Luz\n");
    printf("\n");
    printf("0: Apagar   Fuente de Luz 0 (roja)\n");
    printf("1: Encender Fuente de Luz 0 (roja)\n");
    printf("2: Apagar   Fuente de Luz 1 (azul)\n");
    printf("3: Encender Fuente de Luz 1 (azul)\n");
    printf("\n");
    printf("Movimientos de las Fuentes de Luz\n");
    printf("x: Mover Luz 0 -x  y  X: Mover Luz 0 +x\n");
    printf("y: Mover Luz 0 -y  y  Y: Mover Luz 0 +y\n");
    printf("z: Mover Luz 0 -z  y  Z: Mover Luz 0 +z\n");
    printf("\n");
    printf("a: Mover Luz 1 -x  y  A: Mover Luz 1 +x\n");
    printf("b: Mover Luz 1 -y  y  B: Mover Luz 1 +y\n");
    printf("c: Mover Luz 1 -z  y  X: Mover Luz 1 +z\n");
    printf("ESC = Quit\n");
}

int main(int argc, char **argv){
    help();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 400);
    glutInitWindowPosition(600,400);
    glutCreateWindow("Grupo 08 - T3");
    myinit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutMainLoop();
}
