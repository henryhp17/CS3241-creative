// CS3241Lab1.cpp : Defines the entry point for the console application.
// Henry Pratama Suryadi A0105182R
#include <cmath>
#include <iostream>
#include <time.h>
#include "GL/glut.h"

using namespace std;

#define numStars 150
#define numPlanets 6
#define numMoons 9

GLfloat PI = 3.14;
float alpha = 0.0, k = 1.0;
float tx = 0.0, ty = 0.0;
int clockMode = 0;
long counter = 0;
float kirbyJump = 0.3, kirbyRotate = 0, jumpCounter = 0.5, cometDev;

class star 
{
public:
	float x, y, opacity, radius, blink;

	star()
	{
		x = 0;
		y = 0;
		opacity = 1.0;
		radius = 0.05;
		if (rand() * 1.0 / RAND_MAX >= 0.5) blink = -0.01;
		else blink = 0.01;
	}

	star(float x_in, float y_in, float op_in)
	{
		x = x_in;
		y = y_in;
		opacity = op_in;
		radius = 0.05;
		if (rand() * 1.0 / RAND_MAX >= 0.5) blink = -0.01;
		else blink = 0.01;
	}

	void drawSingleStar() //draw star according to the star properties
	{
		float out_radius;
		out_radius = radius * 1.15;
		glPushMatrix();
		glTranslatef(x, y, 0);
		glColor4f(0.95, 0.65, 0.08, opacity);
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
		glColor4f(0.9, 0.9, 0.6, opacity);
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
		glPopMatrix();
	}

	void sparkle() //modify star opacity to animate sparkling star and position animation
	{
		if (opacity > 0.9) blink = -0.01;
		if (opacity < 0.1) blink = 0.01;
		opacity += blink; //gradually increase opacity

		y += 0.01;
		if (y > 10) y-= 20; 
	}

};

class planet
{
public:
	float distFromRef;
	float angularSpeed;
	GLfloat color[3];
	float size;
	float angle;
	float opacity;

	planet()
	{
		distFromRef = 0;
		angularSpeed = 0;
		color[0] = color[1] = color[2] = 0;
		size = 0;
		angle = 0;
		opacity = 1.0;
	}

	planet(float dist, float speed, GLfloat col1, GLfloat col2, GLfloat col3, float radius, float pos)
	{
		distFromRef = dist;
		angularSpeed = speed;
		color[0] = col1;
		color[1] = col2;
		color[2] = col3;
		size = radius;
		angle = pos;
		opacity = 1.0;
	}

	void createPlanet() //draw planet according to the properties with default circle orbit
	{
		float deg;
		glRotatef(angle, 0, 0, 1);
		glTranslatef(0, distFromRef, 0);
		glColor4f(color[0], color[1], color[2], opacity);
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f(0, 0);
			for (int i = 0 ; i <= 361; i++)
			{
				if (i == 180) {
					glColor4f((color[0] + 1)/2, (color[1] + 1)/2, (color[2] + 1)/2, opacity);
				}
				deg = i * PI / 180.0;
				glVertex2f(cos(deg) * size, sin(deg) * size);
			}
		glEnd();
	}

	void ellipsePlanet() //draw planet according to the properties with modified ellipse orbit
	{
		float deg = angle * PI / 180.0;
		glTranslatef(cos(deg) * 3.0, sin(deg) * 9.0, 0);
		glRotatef(angle - 90, 0, 0, 1);
		glColor4f(color[0], color[1], color[2], opacity);
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f(0, 0);
			for (int i = 0 ; i <= 361; i++)
			{
				if (i == 180) {
					glColor4f((color[0] + 1)/2, (color[1] + 1)/2, (color[2] + 1)/2, opacity);
				}
				deg = i * PI / 180.0;
				glVertex2f(cos(deg) * size, sin(deg) * size);
			}
		glEnd();
	}
	
	void rotatePlanet() //rotate the planet angle to create animation
	{
		angle += (angularSpeed * 1.8 / PI);
		if (angle >= 360) angle = 0;
	}
};

star starList[numStars];
planet planetList[numPlanets];
planet moonList[numMoons];

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

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.3, 1.0);
	glShadeModel (GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void initializePlanet() //initialize properties of all the planets, moons, and stars
{
	//planet 1
	planetList[0] = planet(1.5, 0.8, 0.6, 0.8, 1.0, 0.2, 60.0);

	//planet 2 and its moons
	planetList[1] = planet(3.0, -0.7, 0.2, 0.9, 0.6, 0.3, 280.0);
	moonList[0] = planet(0.5, 1, 0.7, 0.7, 0.7, 0.1, 10.0);
	
	//planet 3 and its moons
	planetList[2] = planet(5.5, 0.4, 0.2, 0.4, 0.5, 0.6, 100.0);
	moonList[1] = planet(0.8, 1, 0.7, 0.7, 0.7, 0.1, 50.0);
	moonList[2] = planet(1.1, 0.7, 0.7, 0.7, 0.7, 0.1, 250.0);
	
	//planet 4 and its moons
	planetList[3] = planet(8.0, 0.2, 0.8, 0.2, 0.6, 0.5, 240.0);
	moonList[3] = planet(0.7, 1.3, 0.7, 0.7, 0.7, 0.1, 10.0);
	moonList[4] = planet(0.9, 1, 0.7, 0.7, 0.7, 0.1, 90.0);
	moonList[5] = planet(1.2, 1.1, 0.7, 0.7, 0.7, 0.1, 270.0);
	moonList[6] = planet(1.4, 0.9, 0.7, 0.7, 0.7, 0.1, 180.0);
	
	//planet 5 and its moons
	planetList[4] = planet(4.5, 1, 0.5, 0.1, 0.2, 0.2, 120.0);
	moonList[7] = planet(0.5, 1, 0.7, 0.7, 0.7, 0.1, 0.0);

	//comet orbiting the sun
	planetList[5] = planet(3.0, 1.5, 0.3, 0.3, 0.3, 0.3, 0.0);

	//randomize all the properties of the stars
	for (int i = 0; i < numStars; i++)
		starList[i] = star((rand() * 20.0 / RAND_MAX) - 10, (rand() * 20.0 / RAND_MAX) - 10, (rand() * 0.8 / RAND_MAX));
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int refMoon[numPlanets] = {0, 1, 2, 4, 1, 0}, curMoon = 0; //set amount of moon for each planet
	
	glPushMatrix();

	//controls transformation
	glScalef(k, k, k);	
	glTranslatef(tx, ty, 0);	
	glRotatef(alpha, 0, 0, 1);

	//draw stars
	for (int i = 0; i < numStars; i++)
		starList[i].drawSingleStar();

	//draw sun
	glColor3f(0.99, 0.72, 0.07);
	drawCircle(1.0);

	//draw planets
	for (int i = 0; i < numPlanets; i++)
	{
		glPushMatrix();
		if (i == 5) {
			glRotatef(45, 0, 0, 1);
			glTranslatef(0, cometDev, 0);
		}
		if (i == 4) planetList[i].ellipsePlanet(); //customized orbit
		else planetList[i].createPlanet();

		//draw moons
		for (int j = 0; j < refMoon[i]; j++)
		{
			glPushMatrix();
			moonList[curMoon].createPlanet();
			curMoon++;
			glPopMatrix();
		}

		//draw jumping kirby
		if (i == 2) {
			glPushMatrix();
			glRotatef(kirbyRotate, 0, 0, 1);
			glTranslatef(0, kirbyJump, 0);
			glScalef(0.1, 0.1, 0.1);
			drawKirby();
			glPopMatrix();
		}
		glPopMatrix();
	}
	
	glPopMatrix();
	glFlush ();
}

void idle()
{
	//update animation here
	//set animation clock timing, deltaTime will increase per millisecond
	int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = timeSinceStart - counter;

	//clock mode configuration
	if (clockMode) {
		//get the current time using time library
		time_t seconds = time(NULL);
		struct tm * timeinfo = localtime(&seconds);
		//set angle of the planets according to the time
		planetList[3].angle = 360-(float)timeinfo->tm_sec/60*360;
		planetList[2].angle = 360-(float)timeinfo->tm_min/60*360;
		planetList[1].angle = 360-(float)timeinfo->tm_hour/24*360;
		//set angle of moons and kirby as the clock hand
		for (int i = 0; i < 7; i++)
			moonList[i].angle = 0;
		kirbyRotate = PI / 2;
		kirbyJump = 2.0;

		//configure opacity of other planets
		planetList[0].opacity = 0.3;
		planetList[4].opacity = 0.3;
		planetList[5].opacity = 0.3;
		moonList[7].opacity = 0.3;

		glutPostRedisplay();
	}

	//solar system configuration
	else if (deltaTime > 10) { // use frame rate of 100 FPS
		//set opacity back to original
		planetList[0].opacity = 1.0;
		planetList[4].opacity = 1.0;
		planetList[5].opacity = 1.0;
		moonList[7].opacity = 1.0;

		//rotate all the planets and the moons according to their own speed
		for (int i = 0; i < numPlanets; i++)
			planetList[i].rotatePlanet();
		for (int i = 0; i < numMoons; i++)
			moonList[i].rotatePlanet();

		//customize the orbit of the comet
		cometDev = abs(planetList[5].angle - 180) / 15;
		//customize jumping kirby on the planet
		if (kirbyJump > 2.0) jumpCounter = -0.05;
		else if (kirbyJump < 0.7) jumpCounter = 0.05;
		kirbyRotate += 1;
		kirbyJump += jumpCounter;
		
		//blinking stars at the background
		for (int i = 0; i < numStars; i++)
			starList[i].sparkle();

		glutPostRedisplay();	//after updating, draw the screen again
		counter = timeSinceStart;
	}
}

void keyboard (unsigned char key, int x, int y)
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
			if(k>0.1)
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

		case 't': //toggle clock mode
			clockMode = (clockMode + 1) % 2;
			glutPostRedisplay();
		break;

		default:
		break;
	}
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 2\n\n";
	cout<<"+++++CONTROL BUTTONS+++++++\n\n";
	cout<<"Scale Up/Down: Q/E\n";
	cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
	cout<<"Move Up/Down: W/S\n";
	cout<<"Move Left/Right: Z/C\n";

	initializePlanet(); //initialize everything
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);	
	//glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
