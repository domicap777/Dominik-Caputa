#include "Ulica.h"



void Ulica::wyswietl(RenderWindow *window)
{
	window->draw(sprite);
}
Ulica::Ulica(int xx, int yy, int o, int rotacja)
{
	this->polozenieX = xx;
	this->polozenieY = yy;
	this->dlugosc = o;
	this->obrot = rotacja;
	t1.loadFromFile("grafika/droga.png");
	sprite.setTexture(t1);
	sprite.setRotation(rotacja);
	sprite.setPosition(this->polozenieX, this->polozenieY);
}



int Ulica::czas(int k)
{
	if (k < 2)
	{
		if (samochodyNaUlicy1.size() > 0)
		{
			Samochod* a = samochodyNaUlicy1[samochodyNaUlicy1.size() - 1];
			if (a->stan==0)
				return ((dlugosc - a->odleglosc)/ a->predkosctmp);
			return 0;
		}
		else return 100;
	}
	else
	{
		if (samochodyNaUlicy2.size() > 0)
		{
			Samochod* a = samochodyNaUlicy2[samochodyNaUlicy2.size() - 1];
			if (a->stan == 0)
				return ((dlugosc - a->odleglosc) / a->predkosctmp);
			return 0;
		}
		else return 100;
	}
}
int Ulica::czas2(int k)
{
	if (k < 2)
	{
		if (samochodyNaUlicy1.size() > 0)
		{
			Samochod* a = samochodyNaUlicy1[samochodyNaUlicy1.size() - 1];
			if (a->stan == 0)
				return ((dlugosc - a->odleglosc) / a->predkosctmp);
			else if (a->stan == 1)
				return 100;
			return 0;
		}
		else return 100;
	}
	else
	{
		if (samochodyNaUlicy2.size() > 0)
		{
			Samochod* a = samochodyNaUlicy2[samochodyNaUlicy2.size() - 1];
			if (a->stan == 0)
				return ((dlugosc - a->odleglosc) / a->predkosctmp);
			else if (a->stan==1)
				return 100;
			return 0;
		}
		else return 100;
	}
}

void Ulica::doadjsamochod(Samochod* a, int odleglosc, int kierunek)
{
	
	a->odleglosc = 0; 
	a->polozenieX = this->polozenieX;
	a->polozenieY = this->polozenieY;
	a->NaJakiejUlicy = this;
	a->obrot = this->obrot; 
	a->kierunek = kierunek;
	a->predkosctmp = a->predkosc;
	switch (kierunek)
	{
	case 0:
		this->samochodyNaUlicy1.insert(samochodyNaUlicy1.begin(), a);
		a->sprite.setRotation(a->obrot + 180);
		a->sprite.setPosition((a->polozenieX + 28), (a->polozenieY + odleglosc));
		a->NajakimSkrzyzowaniu = skrzyzowania[1];
		break;
	case 1:
		this->samochodyNaUlicy1.insert(samochodyNaUlicy1.begin(), a);
		a->sprite.setRotation(a->obrot + 180);
		a->sprite.setPosition((a->polozenieX + 15), (a->polozenieY - 12));
		a->NajakimSkrzyzowaniu = skrzyzowania[0];
		break;
	case 2:
		this->samochodyNaUlicy2.insert(samochodyNaUlicy2.begin(), a);
		a->sprite.setRotation(a->obrot);
		a->sprite.setPosition((a->polozenieX + 2), (a->polozenieY));
		a->NajakimSkrzyzowaniu = skrzyzowania[0];
		break;
	case 3:
		this->samochodyNaUlicy2.insert(samochodyNaUlicy2.begin(), a);
		a->sprite.setRotation(a->obrot );
		a->sprite.setPosition((a->polozenieX + odleglosc - 15), (a->polozenieY) - 18);
		a->NajakimSkrzyzowaniu = skrzyzowania[1];
		break;
	}
}
void Ulica::usunsamochod(int kierunek)
{
	if (kierunek < 2)
	{
		samochodyNaUlicy1.pop_back();
	}
	else samochodyNaUlicy2.pop_back();
}

void Ulica::kontrola()
{

	if (samochodyNaUlicy1.size() > 0&& samochodyNaUlicy1[samochodyNaUlicy1.size() - 1]->odleglosc<dlugosc-50)
	{
		samochodyNaUlicy1[samochodyNaUlicy1.size() - 1]->predkosctmp = samochodyNaUlicy1[samochodyNaUlicy1.size() - 1]->predkosc;
	}


	if (samochodyNaUlicy2.size() > 0 && samochodyNaUlicy2[samochodyNaUlicy2.size() - 1]->odleglosc < dlugosc -50)
	{
		samochodyNaUlicy2[samochodyNaUlicy2.size()-1]->predkosctmp = samochodyNaUlicy2[samochodyNaUlicy2.size() - 1]->predkosc;
	}

	for (int i = 1; i < samochodyNaUlicy1.size(); i++)
	{
		if (samochodyNaUlicy1[i - 1]->odleglosc > samochodyNaUlicy1[i]->odleglosc - 50)
		{
			samochodyNaUlicy1[i - 1]->predkosctmp = samochodyNaUlicy1[i]->predkosctmp;
		}
	}
	for (int i = 1; i < samochodyNaUlicy2.size(); i++)
	{
		if (samochodyNaUlicy2[i - 1]->odleglosc > samochodyNaUlicy2[i]->odleglosc - 50)
		{
			samochodyNaUlicy2[i - 1]->predkosctmp = samochodyNaUlicy2[i]->predkosctmp;
		}
	}
}
