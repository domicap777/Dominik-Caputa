#pragma once
#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>
#include<vector>

using namespace sf;
using namespace std;

class ObiektGraficzny
{
	
protected:
	
	Sprite sprite;
	Texture t1;
	int obrot;
	int polozenieX , polozenieY ;

public:

	 virtual void wyswietl(RenderWindow *window)=0;
};