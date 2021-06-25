#include <GL/glut.h>

#include <Cg/cg.h>
#include <Cg/cgGL.h>

#include <stdlib.h>
#include <stdio.h>

CGcontext	cgContext;
CGprofile	cgFragmentProfile;
CGprogram	cgProgram;
CGparameter	modelViewMatrix, position, color, timeParameter;

float myTime = 0.0;
double cameraY = 0;
float cameraSpeed = 5;

void init() {

	glEnable(GL_DEPTH_TEST);

	cgContext = cgCreateContext();

	cgFragmentProfile = cgGLGetLatestProfile(CG_GL_VERTEX);

	cgGLSetOptimalOptions(cgFragmentProfile);

	cgProgram = cgCreateProgramFromFile(cgContext, CG_SOURCE, "shader.cg", cgFragmentProfile, "main", 0);

	cgGLLoadProgram(cgProgram);
	position = cgGetNamedParameter(cgProgram, "IN.position");
	color = cgGetNamedParameter(cgProgram, "IN.color");
	modelViewMatrix = cgGetNamedParameter(cgProgram, "ModelViewProj");
	timeParameter = cgGetNamedParameter(cgProgram, "timeParameter");
}

void display() {
	myTime += 0.01;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(-10, 0.5f, 0.0f, 0.0f);
	glRotatef(cameraY, 0.0f, 0.5f, 0.0f);

	cgGLEnableProfile(cgFragmentProfile);
	cgGLBindProgram(cgProgram);
	cgGLSetStateMatrixParameter(modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	cgGLSetParameter1f(timeParameter, myTime);

	glutSolidCube(0.5);
	//glutSolidSphere(0.5,30,30);

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


