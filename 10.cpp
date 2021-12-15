#include<GL/glut.h>
#include<stdio.h>
#include<string.h>
#define rgb(x,y,z) glColor3f(x,y,z);

struct point { int x, y; };

point win[20];
int winn = 0;
void drawPoint(point p) {
	glBegin(GL_POINTS);
	glVertex2i(p.x, p.y);
	glEnd();
	glFlush();
}

void drawPoly(point poly[], int n) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
		glVertex2i(poly[i].x, poly[i].y);
	glEnd();
	glFlush();
}

point intersection(point a, point b, point c, point d) {
	int a1 = b.y - a.y;
	int b1 = a.x - b.x;
	int c1 = a.x * b.y - a.y * b.x;

	int a2 = d.y - c.y;
	int b2 = c.x - d.x;
	int c2 = c.x * d.y - c.y * d.x;

	int determinant = a1 * b2 - a2 * b1;
	if (determinant != 0) {
		return {
			(int)((double)(b2 * c1 - b1 * c2) / determinant),
			(int)((double)(a1 * c2 - a2 * c1) / determinant)
		};
	}
	else {
		printf("Error\n");
		return a;
	}
}

void clip(point p1, point p2, point poly[], int* n) {
	int outside[20];
	for (int i = 0; i < (*n); i++)
		outside[i] = (((p2.y - p1.y) * (poly[i].x - p1.x) - (p2.x - p1.x) * (poly[i].y - p1.y)) < 0);

	point newpoly[20];
	int newn = 0;

	for (int i = 0; i < (*n); i++) {
		int j = i == (*n) - 1 ? 0 : i + 1;
		if (outside[i])
			if (outside[j])
				;
			else {
				newpoly[newn++] = intersection(p1, p2, poly[i], poly[j]);
				newpoly[newn++] = poly[j];
			}
		else
			if (outside[j])
				newpoly[newn++] = intersection(p1, p2, poly[i], poly[j]);
			else 
				newpoly[newn++] = poly[j];
	}

	memcpy(poly, newpoly, newn * sizeof(point));
	*n = newn;
}

void SutherlandHodgemanPolyClipping(point poly[], int n) {


	for (int i = 0; i < winn; i++) {
		clip(win[i], win[(i == winn - 1 ? 0 : i + 1)], poly, &n);
	}

	rgb(0, 1, 0);
	drawPoly(poly, n);
}

void display(){}

void mouse(int btn, int state, int x, int y) {
	static int n=0;
	static point poly[20];
	if (state == GLUT_DOWN) {
		if (btn == GLUT_RIGHT_BUTTON) {
			if (!winn) {
				winn = n;
				memcpy(win, poly, n * sizeof(point));
				rgb(1,0,0)
				drawPoly(poly, n);
			}
			else {
				rgb(0, 0, 1)
				drawPoly(poly, n);
				SutherlandHodgemanPolyClipping(poly, n);
			}
			n = 0;
		}
		if (btn == GLUT_LEFT_BUTTON) {
			poly[n++] = { x,500 - y };
			rgb(0,0,0)
			drawPoint(poly[n - 1]);
		}
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Sutherland Hodgeman polygon clipping algorithm");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	gluOrtho2D(0, 500, 0, 500);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glutMainLoop();
}