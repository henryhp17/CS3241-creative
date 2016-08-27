// CS3241Lab1.cpp : Defines the entry point for the console application.
// Henry Pratama Suryadi A0105182R
#include <cmath>
#include <iostream>
#include "GL\glut.h"

using namespace std;

GLfloat PI = 3.14;
float alpha = 0.0, k=1;
float tx = 0.0, ty=0.0;

int left_counter = 0, right_counter = 0;
int showCreator = 0;

void init(void)
{
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow ("CS3241 Lab 1 Henry Pratama Suryadi");
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glShadeModel (GL_SMOOTH);
}

void drawCircle(float radius)
{
	float deg;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 0);
	for (int i = 0 ; i <= 361; i++)
	{
		deg = i * PI / 180.0;
		glVertex2f(cos(deg) * radius, sin(deg) * radius);
	}
	glEnd();
}

void drawOutlineCircle(float in_radius, float out_radius)
{
	float deg;
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(0, 0);
	for (int i = 0 ; i <= 361; i++)
	{
		deg = i * PI / 180.0;
		glVertex2f(cos(deg) * in_radius, sin(deg) * in_radius);
		glVertex2f(cos(deg) * out_radius, sin(deg) * out_radius);
	}
	glEnd();
}

void drawRectangle(float length, float width)
{
	glBegin(GL_POLYGON);
	glVertex2f(-length/2, -width/2);
	glVertex2f(length/2, -width/2);
	glVertex2f(length/2, width/2);
	glVertex2f(-length/2, width/2);
	glEnd();
}

void drawOutline(float length, float width)
{
	glBegin(GL_QUADS);
	glVertex2f(-length/2, -width/2);
	glVertex2f(length/2, -width/2);
	glVertex2f(length/2, width/2);
	glVertex2f(-length/2, width/2);
	glEnd();
}

void drawEllipse(float xradius, float yradius)
{
	float deg;
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0,0);
	for (int i = 0; i <= 361; i++)
	{
		deg = i * PI / 180.0;
		glVertex2f(cos(deg) * xradius, sin(deg) * yradius);
	}
	glEnd();
}

void drawGradientEllipse(float xradius, float yradius)
{
	float deg;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.03, 0.11, 0.22);
	glVertex2f(0, 0);
	glColor3f(0.27, 0.64, 0.91);
	for (int i = 0; i <= 361; i++)
	{
		deg = i * PI / 180.0;
		glVertex2f(cos(deg) * xradius, sin(deg) * yradius);
	}
	glEnd();
}

void drawOutlineEllipse(float in_xradius, float in_yradius, float out_xradius, float out_yradius)
{
	float deg;
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i <= 361; i++)
	{
		deg = i * PI / 180.0;
		glVertex2f(cos(deg) * in_xradius, sin(deg) * in_yradius);
		glVertex2f(cos(deg) * out_xradius, sin(deg) * out_yradius);
	}
	glEnd();
}

void drawOutlineRightHand(float in_xradius, float in_yradius, float out_xradius, float out_yradius)
{
	float deg;
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 75; i <= 265; i++)
	{
		deg = i * PI / 180.0;
		glVertex2f(cos(deg) * in_xradius, sin(deg) * in_yradius);
		glVertex2f(cos(deg) * out_xradius, sin(deg) * out_yradius);
	}
	glEnd();
}

void drawBackground()
{
	float deg, radius;
	radius = 40; 
	glPushMatrix();
		glBegin(GL_TRIANGLE_FAN); //draw blue highlight background
		glColor3f(0.49, 0.6, 0.71);
		glVertex2f(0, 0);
		for (int i = 0 ; i <= 361; i++)
		{
			deg = i * PI / 180.0;
			if (i % 9 == 0) glColor3f(0.38, 0.55, 0.7);
			else if ((i + 6) % 9 == 0) glColor3f(0.3, 0.45, 0.61);
			glVertex2f(cos(deg) * radius, sin(deg) * radius);
		}
		glEnd();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(0, -5, 0);
		glColor3f(0.09, 0.22, 0.39);
		for (int i = -35; i <= 35; i++) //draw circle effect
		{
			glPushMatrix();
				glTranslatef(0.8 * i, 0, 0);
				for (int j = 0; j <= 22; j++)
				{
					drawCircle(0.018 * (23 - j));
					glTranslatef(-0.4, 0.4, 0);
				}
			glPopMatrix();
		}
		glTranslatef(0, -20, 0);
		drawRectangle(80, 40);
	glPopMatrix();
}

void drawSingleStar(float radius)
{
	float out_radius;
	out_radius = radius * 1.15;
	glColor3f(0.95, 0.65, 0.08);
	glPushMatrix();
	for (int i = 0; i < 5; i++) //outer star layer
	{
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(0, 0);
		glVertex2f(cos(0.628) * out_radius, sin(0.628) * out_radius);
		glVertex2f(cos(-0.628) * out_radius, sin(-0.628) * out_radius);
		glVertex2f(2 * cos(0.628) * out_radius, 0);
		glEnd();
		glRotatef(72, 0, 0, 1);
	}
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.9, 0.9, 0.6);
	for (int i = 0; i < 5; i++) //inner star layer
	{
		glBegin(GL_TRIANGLE_STRIP);
		glVertex2f(0, 0);
		glVertex2f(cos(0.628) * radius, sin(0.628) * radius);
		glVertex2f(cos(-0.628) * radius, sin(-0.628) * radius);
		glVertex2f(2 * cos(0.628) * radius, 0);
		glEnd();
		glRotatef(72, 0, 0, 1);
	}
	glPopMatrix();
}

void drawStars()
{
	glPushMatrix();
		glTranslatef(5, 6, 0);
		drawSingleStar(1.2);
		glPushMatrix();
			glTranslatef(2, -2, 0);
			glRotatef(30, 0, 0, 1);
			drawSingleStar(0.5);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(3, 2.2, 0);
			glRotatef(40, 0, 0, 1);
			drawSingleStar(0.4);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-1.5, 3.5, 0);
			glRotatef(10, 0, 0, 1);
			drawSingleStar(0.9);
		glPopMatrix();
	glPopMatrix();
}

void drawKirbyFoot()
{
	float x;
	glColor3f(0.86, 0.01, 0.34);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0, 5);
	for (int i = -50; i <= 50; i++)
	{
		x = i * 0.04;
		glVertex2f(x, pow(x, 2)); 
	}
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = -50; i <= 50; i++)
	{
		x = i * 0.04;
		glVertex2f(x, pow(x, 2)); 
		glVertex2f(1.05 * x, pow(x, 2) - 0.1);

	}
	glEnd();
}

void drawKirbyEyes()
{
	drawGradientEllipse(0.4, 1.1); //blue ellipse
	glColor3f(0, 0, 0);
	drawOutlineEllipse(0.4, 1.1, 0.5, 1.2); //black outline
	glTranslatef(0, 0.2, 0);
	glColor3f(0, 0, 0);
	drawEllipse(0.4, 0.8); //black ellipse
	glTranslatef(0, 0.3, 0);
	glColor3f(1, 1, 1);
	drawEllipse(0.35, 0.5); //white ellipse
}

void drawKirbyTongue(float xradius, float yradius)
{
	float deg, adjust, xmove, ymove;
	adjust = 3;
	xmove = 0.8;
	ymove = -1.5;
	glColor3f(0.95, 0.43, 0.42);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(0,0);
	for (int i = 198; i <= 380; i++) //lower arc
	{
		deg = i * PI / 180.0;
		glVertex2f(cos(deg) * xradius, sin(deg) * yradius);
	}
	for (int i = 79; i <= 164; i++) //upper arc
	{
		deg = i * PI / 180.0;
		glVertex2f((cos(deg) * (xradius + adjust))/2 + xmove, (sin(deg) * (yradius + adjust))/2 + ymove);
	}
	glEnd();
	glColor3f(0, 0, 0);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 79; i <= 164; i++) //outline of the tongue
	{
		deg = i * PI / 180.0;
		glVertex2f((cos(deg) * (xradius + adjust))/2 + xmove, (sin(deg) * (yradius + adjust))/2 + ymove);
		glVertex2f((cos(deg) * (xradius + adjust + 0.2))/2 + xmove, (sin(deg) * (yradius + adjust + 0.2))/2 + ymove);
	}
	glEnd();
}

void drawKirby()
{
	//Kirby feet
	glPushMatrix(); //left foot
		glTranslatef(-5.2, -3.6, 0);
		glRotatef(-65, 0, 0, 1);
		drawKirbyFoot();
	glPopMatrix();
	glPushMatrix(); //right foot
		glTranslatef(4.3, -4.7, 0);
		glRotatef(50, 0, 0, 1);
		drawKirbyFoot();
	glPopMatrix();
	//Kirby main body
	glPushMatrix(); //left hand
		glTranslatef(-2.8,2.2,0);
		glRotatef(-60, 0, 0, 1);
		glColor3f(0.97, 0.64, 0.71);
		drawEllipse(2, 1.5);
		glColor3f(0, 0, 0);
		drawOutlineEllipse(2, 1.5, 2.1, 1.6);
	glPopMatrix();
	glColor3f(0.97, 0.64, 0.71); //big round body
	drawCircle(4);
	glColor3f(0, 0, 0);
	drawOutlineCircle(4, 4.1);
	glPushMatrix(); //right hand
		glTranslatef(3, 1.5, 0);
		glRotatef(220, 0, 0, 1);
		glColor3f(0.97, 0.64, 0.71);
		drawEllipse(2, 1.5);
		glColor3f(0, 0, 0);
		drawOutlineRightHand(2, 1.5, 2.1, 1.6);
	glPopMatrix();
	//Kirby cheek
	glPushMatrix(); //right cheek
		glTranslatef(1.4, 0.5, 0);
		glRotatef(10, 0, 0, 1);
		glColor3f(0.96, 0.48, 0.53);
		drawEllipse(0.65, 0.35);
	glPopMatrix();
	glPushMatrix(); //left cheek
		glTranslatef(-2.6, 1.2, 0);
		glRotatef(-40, 0, 0, 1);
		glColor3f(0.96, 0.48, 0.53);
		drawEllipse(0.65, 0.35);
	glPopMatrix();
	//Kirby eyes
	glPushMatrix(); //right eye
		glTranslatef(0.4, 1.8, 0);
		glRotatef(-12, 0, 0, 1);
		drawKirbyEyes();
		glRotatef(30, 0, 0, 1);
		glTranslatef(0.2, 0.2, 0);
		glColor3f(0, 0, 0);
		drawOutline(1.5, 0.1);
		glTranslatef(0, 0.65, 0);
		glColor3f(0.97, 0.64, 0.71);
		drawRectangle(1.2, 1.2);
	glPopMatrix();
	glPushMatrix(); //left eye
		glScalef(0.95, 0.95, 0.95);
		glTranslatef(-1.4, 2.3, 0);
		glRotatef(-12, 0, 0, 1);
		drawKirbyEyes();
		glRotatef(-30, 0, 0, 1);
		glTranslatef(-0.2, 0.2, 0);
		glColor3f(0, 0, 0);
		drawOutline(1.5, 0.1);
		glTranslatef(0, 0.45, 0);
		glColor3f(0.97, 0.64, 0.71);
		drawRectangle(1.2, 0.8);
	glPopMatrix();
	//Kirby mouth
	glPushMatrix();
		glTranslatef(-0.8, -1.5, 0);
		glRotatef(10, 0, 0, 1);
		glColor3f(0.47, 0.05, 0.29);
		drawEllipse(1.4, 2.1);
		glColor3f(0, 0, 0);
		drawOutlineEllipse(1.4, 2.1, 1.5, 2.2);
		drawKirbyTongue(1.4, 2.1);
	glPopMatrix();
}

void drawBubble(float xradius, float yradius)
{
	float deg;
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(0.71, 0.87, 0.96);
	glVertex2f(-0.9 * xradius, 0);
	glColor3f(0.91, 0.98, 1);
	for (int i = 0; i <= 361; i++)
	{
		deg = i * PI / 180.0;
		glVertex2f(cos(deg) * xradius, sin(deg) * yradius);
	}
	glEnd();
}

void drawWind()
{
	float index;
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = -20; i <= 20; i++)
	{
		index = i * 0.1;
		glVertex2f(index, 0.4 + pow(index * 0.4, 2));
		glVertex2f(index, pow(index * 0.5, 2));
	}
	glEnd();
}

void drawAir()
{
	glPushMatrix(); //draw bubbles
		glTranslatef(-6, -1, 0);
		glRotatef(-5, 0, 0, 1);
		drawBubble(0.6, 0.15);
		glTranslatef(-1, -1, 0);
		drawBubble(0.6, 0.15);
		glTranslatef(-1, 0.5, 0);
		glRotatef(-3, 0, 0, 1);
		drawBubble(1.2, 0.3);
		glTranslatef(-3, 1, 0);
		glRotatef(-10, 0, 0, 1);
		drawBubble(1.2, 0.3);
		glTranslatef(-2, 2, 0);
		glRotatef(-30, 0, 0, 1);
		drawBubble(2.0, 0.5);
		glTranslatef(2, 2, 0);
		drawBubble(1.2, 0.3);
		glTranslatef(-2, 2, 0);
		glRotatef(-15, 0, 0, 1);
		drawBubble(1, 0.25);
	glPopMatrix();
	glPushMatrix(); //draw winds
		glTranslatef(-10, -2.3, 0);
		glRotatef(-17, 0, 0, 1);
		glScalef(2, 1, 3);
		drawWind();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-8, 5, 0);
		glRotatef(-70, 0, 0, 1);
		glScalef(2, 1, 3);
		drawWind();
	glPopMatrix();
}

void drawUnitLine()
{
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(0,8);
	glEnd();
}

void drawUnitLine2()
{
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(0,4);
	glEnd();
}
void drawWhat(int i) 
{
	if (i == 0) return;
	glPushMatrix();
		glScalef(0.5,0.5,0.5);
		drawUnitLine();
		glTranslatef(0,4,0);
		glPushMatrix();
			glRotatef(-90,0,0,1);
			for(int j=0;j<3;j++)
			{
				drawWhat(i-1);
				glRotatef(90,0,0,1);
			}
		glPopMatrix();
	glPopMatrix();
}

void drawWhat2(int i) 
{
	if (i == 0) return;
	glPushMatrix();
		glScalef(0.5,0.5,0.5);
		drawUnitLine2();
		glTranslatef(0,4,0);
		glPushMatrix();
			glRotatef(-90,0,0,1);
			//for(int j=0;j<3;j++)
			//{
				drawWhat2(i-1);
				//glRotatef(90,0,0,1);
			//}
		glPopMatrix();
	glPopMatrix();
}

void drawAUnitLine()
{
	glBegin(GL_LINES);
	glVertex2f(0,0);
	glVertex2f(1,0);
	glEnd();
}

void drawPentagon()
{
	glPushMatrix();
		glTranslatef(0,1,0);
		glRotatef(216,0,0,1);
		for(int i = 0; i < 5; i++) {
			drawAUnitLine();
			glTranslatef(1,0,0);
			glRotatef(72,0,0,1);
		}
	glPopMatrix();
}

void drawManyPentagons()
{
	glPushMatrix();
		glRotatef(180,0,0,1);
		for(int i = 0; i < 5;i++) {
			glPushMatrix();
				glTranslatef(0, 4 * tan(PI/10),0);
				drawPentagon();
			glPopMatrix();
			glRotatef(72,0,0,1);
		}
	glPopMatrix();
}

void draw8Square()
{
	glBegin(GL_LINE_LOOP);
		glVertex2d(-8,8);
		glVertex2d(8,8);
		glVertex2d(8,-8);
		glVertex2d(-8,-8);
	glEnd();
}

void drawSomething(int i)
{
	if(!i) return;
	draw8Square();
	glPushMatrix();
		glTranslatef(8,0,0);
		glRotatef(45,0,0,1);
		glScalef(1/sqrt(2.0),1/sqrt(2.0),1);
		drawSomething(i-1);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(-8,0,0);
		glRotatef(-45,0,0,1);
		glScalef(1/sqrt(2.0),1/sqrt(2.0),1);
		drawSomething(i-1);
	glPopMatrix();
}

void drawRecursiveCircle(int n)
{
	glPushMatrix();
		if (n != 1) {
			for (int i = 0; i < 3; i++) {
				glPushMatrix();
					glTranslatef(0,12,0);
					glScalef(0.5,0.5,0.5);
					drawRecursiveCircle(n - 1);
				glPopMatrix();
				glRotatef(120,0,0,1);
			}
		}
		drawCircle(8);
	glPopMatrix();
}

void drawPolygon()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_POLYGON);
	glVertex2f(0,0);
	glVertex2f(0,1);
	glVertex2f(1,0);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();
	
	//controls transformation using keyboard
	glScalef(k, k, k);	
	glTranslatef(tx, ty, 0);	
	glRotatef(alpha, 0, 0, 1);

	glColor3f(0,0,0);
	drawPolygon();
	/*
	//draw your stuff here
	drawBackground();
	drawStars();
	drawKirby();

	//clone Kirby if mouse button is clicked
	glPushMatrix();
		for (int i = 0; i < left_counter; i++)
		{
			glTranslatef(-(i + 1), 0, 0);
			drawKirby();
		}
	glPopMatrix();
	glPushMatrix();
		for (int i = 0; i < right_counter; i++)
		{
			glTranslatef((i + 1), 0, 0);
			drawKirby();
		}
	glPopMatrix();
	drawAir();

	//show name if mouse middle button is clicked
	if (showCreator)
	{
		glRasterPos2d(-5, -5);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'H');
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'e');
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'n');
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'r');
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'y');
	}*/
	glPopMatrix();
	
	glFlush ();
}

void reshape(int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void mouse(int button, int state, int x, int y)
{
	//clone Kirby with left and right mouse button
	//show creator name with middle mouse button
	switch (button) {
		case GLUT_LEFT_BUTTON:
			if(state == GLUT_DOWN) {
				left_counter += 1;
				glutPostRedisplay();
			}
		break;

		case GLUT_MIDDLE_BUTTON:
			if(state == GLUT_DOWN) {
				showCreator = 1;
				glutPostRedisplay();
			}
			else if(state == GLUT_UP) {
				showCreator = 0;
				glutPostRedisplay();
			}
		break;

		case GLUT_RIGHT_BUTTON:
			if(state == GLUT_DOWN) {
				right_counter += 1;
				glutPostRedisplay();
			}
		break;

		default:
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	//keys to control scaling - k
	//keys to control rotation - alpha
	//keys to control translation - tx, ty
	switch (key) {

		case 'a':
			alpha+=10;
			glutPostRedisplay();
		break;

		case 'd':
			alpha-=10;
			glutPostRedisplay();
		break;

		case 'q':
			k+=0.1;
			glutPostRedisplay();
		break;

		case 'e':
			if(k>0.5)
				k-=0.1;
			glutPostRedisplay();
		break;

		case 'z':
			tx-=0.1;
			glutPostRedisplay();
		break;

		case 'c':
			tx+=0.1;
			glutPostRedisplay();
		break;

		case 's':
			ty-=0.1;
			glutPostRedisplay();
		break;

		case 'w':
			ty+=0.1;
			glutPostRedisplay();
		break;

		default:
		break;
	}
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 1\n\n";
	cout<<"+++++CONTROL BUTTONS+++++++\n\n";
	cout<<"Scale Up/Down: Q/E\n";
	cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
	cout<<"Move Up/Down: W/S\n";
	cout<<"Move Left/Right: Z/C\n";

	glutInit(&argc, argv);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
