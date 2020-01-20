//After lecture, spent 7 hours with the help of Teo to refine the game. So, big thanks to Teo for his assistance! 
//Thank you Michael for: bool statment & showing me Hilze Vonck on YouTube.

#include <iostream>
#include <SFML\Graphics.hpp>

//Compiler Directives
using namespace std;
using namespace sf;

Vector2f window_CurrentDimensions(750,530);
RenderWindow window(VideoMode(750,530), "Arkanoid Game", Style::Close);

	//Global Variables
	//Sprite Variables
	Texture Background, Border, Paddle, Ball, SolidBrick, BrokenBrick;
	//Solid Brick Variables
	float SolidBrickWidth, SolidBrickHeight;
	Sprite SolidBrickSprite(SolidBrick);
	
Sprite SpawnBrick(int BrickType, int BallPositionX, int BallPositionY, Sprite SolidBricks[2]){
	//Accessing the ball colour
	Sprite SolidBrickSprite = SolidBricks[BrickType - 3];
	//SolidBrickSprite.setPosition(BallPositionX *126 +25, BallPositionY *40 +25);
	SolidBrickSprite.setPosition(BallPositionX * window.getSize().x / 5 +29, BallPositionY * window.getSize().x / 10 +29);
	window.draw(SolidBrickSprite);
	return SolidBrickSprite;
}

int main()
{
	//Local Variables
	//Event Variables...
	Event KeyboardEvent;
	//Paddle Variables
	Vector2f PaddleLocation (375,515);
		float PaddleWidth, PaddleHeight;
	//Ball Variables
	Vector2f ballLocation (375,265);
	float BallSpeed = 3.0f;
	float BallWidth, BallHeight;
	bool faceUp = false;
	window.setFramerateLimit(60);
	
	//Background image
	if (!Background.loadFromFile("Assets/Background.png")) 
		{
			cout << "Error 1: Failed to load background image" << "\n";
			system("pause");
		}
	Sprite BackgroundImage(Background);

	//Paddle
	if (!Paddle.loadFromFile("Assets/Paddle.png")) 
		{
		cout << "Error 4: Failed to load Paddle image" << "\n";
		system("pause");
		}
	Sprite PaddleSprite(Paddle);
	PaddleSprite.setPosition(PaddleLocation.x, PaddleLocation.y);
	PaddleSprite.setOrigin(64.0f, 12.5f);
	PaddleWidth = PaddleSprite.getGlobalBounds().width;
	PaddleHeight = PaddleSprite.getGlobalBounds().height;

	//Ball Variable
	if (!Ball.loadFromFile("Assets/Ball.png")) 
		{
		cout << "Error 4: Failed to load ball image" << "\n";
		system("pause");
		}
	Sprite BallSprite(Ball);
	BallSprite.setPosition(ballLocation.x, ballLocation.y);
	BallWidth = BallSprite.getGlobalBounds().width;
	BallHeight = BallSprite.getGlobalBounds().height;
	BallSprite.setOrigin(16.0f, 16.0f);

	//Solid Brick
	if (!SolidBrick.loadFromFile("Assets/Solid Brick.png")) 
		{
		cout << "Error 4: Failed to load Solid Brick image" << "\n";
		system("pause");
		}
	Sprite SolidBrickSprite(SolidBrick);
	SolidBrickWidth = SolidBrickSprite.getGlobalBounds().width;
	SolidBrickHeight = SolidBrickSprite.getGlobalBounds().height;

	//Broken Brick
	if (!BrokenBrick.loadFromFile("Assets/Broken Brick.png")) 
		{
		cout << "Error 4: Failed to load Broken Brick image" << "\n";
		system("pause");
		}
	Sprite BrokenBrickSprite(BrokenBrick);

	//Sprite BallSprite(int BallColours);
	Sprite Bricks[2] = {SolidBrickSprite, BrokenBrickSprite};

	//Array
	srand(time(NULL));
	int PlayField[10][5], i, j;
	for(i = 0; i<10; i++) {
		for(j = 0; j<5; j++) {
			if(i < 3) {
				PlayField[i][j] = 3; 
			} else {
					PlayField[i][j] = 0;
		}
	}
}
		for(i = 0; i<10; i++) {
			for(j = 0; j<5; j++) {
			cout<<PlayField[i][j]<< " ";
	}
	cout<<"\n";
}
   while (window.isOpen()) //The "Game Loop"...
		{
        while (window.pollEvent(KeyboardEvent))
			{
            if (KeyboardEvent.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				{
                window.close();
				break;
				}
				else if (KeyboardEvent.type == Event::KeyPressed) //We Read The Keyboard Keys...
				{
				if (KeyboardEvent.key.code == 71) //This Is NOT The ASCII Code of The Key Pressed, But The "Enum" SFML Input Manager's Code...
					{
					if (PaddleLocation.x >= 95)
						{
						PaddleLocation.x = PaddleLocation.x - 5;
						}
					}
				if (KeyboardEvent.key.code == 72) //This Is NOT The ASCII Code of The Key Pressed, But The "Enum" SFML Input Manager's Code...
					{
					if (PaddleLocation.x <= 658)
						{
						PaddleLocation.x = PaddleLocation.x + 5;
						}
					}
				}
				PaddleSprite.setPosition(PaddleLocation.x, PaddleLocation.y);
		}
	window.clear(Color(150,150,150));
	window.draw(BackgroundImage);

		for(i=9; i>=0; i--)
		{
			for(j=0; j<5; j++)
			{
				if(PlayField[i][j] == 3) 
				{
					Sprite currentBrick(SpawnBrick (PlayField[i][j], j, i, Bricks));
					if(faceUp && BallSprite.getGlobalBounds().intersects(currentBrick.getGlobalBounds()))
					{
						//cout << "Hit brick\n";
						faceUp = false;
						PlayField[i][j] = 4;
					}
				} else if(PlayField[i][j] == 4) {
					Sprite currentBrick(SpawnBrick (PlayField[i][j], j, i, Bricks));
					if(faceUp && BallSprite.getGlobalBounds().intersects(currentBrick.getGlobalBounds()))
					{
						//cout << "Hit brick\n";
						faceUp = false;
						PlayField[i][j] = 0;
					}
				}
			}
		}
		
				if ((BallSprite.getGlobalBounds().intersects(PaddleSprite.getGlobalBounds())))  //Collision Detection for the Ball hitting the paddle...
			{
				faceUp = true;		
			}
				if(faceUp)
					{
						if (ballLocation.y < 45) 
							{
								faceUp = false;
							}	
						ballLocation.y = ballLocation.y - BallSpeed; //The "ball" Sprite Is Moving From RIGHT to LEFT...
						BallSprite.setPosition(ballLocation.x, ballLocation.y);
					} 
				else if(!faceUp) 
				{
					if (ballLocation.y >  window_CurrentDimensions.y)	
						{
							ballLocation = Vector2f (375, 235);
						}
					ballLocation.y = ballLocation.y + BallSpeed; //The "ball" Sprite Is Moving From RIGHT to LEFT...
					BallSprite.setPosition(ballLocation.x,ballLocation.y);
				}
	window.draw(PaddleSprite);
	window.draw(BallSprite);
	window.display();
}
return 0;
}


