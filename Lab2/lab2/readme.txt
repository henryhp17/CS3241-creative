Henry Pratama Suryadi
Matric number: A0105182R

Primitives
	GL_POLYGON
	GL_TRIANGLE_FAN
	GL_TRIANGLE_STRIP
	GL_QUADS
	GLUT_ELAPSED_TIME	: It is used to obtain the current tick in millisecond after glutInit() called and create animation in the program.
Transformatives
	glTranslatef()		: Used for the positioning of the objects.
	glRotatef()			: Used to place each object in the correct direction.
	glScalef()			: Used to scale the object
	glColor4f()			: Used to add transparency in the objects.
	glutGet()			: Used to obtain the value of the current tick.

Drawing: 
I am drawing a solar system with a sun in the center. 
There are 5 planets orbiting the sun and each planet has their own moon. Planet 2 is orbiting in a different direction compared to other planets. Planet 3 has a Kirby jumping happily on it. Planet 4 has the most moons. Planet 5 is orbiting in an elliptic orbit, unique compared to other planets. 
There is a comet orbiting in an elongated elliptical orbit which can be very near to the Sun at one time, and very far at another time. The orbit is obtained by translating the center of the orbit.
Stars in the background are sparkling smoothly and moving in the upward direction to simulate a real life environment.
In the clock mode, planet 2, 3, and 4 become the clock hand and their moons are aligned to further emphasize the clock hand direction. Other objects are slightly becoming more transparent and stopped since they are not important in this mode.

Methods you have modified:
	initializePlanet()	: Function to initialize all the parameters of the planets, moons, and stars.
	idle()				: Function to create the animation procedure. There are two sections to facilitate clock mode and solar system mode. It is modifying the angle and the alpha value of each object.
	display()			: Function to do all the drawings (stars, sun, planets, moons, and Kirby).
	keyboard()			: Included function to get the event when 't' is pressed and change the mode.
Classes:
	star: 
		drawSingleStar()	: Draw a star according to its properties
		sparkle()			: Modify the alpha value to create the blinking and change its position
	planet:
		createPlanet()		: Draw a planet with default circle orbit
		ellipsePlanet()		: Draw a planet with modified ellipse orbit
		rotatePlanet()		: Modify the angle of the planet according to their angular speed to create animation

Extra Features
	Planets are having various orbiting animation, clockwise, counter clockwise, ellipse, elongated ellipse, and circular.
	Location of stars in the background and their brightness is randomized to simulate better environment. Alpha values are modified gradually to make the animation smooth.
	Color of the planet nearer to the sun is brighter, by modifying the color of the point nearer to the sun, simulating sun as the light source.
	Kirby is jumping happily by modifying the center of the orbit.