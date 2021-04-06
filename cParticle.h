#pragma once
class cParticle {
public:
	cParticle();
	void activate();
	// Jeden krok "z �ycia" cz�steczki (czas w sekundach):
	void live(float tt);
	bool active; // Cz�stka aktywna?
	float life, fade; // Czas �ycia i tempo "umierania"
	float size; // Wielko�� cz�stki
	float r, g, b; // Kolor R-G-B
	float x, y, z; // Aktualna pozycja X-Y-Z
	float xi, yi, zi; // Wektor ruchu X-Y-Z
	float xg, yg, zg; // Wektor grawitacji X-Y-Z
};

