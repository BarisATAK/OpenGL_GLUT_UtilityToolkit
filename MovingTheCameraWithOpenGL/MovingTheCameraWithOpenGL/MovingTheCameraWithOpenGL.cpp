#include "pch.h"
#include <iostream>
#include <GL/glut.h>

// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;


/*
The left and right keys will rotate the camera around the Y axis, i.e. in the XZ plane, whereas the up and down keys will move the camera forward and backwards in the current direction.
*/

void processSpecialKeys(int key, int x, int y) {
	float fraction = 0.1f; // Moving speed.

	switch (key) {
	case GLUT_KEY_LEFT:
		angle -= 0.01f;
		lx =  sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case GLUT_KEY_UP:
		x += lx * fraction;
		z += lz * fraction;
		break;
	case GLUT_KEY_DOWN:
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	}
}
void drawSnowMan(void) {
	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw body
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20); //-->(radius, slices, stacks)

	// Draw head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

	// Draw nose
	glColor3f(1.0f, 0.5f, 0.5f);
	glutSolidCone(0.08f, 0.5f, 10, 2); // Draws a cone --> (radius, height, slices, stacks)
}
void changeSize(int w, int h) {
	//Prevent a divide by zero, when window is too short
	// (you can't make a window of zero width).
	if (h == 0)
		h = 1;
	float ratio = w * 1.0f / h;

	// Use the projection Matrix
	glMatrixMode(GL_PROJECTION); // Applies subsequent matrix operations to the projection matrix stack.

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the current perspective
	gluPerspective(45.0f, ratio, 0.1f, 100.f);

	// Get back to the Modelview
	glMatrixMode(GL_MODELVIEW); // Applies subsequent matrix operations to the modelview matrix stack
}
void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(x, 1.0f, z,
			  x + lx, 1.0f, z + lz,
			  0.0f, 1.0f, 0.0f);

	//Draw ground.
	glColor3f(0.9f, 0.9f, 0.9f);

	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	for (int i = -3; i < 3; i++) {
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0f, 0, j*10.0f);
			drawSnowMan();
			glPopMatrix();
		}
	}

	glutSwapBuffers();

}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("OpenGL Snowmen Application");

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene); 
	glutSpecialFunc(processSpecialKeys);

	glEnable(GL_DEPTH_TEST); // Update the Depth Buffer
	glutMainLoop();
}
