#include<stdio.h>
#include<GL/glut.h>
#define fr3 for(int i=0;i<3;i++)

typedef float point[3];

point T[4] = { {0,0,250},{0,250,-250},{250,-250,-250},{-250,-250,-250} };

void drawTri(point a, point b, point c) {
	glVertex3fv(a);
	glVertex3fv(b);
	glVertex3fv(c);
}

void drawTetra(point a, point b, point c, point d) {
	glColor3f(0, 0, 1);
	drawTri(a, b, c);
	glColor3f(0, 1, 0);
	drawTri(a, b, d);
	glColor3f(1, 0, 0);
	drawTri(a, c, d);
	glColor3f( 1, 0, 1);
	drawTri(b, c, d);
}

void volumeDivision(point a, point b, point c, point d, int k) {
	if (k) {
		point ab, ac, ad, bc, bd, cd;
		fr3 ab[i] = (a[i] + b[i]) / 2;
		fr3 ac[i] = (a[i] + c[i]) / 2;
		fr3 ad[i] = (a[i] + d[i]) / 2;
		fr3 bc[i] = (b[i] + c[i]) / 2;
		fr3 bd[i] = (b[i] + d[i]) / 2;
		fr3 cd[i] = (c[i] + d[i]) / 2;

		volumeDivision(a, ab, ac, ad, k - 1);
		volumeDivision(b, ab, bc, bd, k - 1);
		volumeDivision(c, ac, bc, cd, k - 1);
		volumeDivision(d, ad, bd, cd, k - 1);
	}
	else
		drawTetra(a, b, c, d);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

	glBegin(GL_TRIANGLES);
	volumeDivision(T[0], T[1], T[2], T[3], 2);
	glEnd();
	glFlush();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);

	glutCreateWindow("sierpinski gasket");
	glutDisplayFunc(display);
	glOrtho(-300,300, -300, 300, -300, 300);
	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
}