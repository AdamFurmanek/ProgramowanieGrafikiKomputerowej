#include <GL/glut.h>
#include <iostream>

#include <Cg/cg.h>
#include <Cg/cgGL.h>

#include <stdlib.h>
#include <stdio.h>

CGcontext	cgContext;
CGprogram	cgProgram;
CGprofile	cgFragmentProfile;
CGparameter	color, timeParameter;

float timer = 5;
float timerSpeed = 0.1;
bool calculateTimer = true;
double cameraY = 0;
float cameraSpeed = 5;

using namespace std;

void init() {

	glEnable(GL_DEPTH_TEST);

	cgContext = cgCreateContext();

	cgFragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);

	cgGLSetOptimalOptions(cgFragmentProfile);

	cgProgram = cgCreateProgramFromFile(cgContext, CG_SOURCE, "fragmentShader2.cg", cgFragmentProfile, "main", 0);

	cgGLLoadProgram(cgProgram);

	color = cgGetNamedParameter(cgProgram, "IN.color");

	timeParameter = cgGetNamedParameter(cgProgram, "timer");

}

void display() {

	if (calculateTimer) {
		timer += timerSpeed;

		if (timer <= 1)
			timerSpeed = abs(timerSpeed);
		if (timer >= 20)
			timerSpeed = -abs(timerSpeed);
	}

	cout << timer << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(-10, 0.5f, 0.0f, 0.0f);
	glRotatef(cameraY, 0.0f, 0.5f, 0.0f);

	cgGLEnableProfile(cgFragmentProfile);
	cgGLBindProgram(cgProgram);
	cgGLSetParameter1f(timeParameter, timer);

	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
									  // Top face (y = 1.0f)
	glColor3f(1.0f, 1.0f, 1.0f);     // White
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	// Bottom face (y = -0.5f)
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	// Front face  (z = 0.5f)
	glColor3f(1.0f, 1.0f, 1.0f);     // White
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	// Back face (z = -0.5f)
	glColor3f(1.0f, 1.0f, 1.0f);     // White
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);

	// Left face (x = -0.5f)
	glColor3f(1.0f, 1.0f, 1.0f);     // White
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	// Right face (x = 0.5f)
	glColor3f(1.0f, 1.0f, 1.0f);     // White
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glColor3f(1.0f, 0.0f, 0.0f);     // Red
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glEnd();

	cgGLUnbindProgram(cgFragmentProfile);
	cgGLDisableProfile(cgFragmentProfile);

	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
}

void klawiatura(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		cameraY += cameraSpeed;
		break;
	case 'd':
		cameraY -= cameraSpeed;
		break;
	case ' ':
		calculateTimer = !calculateTimer;
		break;
	case 27:
	case 'q':
		cgDestroyContext(cgContext);
		exit(0);
		break;
	}
}


int Launch(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow(argv[0]);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(klawiatura);
	init();
	glutMainLoop();
	return 0;
}


