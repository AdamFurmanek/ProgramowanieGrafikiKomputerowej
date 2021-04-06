#pragma once

#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

 void Display() {
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0, 1.0, 0.0);

		glBegin(GL_QUADS);
		glVertex2f(0, 80);
		glVertex2f(80, 80);
		glVertex2f(80, 60);
		glVertex2f(0, 60);
		glEnd();

		glBegin(GL_QUADS);
		glVertex2f(0, 40);
		glVertex2f(80, 40);
		glVertex2f(80, 20);
		glVertex2f(0, 20);
		glEnd();

		glBegin(GL_QUADS);
		glVertex2f(0, 80);
		glVertex2f(20, 80);
		glVertex2f(20, 00);
		glVertex2f(0, 0);
		glEnd();

		glutSwapBuffers();
	}

	 void Reshape(int w, int h) {
		glViewport(0, 0, (GLsizei)w, (GLsizei)h);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	 void Keyboard(unsigned char key, int x, int y)
	{
		switch (key)
		{
		case 27:
		case 'q':
			exit(0);
			break;
		}
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