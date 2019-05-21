#pragma once
#include "Ulica.h"
#include "obiektGraficzny.h"
#include "Skrzyzowanie.h"
class Skrzyzowanie;
class Samochod :public ObiektGraficzny
{
	friend class Ulica;
protected:
	double predkosc,  odleglosc = 0;
public:
	double predkosctmp;
	int skret;
	int stan = 0;
	int kierunek;
	int ulx, uly;
	Ulica * NaJakiejUlicy;
	Skrzyzowanie *NajakimSkrzyzowaniu;
	void wyswietl(RenderWindow *window);
	void jedz(RenderWindow *window);
	void skretPrawo();
	void skretLewo();
	void jedzProsto();
	Samochod();
};
class korsa :public Samochod
{
	friend class Ulica;
public:
	korsa();
};
class malan :public Samochod
{
	friend class Ulica;
public:
	malan();
};
