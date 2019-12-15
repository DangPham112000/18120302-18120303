#include "TheX.h"

void TheX::getTheX()
{
	thex.setSize(sf::Vector2f(20, 20));
	thex.setOrigin(10, 10);
	thex.setPosition(Random(100, 400), Random(10, 590));
	thex.setFillColor(Color::Red);
	thex.rotate(45);
}

int TheX::Random(int x, int y)
{
	return x + rand() % (y + 1 - x);
}
