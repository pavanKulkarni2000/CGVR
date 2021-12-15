#include<stdio.h>
#include<GL/glut.h>
#define plot(p) {printf("%d %d\n",p.x,p.y);;glVertex2i(p.x,p.y);}

typedef struct { int x, y; } point;

void drawLine(point p1, point p2) {
	point p = p1;
	int incx = p1.x < p2.x ? 1 : -1;
	int incy = p1.y < p2.y ? 1 : -1;
	int dx = p1.x - p2.x; if(dx<0) dx = -dx;
	int dy = p1.y - p2.y; if(dy<0) dy = -dy;

	glBegin(GL_POINTS);
	plot(p);
	if (dx > dy) {
		int inc1 = 2 * dy - 2 * dx;
		int inc2 = 2 * dy;
		int d = 2 * dy - dx;
		for (int i = 0; i < dx; i++) {
			if (d > 0) {
				p.y += incy;
				d += inc1;
			}
			else
				d += inc2;
			p.x += incx;
			plot(p);
		}
	}
	else {
		int inc1 = 2 * dx - 2 * dy;
		int inc2 = 2 * dx;
		int d = 2 * dx - dy;
		for (int i = 0; i < dy; i++) {
			if (d > 0) {
				p.x += incx;
				d += inc1;
			}
			else
				d += inc2;
			p.y += incy;
			plot(p);
		}
	}
	glEnd();
	glFlush();
}

void display(){}

void mouse(int btn, int state, int x, int y) {
	static int flag = 0;
	static point p;
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (flag) {
			flag = 0;
			drawLine(p, { x,500 - y });
		}
		else {
			p = { x,500 - y };
			flag = 1;
		}
	}
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Brasanham's line drawing");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glClearColor(1, 1, 1, 1);
	gluOrtho2D(0, 500, 0, 500);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glutMainLoop();
}