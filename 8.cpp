#include<stdio.h>
#include<GL/glut.h>
#define rgb(x,y,z) glColor3f(x,y,z)

typedef short opcode;
struct point { int x, y; };

point win1, win2, vp1, vp2;

const opcode LEFT=1, RIGHT=2, BOTTOM=4, TOP=8;
opcode getOpcode(point p) {
	opcode o = 0;
	if (p.x < win1.x)
		o |= LEFT;
	if (p.x > win2.x)
		o |= RIGHT;
	if (p.y < win1.y)
		o |= BOTTOM;
	if (p.y > win2.y)
		o |= TOP;
	return o;
}

void drawSquare(point p1, point p2) {
	glBegin(GL_LINE_LOOP);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p2.x, p1.y);
	glVertex2i(p2.x, p2.y);
	glVertex2i(p1.x, p2.y);
	glEnd();
	glFlush();
}

void drawLine(point p1, point p2) {
	glBegin(GL_LINES);
	glVertex2i(p1.x, p1.y);
	glVertex2i(p2.x, p2.y);
	glEnd();
	glFlush();
}

void drawPoint(point p) {
	glBegin(GL_POINTS);
	glVertex2i(p.x, p.y);
	glEnd();
	glFlush();
}

void CohenSutherlandLineClipping(point p1, point p2) {
	opcode op1=getOpcode(p1), op2=getOpcode(p2), op;
	point p;
	while (1) {

		if ((op1 | op2) == 0) {
			break;
		}
		if ((op1 & op2) != 0) {
			return;
		}

		op = op1 ? op1 : op2;

		if (op & LEFT) {
			p.x = win1.x;
			p.y = p1.y + ((double)win1.x - p1.x) * ((double)p1.y - p2.y) / ((double)p1.x - p2.x);
		}
		else if (op & RIGHT) {
			p.x = win2.x;
			p.y = p1.y + ((double)win2.x - p1.x) * ((double)p1.y - p2.y) / ((double)p1.x - p2.x);
		}
		else if (op & BOTTOM) {
			p.y = win1.y;
			p.x = p1.x + ((double)win1.y - p1.y) * ((double)p1.x - p2.x) / ((double)p1.y - p2.y);
		}
		else {
			p.y = win2.y;
			p.x = p1.x + ((double)win2.y - p1.y) * ((double)p1.x - p2.x) / ((double)p1.y - p2.y);
		}

		if (op == op1) {
			p1 = p;
			op1 = getOpcode(p1);
		}
		else {
			p2 = p;
			op2 = getOpcode(p2);
		}
	}

	double sx = ((double)vp2.x - vp1.x) / ((double)win2.x - win1.x);
	double sy = ((double)vp2.y - vp1.y) / ((double)win2.y - win1.y);

	p1.x = vp1.x + sx * (p1.x - win1.x);
	p1.y = vp1.y + sy * (p1.y - win1.y);

	p2.x = vp1.x + sx * (p2.x - win1.x);
	p2.y = vp1.y + sy * (p2.y - win1.y);

	drawLine(p1, p2);
}

void mouse(int btn, int st, int x, int y) {
	static int flag = 0;
	static point prev;
	if (st == GLUT_DOWN && btn == GLUT_LEFT_BUTTON) {
		flag++;
			point p = { x,500 - y };

			rgb(0, 0, 0);
			drawPoint(p);

			switch (flag) {
			case 1:win1 = p; break;
			case 2:win2 = p; rgb(1, 0, 0); drawSquare(win1, win2); break;
			case 3:vp1 = p; break;
			case 4:vp2 = p; rgb(0, 1, 0); drawSquare(vp1, vp2); break;
			default:
				if (flag % 2) prev = p;
				else {
					rgb(0, 0, 1);
					drawLine(prev, p);
					CohenSutherlandLineClipping(prev, p);
				}
			}

	}
}

void display(){}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Cohen Sutherland Line Clipping");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	gluOrtho2D(0, 500, 0, 500);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glutMainLoop();
}