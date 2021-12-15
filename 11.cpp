#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

struct point { int x, y; };

float m=1, c=30, angle=45;

void drawHouse() {
	glLineWidth(3);
	glColor3f(0, 0, 1);
	glBegin(GL_LINE_LOOP);
	glVertex2i(150, 0);
	glVertex2i(150, 100);
	glVertex2i(200, 100);
	glVertex2i(200, 0);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(150, 100);
	glVertex2i(200, 100);
	glVertex2i(175, 200);
	glEnd();

	glColor3f(0, 1, 0);
	glBegin(GL_LINE_LOOP);
	glVertex2i(160, 0);
	glVertex2i(160, 20);
	glVertex2i(170, 20);
	glVertex2i(170, 0);
	glEnd();

	glFlush();
}

void drawLine(point p1, point p2) {

	glLineWidth(1);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p2.x, p2.y);
	glEnd();
	glFlush();
}

int mode = 0;
void display() {

	glClear(GL_COLOR_BUFFER_BIT);

	drawLine({ 0,-250 }, { 0,250 });
	drawLine({-250, 0 }, { 250,0 });

	drawHouse();

	glPushMatrix();
	if (mode == 0) {
		glTranslatef(150, 0, 0);
		glRotatef(angle, 0, 0, 1);
		glTranslatef(-150, 0, 0);
	}
	else {
		float theta = atanf(m) * 180.0 / 3.14159;
		drawLine({ 0, (int)c }, { 250, (int)(250 * m + c) });
		glTranslatef(0, c, 0);
		glRotatef(theta, 0, 0, 1);
		glScalef(1, -1, 1);
		glRotatef(-theta, 0, 0, 1);
		glTranslatef(0, -c, 0);
	}
	drawHouse();
	glPopMatrix();
}

void mouse(int btn, int state, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mode ^= 1;
		glutPostRedisplay();
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Transformations");
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	gluOrtho2D(-250,250,-250,250);
	glClearColor(1, 1, 1, 1);
	glutMainLoop();
}