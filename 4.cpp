#include<stdio.h>
#include<GL/glut.h>

struct point { int x, y; };

void symmetry8(point p,point c){
	glVertex2i(c.x - p.x, c.y - p.y);
	glVertex2i(c.x - p.x, c.y + p.y);
	glVertex2i(c.x + p.x, c.y - p.y);
	glVertex2i(c.x + p.x, c.y + p.y);
	glVertex2i(c.x - p.y, c.y - p.x);
	glVertex2i(c.x - p.y, c.y + p.x);
	glVertex2i(c.x + p.y, c.y - p.x);
	glVertex2i(c.x + p.y, c.y + p.x);
}

void drawCircle(point c,int r) {

	point p = { 0,r };
	int d = 1 - r;

	glBegin(GL_POINTS);
	symmetry8(p, c);
	while (p.x < p.y) {
		if (d >= 0) {
			p.y -= 1;
			d += 2 * p.x - 2 * p.y + 5;
		}
		else
			d += 2 * p.x + 3;
		p.x += 1;
		symmetry8(p, c);
	}
	glEnd();
	glFlush();
}

void display1() {

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 1);
	for (int i = 0; i < 200; i += 2)
		drawCircle({ i,i }, 100);

}

void display2() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	for(int i=0;i<100;i+=2){
		glBegin(GL_LINE_LOOP);
		glVertex2i(100 + i, 100 + i);
		glVertex2i(-100 + i, 100 + i);
		glVertex2i(-100 + i, -100 + i);
		glVertex2i(100 + i, -100 + i);
		glEnd();
	}
	glFlush();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);

	glutCreateWindow("Cylinder");
	glutDisplayFunc(display1);
	gluOrtho2D(-250, 250, -250, 250);
	glClearColor(1, 1, 1, 1);

	glutCreateWindow("Parallelepiped");
	glutDisplayFunc(display2);
	gluOrtho2D(-250, 250, -250, 250);
	glClearColor(1, 1, 1, 1);

	glutMainLoop();
}