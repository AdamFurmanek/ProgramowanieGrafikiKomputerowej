#include <GL/glut.h>
#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include <stdlib.h>
#include <stdio.h>

CGcontext	cgContext;
CGprogram	cgProgram;
CGprofile	cgVertexProfile;
CGparameter	modelViewMatrix, position, color, wave;

int waveLength = 6, waveWidth = 5;
float waveSpeed = 0.1f;
float wavePosition = -waveLength-3;

double cameraY = 50;
float cameraSpeed = 5;

void init() {

	glEnable(GL_DEPTH_TEST);

	cgContext = cgCreateContext();
	cgVertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
	cgGLSetOptimalOptions(cgVertexProfile);
	cgProgram = cgCreateProgramFromFile(cgContext, CG_SOURCE, "shader2.cg", cgVertexProfile, "main", 0);
	cgGLLoadProgram(cgProgram);
	position = cgGetNamedParameter(cgProgram, "IN.position");
	color = cgGetNamedParameter(cgProgram, "IN.color");
	modelViewMatrix = cgGetNamedParameter(cgProgram, "ModelViewProj");
	wave = cgGetNamedParameter(cgProgram, "wave");
}

void display() {
	wavePosition += waveSpeed;
	if (wavePosition > waveLength)
		wavePosition = -waveLength - 3;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(-10, 0.5f, 0.0f, 0.0f);
	glRotatef(cameraY, 0.0f, 0.5f, 0.0f);
	glScalef(0.1, 0.1, 0.1);

	cgGLSetStateMatrixParameter(modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	cgGLEnableProfile(cgVertexProfile);
	cgGLBindProgram(cgProgram);
	cgGLSetParameter1f(wave, wavePosition);

	glBegin(GL_QUADS);
		for (int i = -waveLength; i < waveLength; i++) {
			glVertex3f(i, 0.0f, waveWidth);
			glVertex3f(i+1, 0.0f, waveWidth);
			glVertex3f(i+1, 0.0f, -waveWidth);
			glVertex3f(i, 0.0f, -waveWidth);
		}
	glEnd();

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


