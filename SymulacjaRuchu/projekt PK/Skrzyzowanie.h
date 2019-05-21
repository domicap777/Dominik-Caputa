#pragma once
#include "obiektGraficzny.h"
#include "Ulica.h"

class Ulica;
class Samochod;

class Skrzyzowanie :public ObiektGraficzny
{

public:
	int blokada[4][3] = { { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 } };
	Ulica * drogi[4];
	void wyswietl(RenderWindow *window);
	bool nadzor(Samochod*);
	Skrzyzowanie(int, int,Ulica*, Ulica*, Ulica*, Ulica*);
};
