#pragma once
#include "obiektGraficzny.h"
#include "Samochod.h"
#include "Skrzyzowanie.h"
class Skrzyzowanie;

class Ulica :public ObiektGraficzny
{
	friend class Samochod;
protected:
	int dlugosc;
	
public:
	int czas(int);
	int czas2(int);
	vector < Samochod*> samochodyNaUlicy1;
	vector < Samochod*> samochodyNaUlicy2;
	Skrzyzowanie * skrzyzowania[2];
	void doadjsamochod(Samochod*, int, int);
	void usunsamochod(int);
	void kontrola();
	void wyswietl(RenderWindow *window);
	Ulica(int, int, int, int);

};
