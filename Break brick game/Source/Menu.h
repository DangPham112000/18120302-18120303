#ifndef __Menu_h__
#define __Menu_h__
#include <SFML/Graphics.hpp>

using namespace sf;
class Menu
{
private:
	int selectIndex;
	Font font;
	Text menu[3];
public:
	Menu(float width, float height);
	~Menu();
	void Draw(RenderWindow& window);
	void Del(RenderWindow& window);
	void MoveUp();
	void MoveDown();
	int Getpress() { return selectIndex; }
};
#endif
