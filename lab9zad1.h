#include <GL/glut.h>

#include <Cg/cg.h>
#include <Cg/cgGL.h>

#include <stdlib.h>
#include <stdio.h>

CGcontext	cgContext;

CGprogram	cgVertexProgram;
CGprofile	cgVertexProfile;
CGparameter	modelViewMatrix, vertexPosition, vertexColor, timeParameter;

CGprogram  cgFragmentProgram;
CGprofile cgFragmentProfile;
CGparameter fragmentColor, fragmentTimeParameter;

float timer = 0.0;
float timrSpeed = 0.01;

double cameraY = 0;
float cameraSpeed = 5;

void init() {

	glEnable(GL_DEPTH_TEST);
	cgContext = cgCreateContext();

	cgVertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
	cgGLSetOptimalOptions(cgVertexProfile);
	cgVertexProgram = cgCreateProgramFromFile(cgContext, CG_SOURCE, "shader4.cg", cgVertexProfile, "main", 0);
	cgGLLoadProgram(cgVertexProgram);
	vertexPosition = cgGetNamedParameter(cgVertexProgram, "IN.position");
	vertexColor = cgGetNamedParameter(cgVertexProgram, "IN.color");
	modelViewMatrix = cgGetNamedParameter(cgVertexProgram, "ModelViewProj");
	timeParameter = cgGetNamedParameter(cgVertexProgram, "timeParameter");

	cgFragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
	cgGLSetOptimalOptions(cgFragmentProfile);
	cgFragmentProgram = cgCreateProgramFromFile(cgContext, CG_SOURCE, "fragmentShader3.cg", cgFragmentProfile, "main", 0);
	cgGLLoadProgram(cgFragmentProgram);
	fragmentColor = cgGetNamedParameter(cgFragmentProgram, "IN.color");
	fragmentTimeParameter = cgGetNamedParameter(cgFragmentProgram, "timer");
}

void display() {
	timer += 0.01;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glRotatef(-10, 0.5f, 0.0f, 0.0f);
	glRotatef(cameraY, 0.0f, 0.5f, 0.0f);

	cgGLEnableProfile(cgVertexProfile);
	cgGLBindProgram(cgVertexProgram);
	cgGLSetStateMatrixParameter(modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);
	cgGLSetParameter1f(timeParameter, timer);

	cgGLEnableProfile(cgFragmentProfile);
	cgGLBindProgram(cgFragmentProgram);
	cgGLSetParameter1f(fragmentTimeParameter, 10);

	glutSolidCube(1);

	cgGLDisableProfile(cgFragmentProfile);
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
