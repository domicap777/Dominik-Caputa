#define _USE_MATH_DEFINES
#include "Samochod.h"
#include <cmath>

void Samochod::wyswietl(RenderWindow * window)
{
	if (sprite.getPosition().y > window->getSize().y)
		sprite.move(0, -(int)(window->getSize().y));
	if (sprite.getPosition().y < 0)
		sprite.move(0, window->getSize().y);
	if (sprite.getPosition().x > window->getSize().x)
		sprite.move(-(int)(window->getSize().x), 0);
	if (sprite.getPosition().x < 0)
		sprite.move(window->getSize().y, 0);
	window->draw(sprite);
}

void Samochod::jedz(RenderWindow *window)
{
	sprite.move(predkosctmp * sin((sprite.getRotation() / 180)*M_PI), predkosctmp* cos((sprite.getRotation() / 180)*M_PI));
	odleglosc += predkosctmp;
	if (odleglosc+15 >= (this->NaJakiejUlicy->dlugosc ))
	{
		stan = 1;
	}
}

	void Samochod::skretPrawo()
	{
		predkosctmp = 1;
	sprite.rotate(4);
	if (kierunek % 2)
		sprite.move(predkosctmp * sin((sprite.getRotation() / 180)*M_PI), predkosctmp* -cos((sprite.getRotation() / 180)*M_PI));
	else
		sprite.move(predkosctmp * -sin((sprite.getRotation() / 180)*M_PI), predkosctmp* cos((sprite.getRotation() / 180)*M_PI));
	odleglosc += predkosctmp;
	if (odleglosc + 15 >= 25 + this->NaJakiejUlicy->dlugosc)
	{
		odleglosc = 0;
		stan = 2;
	}
}

void Samochod::skretLewo()
{
	predkosctmp = 1;
	if (kierunek % 2)
	{
		sprite.rotate(-2.8);
		sprite.move(predkosctmp * sin((sprite.getRotation() / 180)*M_PI), predkosctmp* -cos((sprite.getRotation() / 180)*M_PI));
	}
	else
	{
		sprite.rotate(-1.3);
		sprite.move(predkosctmp * -sin((sprite.getRotation() / 180)*M_PI), predkosctmp* cos((sprite.getRotation() / 180)*M_PI));
	}
	odleglosc += predkosctmp;
	if (odleglosc + 15 >= 40 + this->NaJakiejUlicy->dlugosc)
	{
		odleglosc = 0;
		stan = 2;
	}

}

void Samochod::jedzProsto()
{
	predkosctmp = 2;
	sprite.move(predkosctmp * sin((sprite.getRotation() / 180)*M_PI), predkosctmp* cos((sprite.getRotation() / 180)*M_PI));
	odleglosc += predkosctmp;
	if (odleglosc + 15 >= 45 + this->NaJakiejUlicy->dlugosc)
	{
		odleglosc = 0;
		stan = 2;
	}

}

Samochod::Samochod()
{
	t1.loadFromFile("grafika/samochód.png");
	sprite.setTexture(t1);
	predkosc =  rand() % 30 / 10 + 2;
	predkosctmp = predkosc;
	skret = rand() % 3 - 1;
}

korsa::korsa()
{
	t1.loadFromFile("grafika/samochód.png");
	sprite.setTexture(t1);
	predkosc = rand() % 20 / 10 + 2.5;
	predkosctmp = predkosc;
	skret = rand() % 3 - 1;
}

malan::malan()
{
	t1.loadFromFile("grafika/samochód2.png");
	sprite.setTexture(t1);
	predkosc = rand() % 20 / 9 + 2.5;
	predkosctmp = predkosc;
	skret = rand() % 3 - 1;
}