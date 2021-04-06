#include "cParticle.h"
#include <math.h>
#include <random>
#include <iostream>

#define MAX_PART 50 // Liczba cz¹stek
// Odstêp (sekundy) miêdzy aktywacjami kolejnych cz¹stek:
#define ACTIVATE_TIME 0.1
// Losowanie liczby w zakresie 0..1:
#define RAND_MAX 30
#define F_RAND() ((float)rand()/RAND_MAX)
#define M_PI 3.14158

using namespace std;

cParticle::cParticle() {
	activate();
	// Ustawienie koloru:
	r = 0.6f;
	g = 0.6f;
	b = 0.6f;
	// Pozosta³e parametry:
	active = false;
	size = F_RAND() * 5.0f + 0.5f; // Rozmiar
}

void cParticle::activate() {
	life = 30.0f; // Pe³nia ¿ycia (dla 0 cz¹stka ginie)
	fade = 0.05f + F_RAND() * 0.4f; // Tempo umierania (1/sekunda)
	// Pocz¹tkowa pozycja cz¹stki (emiter punktowy):
	x = y = z = 0.0f;
	// Wektor ruchu - losowo z u¿yciem SFERYCZNEGO uk³adu:
	float fi = M_PI / 4; // 45 stopni w górê
	float psi = F_RAND() * (M_PI * 2); // 0-360 stopni wokó³ osi Y
	float rr = F_RAND() * 12 + 16; // D³ugoœæ wektora ruchu
	// Przeliczenie na uk³ad kartezjañski:
	xi = rr * cos(fi) * cos(psi);
	yi = rr * sin(fi);
	zi = rr * cos(fi) * sin(psi);
	// Wektor grawitacji:
	xg = zg = 0;
	yg = -10; // Grawitacja "tradycyjna" w dó³
}

void cParticle::live(float tt) {

	// Przesuniêcie cz¹stki zgodnie z wektorem ruchu:
	x += xi * tt * 0.00001;
	y += yi * tt * 0.00001;
	z += zi * tt * 0.00001;
	// Modyfikacja wektora ruchu przez wektor grawitacji:
	xi += xg * tt * 0.00001;
	yi += yg * tt * 0.00001;
	zi += zg * tt * 0.00001;
	// Zabranie ¿ycia:
	life -= fade * tt;
	// Je¿eli cz¹stka "umar³a", reaktywacja:
	if (life <= 0.0f)
		activate();
}