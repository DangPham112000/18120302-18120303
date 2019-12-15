#include "Brick.h"

Brick::Brick()
{

}

Brick::~Brick()
{
}

Brick::Brick(int x, int y)
{
	brick.setSize(sf::Vector2f(30, 30));
	brick.setOrigin(15, 15);
	brick.setPosition(x, y);
	brick.setFillColor(sf::Color(Random(100, 999), Random(100, 999), Random(100, 999)));
}

void Brick::getBrick()
{
	brick.setSize(sf::Vector2f(30, 30));
	brick.setOrigin(15, 15);
	brick.setPosition(Random(500, 785), Random(15, 585));
	brick.setFillColor(sf::Color(Random(100, 999), Random(100, 999), Random(100, 999)));
}

int Brick::Random(int x, int y)
{
	//srand((int)time(0));
	return x + rand() % (y + 1 - x);
	
}

int Brick::Check_Trung_Brick(Brick a[], int index)
{
	for (int i = 0; i < index; i++)
	{
		int xA = a[i].brick.getPosition().x;
		int xB = a[index].brick.getPosition().x;
		int yA = a[i].brick.getPosition().y;
		int yB = a[index].brick.getPosition().y;
		float distance = sqrt((xA - xB) * (xA - xB) + (yA - yB) * (yA - yB));
		if (distance < 42.42)
		{

			return 1;
		}

	}
	return 0;
}
