#pragma once
#include <time.h>
#include <stdlib.h>

class Ball {
public:
	float position[2];
	float motion[2];
	float radius;
	float r, g, b;

	Ball() {
		//Zakres pozycji od -0.75 do 0.75
		position[0] = rand() % 1500;
		position[1] = rand() % 1500;
		position[0] = position[0] / 1000 - 0.75;
		position[1] = position[1] / 1000 - 0.75;

		//Zakres wektora ruchu od -0.01 do 0.01
		motion[0] = rand() % 2000;
		motion[1] = rand() % 2000;
		motion[0] = motion[0] / 100000 - 0.01;
		motion[1] = motion[1] / 100000 - 0.01;

		//Zakres promienia (i masy) od 0 do 0.1
		radius = (rand() % 1000);
		radius = radius / 10000;

		r = 1;
		g = 0;
		b = 0;
	}

	void Draw() {

		//Wyœwietlenie pi³ki.
		glTranslatef(position[0], position[1], 0);
		glColor3f(r, g, b);
		glutSolidSphere(radius, 20, 20);
		glTranslatef(-position[0], -position[1], 0);
	}

};