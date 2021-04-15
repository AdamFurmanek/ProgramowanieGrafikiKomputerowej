#pragma once

#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

double cameraX = 0;
double cameraY = 0;
double cameraSpeed = 3.0;
bool figure = true;
GLUquadricObj* obj;

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();
	glRotatef(cameraX, 1.0f, 0.0f, 0.0f);
	glRotatef(cameraY, 0.0f, 1.0f, 0.0f);

	obj = gluNewQuadric();
	gluQuadricDrawStyle(obj, GLU_FILL);
	gluQuadricNormals(obj, GLU_SMOOTH);
	if(figure)
		gluCylinder(obj, 0.1, 0.3, 0.4, 10, 10);
	else
		gluSphere(obj, 0.4, 10, 10);

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
	case ' ':
		figure = !figure;
		cameraX = cameraY = 0;
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
	glutMainLoop();
}