#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace sf;

class TheX
{
public:
	RectangleShape thex;
	int key = 0;
	void getTheX();
	int Random(int x, int y);

};
