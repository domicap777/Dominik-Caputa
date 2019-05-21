#include <SFML/Graphics.hpp>
#include "obiektGraficzny.h"
#include "Samochod.h"
#include "Skrzyzowanie.h"
#include "Ulica.h"
#include <time.h>

using namespace sf;
using namespace std;

int main()
{

	cout << "podaj odleglosc miedzy ulicami:" << endl;
	int odleglosc = 200;
	int ileSamochodow;
	do
	{
		cin >> odleglosc;
	} while (odleglosc > 600 || odleglosc < 0);
	Ulica* tmpUlica;
	Skrzyzowanie* tmpSkrzyzowanie;
	int ile = floor(800 / (odleglosc + 30));
	cout << "podaj ilosc samochodow nie wieksza niz " << ile*ile * 4 << ":" << endl;
	do
	{
		cin >> ileSamochodow;
	} while (ileSamochodow > ile*ile * 4 || ileSamochodow < 0);

	int wymiary = (odleglosc + 30)* ile;
	RenderWindow window(VideoMode(wymiary, wymiary), "symulacja ruchu drogowego");
	Ulica ***ulice = new Ulica**[ile * 2+1];
	Skrzyzowanie ***skrzyzowania = new Skrzyzowanie**[ile];
	for (int i = 0; i < ile * 2+1; i++) 
	{
		ulice[i] = new Ulica*[ile+1];
	}
	for (int i = 0; i < ile ; i++) 
	{
		skrzyzowania[i] = new Skrzyzowanie*[ile];
	}
	for (int i = 0; i < ile * 2+1; i++)
	{
		for (int j = 0; j < ile+1; j++)
		{
			if (i % 2)
				tmpUlica = new Ulica(j* (odleglosc + 30)- odleglosc / 2, 30 + odleglosc / 2 +i/2 * (odleglosc + 30) , odleglosc, -90);
			else
				tmpUlica = new Ulica(odleglosc / 2 + j * (odleglosc + 30), i/2 * (odleglosc + 30)- odleglosc / 2, odleglosc, 0);
			ulice[i][j] = tmpUlica;
		}
	}
	for (int i = 0; i < ile; i++)
	{
		for (int j = 0; j < ile; j++)
		{
			tmpSkrzyzowanie = new Skrzyzowanie(odleglosc / 2 + i  * (odleglosc + 30), odleglosc / 2+ j * (odleglosc + 30),ulice[j*2][i], ulice[j * 2 + 1][(i + 1) % ile], ulice[(j*2+2) % (ile * 2)][i], ulice[j * 2 + 1][i]);
			skrzyzowania[j][i] = tmpSkrzyzowanie;
		}
	}
	for (int i = 0; i < ile * 2; i++)
	{
		for (int j = 0; j < ile; j++)
		{ 
			ulice[i][j]->skrzyzowania[0] = skrzyzowania[i/2][j];
			if(i%2)
				ulice[i][j]->skrzyzowania[1] = skrzyzowania[i/2][(j-1+ile)%ile];//poziome
			else
				ulice[i][j]->skrzyzowania[1] = skrzyzowania[(i/2-1+ile)%ile][j];
		}
	}
	srand(time(NULL));
	Samochod** a = new Samochod*[ileSamochodow];
	for (int i = 0; i < ileSamochodow; )
	{
		if (rand() % 2)
			a[i] = new korsa;
		else
			a[i] = new malan;
		int x = rand() % ile;
		int y = rand() % (ile*2);
		int kierunek = rand() % 2;
		if (((ulice[y][x]->samochodyNaUlicy1.empty())&&(kierunek==0))|| ((ulice[y][x]->samochodyNaUlicy2.empty()) &&( kierunek == 1)))//funkcja sprawdzaj¹ca  poprawa 
		{
			ulice[y][x]->doadjsamochod(a[i],  odleglosc, kierunek*2+(y%2));
			i++;
		}
	}
	Clock clock;
	float timer = 0, delay = 0.03;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Escape) window.close();
		}
		if (timer > delay)
		{
			timer = 0;
			for (int i = 0; i < ileSamochodow; i++)
			{
				if (a[i]->stan == 0)
				{
					a[i]->NaJakiejUlicy->kontrola(); //slabe
					a[i]->jedz(&window);

				}
				if (a[i]->stan == 1)
				{
					if (a[i]->NajakimSkrzyzowaniu->nadzor(a[i]))//warunek z skrzyzowania
					{
						a[i]->stan = 3;
					}
					else
					{
						a[i]->predkosctmp = 0;
					}
				}
				if (a[i]->stan == 2)
				{
					a[i]->NaJakiejUlicy->usunsamochod(a[i]->kierunek);
					if (a[i]->kierunek == 0 || a[i]->kierunek == 3)
						a[i]->NaJakiejUlicy->skrzyzowania[1]->drogi[(a[i]->kierunek + a[i]->skret+4)%4]->doadjsamochod(a[i], odleglosc, (a[i]->kierunek + a[i]->skret+4) % 4);
					else
						a[i]->NaJakiejUlicy->skrzyzowania[0]->drogi[(a[i]->kierunek + a[i]->skret+4)%4]->doadjsamochod(a[i], odleglosc, (a[i]->kierunek + a[i]->skret+4) % 4);
					a[i]->skret = (rand() % 3) - 1;
					a[i]->stan = 0;
				}
				if (a[i]->stan == 3)
				{
					if (a[i]->skret == 0)
						a[i]->jedzProsto();
					else if (a[i]->skret == 1)
						a[i]->skretPrawo();
					else if (a[i]->skret == -1)
						a[i]->skretLewo();
				}
			}
		}
		
		for (int i = 0; i < (ile * 2)+1; i++)
		{
			for (int j = 0; j < ile+1; j++)
			{
				ulice[i][j]->wyswietl(&window);
			}
		}
		for (int i = 0; i < ile; i++)
		{
			for (int j = 0; j < ile; j++)
			{
				skrzyzowania[i][j]->wyswietl(&window);
			}
		}
		for (int i = 0; i<ileSamochodow; i++)
		{
			a[i]->wyswietl(&window);
		}
		window.display();
		window.clear(Color::Green);
	}	
	for (int j = 0; j < ile + 1; j++)
		delete[] ulice[j];
	delete[] ulice;
	for (int j = 0; j < ile ; j++)
		delete[] skrzyzowania[j];
	delete[] skrzyzowania;
	delete[] a;
	return 0;
}
