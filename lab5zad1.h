#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "Ball.h"
#include <math.h>

Ball *balls[5];

int ballsAmount = 5;

void BallCollision(float x1, float y1, float x2, float y2, float &mx1, float &my1, float &mx2, float &my2, float r1, float r2) {
	 //Funkcja na podstawie poradnika https://www.plasmaphysics.org.uk/programs/coll2d_cpp.htm
	 float r21 = r2 / r1;
	 float x21 = x2 - x1;
	 float y21 = y2 - y1;
	 float vx21 = mx2 - mx1;
	 float vy21 = my2 - my1;

	 float length1 = abs((x1 + mx1)-(x2 + mx2));
	 float length2 = abs((y1 + my1)-(y2 + my2));

	 if (sqrtf(length1 * length1 + length2 * length2) <= r1 + r2) {
		 float a = y21 / x21;
		 float dvx2 = -2 * (vx21 + a * vy21) / ((1 + a * a) * (1 + r21));
		 mx2 = mx2 + dvx2;
		 my2 = my2 + a * dvx2;
		 mx1 = mx1 - r21 * dvx2;
		 my1 = my1 - a * r21 * dvx2;
	 }
 }

void WallCollision(float &x, float &y, float& mx, float& my, float r) {

	//Wykonaj ruch jeœli nie wyjdziesz za œcianê.
	float newX = x + mx;
	float newY = y + my;

	if (newX + r > 1 || newX - r < -1)
		mx = -mx;
	else
		x = newX;

	if (newY + r > 1 || newY - r < -1)
		my = -my;
	else
		y = newY;
 }

void BallsMotion() {

	 //SprawdŸ kolizjê ka¿dej pi³ki z ka¿d¹ inn¹ pi³k¹.
	 for (int i = 0; i < ballsAmount; i++) {
		 for (int k = 0; k < ballsAmount; k++) {
			 if (k != i) {
				 BallCollision(
					 balls[i]->position[0], balls[i]->position[1],
					 balls[k]->position[0], balls[k]->position[1],
					 balls[i]->motion[0], balls[i]->motion[1],
					 balls[k]->motion[0], balls[k]->motion[1],
					 balls[i]->radius, balls[k]->radius
				 );
			 }
		 }
	 }

	 //SprawdŸ kolizjê ze œcian¹ (i wykonaj ruch).
	 for (int i = 0; i < ballsAmount; i++) {
		 WallCollision(
			 balls[i]->position[0],
			 balls[i]->position[1],
			 balls[i]->motion[0],
			 balls[i]->motion[1],
			 balls[i]->radius
		 );
	 }
 }

void Display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	//Wyœwietlenie wszystkich pi³ek.
	for (int i = 0; i < ballsAmount; i++)
		balls[i]->Draw();

	//Obliczenie ruchu pi³ek.
	BallsMotion();

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
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
	//Ruch pierwszej pi³ki (pi³ka gracz) za pomoc¹ WASD.
	case 'w':
		balls[0]->motion[1] = 0.01;
		balls[0]->motion[0] = 0;
		break;
	case 's':
		balls[0]->motion[1] = -0.01;
		balls[0]->motion[0] = 0;
		break;
	case 'a':
		balls[0]->motion[0] = -0.01;
		balls[0]->motion[1] = 0;
		break;
	case 'd':
		balls[0]->motion[0] = 0.01;
		balls[0]->motion[1] = 0;
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
	glutInitWindowSize(800, 800);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	srand(time(0));

	//Utworzenie pi³ek.
	for (int i = 0; i < ballsAmount; i++)
		balls[i] = new Ball();

	//Zmiana koloru pierwszej z nich na zielony (pi³ka gracza).
	balls[0]->r = 0;
	balls[0]->g = 1;

	glutMainLoop();
}