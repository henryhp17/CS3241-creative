// CS3241Lab1.cpp : Defines the entry point for the console application.
// #include <cmath>
#include <Windows.h>
#include "math.h"
#include <iostream>
#include <fstream>
#include "GL\glut.h"

#define M_PI 3.141592654

// global variable
bool m_Smooth = FALSE;
bool m_Highlight = FALSE;
GLfloat angle = 0;   /* in degrees */
GLfloat angle2 = 0;   /* in degrees */
GLfloat zoom = 1.0;
int mouseButton = 0;
int moving, startx, starty;

#define NO_OBJECT 4;
int current_object = 0;

using namespace std;

void setupLighting()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	// Lights, material properties
    GLfloat	ambientProperties[]  = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat	diffuseProperties[]  = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat	specularProperties[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightPosition[] = {-100.0f,100.0f,100.0f,1.0f};
	
    glClearDepth( 1.0 );

	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition);
	
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
    glLightfv( GL_LIGHT0, GL_SPECULAR, specularProperties);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

	// Default : lighting
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

void drawSphere(double r)
{

	float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    float mat_diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
    float no_shininess = 0.0f;

	// setup object shading
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	if (m_Highlight)
	{
		// your codes for highlight here
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_ambient);
		glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);
	} else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	}
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	
	int n = 20;
    for (int i = 0; i < n; i++) {
		for (int j = 0; j < 2 * n; j++) {
			if (m_Smooth)
			{
				glBegin(GL_POLYGON);
				    // the normal of each vertex is actually its own coordinates normalized for a sphere
					// I used the vector obtained from (the coordinates of the vertex - coordinate of the sphere's center)
					// almost the same with the non-smooth version, but I defined different normals for every vertices
				    // your normal here
					glNormal3d(sin(i*M_PI/n)*cos(j*M_PI/n), cos(i*M_PI/n)*cos(j*M_PI/n), sin(j*M_PI/n));
					glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n), r*cos(i*M_PI/n)*cos(j*M_PI/n), r*sin(j*M_PI/n));
				    // your normal here
					glNormal3d(sin((i+1)*M_PI/n)*cos(j*M_PI/n), cos((i+1)*M_PI/n)*cos(j*M_PI/n), sin(j*M_PI/n));
					glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n), r*cos((i+1)*M_PI/n)*cos(j*M_PI/n), r*sin(j*M_PI/n));
				    // your normal here
					glNormal3d(sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n), cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n), sin((j+1)*M_PI/n));
					glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n), r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n), r*sin((j+1)*M_PI/n));
					// your normal here
					glNormal3d(sin(i*M_PI/n)*cos((j+1)*M_PI/n), cos(i*M_PI/n)*cos((j+1)*M_PI/n), sin((j+1)*M_PI/n));
					glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n), r*cos(i*M_PI/n)*cos((j+1)*M_PI/n), r*sin((j+1)*M_PI/n));
 				glEnd();
			} else {
				glBegin(GL_POLYGON);
					// Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
					// Set normal of the vertices with the same normal as the normal of the polygon
					glNormal3d(sin((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n), cos((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n), sin((j+0.5)*M_PI/n));
					glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n), r*cos(i*M_PI/n)*cos(j*M_PI/n), r*sin(j*M_PI/n));
					glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n), r*cos((i+1)*M_PI/n)*cos(j*M_PI/n), r*sin(j*M_PI/n));
					glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n), r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n), r*sin((j+1)*M_PI/n));
					glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n), r*cos(i*M_PI/n)*cos((j+1)*M_PI/n), r*sin((j+1)*M_PI/n));
 				glEnd();
			}
		}
	}
}

void drawCone(double r, double h)
{
	int n = 20;
	float s = sqrt(pow(r,2)+pow(h,2));
	glBegin(GL_TRIANGLE_FAN);
	glNormal3d(0, 0, 1);
	glVertex3d(0, 0, h);
		for (int i = 0; i < 2 * n; i++) {
			if (m_Smooth) { // smooth cone vertices and normals
				// normals for the cone is about the same as sphere, but the z-element is the ratio between height and radius of cone
				// ratio of the normals can be determined using phytagorean formula
				glNormal3d(h/s*sin((i)*M_PI/n), h/s*cos((i)*M_PI/n), r/s);
				glVertex3d(r*sin(i*M_PI/n), r*cos(i*M_PI/n), 0);
				glNormal3d(h/s*sin((i+1)*M_PI/n), h/s*cos((i+1)*M_PI/n), r/s);
				glVertex3d(r*sin((i+1)*M_PI/n), r*cos((i+1)*M_PI/n), 0);
			} else { // non-smooth cone vertices and normals
				glNormal3d(h/s*sin((i+0.5)*M_PI/n), h/s*cos((i+0.5)*M_PI/n), r/s);
				glVertex3d(r*sin(i*M_PI/n), r*cos(i*M_PI/n), 0);
				glVertex3d(r*sin((i+1)*M_PI/n), r*cos((i+1)*M_PI/n), 0);
			}
		}
	glEnd();
}

void drawCylinder(double r, double t)
{
	int n = 20;
	for (int i = 0; i < 2 * n; i++) {
		if (m_Smooth) {
			glBegin(GL_POLYGON);
				// smooth cylinder vertices and normals
				// normals for the cylinder is about the same as sphere, but the z-element is 0
				// set the normal of as the nearest distance from the z-axis
				glNormal3d(sin((i)*M_PI/n), cos((i)*M_PI/n), 0);
				glVertex3d(r*sin(i*M_PI/n), r*cos(i*M_PI/n), 0);
				glNormal3d(sin((i+1)*M_PI/n), cos((i+1)*M_PI/n), 0);
				glVertex3d(r*sin((i+1)*M_PI/n), r*cos((i+1)*M_PI/n), 0);
				glNormal3d(sin((i+1)*M_PI/n), cos((i+1)*M_PI/n), 0);
				glVertex3d(r*sin((i+1)*M_PI/n), r*cos((i+1)*M_PI/n), t);
				glNormal3d(sin((i)*M_PI/n), cos((i)*M_PI/n), 0);
				glVertex3d(r*sin(i*M_PI/n), r*cos(i*M_PI/n), t);
			glEnd();
		} else {
			glBegin(GL_POLYGON);
				// non-smooth cylinder vertices and normals
				glNormal3d(sin((i+0.5)*M_PI/n), cos((i+0.5)*M_PI/n), 0);
				glVertex3d(r*sin(i*M_PI/n), r*cos(i*M_PI/n), 0);
				glVertex3d(r*sin((i+1)*M_PI/n), r*cos((i+1)*M_PI/n), 0);
				glVertex3d(r*sin((i+1)*M_PI/n), r*cos((i+1)*M_PI/n), t);
				glVertex3d(r*sin(i*M_PI/n), r*cos(i*M_PI/n), t);
			glEnd();
		}
	}
}

void drawSpindle(double r, double t, double h1, double h2)
{
	float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient_color[] = {0.5f, 0.2f, 0.3f, 1.0f};
    float mat_diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
    float no_shininess = 0.0f;
    float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};

	// setup object shading
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	if (m_Highlight)
	{
		// your codes for highlight here
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_ambient_color);
		glMaterialf(GL_FRONT, GL_SHININESS, 24.0f);

	} else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	}
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

	//draw the spindle shaped object
	glPushMatrix();
		glTranslatef(0, 0, t);
		drawCone(r, h1);
	glPopMatrix();
	drawCylinder(r, t);
	glPushMatrix();
		glRotatef(180, 1, 0, 0);
		drawCone(r, h2);
	glPopMatrix();
}

void drawInfluenzaVirus()
{
	drawSphere(1); // main body of the virus
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			// add the extra features and "hands" of the virus
			glPushMatrix();
				glTranslatef(0, 0, 1.3);
				drawSpindle(0.2, 0.1, 0.2, 0.4);
			glPopMatrix();
			glRotatef(45, 1, 0, 0);
		}
		glRotatef(45, 0, 1, 0);
	}
}

void drawSegment(double r, double t, double h)
{
	// draw one single triangle for the side of the bridge
	glPushMatrix();
		glRotatef(60, 1, 0, 0);
		for (int i = 0; i < 3; i++)
		{
			drawSphere(r);
			glTranslatef(0, 0, h);
			drawSpindle(r, t, h, h);
			glTranslatef(0, 0, h + t);
			glRotatef(120, 1, 0, 0);
		}
	glPopMatrix();
}

void drawTrainBridge()
{
	double r = 0.05, t = 0.1, h = 0.5, w = 1;
	double length = 2 * h + t;
	double rad = 60 * M_PI / 180;
	
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(- t / 2 - 1.5 * h, 0, -5 * length);
	for (int i = 0; i < 2; i++) {
		glPushMatrix();
			for (int j = 0; j < 10; j++) {
				if (i == 0) {
					// draw the base of the bridge
					glPushMatrix();
						glRotatef(90, 0, 1, 0);
						glTranslatef(length * cos(rad), -length * sin(rad), h / 2);
						for (int k = 0; k < 5; k++) {
							drawSpindle(r, t + 2*h, h, h);
							glTranslatef(-length/5, 0, 0);
						}
						drawSpindle(r, t + 2*h, h, h);
					glPopMatrix();
				}
				glPushMatrix();
					// draw the support of the bridge
					glPushMatrix();
						glTranslatef(0, -(h - t + length * cos(rad)), 0);
						glRotatef(90, 1, 0, 0);
						drawSpindle(2*r, 2*h, t, t);
					glPopMatrix();
					// draw the side of the bridge with segments
					for (int k = 0; k < 2; k++) {
						if (k < j + 1) {
							drawSegment(r, t, h);
							glTranslatef(0, length * sin(rad), -length * cos(rad));
						}
					}
					glTranslatef(0, -length * sin(rad), length * cos(rad) + h);
					// draw extra closing to make the side and upper bridge more solid
					if (j > 0) {
						if (j < 9) drawSpindle(r, t, h, h);
						if (i == 0) {
							glRotatef(90, 0, 1, 0);
							glTranslatef(h, 0, h);
							drawSpindle(r, t + h, h, h);
						}
					}
				glPopMatrix();
				glTranslatef(0, 0, length);
			}
		glPopMatrix();
		glTranslatef(t + 3 * h, 0, 0);
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(0, 0, -6);
	    glRotatef(angle2, 1.0, 0.0, 0.0);
		glRotatef(angle, 0.0, 1.0, 0.0);
		glScalef(zoom, zoom, zoom);

		switch (current_object) {
		case 0:
			drawSphere(1);
			break;
		case 1:
			// draw your second primitive object here
			drawSpindle(0.5, 1, 0.5, 0.3);
			break;
		case 2:
			// draw your first composite object here
			drawInfluenzaVirus();
			break;
		case 3:
			// draw your second composite object here
			drawTrainBridge();
			break;
		default:
			break;
		};
	glPopMatrix();
	glutSwapBuffers();
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
	case 'p':
	case 'P':
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		break;			
	case 'w':
	case 'W':
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		break;			
	case 'v':
	case 'V':
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
		break;			
	case 's':
	case 'S':
		m_Smooth = !m_Smooth;
		break;
	case 'h':
	case 'H':
		m_Highlight = !m_Highlight;
		break;
	
	case '1':
	case '2':
	case '3':
	case '4':
		current_object = key - '1';
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
	if (state == GLUT_DOWN) {
		mouseButton = button;
		moving = 1;
		startx = x;
		starty = y;
	}
	if (state == GLUT_UP) {
		mouseButton = button;
		moving = 0;
	}
}

void motion(int x, int y)
{
	if (moving) {
		if (mouseButton==GLUT_LEFT_BUTTON)
		{
			angle = angle + (x - startx);
			angle2 = angle2 + (y - starty);
		}
		else zoom += ((y - starty) * 0.001);
		startx = x;
		starty = y;
		glutPostRedisplay();
	}
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 3"<< endl<< endl;

	cout << "1-4: Draw different objects"<<endl;
	cout << "S: Toggle Smooth Shading"<<endl;
	cout << "H: Toggle Highlight"<<endl;
	cout << "W: Draw Wireframe"<<endl;
	cout << "P: Draw Polygon"<<endl;
	cout << "V: Draw Vertices"<<endl;
	cout << "Q: Quit" <<endl<< endl;

	cout << "Left mouse click and drag: rotate the object"<<endl;
	cout << "Right mouse click and drag: zooming"<<endl;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow ("CS3241 Assignment 3");
	glClearColor (1.0,1.0,1.0, 1.0);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	setupLighting();
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); 
	glDepthMask(GL_TRUE);

    glMatrixMode(GL_PROJECTION);
    gluPerspective( /* field of view in degree */ 40.0,
	/* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 80.0);
	glMatrixMode(GL_MODELVIEW);
	glutMainLoop();

	return 0;
}
