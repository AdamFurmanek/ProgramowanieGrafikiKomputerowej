#include <GL/glut.h>

#include <Cg/cg.h>
#include <Cg/cgGL.h>

#include <stdlib.h>
#include <stdio.h>

CGcontext	cgContext;
CGprogram	cgProgram;
CGprofile	cgVertexProfile;
CGparameter	modelViewMatrix, position, color, timerParameter;

float timer = 0;
float timerSpeed = 0.005;
bool calculateTimer = true;
double cameraY = 0;
float cameraSpeed = 5;

void init() {

	glEnable(GL_DEPTH_TEST);

	cgContext = cgCreateContext();

	cgVertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);

	cgGLSetOptimalOptions(cgVertexProfile);

	cgProgram = cgCreateProgramFromFile(cgContext, CG_SOURCE, "shader3.cg", cgVertexProfile, "main", 0);

	cgGLLoadProgram(cgProgram);
	position = cgGetNamedParameter(cgProgram, "IN.position");
	color = cgGetNamedParameter(cgProgram, "IN.color");
	modelViewMatrix = cgGetNamedParameter(cgProgram, "ModelViewProj");
	timerParameter = cgGetNamedParameter(cgProgram, "timer");
}

void display() {
	if (calculateTimer) {
		timer += timerSpeed;

		if (timer <= 0)
			timerSpeed = abs(timerSpeed);
		if (timer >= 0.25)
			timerSpeed = -abs(timerSpeed);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(-10, 0.5f, 0.0f, 0.0f);
	glRotatef(cameraY, 0.0f, 0.5f, 0.0f);


	cgGLSetStateMatrixParameter(modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	cgGLEnableProfile(cgVertexProfile);
	cgGLBindProgram(cgProgram);
	cgGLSetParameter1f(timerParameter, timer);

	glutSolidCube(0.5);

	cgGLUnbindProgram(cgVertexProfile);
	cgGLDisableProfile(cgVertexProfile);

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


