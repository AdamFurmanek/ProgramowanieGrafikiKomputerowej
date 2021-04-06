#include "cParticle.h"
#include <math.h>
#include <random>
#include <iostream>

#define MAX_PART 50 // Liczba cz�stek
// Odst�p (sekundy) mi�dzy aktywacjami kolejnych cz�stek:
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
	// Pozosta�e parametry:
	active = false;
	size = F_RAND() * 5.0f + 0.5f; // Rozmiar
}

void cParticle::activate() {
	life = 30.0f; // Pe�nia �ycia (dla 0 cz�stka ginie)
	fade = 0.05f + F_RAND() * 0.4f; // Tempo umierania (1/sekunda)
	// Pocz�tkowa pozycja cz�stki (emiter punktowy):
	x = y = z = 0.0f;
	// Wektor ruchu - losowo z u�yciem SFERYCZNEGO uk�adu:
	float fi = M_PI / 4; // 45 stopni w g�r�
	float psi = F_RAND() * (M_PI * 2); // 0-360 stopni wok� osi Y
	float rr = F_RAND() * 12 + 16; // D�ugo�� wektora ruchu
	// Przeliczenie na uk�ad kartezja�ski:
	xi = rr * cos(fi) * cos(psi);
	yi = rr * sin(fi);
	zi = rr * cos(fi) * sin(psi);
	// Wektor grawitacji:
	xg = zg = 0;
	yg = -10; // Grawitacja "tradycyjna" w d�
}

void cParticle::live(float tt) {

	// Przesuni�cie cz�stki zgodnie z wektorem ruchu:
	x += xi * tt * 0.00001;
	y += yi * tt * 0.00001;
	z += zi * tt * 0.00001;
	// Modyfikacja wektora ruchu przez wektor grawitacji:
	xi += xg * tt * 0.00001;
	yi += yg * tt * 0.00001;
	zi += zg * tt * 0.00001;
	// Zabranie �ycia:
	life -= fade * tt;
	// Je�eli cz�stka "umar�a", reaktywacja:
	if (life <= 0.0f)
		activate();
}