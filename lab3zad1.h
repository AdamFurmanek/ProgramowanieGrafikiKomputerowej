#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include "cParticle.h"
#include <GLFW/glfw3.h>
#include <iostream>

#define MAX_PART 20
#define ACTIVATE_TIME 1

using namespace std;

double cameraX = 0;
double cameraY = 0;
double cameraSpeed = 3.0;
GLuint lista;
cParticle particles[MAX_PART];
float act_time = 0;
int now_time, last_time;

bool figure = true;

void Display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	now_time = glutGet(GLUT_ELAPSED_TIME);

	// Animacja ¿ycia i aktywowanie cz¹stek:
	float times = (now_time - last_time) / 1000.0f;
	last_time = now_time;
	// Zliczenie czasu (s) do aktywacji kolejnej cz¹stki:
	act_time += times;
	cout << act_time << endl;
	// Postêp ¿ycia aktywnych cz¹stek:
	for (int i = 0;i < MAX_PART;i++) {
		if (particles[i].active)
			particles[i].live(times);
		else {
			// Czy up³yn¹³ czas do aktywacji kolejnej cz¹stki?
			if (act_time >= ACTIVATE_TIME) {
				act_time -= ACTIVATE_TIME;
				particles[i].active = true;
			}
			break;
		}
	}

	glPointSize(12);
	glEnableClientState(GL_VERTEX_ARRAY);
	// Miejsce na jeden wierzcho³ek:
	float vv[3];
	glVertexPointer(3, GL_FLOAT, 0, vv);
	for (int i = 0;i < MAX_PART;i++) {
		if (particles[i].active) {
			// Ustawienie koloru RGBA:
			glColor4f(particles[i].r, particles[i].g,
				particles[i].b, particles[i].life);
			// Wspó³rzêdne punktu:
			vv[0] = particles[i].x;
			vv[1] = particles[i].y;
			vv[2] = particles[i].z;
			// Narysowanie:
			glDrawArrays(GL_POINTS, 0, 1);
		}
	}
	
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
	case ' ':
		figure = !figure;
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
	glEnable(GL_BLEND);
	last_time = glutGet(GLUT_ELAPSED_TIME);
	for (int i = 0;i < MAX_PART;i++) {
		particles[i].active = true;
	}
	glutMainLoop();
}