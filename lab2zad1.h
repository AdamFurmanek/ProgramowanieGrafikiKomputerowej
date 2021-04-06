#pragma once

#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

double cameraX = 0;
double cameraY = 0;
double speed = 3.0;
GLuint lista;

bool figure = true;

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glRotatef(10, 0.5f, 0.0f, 0.0f);
	glRotatef(cameraY, 0.0f, 0.5f, 0.0f);

	glBlendFunc(GL_ONE, GL_ONE);
	glColor4f(1.0, 1.0, 1.0, 0);
	figure ? glutSolidCube(0.3) : glutSolidSphere(0.2, 30, 30);

	glTranslatef(0, -0.5, 0);

	glBlendFunc(GL_SRC_ALPHA, GL_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 0.4);
	figure ? glutSolidCube(0.3) : glutSolidSphere(0.2, 30, 30);

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
	case ' ':
		figure = !figure;
	case 'a':
		cameraY += speed;
		break;
	case 'd':
		cameraY -= speed;
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
	glEnable(GL_BLEND);
	glutMainLoop();
}