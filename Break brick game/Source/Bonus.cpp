#include "Bonus.h"

Bonus::Bonus()
{
}

Bonus::~Bonus()
{
}

void Bonus::getBonus()
{
	bonus.setRadius(10);
	//bonus.setOrigin(10, 10);
	bonus.setPosition(Random(100, 400), Random(10, 590));
	//bonus.setPosition(50,50);
	bonus.setFillColor(Color::Green);

}

int Bonus::Random(int x, int y)
{
	return x + rand() % (y + 1 - x);
}
