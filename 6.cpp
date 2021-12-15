#include<math.h>
#include<GL/glut.h>

float dtor(int d) {
	return d * 3.14159 / 180.0;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);

	glColor3f(0, 0, 1);
	float phir, thetar, phi20r;
	for (int phi = -80; phi <= 80; phi += 10) {
		phir = dtor(phi);
		phi20r = dtor(phi + 10);
		glBegin(GL_QUAD_STRIP);
		for (int theta = -180; theta <= 180; theta += 10) {
			thetar = dtor(theta);
			glVertex3f(sin(thetar) * cos(phir), cos(thetar) * cos(phir), sin(phir));
			glVertex3f(sin(thetar) * cos(phi20r), cos(thetar) * cos(phi20r), sin(phi20r));
		}
		glEnd();
	}

	phir = dtor(80);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 1);
	for (int theta = -180; theta <= 180; theta += 10) {
		thetar = dtor(theta);
		glVertex3f(sin(thetar) * cos(phir), cos(thetar) * cos(phir), sin(phir));
	}
	glEnd();

	phir = -phir;
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, -1);
	for (int theta = -180; theta <= 180; theta += 10) {
		thetar = dtor(theta);
		glVertex3f(sin(thetar) * cos(phir), cos(thetar) * cos(phir), sin(phir));
	}
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);

	glutCreateWindow("Sphere");
	glutDisplayFunc(display);
	glOrtho(-1,1,-1,1,-1,1);
	glClearColor(1, 1, 1, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}