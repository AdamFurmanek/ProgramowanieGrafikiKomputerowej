#pragma once

#include <gl/glew.h>
#include <GL/glut.h>
#include "Targa.h"

const float cube_vert[] = {
0.5f, 0.5f, -0.5f,
-0.5f, 0.5f, -0.5f,
0.5f, 0.5f, 0.5f,
-0.5f, 0.5f, 0.5f,

0.5f, -0.5f, 0.5f,
-0.5f, -0.5f, 0.5f,
0.5f, -0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,

-0.5f, 0.5f, 0.5f,
-0.5f, -0.5f, 0.5f,
0.5f, 0.5f, 0.5f,
0.5f, -0.5f, 0.5f,

0.5f, -0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,
0.5f, 0.5f, -0.5f,
-0.5f, 0.5f, -0.5f,

-0.5f, 0.5f, -0.5f,
-0.5f, -0.5f, -0.5f,
-0.5f, 0.5f, 0.5f,
-0.5f, -0.5f, 0.5f,

0.5f, 0.5f, -0.5f,
0.5f, 0.5f, 0.5f,
0.5f, -0.5f, -0.5f,
0.5f, -0.5f, 0.5f

};

const float cube_norm[] = {
0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f,

0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,

0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,

0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f,

-1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f,

1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,
};

const unsigned char walls[] = {
0, 1, 2,// strona 1
1, 3, 2,
4, 5, 6, // strona 2
5, 7, 6,
8, 9, 10, // strona 3
9, 11, 10,
12, 13, 14, // strona 4
13, 15, 14,
16, 17, 18, // strona 5
17, 19, 18,
20, 21, 22, // strona 6
21, 23, 22,
};

const float cube_texc[] = {
	0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f,		1.0f, 1.0f,
	1.0f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 1.0f,
	1.0f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 1.0f,
	0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f,		1.0f, 1.0f,
	1.0f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 1.0f,
	0.0f, 0.0f,		1.0f, 0.0f,		0.0f, 1.0f,		1.0f, 1.0f
};

GLuint ShadeTex;
GLuint ColorTex;

double cameraY = 0;

void Display() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glScalef(0.5, 0.5, 0.5);
	glRotatef(10, 0.5f, 0.0f, 0.0f);
	glRotatef(cameraY++, 0.0f, 0.5f, 0.0f);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ColorTex);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ShadeTex);
	glDrawElements(GL_TRIANGLES, sizeof(walls), GL_UNSIGNED_BYTE, walls);

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

static void Launch(int argc, char* argv[]) {
	//Init okna.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutCreateWindow(argv[0]);

	//Przypisanie podstawowych funkcji.
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);

	//W³¹czenie depth test.
	glEnable(GL_DEPTH_TEST);

	//Wczytanie wspó³rzêdnych bloku i w³¹czenie cullface.
	glVertexPointer(3, GL_FLOAT, 0, cube_vert);
	glTexCoordPointer(2, GL_FLOAT, 0, cube_texc);
	glNormalPointer(GL_FLOAT, 0, cube_norm);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	//W³¹czenie kana³u alfa tekstru tga.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Glew i multiteksturowanie.
	glewInit();
	glActiveTexture(GL_TEXTURE0); glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1); glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &ColorTex);
	glBindTexture(GL_TEXTURE_2D, ColorTex);
	LoadTGAMipmap(_strdup("Textures//leaves.tga"));

	glGenTextures(1, &ShadeTex);
	glBindTexture(GL_TEXTURE_2D, ShadeTex);
	LoadTGAMipmap(_strdup("Textures//shade.tga"));

	glClientActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, cube_texc);

	glClientActiveTexture(GL_TEXTURE1);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, cube_texc);

	glutMainLoop();
}