#pragma once

#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>

#include "Particle.h"
#include <vector>

float positionX = 0;
float positionZ = 0;
double positionSpeed = 0.1;
GLuint lista;

std::vector<Particle*> particles;

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 0, 1);
	glRotatef(10, -0.5f, 0.0f, 0.0f);
	glRotatef(45, 0.0f, 0.5f, 0.0f);

	glTranslatef(positionX, 0, positionZ);

	glDisable(GL_BLEND);
	glColor3f(1.0, 0.4, 0.4);
	glutSolidCube(0.3);

	glTranslatef(-positionX, 0, -positionZ);

	for (int i = 0; i < particles.size(); i++) {
		particles[i]->Draw();
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
	//STEROWANIE SZEŒCIANEM WASD
	switch (key)
	{
	case 'w':
		positionX -= positionSpeed;
		positionZ += positionSpeed;
		break;
	case 'a':
		positionX -= positionSpeed;
		positionZ -= positionSpeed;
		break;
	case 's':
		positionX += positionSpeed;
		positionZ -= positionSpeed;
		break;
	case 'd':
		positionX += positionSpeed;
		positionZ += positionSpeed;
		break;
	case 27:
	case 'q':
		exit(0);
		break;
	}
}

void Timer(int parameter)
{
	for (int i = 0; i < particles.size(); i++) {
		particles[i]->CalculatePosition();
	}
	glutTimerFunc(15, Timer, 1);
}

void AddParticles(int amount) {
	for (int i = 0; i < amount; i++) {
		float x = (float)(rand() % 2000) / 1000 - 1;
		float y = (float)(rand() % 2000) / 1000 - 1;
		float z = (float)(rand() % 2000) / 1000 - 1;
		Particle* particle = new Particle(x,y,z, 0.2);
		particles.push_back(particle);
	}
}

void SortParticles() {
	for (int i = 0; i < particles.size(); i++) {
		for (int j = i + 1; j < particles.size(); j++) {
			if (particles[i]->positionZ < particles[j]->positionZ) {
				Particle* temp = particles[i];
				particles[i] = particles[j];
				particles[j] = temp;
			}
		}
	}
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

	AddParticles(500);
	SortParticles();

	glutTimerFunc(15, Timer, 1);
	glutMainLoop();
}