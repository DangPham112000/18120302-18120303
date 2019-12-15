#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;
using namespace sf;
class Brick
{
public:
	Brick();
	~Brick();
	Brick(int x, int y);
	int key = 0;
	RectangleShape brick;
	void getBrick();
	int Random(int x, int y);
	int Check_Trung_Brick(Brick a[], int index);
};

