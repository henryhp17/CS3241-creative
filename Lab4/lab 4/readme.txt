Henry Pratama Suryadi
Matric number: A0105182R

Primitives
	GL_LINE_STRIP		: It is easier to use this primitive compared to GL_LINES because I do not have to specify the same point twice, it is easier to display the control lines and bezier curve because we only need to list down the points once.

Tangent vector:
	To compute the tangent vector, I differentiate the function of x and y coordinates accordingly. Then I use the 'atan2' function to get the direction of the arrow in terms of degree. Direction of the tangent vector is defined by rotating the arrow by this amount of degree.
	In order to make the tangent vector distribution equal between different curves, I compute the length of the curve each time it creates a new line segment. After the length of the total curve pass a certain threshold (64 in this case), it will compute the tangent vector in that point and display it if required. Therefore, we can make sure that there is equal distance between tangent arrows. I do not use the NOBJECTONCURVE.

Drawing: Grass, I simulated a shape of grass using the bezier curve.

Methods I have modified:
	drawKirby()			: Function to draw a kirby, I used my lab 1 as a header file and draw kirby as the object on curve.
	drawCurveObject()	: Function to draw tangent vector and object, called if length has surpassed a certain threshold.
	isAutoC1Point()		: Function to check whether the current point is a C1 point or not.
	swapC1Points()		: Function to swap the current point to an automatically precalculated C1 point from separate array.
	drawBezierCurve()	: Function to draw the bezier curve.
	display()			: Modified to check which component of the drawing need to be displayed and draw accordingly.
	readFile()			: Modified to compute the C1 points while reading the list of points from text file.
	mouse()				: Modified to compute the C1 points if mouse is processing the desired C1 point.