#pragma once

#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

int figure = 0;

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);

	switch (figure) {
	case 0:
		glutSolidSphere(0.5, 10, 10);
		break;
	case 1:
		glutSolidCube(0.5);
		break;
	case 2:
		glutSolidCone(0.5, 2, 3, 1);
		break;
	case 3:
		glutSolidTorus(0.5, 1, 4, 6);
		break;
	case 4:
		glutSolidTeapot(0.5);
		break;
	}

	glutSwapBuffers();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		figure--;
		break;
	case 'd':
		figure++;
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
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // ustawienie podwójnego buforowania i kolorów RGB
	glutInitWindowSize(640, 480); // rozmiar okna
	glutCreateWindow(argv[0]);
	glutDisplayFunc(Display); // ustawienie funkcji odpowiedzialnej za rysowanie
	glutReshapeFunc(Reshape); // ustawienie funkcji wywo³ywanej przy zmianie rozmiaru okna
	glutKeyboardFunc(Keyboard); // ustawienie funkcji obs³ugi klawiatury
	glutMainLoop();
}