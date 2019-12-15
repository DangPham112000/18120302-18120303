#include "GameManager.h"


void GameManager::initWindow()
{
	this->window = new RenderWindow(VideoMode(1000, 600), "PONG GAME", Style::Titlebar | Style::Close);
	this->window->setVerticalSyncEnabled(true);
}


GameManager::GameManager()
{
	this->initWindow();
}
GameManager::~GameManager()
{
	delete this->window;
}
//ham di chuyen hai thanh truot 
void GameManager::movepaddle()
{
	Vector2f paddleSize(25, 150);
	float ballAngle = 0.f;
	float deltaTime = clock.restart().asSeconds();
	if (Keyboard::isKeyPressed(Keyboard::W) && (leftPaddle.getPosition().y - paddleSize.y / 2 > 5.f))
	{
		leftPaddle.move(0.f, -paddleSpeed * deltaTime);//Thanh trai di chuyen len
	}
	if (Keyboard::isKeyPressed(Keyboard::S) && (leftPaddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f))
	{
		leftPaddle.move(0.f, paddleSpeed * deltaTime);//Thanh trai di chuyen xuong
	}
	if (Keyboard::isKeyPressed(Keyboard::Up) && (rightPaddle.getPosition().y - paddleSize.y / 2 > 5.f))
	{
		rightPaddle.move(0.f, -paddleSpeed * deltaTime);//Thanh phai di chuyen len
	}
	if (Keyboard::isKeyPressed(Keyboard::Down) && (rightPaddle.getPosition().y + paddleSize.y / 2 < gameHeight - 5.f))
	{
		rightPaddle.move(0.f, paddleSpeed * deltaTime);//Thanh phai di chuyen xuong
	}
}
//Ham chay chuong trinh
int GameManager::run()
{
	srand(static_cast<unsigned int>(std::time(NULL)));
	//khoi tao cac gia tri

	// Note
	int  index_thex;
	TheX tx[2];
	for (int i = 0; i < 2; i++)
	{
		tx[i].getTheX();
	}

	//Note
	int index_bonus;
	Bonus bn[2];
	for (int i = 0; i < 2; i++)
	{
		bn[i].getBonus();
	}

	Brick br[20];
	for (int i = 0; i < 20; i++)
	{
		do
		{
			br[i].getBrick();
		} while (br[i].Check_Trung_Brick(br, i) == 1);

	}
	File file;
	int highscore = file.Docfile();


	Text text_highscore_Chu;
	text_highscore_Chu.setString("High Score :");
	text_highscore_Chu.setFont(font);
	text_highscore_Chu.setCharacterSize(24);
	text_highscore_Chu.setFillColor(Color::Blue);
	text_highscore_Chu.setPosition(820, 320);


	Text text_highscore_So;
	string highsc = to_string(highscore);
	text_highscore_So.setString(highsc);
	text_highscore_So.setFont(font);
	text_highscore_So.setCharacterSize(50);
	text_highscore_So.setFillColor(Color::Blue);
	text_highscore_So.setPosition(850, 360);


	Text text;
	text.setString("Score :");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setFillColor(Color::Red);
	text.setPosition(820, 10);


	Text text2;
	text2.setString("Combo :");
	text2.setFont(font);
	text2.setCharacterSize(24);
	text2.setFillColor(Color::Red);
	text2.setPosition(820, 80);
	int count = 0;
	int index;
	Vector2f paddleSize(25, 150);
	float ballRadius = 10.f;
	Vector2f position;
	float rightPaddleSpeed = 0.f;
	float ballSpeed = -400.f;
	float ballAngle = 0.f;
	RectangleShape standbar;
	standbar.setSize(Vector2f(5,600));
	standbar.setPosition(800, 0);
	standbar.setFillColor(Color::Red);
	//Tai hinh nen 
	Sprite background;
	Texture texture;
	if (!texture.loadFromFile("Football.png"))
	{
		cout << "ERROR" << endl;
	}
	background.setTexture(texture);
	
	Sprite backgroundmenu;
	Texture texturemenu;
	if (!texturemenu.loadFromFile("cr72.jpg"))
	{
		cout << "ERROR" << endl;
	}
	backgroundmenu.setTexture(texturemenu);
	backgroundmenu.setTextureRect(IntRect(200, 0, 1000, 600));
	Menu menu(this->window->getSize().x, this->window->getSize().y);
	// Tai am thanh tu file co san trong resoure
	ballSoundBuffer.loadFromFile("resources/ball.wav");
	Sound ballSound(ballSoundBuffer);
	// Goi ham khoi tao thanh ben trai
	createleftPaddle();
	// Goi ham khoi tao ham ben phai
	createrightPaddle();
	// Goi ham khoi tao qua bong
	createBall();
	//  Tai kieu chu co san trong resource
	font.loadFromFile("resources/sansation.ttf");
	// Goi ham khoi tao thong bao 
	setPauseMessage();
	setMessage();
	
	Clock clock;
	
	int time = 0;

	while (this->window->isOpen())
	{
		//Xu li cac lenh 
		while (this->window->pollEvent(event))
		{
			
	
			switch (event.type)
			{
				//Thoat tro choi
			case Event::Closed:
				this->window->close();

			case Event::KeyPressed:
				switch (event.key.code)
			case Keyboard::Escape:
				isPlaying = false;
				break;
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Up://Phim mui ten di xuong
					menu.MoveUp();//Goi ham di chuyen thanh phai di len
					break;
				case Keyboard::Down://Phim mui ten di xuong
					menu.MoveDown();//Goi ham di chuyen thanh phai di xuong
					break;
				case Keyboard::Space://Phim cach
					isAgree = true;
					break;
				case Keyboard::BackSpace:
				//	time = 0;
					break;
				case Keyboard::F1://Nhan phim F1 de dung tro choi
					isPlaying = false;
					break;
				case Keyboard::Return://Tren menu, nhan Enter de chon cac lenh
					switch (menu.Getpress())
					{
					case 0://Hai nguoi choi, Khoi tao lai cac gia tri
							isPlaying = true;
							intScore1 = 0;
							//intScore2 = 0;
						break;
					case 1://Thoat tro choi
						this->window->close();
						cout << "Exit is pressed" << endl;
						break;
					case 2://Chua hoan thanh
						cout << "Udating is pressed" << endl;
						break;
					}
					break;
				}
			}
		}
		//Goi ham thiet lap lai ket qua tro choi
		setCore();
		if (isPlaying)
		{
			//Khoi tao cac gia tri can trong tro choi
			float deltaTime = clock.restart().asSeconds();
			float factor = ballSpeed * deltaTime;
			position.x = cos(ballAngle)*factor;
			position.y = sin(ballAngle)*factor;
			ball.move(position.x, position.y);
			movepaddle();
			//Xet vi tri qua bong va thanh hai ben truot
			//Neu qua bong chay ngoai ben trai
			if (ball.getPosition().x + 2 * ballRadius < leftPaddle.getPosition().x)
			{
				ballSpeed = -400.f;
				reset(br, count, bn, tx);
				

				
				time++;
			}
			//Neu qua bong chay ngaoi ben phai
			if (ball.getPosition().x - 2*ballRadius > rightPaddle.getPosition().x)
			{
				
				ballSpeed = -400.f;
				reset(br,count, bn, tx);
				
				time++;
			}
			
			//Xet vi tri qua bong va hai ben tuong
			//Qua bong dap tuong tren
			if (ball.getPosition().y - ballRadius < 0.f)
			{
				ballSound.play();
				ballAngle = -ballAngle;
				ball.setPosition(ball.getPosition().x, ballRadius + 0.1f);//Qua bong doi lai
				ballSound.play();
			}
			//Qua bong dap tuong duoi
			if (ball.getPosition().y + ballRadius > gameHeight)
			{
				ballSound.play();
				ballAngle = -ballAngle;
				ball.setPosition(ball.getPosition().x, gameHeight - ballRadius - 0.1f);//Qua bong doi lai
				ballSound.play();
			}
			
			//Qua bong dap vao thanh trai
			if (ball.getPosition().x - ballRadius < leftPaddle.getPosition().x + paddleSize.x / 2 &&
				ball.getPosition().x - ballRadius > leftPaddle.getPosition().x &&
				ball.getPosition().y + ballRadius >= leftPaddle.getPosition().y - paddleSize.y / 2 &&
				ball.getPosition().y - ballRadius <= leftPaddle.getPosition().y + paddleSize.y / 2)
			{
				if (ball.getPosition().y > leftPaddle.getPosition().y)
				{
					ballAngle = pi - ballAngle + (rand() % 20) * pi / 180;
				}
				else
					ballAngle = pi - ballAngle - (rand() % 20) * pi / 180;
				combo = 0;
				ballSpeed = ballSpeed - 30;
				cout << ballSpeed << "\t";
				ballSound.play();
				ball.setPosition(leftPaddle.getPosition().x + ballRadius + paddleSize.x / 2 + 0.1f, ball.getPosition().y);
				time++;
			}

			
			//Qua bong dap thanh phai
			if (ball.getPosition().x + ballRadius > 790 )
			{
				if (ball.getPosition().y > 300)
					ballAngle = pi - ballAngle + (rand() % 20) * pi / 180;//Qua bong di chuyen goc ngau nhien
				else
					ballAngle = pi - ballAngle - (rand() % 20) * pi / 180;//Qua bong di chuyen goc ngau nhien

				//ballSpeed = ballSpeed + 10;
				cout << ballSpeed << "\t";
				ballSound.play();
				ball.setPosition(790 - ballRadius - 0.1f, ball.getPosition().y);
			}
			// Xu li cham Brick
			if (Check_Cham_VatPham(ball, br, 20, index) == 1)
			{
				br[index].brick.setFillColor(sf::Color::Black);
				if (br[index].key == 0)
				{
					count++;
					ballAngle = pi - ballAngle + (rand() % 20) * pi / 180;
					cout << count << endl;
					
					combo++;
					intScore1 += combo;
					
					br[index].key = 1;
				}
				
				

			}
			//Note 
			//Check cham TheX
			if (Check_Cham_TheX(ball, tx, 2, index_thex) == 1)
			{
				tx[index_thex].thex.setFillColor(Color::Black);
				if (tx[index_thex].key == 0)
				{
					if (intScore1 < 10) intScore1 = 0;
					else intScore1 -= 10;
					tx[index_thex].key = 1;
				}
			}
			//Note
			//Check cham bonus
			if (Check_Cham_Bonus(ball, bn, 2, index_bonus) == 1)
			{
				bn[index_bonus].bonus.setFillColor(Color::Black);
				if (bn[index_bonus].key == 0)
				{
					intScore1 += 10;
					bn[index_bonus].key = 1;
				}
			}
			if (count == 20)
			{
				if (intScore1 > highscore)
				{
					file.Ghifile(intScore1);
					highscore = intScore1;
					string highsc = to_string(highscore);
					text_highscore_So.setString(highsc);
				}
				
				isPlaying = 0;

				
			}
			Message.setString("\nPress F1 to stop");
			window->clear();//Xoa man hinh
			menu.Del(*window);//Ve doi tuong Menu
			//Ve cac doi tuong
			//window->draw(background);
			
			//window->draw(textScore2);
			window->draw(Message);
			window->draw(standbar);
			window->draw(text);
			window->draw(textScore1);
			window->draw(text_highscore_Chu);
			window->draw(text_highscore_So);
			if (combo >1)
			{
				window->draw(text2);
				window->draw(textCombo);
			}
			//window->draw(textScore1);
			for (int i = 0; i < 20; i++)
			{
				window->draw(br[i].brick);
			}
			window->draw(leftPaddle);
			//window->draw(rightPaddle);			
			//Note
			for (int i = 0; i < 2; i++)
			{
				window->draw(tx[i].thex);
			}
			//Note
			for (int i = 0; i < 2; i++)
			{
				window->draw(bn[i].bonus);
			}
			window->draw(ball);
			window->display();

		}
		//Khi dung game
		if (!isPlaying)
		{
			window->clear();
			window->clear(sf::Color::Black);//Xoa man hinh
			window->draw(backgroundmenu);//Ve nen
			ballAngle = 0.f;
			if (time == 0 && !isAgree)
			{
				window->draw(pauseMessage);
			}
			if (time != 0)
			{
				//pauseMessage.setString("Stop Game !\n");
				Text text_your_score;
				text_your_score.setString("Score :");
				text_your_score.setFont(font);
				text_your_score.setCharacterSize(50);
				text_your_score.setFillColor(Color::Red);
				text_your_score.setPosition(200, 200);
				window->draw(text_your_score);
				Text text_score_end;
				string strScore1 = to_string(intScore1);
				text_score_end.setString(strScore1);
				text_score_end.setFont(font);
				text_score_end.setCharacterSize(50);
				text_score_end.setFillColor(Color::Red);
				text_score_end.setPosition(400, 200);
				window->draw(text_score_end);
				if (intScore1 > intScore2)
				{
					//pauseMessage.setString("Stop Game !\n");
					
				}
				else
				{
					pauseMessage.setString("Game stopped!\n");
				}
				Message.setString("\nPress Enter to play again");
				//window->draw(textScore1);//...
				//window->draw(textScore2);//...
				window->draw(Message);//...
				//window->draw(pauseMessage);///...
			}
			if (time == 0 && isAgree)
			{
				menu.Draw(*window);
			}
			
			window->display();//Trinh dien cac doi tuong
		}
	}

	return EXIT_SUCCESS;
}
//Ham tao thanh trai
void GameManager::createleftPaddle()
{
	Vector2f paddleSize(25, 150);
	leftPaddle.setSize(paddleSize - Vector2f(3, 3));
	leftPaddle.setOutlineThickness(3);
	leftPaddle.setOutlineColor(Color::Black);
	leftPaddle.setFillColor(Color(100, 100, 200));
	leftPaddle.setOrigin(paddleSize / 2.f);
	leftPaddle.setPosition(10 + paddleSize.x / 2, gameHeight / 2);
}
//Ham tao thanh phai
void GameManager::createrightPaddle()
{
	Vector2f paddleSize(25, 150);
	rightPaddle.setSize(paddleSize - Vector2f(3, 3));
	rightPaddle.setOutlineThickness(3);
	rightPaddle.setOutlineColor(Color::Blue);
	rightPaddle.setFillColor(Color::Yellow);
	rightPaddle.setOrigin(paddleSize / 2.f);
	rightPaddle.setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);
}
//Ham tao qua bong 
void GameManager::createBall()
{
	float ballRadius = 10.f;
	ball.setRadius(ballRadius - 3);
	ball.setOutlineThickness(10);
	ball.setOutlineColor(Color::Cyan);
	ball.setFillColor(Color::White);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	ball.setPosition(gameWidth / 2, gameHeight / 2);
}
//Ham tao cac thong bao
void GameManager::setPauseMessage()
{
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(40);
	pauseMessage.setPosition(150.f, 30.f);
	pauseMessage.setFillColor(Color::Red);
	pauseMessage.setString("Welcome to Pong!\nPress space to continue");
}

void GameManager::setMessage()
{
	Message.setFont(font);
	Message.setCharacterSize(40);
	Message.setPosition(100.f, 450.f);
	Message.setFillColor(Color::White);
}
//Ham khoi tao ket qua
void GameManager::setCore()
{
	
	Vector2f paddleSize(25, 150);
	string strScore1 = to_string(intScore1);
	textScore1.setString(strScore1);
	textScore1.setFont(font);
	textScore1.setCharacterSize(40);
	textScore1.setFillColor(Color::Red);
	textScore1.setPosition(Vector2f(840,40));

	string strCombo = to_string(combo);
	textCombo.setString(strCombo);
	textCombo.setFont(font);
	textCombo.setCharacterSize(40);
	textCombo.setFillColor(Color::Red);
	textCombo.setPosition(Vector2f(840, 100));

	string strScore2 = to_string(intScore2);
	textScore2.setString(strScore2);
	textScore2.setFont(font);
	textScore2.setFillColor(Color::Blue);
	textScore2.setCharacterSize(40);
	textScore2.setPosition(gameWidth/2 + 100, 0.f);
}

//Ham khoi tao lai vi tri cac doi tuong: Thanh phai, thah trai, qua bong
void GameManager::reset(Brick br[], int& count, Bonus bn[], TheX tx[])//Note
{
	count = 0;
	combo = 0;
	intScore1 = 0;
	float ballAngle = 0.f;
	Vector2f paddleSize(25, 150);
	rightPaddle.setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);
	leftPaddle.setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	ball.setPosition(gameWidth / 2, gameHeight / 2);
	//ballAngle = (rand() % 360) * 2 * pi / 360;
	ballAngle = 0.f;
	//Brick br[20];
	for (int i = 0; i < 20; i++)
	{
		do
		{
			br[i].getBrick();
			br[i].key = 0;
		} while (br[i].Check_Trung_Brick(br, i) == 1);

	}
	//Note
	for (int i = 0; i < 2; i++)
	{
		bn[i].getBonus();
		bn[i].key = 0;
	}
	//Note
	for (int i = 0; i < 2; i++)
	{
		tx[i].getTheX();
		tx[i].key = 0;
	}
}

int GameManager::Check_Cham_VatPham(CircleShape b, Brick br[], int n, int& index)
{
	for (int i = 0; i < n; i++)
	{
		int xA = b.getPosition().x;
		int xB = br[i].brick.getPosition().x;
		int yA = b.getPosition().y;
		int yB = br[i].brick.getPosition().y;
		float distance = sqrt((xA - xB) * (xA - xB) + (yA - yB) * (yA - yB));
		if (distance < 42.42)
		{
			index = i;
			return 1;
		}

	}
	return 0;
}

int GameManager::Check_Cham_TheX(CircleShape b, TheX tx[], int n, int& index)
{
	for (int i = 0; i < n; i++)
	{
		int xA = b.getPosition().x;
		int xB = tx[i].thex.getPosition().x;
		int yA = b.getPosition().y;
		int yB = tx[i].thex.getPosition().y;
		float distance = sqrt((xA - xB) * (xA - xB) + (yA - yB) * (yA - yB));
		if (distance < 35.35)
		{
			index = i;
			return 1;
		}

	}
	return 0;
}

int GameManager::Check_Cham_Bonus(CircleShape b, Bonus bn[], int n, int& index)
{
	for (int i = 0; i < n; i++)
	{
		int xA = b.getPosition().x;
		int xB = bn[i].bonus.getPosition().x;
		int yA = b.getPosition().y;
		int yB = bn[i].bonus.getPosition().y;
		float distance = sqrt((xA - xB) * (xA - xB) + (yA - yB) * (yA - yB));
		if (distance < 35.35)
		{
			index = i;
			return 1;
		}

	}
	return 0;
}




