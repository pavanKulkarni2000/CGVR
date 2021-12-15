#include<algorithm>
#include<GL/glut.h>

struct point { int x, y; };

int W = 500, H = 500;

void display(){}

void drawLine(point p1, point p2) {
	glBegin(GL_LINES);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p2.x, p2.y);
	glEnd();
	glFlush();
}

void edgeDetect(point p1, point p2, int y, int xint[], int* len) {
	if ((y>=p1.y&&y<p2.y)||(y>=p2.y&&y<p1.y) )
		xint[(*len)++] = (y - (double)p1.y) * (p2.x - (double)p1.x) / (p2.y - (double)p1.y) + p1.x;
}

void drawPolygon(point poly[], int n) {
	int xint[100];
	int len = 0;
	for (int y = 0; y <= H; y++) {
		len = 0;
		for (int l = 0; l < n; l++) {
			edgeDetect(poly[l], poly[(l == n - 1 ? 0 : l+1)], y, xint, &len);
		}
		printf("len=%d\n", len);
		std::sort(xint, xint + len);
		for (int x = 0; x < len && x+1<len; x+=2) {
			drawLine({ xint[x],y }, { xint[ x+1],y });
		}
	}
}

void mouse(int btn, int state, int x, int y) {

	static point poly[20];
	static int n = 0;
	if (state == GLUT_DOWN) {
		if (btn == GLUT_LEFT_BUTTON) {
			point p = { x,H - y };
			glBegin(GL_POINTS);
			glVertex2i(p.x, p.y);
			glEnd();
			glFlush();
			poly[n++] = p;
		}
		else if (btn == GLUT_RIGHT_BUTTON) {
			glutMouseFunc(NULL);
			glColor3f(1, 0, 0);
			drawPolygon(poly, n);
		}
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(W, H);
	glutCreateWindow("Scanline filling");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	gluOrtho2D(0, W, 0, H);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	glutMainLoop();
}