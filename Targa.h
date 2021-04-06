/* Klasa £adujπca textury z plikÛw. èrÛd≥o: Kurs "Grafika komputerowa" Doktora Grzegorza £ukawskiego na platformie Moodle. */
#ifndef Targa_h
#define Targa_h

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <GL/glut.h>

typedef struct {
	GLuint bpp;		// iloúÊ bitÛw na piksel
	GLuint width;	// rozmiary w pikselach
	GLuint height;
} TARGAINFO;

// Funkcje
GLubyte* LoadTGAImage(char* filename, TARGAINFO* info);
bool LoadTGATexture(char* filename);
bool LoadTGAMipmap(char* filename);

#endif