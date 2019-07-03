#include "pch.h"
#include <iostream>
#include <GL/glut.h>

float angle = 0.0f;
float red = 1.0f, blue = 1.0f, green = 1.0f;

//The x and y are mouse positions.
void processNormalKeys(unsigned char key, int x, int y) { //For normal keys like letters, numbers...
	if (key == 27) //27 --> ASCII code value for Esc.
		exit(0);
	else if (key == 'r') {
		int mod = glutGetModifiers();
		if (mod == GLUT_ACTIVE_ALT)
			red = 0.0f; //If you press the ALT+R. But the caps lock should be off.
		else
			red = 1.0; //If you just press the r.
	}
}
void processSpecialKeys(int key, int x, int y) { //For the special keybord events.
	int mod;

	switch (key) {
	case GLUT_KEY_F1: //If you press the F1,paints the red.
		mod = glutGetModifiers();
		if (mod == (GLUT_ACTIVE_CTRL) | (GLUT_ACTIVE_ALT)) { ////If you press the CTRL+ALT+F1. But the caps lock should be off.
			red = 1.0f;
			green = 0.0f;
			blue = 0.0f;
		}
		break;
	case GLUT_KEY_F2: //If you press the F2,paints the green.
		red = 0.0f;
		green = 1.0f;
		blue = 0.0f;
		break;
	case GLUT_KEY_F3: //If you press the F3,paints the blue.
		red = 0.0f;
		green = 0.0f;
		blue = 1.0f;
		break;
	}
}
void Render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Firtsly clear the color buffer and depth buffer.

	glLoadIdentity(); //Reset transformations.

	//Set the camera
	gluLookAt(0.0f, 0.0f, 10.0f, //The first trio  --> Specifies the position of the eye point.
		0.0f, 0.0f, 0.0f,	 //The second trio --> Specifies the position of the reference point.
		0.0f, 1.0f, 0.0f); //The third trio  --> Specifies the direction of the up vector.

	glRotatef(angle, 0.0f, 1.0f, 0.0f); //Turns around the Y axis.
	glColor3f(red, green, blue); //(R,G,B) --> (if you do not specify the color, the color becomes white.)
	glBegin(GL_TRIANGLES); //Draw a triangle.
	glVertex3f(-1.0f, 0.0f, 5.0f);
	glVertex3f(1.0f, 0.0f, 5.0f);
	glVertex3f(0.0f, 1.0f, 5.0f);
	glEnd();

	angle += 0.1f;

	//That is for Double Buffer.
	glutSwapBuffers(); //To swap the front and back buffer.(Back Buffer -> Draws the shape on the back side, Front Buffer -> Shows to shape on the screen.)
}

void ChangeSize(int n_width, int n_height) { //For the perspective.
	float ratio;

	if (n_height == 0) //To the prevent a divide by zero.
		n_height = 1;

	ratio = 1.0 *n_width / n_height; //The first step should compute the ratio between the width and the height.

	glMatrixMode(GL_PROJECTION); //Applies subsequent matrix operations to the projection matrix stack.

	glLoadIdentity(); //Replace the current matrix with the identity matrix.

	glViewport(0, 0, n_width, n_height); // Set the viewport. (The first two parameters are the x and y position.)

	gluPerspective(45, ratio, 1, 100); //The first one defines the field of view angle in the yz plane, the ratio defines the relation between the width and height of the viewport.The last two parameters define
									   //the near and far clipping planes.

	glMatrixMode(GL_MODELVIEW); //Applies subsequent matrix operations to the modelview matrix stack

}

void main(int argc, char **argv)
{
	glutInit(&argc, argv); //Init the glut.
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA); //Choose the which modes you want.
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 320);
	glutCreateWindow("I am learning OpenGL_GLUT!!!"); //Create a OpenGL window.

	glutDisplayFunc(Render); //Run the Render function with callback.

	glutReshapeFunc(ChangeSize); // sets the reshape callback for the current window.

	glutIdleFunc(Render); //That lets you register a callback function to be called when the application is idle.
	glutKeyboardFunc(processNormalKeys); //For normal keys.
	glutSpecialFunc(processSpecialKeys); //For special keys.

	glutMainLoop(); //Never ending loop.
}