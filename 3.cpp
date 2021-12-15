#include<stdio.h>
#include<GL/glut.h>
#include<Windows.h>

int wid1, wid2;
float angle = 0;
void display() {
	int wid = glutGetWindow();
	glClear(GL_COLOR_BUFFER_BIT);

	if (wid == wid2) glRotatef(0.2, 0, 0, 1);

	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2i( -200, -100);
	glColor3f(0, 1, 0);
	glVertex2i( -200, 100);
	glColor3f( 0, 0, 1);
	glVertex2i( 200, 100);
	glColor3f( 1, 0, 1);
	glVertex2i( 200, -100);
	glEnd();
	glFlush();

	if (wid == wid2)  glutSwapBuffers();
}

void idle() {
	Sleep(10);
	angle += 0.2;
	glutPostRedisplay();
}

void mouse(int btn, int state, int x, int y) {
	static int flag = 0;
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		flag ^= 1;
		glutIdleFunc(flag?idle:NULL);
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);

	wid1=glutCreateWindow("Rectangle");
	glutDisplayFunc(display);
	gluOrtho2D(-250, 250, -250, 250);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	wid2=glutCreateWindow("Spinning rectangle");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	gluOrtho2D(-250, 250, -250, 250);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glutMainLoop();
}