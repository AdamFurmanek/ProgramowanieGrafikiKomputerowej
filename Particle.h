#pragma once

#include <GL/glut.h>

class Particle {
public:
	float positionX, positionY, positionZ;
	float size;
	float r, g, b;

	Particle(float positionX = 0, float positionY = 0, float positionZ = 0.7, float size = 0.1, float r = 1, float g = 1, float b = 1) {
		this->positionX = positionX;
		this->positionY = positionY;
		this->positionZ = positionZ;
		this->size = size;
		this->r = r;
		this->g = g;
		this->b = b;
	}

	void CalculatePosition() {
		switch ((rand() % 6)) {
		case 0:
			positionX += 0.006;
			break;
		case 1:
			positionY += 0.006;
			break;
		case 2:
			positionZ += 0.006;
			break;
		case 3:
			positionX -= 0.006;
			break;
		case 4:
			positionY -= 0.006;
			break;
		case 5:
			positionZ -= 0.006;
			break;

		}
	}

	void Draw() {
		glPushMatrix();

		glTranslatef(positionX, positionY, positionZ);

		GLfloat matrix[4][4];
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)matrix);
		for (int m = 0;m < 3;m++) {
			for (int n = 0;n < 3;n++)
				if (m != n) matrix[m][n] = 0.0f;
				else matrix[m][n] = 1.0f;
		}
		glLoadMatrixf((GLfloat*)matrix);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(r, g, b, 0.4);
		
		glBegin(GL_POLYGON);
			glVertex2d(size, -size);
			glVertex2d(-size, -size);
			glVertex2d(-size, size);
			glVertex2d(size, size);
		glEnd();

		glPopMatrix();
	}

};