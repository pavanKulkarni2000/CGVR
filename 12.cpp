#include<GL/glut.h>
#include<stdio.h>
#include<Windows.h>

float spin[3] = { 0,0,0 };

float vertices[] = {
	1,1,1,
	1,1,-1,
	-1,1,-1,
	-1,1,1,

	1,-1,1,
	1,-1,-1,
	-1,-1,-1,
	-1,-1,1

};

float colors[] = {
	1,0,0,
	1,0,1,
	0,0,1,
	0,1,0,

	1,1,0,
	0,1,1,
	1,0.5,0.5,
	0.5,0.5,1
};

GLubyte indices[] = {
	0,1,2,3,
	4,5,6,7,
	0,1,5,4,
	3,2,6,7,
	3,0,4,7,
	2,1,5,6
};

void reshape(int w, int h) {
	glViewport(0, w, 0, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h) {
		float r = h / w;
		glOrtho(-2, 2, r * -2, r * 2, -2, 2);
	}
	else {
		float r = w/h;
		glOrtho(-2 * r, 2 * r, -2, 2, -2, 2);
	}
	glMatrixMode(GL_MODELVIEW);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(spin[0], 1, 0, 0);
	glRotatef(spin[1], 0, 1, 0);
	glRotatef(spin[2], 0, 0, 1);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
	glFlush();
	glPopMatrix();
}
short axis = 1;
void idle() {
	spin[axis] += 0.2;
	if (spin[axis] == 360) spin[axis] = 0;
	glutPostRedisplay();
	Sleep(10);
}

void mouse(int btn, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		if (btn == GLUT_LEFT_BUTTON) axis = 0;
		if (btn == GLUT_MIDDLE_BUTTON) axis = 1;
		if (btn == GLUT_RIGHT_BUTTON) axis = 2;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Spinning cube");
	glutDisplayFunc(display);
	glOrtho(-3, 3, -3, 3, -3, 3);
	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutMainLoop();
}