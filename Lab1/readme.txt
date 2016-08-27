Henry Pratama Suryadi
Matric number: A0105182R

Primitives
	GL_POLYGON			: This primitive is used to create a rectangle, used as Kirby's eyelid. Top part of his eyes are covered by the rectangles to cover and create the shape of his eyes.
	GL_TRIANGLE_FAN		: This primitive is mainly used to create ellipse. Ellipses are used to create Kirby's body part and bubbles. Some of the ellipse are only half to create the proper shape. It is also used to create highlight in the background.
	GL_TRIANGLE_STRIP	: This primitive is used to create the outline thickness of the drawing. Using only GL_LINE for the outline is too thin and do not create emphasize in the drawing. This primitive can be used to create the line thickness. Moreover, it is also used to create arcs and stars, the decoration for the drawing.
	GL_QUADS			: This primitive is used as the outline of Kirby's eyelid.
Transformatives
	glTranslatef()		: Used for the positioning of the objects.
	glRotatef()			: Used to place each object in the correct direction.
	glScalef()			: Only used 

Drawing: I am drawing Kirby in action, the protagonist for Kirby series of video games from Nintendo. He has the ability to absorb enemies and copy his foes' powers. He also appears in some anime and manga as the main character.

Methods you have modified:
	mouse()		: I created 'mouse' function as an output response to mouse clicks.
	init()		: I moved all the initialization function of glut to this function.
	display()	: I did all the drawing routines in this function. It is used to draw background, Kirby, stars, air, and to write my name.
	
All other functions have their own use, described by their name.
	drawBackground()
	drawStars() -> drawSingleStar()
	drawKirby() -> drawKirbyFoot(), drawKirbyEyes(), drawKirbyTongue()
	drawAir() -> drawBubble(), drawWind()

Extra Features
	Using keyboard, we can rotate, shift, and zoom the picture. (default functions)
	Using mouse, if we click the left button, another Kirby will appear on the left side. On the other hand, if we click the right button, another Kirby will appear on the right side.
	If we click the middle button, while the button is hold down, my name will appear on the screen below the Kirby's picture.
	To create some parts of Kirby's body, I used quadratic function to differentiate the shape than the usual ellipse.