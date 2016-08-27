Henry Pratama Suryadi
Matric number: A0105182R

Primitives
	GL_POLYGON			: Draw the sphere and cylinder
	GL_TRIANGLE_FAN		: Draw the cone, because cone has one vertex on the top, and the rest at the bottom
Transformatives
	glTranslatef()		: Used for the positioning of the objects.
	glRotatef()			: Used to place each object in the correct direction.
	glScalef()			: Used to scale the object
	glColor4f()			: Used to add transparency in the objects.
	glutGet()			: Used to obtain the value of the current tick.
Material Settings
	GL_AMBIENT
	GL_DIFFUSE
	GL_SPECULAR			: Change this value to the ambient value to get the light reflected
	GL_SHININESS		: Change this value to set the spread of light reflection
I modified the normal vector of each vertex in sphere object to create smooth surface. It is computed by getting the vector of the vertex to the center of the sphere. Each vertex will have different normal vector.

Drawing: 
Primitive Object 	: Spindle
	It consists of one cylinder in the middle and two cones at both of its ends. I set the radius of the three elements to be the same. We can modify the height of cylinder and each cone individually, making it easier to give more variation to the shape.
	Normal of the cylinder can be computed by getting the nearest distance of each vertex to the z-axis of the cylinder. Therefore, the z-element of the normal vector is always zero. x and y element can be easily computed using circle vertex coordinates formula.
	Normal of the cone is almost the same as the cylinder. However, the z-element is not zero. It is computed using phytagorean formula to find the ratio between the height and the radius of the cone. Logically, the surface will face a little bit upward because of the difference of the top and the bottom radius.
Composite Object 1 	: Influenza Virus
	Virus consists of one sphere in the middle as the main body and DNA container. Around the sphere, I put a lot of spindles to simulate the envelope proteins.
Composite Object 2	: Train Bridge
	Bridge is computed using loop. I used loop to set the length of the bridge. It has pole support at the bottom and support at the top. Sides of the bridge is also computed using loop. Spindle and sphere primitives are used to construct this bridge.

Methods you have modified:
	drawSphere()	: Function is modified so that the sphere can be used in smooth mode and in highlight mode,
	display()		: All function to create objects are called from here to draw everything in the window. Those functions are drawSpindle(), drawInfluenzaVirus(), and drawTrainBridge()