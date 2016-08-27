#include "drawHouses.h"

#define M_PI 3.141592654

void A0105182Details(GLuint tex)
{
	// Function to create doors and windows on the building
	// Pass the desired texture to the function
	glBindTexture(GL_TEXTURE_2D, tex);
	glBegin(GL_QUADS);
		glTexCoord2d(0.1, 0); glVertex3f(0, 0, -0.3);
		glTexCoord2d(1, 0);	glVertex3f(0, 0, 0.3);
		glTexCoord2d(1, 1); glVertex3f(0, 1, 0.3);
		glTexCoord2d(0.1, 1); glVertex3f(0, 1, -0.3);
	glEnd();
}

void A0105182Tower(GLuint texSet[], float radius, float height)
{
	// Function to create a tower with modifiable radius and height
	float deg;
	glBindTexture(GL_TEXTURE_2D, texSet[1]);
	glBegin(GL_QUAD_STRIP);
		for (int i = 0; i <= 36; i++) {
			deg = i * M_PI / 18;
			glTexCoord2d(i / 12.0, 0); glVertex3f(cos(deg) * radius, 0.01, sin(deg) * radius);
			glTexCoord2d(i / 12.0, 3); glVertex3f(cos(deg) * radius, height, sin(deg) * radius);
		}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texSet[13]);
	glBegin(GL_TRIANGLE_FAN);
		glTexCoord2d(0.5, 0); glVertex3f(0, height + 2, 0);
		for (int i = 0; i <= 36; i++) {
			deg = i * M_PI / 18;
			glTexCoord2d(i / 36.0, 1); glVertex3f(cos(deg) * 1.1 * radius, height, sin(deg) * 1.1 * radius);
		}
	glEnd();
}

void A0105182TowerComplex(GLuint texSet[])
{
	// Function to create towers and the details on the tower
	glPushMatrix();
		// Tower 1: the highest tower of the castle
		glTranslatef(-1, 0, -1);
		A0105182Tower(texSet, 0.7, 8);
		glPushMatrix();
			glTranslatef(0.71, 6.7, 0);
			A0105182Details(texSet[28]);
		glPopMatrix();
		glPushMatrix();
			glRotatef(120, 0, 1, 0);
			glTranslatef(0.71, 5.2, 0);
			A0105182Details(texSet[28]);
		glPopMatrix();
		A0105182Tower(texSet, 1, 4);
		glPushMatrix();
			glRotatef(180, 0, 1, 0);
			glTranslatef(1.01, 2.2, 0);
			A0105182Details(texSet[28]);
		glPopMatrix();
		// Tower 2: the second tower of the castle
		glTranslatef(2, 0, 0);
		A0105182Tower(texSet, 0.9, 6);
		glPushMatrix();
			glRotatef(30, 0, 1, 0);
			glTranslatef(0.91, 2.2, 0);
			A0105182Details(texSet[28]);
		glPopMatrix();
		glPushMatrix();
			glRotatef(-60, 0, 1, 0);
			glTranslatef(0.91, 4.7, 0);
			A0105182Details(texSet[28]);
		glPopMatrix();
		// Tower 3: the shortest tower of the castle
		glTranslatef(-1, 0, -1);
		A0105182Tower(texSet, 0.9, 5);
		glPushMatrix();
			glRotatef(55, 0, 1, 0);
			glTranslatef(0.91, 3.7, 0);
			A0105182Details(texSet[28]);
		glPopMatrix();
	glPopMatrix();
}

void A0105182MainBuilding(GLuint texSet[])
{
	// Wall of the building
	glBindTexture(GL_TEXTURE_2D, texSet[0]);
	glBegin(GL_QUAD_STRIP);
		glTexCoord2d(0, 0); glVertex3f(-1, 0.01, -1);
		glTexCoord2d(0, 1); glVertex3f(-1, 4.01, -1);
		glTexCoord2d(1, 0); glVertex3f(1, 0.01, -1);
		glTexCoord2d(1, 1); glVertex3f(1, 4.01, -1);
		glTexCoord2d(3, 0); glVertex3f(1, 0.01, 3);
		glTexCoord2d(3, 1); glVertex3f(1, 4.01, 3);
		glTexCoord2d(4, 0); glVertex3f(-1, 0.01, 3);
		glTexCoord2d(4, 1); glVertex3f(-1, 4.01, 3);
		glTexCoord2d(6, 0); glVertex3f(-1, 0.01, -1);
		glTexCoord2d(6, 1); glVertex3f(-1, 4.01, -1);
	glEnd();
	// Roof of the building
	glBindTexture(GL_TEXTURE_2D, texSet[13]);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex3f(-1, 4, -1);
		glTexCoord2d(2, 0); glVertex3f(-1, 4, 3);
		glTexCoord2d(1.5, 1); glVertex3f(0, 5, 2);
		glTexCoord2d(0.5, 1); glVertex3f(0, 5, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texSet[13]);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex3f(1, 4, -1);
		glTexCoord2d(2, 0); glVertex3f(1, 4, 3);
		glTexCoord2d(1.5, 1); glVertex3f(0, 5, 2);
		glTexCoord2d(0.5, 1); glVertex3f(0, 5, 0);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texSet[13]);
	glBegin(GL_TRIANGLES);
		glTexCoord2d(0.5, 1); glVertex3f(0, 5, 2);
		glTexCoord2d(1, 0); glVertex3f(1, 4, 3);
		glTexCoord2d(0, 0); glVertex3f(-1, 4, 3);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, texSet[13]);
	glBegin(GL_TRIANGLES);
		glTexCoord2d(0.5, 1); glVertex3f(0, 5, 0);
		glTexCoord2d(1, 0); glVertex3f(1, 4, -1);
		glTexCoord2d(0, 0); glVertex3f(-1, 4, -1);
	glEnd();
	// Details of the building
	glPushMatrix();
		glTranslatef(-1.01, 2.8, 2.2);
		A0105182Details(texSet[30]);
		glTranslatef(2.02, 0, 0);
		A0105182Details(texSet[30]);
		glTranslatef(-1.01, 0, 0.81);
		glRotatef(90, 0, 1, 0);
		A0105182Details(texSet[30]);
	glPopMatrix();
}

void A0105182Observatory(GLuint texSet[])
{
	float deg, radius = 1.2;
	glPushMatrix();
		// The circle wall of observatory
		glTranslatef(1.5, 0, 0.8);
		glBindTexture(GL_TEXTURE_2D, texSet[0]);
		glBegin(GL_QUAD_STRIP);
			for (int i = 0; i <= 36; i++) {
				deg = i * M_PI / 18;
				glTexCoord2d(i / 18.0, 0); glVertex3f(cos(deg) * radius, 0.01, sin(deg) * radius);
				glTexCoord2d(i / 18.0, 1); glVertex3f(cos(deg) * radius, 3, sin(deg) * radius);
			}
		glEnd();
		// Door of the observatory
		glPushMatrix();
			glRotatef(45, 0, 1, 0);
			glTranslatef(1.2, 1.5, 0);
			A0105182Details(texSet[5]);
		glPopMatrix();
		// Half spherical roof of the observatory
		int n = 20;
		glTranslatef(0, 3, 0);
		glRotatef(-90, 1, 0, 0);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				glBindTexture(GL_TEXTURE_2D, texSet[31]);
				glBegin(GL_POLYGON);
					glTexCoord2d(sin(i*M_PI/n)*cos(j*M_PI/n)+0.5, cos(i*M_PI/n)*cos(j*M_PI/n)+0.5);
					glVertex3d(radius*sin(i*M_PI/n)*cos(j*M_PI/n), radius*cos(i*M_PI/n)*cos(j*M_PI/n), radius*sin(j*M_PI/n));
					glTexCoord2d(sin((i+1)*M_PI/n)*cos(j*M_PI/n)+0.5, cos((i+1)*M_PI/n)*cos(j*M_PI/n)+0.5);
					glVertex3d(radius*sin((i+1)*M_PI/n)*cos(j*M_PI/n), radius*cos((i+1)*M_PI/n)*cos(j*M_PI/n), radius*sin(j*M_PI/n));
					glTexCoord2d(sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n)+0.5, cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n)+0.5);
					glVertex3d(radius*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n), radius*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n), radius*sin((j+1)*M_PI/n));
					glTexCoord2d(sin(i*M_PI/n)*cos((j+1)*M_PI/n)+0.5, cos(i*M_PI/n)*cos((j+1)*M_PI/n)+0.5);
					glVertex3d(radius*sin(i*M_PI/n)*cos((j+1)*M_PI/n), radius*cos(i*M_PI/n)*cos((j+1)*M_PI/n), radius*sin((j+1)*M_PI/n));
				glEnd();
			}
		}
	glPopMatrix();

}

void A0105182DefenseTower(GLuint texSet[])
{
	glPushMatrix();
		glTranslatef(-1.5, 0, 1);
		for (int i = 0; i < 4; i++) {
			// Main building block of the defense tower
			glBindTexture(GL_TEXTURE_2D, texSet[1]);
			glBegin(GL_QUAD_STRIP);
				glTexCoord2d(0, 0); glVertex3f(-0.7, 0.01, -0.7);
				glTexCoord2d(1, 0); glVertex3f(-0.7, 0.01, 0.7);
				glTexCoord2d(0, 1.6); glVertex3f(-0.7, 5, -0.7);
				glTexCoord2d(1, 1.6); glVertex3f(-0.7, 5, 0.7);
				glTexCoord2d(0, 2); glVertex3f(-1, 5.3, -1);
				glTexCoord2d(1, 2); glVertex3f(-1, 5.3, 1);
				glTexCoord2d(0, 2.5); glVertex3f(-1, 6.5, -1);
				glTexCoord2d(1, 2.5); glVertex3f(-1, 6.5, 1);
				glTexCoord2d(0, 2.8); glVertex3f(-0.76, 6.5, -0.76);
				glTexCoord2d(1, 2.8); glVertex3f(-0.76, 6.5, 0.76);
			glEnd();
			// Flat roof of the tower
			glBindTexture(GL_TEXTURE_2D, texSet[19]);
			glBegin(GL_TRIANGLES);
				glTexCoord2d(1, 0.5); glVertex3f(0, 6.5, 0);
				glTexCoord2d(0, 0); glVertex3f(-0.6, 6.5, -0.6);
				glTexCoord2d(0, 1); glVertex3f(-0.6, 6.5, 0.6);
			glEnd();
			// Window at the top of the tower
			if (i % 2 == 0) {
				glPushMatrix();
					glTranslatef(1.01, 5.5, -0.3);
					A0105182Details(texSet[28]);
				glPopMatrix();
			}
			glPushMatrix();
				for (int j = 0; j < 2; j++) {
					// Ornament at the top of the tower
					glBindTexture(GL_TEXTURE_2D, texSet[1]);
					glBegin(GL_QUAD_STRIP);
						glTexCoord2d(0, 0); glVertex3f(-1, 6.5, -1);
						glTexCoord2d(0, 0.2); glVertex3f(-1, 6.9, -1);
						glTexCoord2d(0.2, 0); glVertex3f(-1, 6.5, -0.6);
						glTexCoord2d(0.2, 0.2); glVertex3f(-1, 6.9, -0.6);
						glTexCoord2d(0.4, 0); glVertex3f(-0.6, 6.5, -0.6);
						glTexCoord2d(0.4, 0.2); glVertex3f(-0.6, 6.9, -0.6);
						glTexCoord2d(0.6, 0); glVertex3f(-0.6, 6.5, -1);
						glTexCoord2d(0.6, 0.2); glVertex3f(-0.6, 6.9, -1);
						glTexCoord2d(0.8, 0); glVertex3f(-1, 6.5, -1);
						glTexCoord2d(0.8, 0.2); glVertex3f(-1, 6.9, -1);
					glEnd();
					glTranslatef(0, 0, 0.8);
				}
			glPopMatrix();
			glRotatef(90, 0, 1, 0);
		}
		// Door of the tower
		glTranslatef(-0.71, 1.5, 0);
		A0105182Details(texSet[5]);
	glPopMatrix();
}

void A0105182Obelisk(GLuint tex)
{
	float deg, radius = 0.5;

	for (int i = 0; i < 4; i++) {
		// Body of the obelisk
		glBindTexture(GL_TEXTURE_2D, tex);
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= 6; j++) {
				deg = j * M_PI / 3;
				glTexCoord2d(j / 6.0, 0); glVertex3f(cos(deg) * radius - 3.5, 0.01, sin(deg) * radius - 3.5);
				glTexCoord2d(j / 6.0, 1); glVertex3f(cos(deg) * 0.6 * radius - 3.5, 4, sin(deg) * 0.6 * radius - 3.5);
			}
		glEnd();
		// Top part of the obelisk
		glBindTexture(GL_TEXTURE_2D, tex);
		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2d(0.5, 0); glVertex3f(-3.5, 5, -3.5);
			for (int j = 0; j <= 6; j++) {
				deg = j * M_PI / 3;
				glTexCoord2d(j / 6.0, 1); glVertex3f(cos(deg) * 0.6 * radius - 3.5, 4, sin(deg) * 0.6 * radius - 3.5);
			}
		glEnd();
		glRotatef(90, 0, 1, 0);
	}
}

void A0105182Wall(GLuint texSet[])
{
	float deg, radius;

	for (int i = 0; i < 4; i++) {
		glPushMatrix();
			// Top part of the wall
			radius = 3.2;
			glBindTexture(GL_TEXTURE_2D, texSet[2]);
			glBegin(GL_QUAD_STRIP);
				for (int j = 0; j <= 16; j++) {
					deg = j * M_PI / 30;
					glTexCoord2d(j / 6.0, 0); glVertex3f(cos(deg) * (radius + 0.3), 2.5, sin(deg) * (radius + 0.3));
					glTexCoord2d(j / 6.0, 1); glVertex3f(cos(deg) * radius, 2.5, sin(deg) * radius);
				}
			glEnd();
			for (int j = 0; j < 2; j++) {
				// Inner and outer part of the wall
				radius = 3.2;
				glBindTexture(GL_TEXTURE_2D, texSet[2]);
				glBegin(GL_QUAD_STRIP);
					for (int k = 0; k <= 16; k++) {
						deg = k * M_PI / 30;
						glTexCoord2d(k / 6.0, 0); glVertex3f(cos(deg) * (radius + 0.3 * j), 0.01, sin(deg) * (radius + 0.3 * j));
						glTexCoord2d(k / 6.0, 1); glVertex3f(cos(deg) * (radius + 0.3 * j), 2.5, sin(deg) * (radius + 0.3 * j));
					}
				glEnd();
				glBindTexture(GL_TEXTURE_2D, texSet[2]);
				glBegin(GL_QUAD_STRIP);
					for (int k = 0; k <= 16; k++) {
						deg = k * M_PI / 30;
						glTexCoord2d(k / 6.0, 0); glVertex3f(cos(deg) * (radius + 0.3 * j), 0.01, sin(deg) * (radius + 0.3 * j));
						glTexCoord2d(k / 6.0, 1); glVertex3f(cos(deg) * (radius + 0.3 * j), 2.5, sin(deg) * (radius + 0.3 * j));
					}
				glEnd();
				// Reinforcement at the certain segments of the wall
				radius = 0.5;
				glBindTexture(GL_TEXTURE_2D, texSet[14]);
				glPushMatrix();
					glRotatef(45 * j, 0, 1, 0);
					glTranslatef(0, 0, -3.3);
					glRotatef(45, 0, 1, 0);
					glBegin(GL_QUAD_STRIP);
						for (int k = 0; k <= 4; k++) {
							deg = k * M_PI / 2;
							glTexCoord2d(k / 4.0, 0); glVertex3f(cos(deg) * (radius + 0.1), 0.01, sin(deg) * (radius + 0.1));
							glTexCoord2d(k / 4.0, 1); glVertex3f(cos(deg) * radius, 3, sin(deg) * radius);
						}
					glEnd();
					glBindTexture(GL_TEXTURE_2D, texSet[14]);
					glBegin(GL_QUADS);
						glTexCoord2d(1, 0); glVertex3f(0.5, 3, 0);
						glTexCoord2d(1, 1); glVertex3f(0, 3, 0.5);
						glTexCoord2d(0, 1); glVertex3f(-0.5, 3, 0);
						glTexCoord2d(0, 0); glVertex3f(0, 3, -0.5);
					glEnd();
				glPopMatrix();
			}
		glPopMatrix();
		glRotatef(90, 0, 1, 0);
	}
}

void A0105182Grass(GLuint texSet[])
{
	float deg;
	// Base grass of the outer part of the wall
	glBindTexture(GL_TEXTURE_2D, texSet[9]);
	glBegin(GL_QUADS);
		glTexCoord2d(0, 0); glVertex3f(-4, 0.01, -4);
		glTexCoord2d(1, 0); glVertex3f(4, 0.01, -4);
		glTexCoord2d(1, 1); glVertex3f(4, 0.01, 4);
		glTexCoord2d(0, 1); glVertex3f(-4, 0.01, 4);
	glEnd();
	// Grass inside the wall with higher level
	glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		glBindTexture(GL_TEXTURE_2D, texSet[7]);
		glBegin(GL_TRIANGLE_FAN);
			glTexCoord2d(0.5, 0.5); glVertex3f(0, 1.5, 0);
			for (int i = 0; i <= 144; i++)
			{
				deg = i * M_PI / 72;
				glTexCoord2d(cos(deg) + 0.5, sin(deg) + 0.5); glVertex3f(cos(deg) * 3.2, 1.5, sin(deg) * 3.2);
			}
		glEnd();
	glPopMatrix();
}

void A0105182House(GLuint texSet[])
{
	//plot dimension
	//x: -4:4
	//y: 0:12
	//z: -4:4
	
	//bounding volume
	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
		A0105182TowerComplex(texSet);
		A0105182MainBuilding(texSet);
		A0105182Observatory(texSet);
		A0105182DefenseTower(texSet);
		A0105182Obelisk(texSet[25]);
		A0105182Wall(texSet);
		A0105182Grass(texSet);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}