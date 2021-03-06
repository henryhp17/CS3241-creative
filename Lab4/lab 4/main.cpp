// CS3241Lab1.cpp : Defines the entry point for the console application.
// #include <cmath>
#include "math.h"
#include <iostream>
#include <fstream>
#include "GL\glut.h"
#include "kirby.h"

#define MAXPTNO 1000
#define NLINESEGMENT 32
#define NOBJECTONCURVE 8
#define PI 3.14159265

using namespace std;

// Global variables that you can use
struct Point {
	int x, y;
};

// Storage of control points
int nPt = 0;
Point ptList[MAXPTNO];
Point ptC1[MAXPTNO];

// Display options
bool displayControlPoints = true;
bool displayControlLines = true;
bool displayTangentVectors = false;
bool displayObjects = false;
bool C1Continuity = false;
	
void drawRightArrow()
{
	glColor3f(0,1,0);
	glBegin(GL_LINE_STRIP);
		glVertex2f(0,0);
		glVertex2f(100,0);
		glVertex2f(95,5);
		glVertex2f(100,0);
		glVertex2f(95,-5);
	glEnd();
}

void drawCurveObject(double t, int index, double xcoor, double ycoor)
{
	double dx, dy, deg;

	// Compute the gradient of the current point of the bezier curve
	dx = 3*pow((1-t),2)*(ptList[index-2].x-ptList[index-3].x) + 6*(1-t)*t*(ptList[index-1].x-ptList[index-2].x) + 3*pow(t,2)*(ptList[index].x-ptList[index-1].x);
	dy = 3*pow((1-t),2)*(ptList[index-2].y-ptList[index-3].y) + 6*(1-t)*t*(ptList[index-1].y-ptList[index-2].y) + 3*pow(t,2)*(ptList[index].y-ptList[index-1].y);
	deg = atan2(dy, dx)*180.0/PI;
	
	glPushMatrix();
		glTranslatef(xcoor,ycoor,0);
		glRotatef(deg,0,0,1);
		// Draw the tangent at the desired point, with the desired direction
		if (displayTangentVectors) drawRightArrow();
		// Draw object at the point, according to the tangent
		if (displayObjects)
		{
			glPushMatrix();
				glRotatef(180,0,0,1);
				glScalef(5.0,5.0,1.0);
				drawKirby();
			glPopMatrix();
		}
	glPopMatrix();
}

bool isAutoC1Point(int index) // Check if the point is C1 point
{
	if(((index - 1) % 3 == 0) && (index > 1)) return true;
	return false;
}

void swapC1Points() // Swap the current point with auto-calculated C1 point
{
	Point temp;
	
	// Display the C1 point, store current point in other variable
	for (int i = 0; i < nPt; i++)
	{
		if (isAutoC1Point(i))
		{
			temp = ptList[i];
			ptList[i] = ptC1[i];
			ptC1[i] = temp;
		}
	}
}

double drawBezierCurve(int index, double length)
{
	double xcoor, xtemp, ycoor, ytemp, t;
	
	glBegin(GL_LINE_STRIP);
		for (int i = 0; i <= NLINESEGMENT; i++)
		{
			// Compute the points along the bezier curve, according to control points
			t = i * 1.0 / NLINESEGMENT;
			xcoor = pow((1-t),3)*ptList[index-3].x + 3*pow((1-t),2)*t*ptList[index-2].x + 3*(1-t)*pow(t,2)*ptList[index-1].x + pow(t,3)*ptList[index].x;
			ycoor = pow((1-t),3)*ptList[index-3].y + 3*pow((1-t),2)*t*ptList[index-2].y + 3*(1-t)*pow(t,2)*ptList[index-1].y + pow(t,3)*ptList[index].y;
			glVertex2d(xcoor,ycoor);
			
			// Calculate the length of the current line segment
			if (i != 0) length += sqrt(pow((xcoor-xtemp),2)+pow((ycoor-ytemp),2));
			// Display the tangent or objects for every 64 length, to make the distribution equal between each bezier curve
			if ((length > 64) && (displayTangentVectors || displayObjects))
			{
				length -= 64;
				glEnd();
				drawCurveObject(t, index, xcoor, ycoor);
				glColor3f(0,0,1);
				glBegin(GL_LINE_STRIP);
				glVertex2d(xcoor,ycoor);
			}
			xtemp = xcoor;
			ytemp = ycoor;
		}
	glEnd();

	return length;
}

void display(void)
{
	double lenBezier = 0;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();

	// Swap points when C1 continuity is desired
	if (C1Continuity) swapC1Points();

	if (displayControlPoints)
	{
		glPointSize(5);
		glBegin(GL_POINTS);
			for (int i = 0; i < nPt; i++)
			{
				// Display the control points accordingly
				glColor3f(0,0,0);
				if (C1Continuity && isAutoC1Point(i))
				{
					glColor3d(0.5,0.5,0.5);
					glVertex2d(ptList[i].x,ptList[i].y);
					glColor3f(0,0,0);
				}
				else
				{
					glVertex2d(ptList[i].x,ptList[i].y);
				}
			}
		glEnd();
		glPointSize(1);

	}

	if (displayControlLines) 
	{
		glColor3f(0,1,0);
		glBegin(GL_LINE_STRIP);
			for (int i = 0; i < nPt; i++)
			{
				// Display the control lines accordingly
				glVertex2d(ptList[i].x,ptList[i].y);
			}
		glEnd();
	}

	// Draw the bezier curve using 4 control points
	glColor3f(0,0,1);
	for (int i = 1; i < nPt; i++)
	{
		if (i % 3 == 0) drawBezierCurve(i, lenBezier);
	}

	glPopMatrix();
	if (C1Continuity) swapC1Points();// Swap back the C1 points
	glutSwapBuffers ();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,w,h,0);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
}

void readFile()
{
	std::ifstream file;
    file.open("savefile.txt");
	file >> nPt;

	if (nPt > MAXPTNO)
	{
		cout << "Error: File contains more than the maximum number of points." << endl;
		nPt = MAXPTNO;
	}

	for (int i = 0; i < nPt; i++)
	{
		file >> ptList[i].x;
		file >> ptList[i].y;
		// Compute the C1 points according to the saved points
		if (isAutoC1Point(i))
		{
			ptC1[i].x = 2*ptList[i-1].x - ptList[i-2].x;
			ptC1[i].y = 2*ptList[i-1].y - ptList[i-2].y;
		}
	}
    file.close();// is not necessary because the destructor closes the open file by default
}

void writeFile()
{
	std::ofstream file;
    file.open("savefile.txt");
    file << nPt << endl;

	for (int i = 0; i < nPt; i++)
	{
		file << ptList[i].x << " ";
		file << ptList[i].y << endl;
	}
    file.close();// is not necessary because the destructor closes the open file by default
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 'r':
		case 'R':
			readFile();
		break;

		case 'w':
		case 'W':
			writeFile();
		break;

		case 'T':
		case 't':
			displayTangentVectors = !displayTangentVectors;
		break;

		case 'o':
		case 'O':
			displayObjects = !displayObjects;
		break;

		case 'p':
		case 'P':
			displayControlPoints = !displayControlPoints;
		break;

		case 'L':
		case 'l':
			displayControlLines = !displayControlLines;
		break;

		case 'C':
		case 'c':
			C1Continuity = !C1Continuity;
		break;

		case 'e':
		case 'E':
			// Do something to erase all the control points added
			nPt = 0;
		break;

		case 'Q':
		case 'q':
			exit(0);
		break;

		default:
		break;
	}

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	/* button: GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON */
	/* state: GLUT_UP or GLUT_DOWN */
	enum
	{
		MOUSE_LEFT_BUTTON = 0,
		MOUSE_MIDDLE_BUTTON = 1,
		MOUSE_RIGHT_BUTTON = 2,
		MOUSE_SCROLL_UP = 3,
		MOUSE_SCROLL_DOWN = 4
	};
	if ((button == MOUSE_LEFT_BUTTON) && (state == GLUT_UP))
	{
		if (nPt == MAXPTNO)
		{
			cout << "Error: Exceeded the maximum number of points." << endl;
			return;
		}
		ptList[nPt].x=x;
		ptList[nPt].y=y;
		
		// Compute the auto C1 points according to the mouse clicks
		if (isAutoC1Point(nPt))
		{
			ptC1[nPt].x = 2*ptList[nPt-1].x - ptList[nPt-2].x;
			ptC1[nPt].y = 2*ptList[nPt-1].y - ptList[nPt-2].y;
		}

		nPt++;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	cout << "CS3241 Lab 4"<< endl << endl;
	cout << "Left mouse click: Add a control point" << endl;
	cout << "Q: Quit" << endl;
	cout << "P: Toggle displaying control points" << endl;
	cout << "L: Toggle displaying control lines" << endl;
	cout << "E: Erase all points (Clear)" << endl;
	cout << "C: Toggle C1 continuity" << endl;	
	cout << "T: Toggle displaying tangent vectors" << endl;
	cout << "O: Toggle displaying objects" << endl;
	cout << "R: Read in control points from \"savefile.txt\"" << endl;
	cout << "W: Write control points to \"savefile.txt\"" << endl;
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow ("CS3241 Assignment 4");
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
