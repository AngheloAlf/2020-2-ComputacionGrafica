//	This program illustrates the use of the glut library for
//	interfacing with a window system

//	Description of operation of program is in Chapter 3

#define NULL 0

#include <time.h>
#include <GL/glut.h>
#include <string.h>

using namespace std;

void mouse(int, int, int, int);
void display(void);
void idle(void);
void drawSquare(int, int);
//long time(int);
int  pick(int, int);

/* globals */
GLsizei wh = 500, ww = 500; 	    /* initial window size */
GLfloat size = 3.0;				    /* half side length of square */

int		base;					    /* font list base */
time_t	baset;					    /* time base */
GLfloat	r = 1.0, g = 1.0, b = 1.0;	/* drawing color */
int		fill = 0;					/* fill flag */

void drawSquare(int x, int y)
{	y = wh - y;
	glColor3ub((char)rand() % 256,(char)rand() % 256,(char)rand() % 256);
	glBegin(GL_POLYGON);
		glVertex2f(x + size, y + size);
		glVertex2f(x - size, y + size);
		glVertex2f(x - size, y - size);
		glVertex2f(x + size, y - size);
	glEnd();
}

/* Rehaping routine called whenever window is resized or moved */
void myReshape(int w, int h)
{	/* Adjust clipping box */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

/* Adjust viewport and  clear */
	glViewport(0, 0, w, h);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	display();
	glFlush();

/* Set global size for use by drawing routine */
	ww = w;
	wh = h;
}

void myinit(void)
{	/* Set up a font in display list */
	int i;
	baset = time(NULL);
	base  = glGenLists(128);
	for(i = 0; i < 128; i++)
	{	glNewList(base + i, GL_COMPILE);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, i);
		glEndList();
	}
	glListBase(base);
	glViewport(0, 0, ww, wh);

/*	Pick 2D clipping window to match size of X window
	This choice avoids having to scale object coordinates
	each time window is resized */

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLdouble)ww , 0.0, (GLdouble)wh , -1.0, 1.0);

/* set clear color to black and clear window */
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void mouse(int btn, int state, int x, int y)
{	static int draw_mode = 0; /* drawing mode */
	static int count;
	int where;
	static int xp[2], yp[2];
	if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   	{	glPushAttrib(GL_ALL_ATTRIB_BITS);
       	glutIdleFunc(NULL);
		where = pick(x, y);
		glColor3f(r, g, b);
		if(where != 0)
       		{	count = 0;
          		draw_mode = where;
       		}
       		else if(draw_mode == 1 && count == 0)
       			{	count = 1;
              		xp[0] = x;
              		yp[0] = y;
       			}
       			else if(draw_mode == 1 && count != 0)
       				{	glBegin(GL_LINES);
                 			glVertex2i(x, wh - y);
                 			glVertex2i(xp[0], wh - yp[0]);
              			glEnd();
//draw_mode = 0;
                        count = 0;
       				}
       			else if(draw_mode == 2 && count == 0)
       				{	count = 1;
                  	xp[0] = x;
                    yp[0] = y;
       				}
       			else if(draw_mode == 2 && count != 0)
       				{	if(fill) glBegin(GL_POLYGON);
              				else	glBegin(GL_LINE_LOOP);
                 						glVertex2i(x, wh - y);
                 						glVertex2i(x, wh - yp[0]);
                 						glVertex2i(xp[0], wh - yp[0]);
                 						glVertex2i(xp[0], wh - y);
              						glEnd();
//	draw_mode=0
                        count = 0;
       				}
       			else if(draw_mode == 3 && count == 0)
       				{	count = 1;
              			xp[0] = x;
              			yp[0] = y;
       				}
       			else if(draw_mode == 3 && count == 1)
       				{	count = 2;
              			xp[1] = x;
              			yp[1] = y;
       				}
       			else if(draw_mode == 3 && count == 2)
       				{	if(fill) glBegin(GL_POLYGON);
              				else 	glBegin(GL_LINE_LOOP);
                 						glVertex2i(xp[0],wh-yp[0]);
                              	glVertex2i(xp[1],wh-yp[1]);
                 						glVertex2i(x,wh-y);
              						glEnd();
//	draw_mode=0
              			count = 0;
       				}
       			else if(draw_mode == 4)
       				{	drawSquare(x, y);
          				count++;
       				}
                glutIdleFunc(idle);
                glPopAttrib();
       			glFlush();
		}
}

int pick(int x, int y)
{	y = wh - y;
	if(y < wh - ww / 10) return 0;
	else	if(x < ww / 10) return 1;
			else if(x < ww / 5) return 2;
			else if(x < 3 * ww / 10) return 3;
			else if(x < 2 * ww / 5) return 4;
			else return 0;
}

void screen_box(int x, int y, int s )
{	glBegin(GL_QUADS);
		glVertex2i(x,	y);
		glVertex2i(x+s,	y);
		glVertex2i(x+s,	y+s);
		glVertex2i(x,	y+s);
	glEnd();
}

void idle(void)
{	char out[] = "00:00:00";
	time_t t;
	int min, sec, hr;

	glPushAttrib(GL_ALL_ATTRIB_BITS);
	t = time(NULL) - baset;
	hr = t / 3600;
	min = (t - 3600 * hr) / 60;
	sec = (t - 3600 * hr - 60 * min);
	hr = hr % 24;
	out[0] = '0' + hr / 10;
	out[1] = '0' + hr % 10;
	out[3] = '0' + min / 10;
	out[4] = '0' + min % 10;
	out[6] = '0' + sec / 10;
	out[7] = '0' + sec % 10;
	glRasterPos2i(ww - 80, wh - 15);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_QUADS);
		glVertex2i(ww - 80, wh - 15);
		glVertex2i(ww, wh - 15);
		glVertex2i(ww, wh);
		glVertex2i(ww - 80, wh);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glCallLists( strlen(out) , GL_BYTE, out);
	glFlush();
	glPopAttrib();
}

void right_menu(int id)
{	glutIdleFunc(NULL);
	if(id == 1) exit(1);
	else display();
	glutIdleFunc(idle);
}

void middle_menu(int id)
{	glutIdleFunc(NULL);
	glutIdleFunc(idle);
}

void color_menu(int id)
{	glutIdleFunc(NULL);
	if(id == 1) {r = 1.0; g = 0.0; b = 0.0;}
	else	if(id==2) {r=0.0; g=1.0; b=0.0;}
			else	if(id==3) {r=0.0; g=0.0; b=1.0;}
					else	if(id==4) {r=0.0; g=1.0; b=1.0;}
   							else 	if(id==5) {r=1.0; g=0.0; b=1.0;}
   							else 	if(id==6) {r=1.0; g=1.0; b=0.0;}
   									else 	if(id==7) {r=1.0; g=1.0; b=1.0;}
   											else if(id==8) {r=0.0; g=0.0; b=0.0;}
	glutIdleFunc(idle);
}

void pixel_menu(int id)
{	glutIdleFunc(NULL);
	if(id==1)	size=2 * size;
	else			if(size > 1) size=size/2;
	glutIdleFunc(idle);
}

void fill_menu(int id)
{	glutIdleFunc(NULL);
	if(id==1)	fill=1;
	else		fill=0;
	glutIdleFunc(idle);
}

void display(void)
{	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glutIdleFunc(NULL);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	screen_box(0, wh - ww / 10, ww / 10);

	glColor3f(1.0, 0.0, 0.0);
	screen_box(ww / 10, wh - ww / 10, ww / 10);

	glColor3f(0.0, 1.0, 0.0);
	screen_box(ww / 5, wh - ww / 10, ww / 10);

	glColor3f(0.0, 0.0, 1.0);
	screen_box(3 * ww / 10, wh - ww / 10, ww / 10);

	glColor3f(0.0, 0.0, 0.0);
	screen_box(ww / 10 + ww / 40, wh - ww / 10 + ww / 40, ww / 20);

	glBegin(GL_LINES);
   		glVertex2i(wh / 40, wh - ww / 20);
		glVertex2i(wh / 40 + ww / 20, wh - ww / 20);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex2i(ww / 5 + ww / 40, wh - ww / 10 + ww / 40);
		glVertex2i(ww / 5 + ww / 20, wh - ww / 40);
		glVertex2i(ww / 5 + 3 * ww / 40, wh - ww / 10 + ww / 40);
	glEnd();

	glPointSize(3.0);
	glBegin(GL_POINTS);
		glVertex2i(3 * ww / 10 + ww / 20, wh - ww / 20);
	glEnd();

	glutIdleFunc(idle);
	glFlush();
	glPopAttrib();
}

int main(int argc, char** argv)
{	int c_menu, p_menu, f_menu;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Edward Angel: paint.c");
	glutDisplayFunc(display);

	c_menu=glutCreateMenu(color_menu);
	glutAddMenuEntry("Red",1);
	glutAddMenuEntry("Green",2);
	glutAddMenuEntry("Blue",3);
	glutAddMenuEntry("Cyan",4);
	glutAddMenuEntry("Magenta",5);
	glutAddMenuEntry("Yellow",6);
	glutAddMenuEntry("White",7);
	glutAddMenuEntry("Black",8);

	p_menu=glutCreateMenu(pixel_menu);
	glutAddMenuEntry("Increase pixel size", 1);
	glutAddMenuEntry("Decrease pixel size", 2);

	f_menu=glutCreateMenu(fill_menu);
	glutAddMenuEntry("Fill ON", 1);
	glutAddMenuEntry("Fill OFF", 2);

	glutCreateMenu(middle_menu);
	glutAddMenuEntry("Quit",1);
	glutAddMenuEntry("Clear",2);
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	glutCreateMenu(right_menu);
	glutAddSubMenu("Colors", c_menu);
	glutAddSubMenu("Pixel Size", p_menu);
	glutAddSubMenu("Fill", f_menu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	myinit();
	glutReshapeFunc(myReshape);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);
	glutMainLoop();
}
