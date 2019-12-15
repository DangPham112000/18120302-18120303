#ifndef _GameManager_h__
#define _GameManager_h__
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include "Menu.h"
#include "Brick.h"
#include "File.h"
#include "Bonus.h"
#include "TheX.h"
using namespace sf;
using namespace std;
const float pi = 3.14159f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 300.f;
const Time AITime = seconds(0.1f);

class GameManager
{
private:
	RenderWindow* window;
	Event event;
	RectangleShape leftPaddle;
	RectangleShape rightPaddle;
	CircleShape ball;
	Text pauseMessage;
	Text Message;
	Sprite* pictures;
	SoundBuffer ballSoundBuffer;
	SoundBuffer Games;

	void initWindow();
public:
	Text textScore1;
	Text textScore2;
	Font font;
	Clock AITimer;
	GameManager();
	~GameManager();
	int run();
	void createleftPaddle();
	void createrightPaddle();
	void createBall();
	void setPauseMessage();
	void setMessage();
	void setCore();
	void reset(Brick br[], int& count, Bonus bn[], TheX tx[]);
	int Check_Cham_VatPham(CircleShape b, Brick br[], int n, int& index);
	int Check_Cham_TheX(CircleShape b, TheX tx[], int n, int& index);
	int Check_Cham_Bonus(CircleShape b, Bonus bn[], int n, int& index);
	void movepaddle();

	Clock clock;
	bool isPlaying = false;
	bool isAgree = false;
	int intScore1;
	int intScore2;
	int combo = 0;
	Text textCombo;
	int time = 0;
};
#endif

