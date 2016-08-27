#include <iostream>
#include "math.h"
#include "GL\glut.h"

using namespace std;
#define PI 3.14159265

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