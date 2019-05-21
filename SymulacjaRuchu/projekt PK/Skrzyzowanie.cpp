#include "Skrzyzowanie.h"



void Skrzyzowanie::wyswietl(RenderWindow * window)
{
	window->draw(sprite);
}

bool Skrzyzowanie::nadzor(Samochod* a)
{
	if (a->skret == 1)
	{
		return true;
	}
	if (a->skret == 0)
	{
		if(drogi[(a->kierunek+1)%4]->czas((a->kierunek + 3)%4)>45/2)
			return true;
	}
	if (a->skret == -1)
	{
		if (drogi[(a->kierunek + 1) % 4]->czas((a->kierunek + 3) % 4) > 40)
		if (drogi[a->kierunek]->czas2((a->kierunek + 2)%4) > 40)
			return true;
	}
	return false;
}


Skrzyzowanie::Skrzyzowanie(int xx, int yy, Ulica* a, Ulica* b, Ulica* c, Ulica* d)
{
	drogi[0] = a;
	drogi[1] = b;
	drogi[2] = c;
	drogi[3] = d;
	this->polozenieX = xx;//
	this->polozenieY = yy;//
	t1.loadFromFile("grafika/skrzy¿owanie.png");
	sprite.setTexture(t1);
	sprite.setPosition(this->polozenieX, this->polozenieY);
}


