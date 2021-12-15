#include<stdio.h>
#include<GL/glut.h>
#define rgb(x,y,z) glColor3f(x,y,z);

struct point { int x, y; } win1, win2, vp1, vp2;

void display(){}

void drawPoint(point p) {
	glBegin(GL_POINTS);
	glVertex2i(p.x, p.y);
	glEnd();
	glFlush();
}

void drawLine(point p1,point p2) {
	glBegin(GL_LINES);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p2.x, p2.y);
	glEnd();
	glFlush();
}

void drawSquare(point p1,point p2) {
	glBegin(GL_LINE_LOOP);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p1.x, p2.y);
	glVertex2i(p2.x, p2.y);
	glVertex2i(p2.x, p1.y);
	glEnd();
	glFlush();
}

void LiangBaraskyLineClipping(point p1, point p2) {
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	int P[] = { -dx, dx, -dy, dy };
	int Q[] = { p1.x - win1.x, win2.x - p1.x, p1.y - win1.y, win2.y - p1.y };
	double t1 = 0, t2 = 1;
	for (int i = 0; i < 4; i++) {
		double t = (double)Q[i] / P[i];
		if (P[i] < 0) {
			if (t > t1)
				t1 = t;
			if (t > t2)
				return;
		}
		else if(P[i] > 0) {
			if (t < t2)
				t2 = t;
			if (t < t1)
				return;
		}
		else if (Q[i] < 0) return;

	}

	if (t2 != 1)
		p2 = {
		p1.x + (int)(t2 * dx),
		p1.y + (int)(t2 * dy),
	};

	if (t1 != 0)
		p1 = {
		p1.x + (int)(t1 * dx),
		p1.y + (int)(t1 * dy),
	};

	double sx = ((double)vp2.x - vp1.x) / ((double)win2.x - (double)win1.x);
	double sy = ((double)vp2.y - vp1.y) / ((double)win2.y - win1.y);
	p1.x = vp1.x + sx * (p1.x - win1.x);
	p1.y = vp1.y + sy * (p1.y - win1.y);
	p2.x = vp1.x + sx * (p2.x - win1.x);
	p2.y = vp1.y + sy * (p2.y - win1.y);
	drawLine(p1, p2);
}

void mouse(int btn, int state, int x, int y) {
	static int mode = 0;
	static point prev;
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mode++;

		point p = { x,500 - y };
		rgb(0,0,0)
		drawPoint(p);

		switch (mode) {
		case 1:
			win1 = p; break;
		case 2:
			win2 = p; rgb(1, 0, 0) drawSquare(win1, win2); break;
		case 3:
			vp1 = p; break;
		case 4:
			vp2 = p; rgb(0, 1, 0) drawSquare(vp1, vp2); break;
		default: 
			if (mode % 2) 
				prev = p;
			else {
				rgb(0, 0, 1)
				drawLine(prev,p);
				LiangBaraskyLineClipping(prev, p);
			}
		}
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Laing barasky Line clipping algorithm");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	gluOrtho2D(0, 500, 0, 500);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glutMainLoop();
}