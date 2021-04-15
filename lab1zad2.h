#pragma once

#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

double cameraX = 0;
double cameraY = 0;
double cameraSpeed = 3.0;
GLuint lista;

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	glRotatef(cameraX, 0.5f, 0.0f, 0.0f);
	glRotatef(cameraY, 0.0f, 0.5f, 0.0f);

	lista = glGenLists(1);
	if (lista != 0) {
		glNewList(lista, GL_COMPILE);

		glBegin(GL_QUADS);

		glColor3f(0.0f, 0.1f, 0.0f);     // Green
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		// Bottom face (y = -0.5f)
		glColor3f(0.5f, 0.5f, 0.0f);     // Orange
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		// Front face  (z = 0.5f)
		glColor3f(0.5f, 0.0f, 0.0f);     // Red
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		// Back face (z = -0.5f)
		glColor3f(0.5f, 0.5f, 0.0f);     // Yellow
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		// Left face (x = -0.5f)
		glColor3f(0.0f, 0.0f, 0.5f);     // Blue
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		// Right face (x = 0.5f)
		glColor3f(0.5f, 0.0f, 0.5f);     // Magenta
		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glEnd();  // End of drawing color-cube
		glEndList();
	}

	glCallList(lista);

	glFlush();

	glutSwapBuffers();
}

void Reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		cameraX += cameraSpeed;
		break;
	case 's':
		cameraX -= cameraSpeed;
		break;
	case 'a':
		cameraY += cameraSpeed;
		break;
	case 'd':
		cameraY -= cameraSpeed;
		break;
	case 27:
	case 'q':
		exit(0);
		break;
	}
	Display();
}
static void Launch(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}