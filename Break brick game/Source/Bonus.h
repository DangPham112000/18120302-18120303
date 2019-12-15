#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace sf;

class Bonus
{
public:
	Bonus();
	~Bonus();
	CircleShape bonus;
	int key = 0;
	void getBonus();
	int Random(int x, int y);


};

