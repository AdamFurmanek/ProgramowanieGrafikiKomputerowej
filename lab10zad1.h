#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>
#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include "Targa.h"

static CGcontext   CgContext;
static CGprofile   CgFragmentProfile;
static CGprogram   CgFragmentProgram;
static CGparameter CgFragmentParamDecal;

GLuint texture;

void init() {

    CgContext = cgCreateContext();
    CgFragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
    cgGLSetOptimalOptions(CgFragmentProfile);
    CgFragmentProgram = cgCreateProgramFromFile(CgContext, CG_SOURCE, "fragmentShader4.cg", CgFragmentProfile, "main", NULL);
    cgGLLoadProgram(CgFragmentProgram);

}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cgGLBindProgram(CgFragmentProgram);
    cgGLEnableProfile(CgFragmentProfile);
    cgGLEnableTextureParameter(CgFragmentParamDecal);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 1);
    glVertex2f(-0.5, 0.5);

    glTexCoord2f(1, 1);
    glVertex2f(0.5, 0.5);

    glTexCoord2f(1, 0);
    glVertex2f(0.5, -0.5);

    glTexCoord2f(0, 0);
    glVertex2f(-0.5, -0.5);

    glEnd();

    cgGLDisableProfile(CgFragmentProfile);
    cgGLDisableTextureParameter(CgFragmentParamDecal);
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'q':
        cgDestroyContext(CgContext);
        exit(0);
        break;
    }
}

int Launch(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    LoadTGAMipmap(_strdup("Textures//leaves.tga"));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    init();

    glutMainLoop();
    return 0;
}