#pragma once
class cParticle {
public:
	cParticle();
	void activate();
	// Jeden krok "z ¿ycia" cz¹steczki (czas w sekundach):
	void live(float tt);
	bool active; // Cz¹stka aktywna?
	float life, fade; // Czas ¿ycia i tempo "umierania"
	float size; // Wielkoœæ cz¹stki
	float r, g, b; // Kolor R-G-B
	float x, y, z; // Aktualna pozycja X-Y-Z
	float xi, yi, zi; // Wektor ruchu X-Y-Z
	float xg, yg, zg; // Wektor grawitacji X-Y-Z
};

