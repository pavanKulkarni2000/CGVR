#include<stdio.h>
#include<GL/glut.h>
#include<Windows.h>

struct point { int x, y; };

void symmetry8(point p, point c) {
	glBegin(GL_POINTS);
	glVertex2i(c.x - p.x, c.y - p.y);
	glVertex2i(c.x - p.x, c.y + p.y);
	glVertex2i(c.x + p.x, c.y - p.y);
	glVertex2i(c.x + p.x, c.y + p.y);
	glVertex2i(c.x - p.y, c.y - p.x);
	glVertex2i(c.x - p.y, c.y + p.x);
	glVertex2i(c.x + p.y, c.y - p.x);
	glVertex2i(c.x + p.y, c.y + p.x);
	glEnd();
	glFlush();
	Sleep(100);
}

int r;
void drawCircle(point c) {
	point p = { 0,r };
	int d = 1 - r;

	symmetry8(p, c);
	while (p.x < p.y) {
		if (d >= 0) {
			d += 2 * p.x - 2 * p.y + 5;
			p.y -= 1;
		}
		else d += 2 * p.x + 3;
		p.x += 1;
		symmetry8(p, c);
	}
}

void display() { drawCircle({ 200,200 }); }

void mouse(int btn, int state, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		drawCircle({ x,500 - y });
}

void main(int argc, char** argv) {
	printf("> Enter the radius.\n");
	scanf_s("%d", &r);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Brasanham's circle drawing mode");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	gluOrtho2D(0, 500, 0, 500);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glutMainLoop();
}