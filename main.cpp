#include <SFML/Graphics.hpp>
#include<sstream>
#include <iostream>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;


void updateBranches(int seed);
const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side{LEFT,RIGHT,NONE};
side branchPositions[NUM_BRANCHES];

 
int main(){
	//Video Mode Object
	VideoMode vm(1920, 1080);

	//Open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	// Create a texture to hold a graphic on the GPU
	Texture textureBackground;

	// Load a graphic into the texture
	textureBackground.loadFromFile("graphics/background.png");

	// Create a sprite
	Sprite spriteBackground;

	// Attach the texture to the sprite
	spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen
	spriteBackground.setPosition(0, 0);

	// // Random number only once
	// srand((int)time(0));

	// Create and load the cloud
	Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;

	spriteCloud1.setTexture(textureCloud);
	spriteCloud1.setPosition(0, 0);

	spriteCloud2.setTexture(textureCloud);
	spriteCloud2.setPosition(1650, 0);

	spriteCloud3.setTexture(textureCloud);
	spriteCloud3.setPosition(0, 200);

	// Initial value of clouds
	bool cloud1Active = false;
	float cloud1Speed = 0.0f;

	bool cloud2Active = false;
	float cloud2Speed = 0.0f;

	bool cloud3Active = false;
	float cloud3Speed = 0.0f;

	// Load tree and display on the screen
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810, 0);

	// Add RIP
	Texture textureRIP;
	textureRIP.loadFromFile("graphics/rip.png");
	Sprite spriteRIP;
	spriteRIP.setTexture(textureRIP);
	spriteRIP.setPosition(3000, 3000);

	// Inital Tree speed and active
	bool treeActive = false;
	float treeSpeed = 0.0f;

	// Draw bee in the screen
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);

	// Draw the player
	Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	Sprite spritePlayer;
	spritePlayer.setTexture(texturePlayer);
	// spritePlayer.setPosition(spriteTree.getPosition().x + spriteTree.getLocalBounds().width + 30 , 700);
	spritePlayer.setPosition(spriteTree.getPosition().x, 700);
	spritePlayer.setScale(-1, 1);

	// Initialy player will be at the left side
	side playerSide = side::LEFT;


	// Draw the Axe
	Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	Sprite spriteAxe;
	spriteAxe.setTexture(textureAxe);
	
	spriteAxe.setPosition(spritePlayer.getPosition().x - 140, spritePlayer.getPosition().y + 115);


	// is bee active
	bool beeActive = false;

	// initial speed of the bee
	float beeSpeed = 0.0f;


	// update the branch sprite
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");

	for(int i=0;i<NUM_BRANCHES;i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(Vector2f(-2000,-2000));
		branches[i].setOrigin(220,20);
	}


	for(int i=0;i<NUM_BRANCHES;i++)
	{
		updateBranches(i);
	}

	// bool branch1Active = false;
	// bool branch2Active = false;

	Event event;
	Clock clock;
	bool paused = true;
	int score = 0;


	// Message and Score
	Text messageText,scoreText;
	Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	messageText.setFont(font);
	scoreText.setFont(font);
	messageText.setString("Press Enter To Start !!!");
	scoreText.setString("Score: 0");
	scoreText.setCharacterSize(75);
	scoreText.setCharacterSize(100);
	messageText.setFillColor(Color::Green);
	scoreText.setFillColor(Color::Green);

	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
	messageText.setPosition(1920/2.0f,1080/2.0f);
	scoreText.setPosition(20,20);

	//TimeBar
	RectangleShape timeBar;
	float timeBarStartWidth=400;
	float timeBarHeight=80;
	timeBar.setSize(Vector2f(timeBarStartWidth,timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920/2)-timeBarStartWidth/2,980);

	Time gameTimeTotal;
	float timeRemaining=6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	bool acceptInput = false;





	while (window.isOpen())
	{
		window.pollEvent(event);

		if (Keyboard::isKeyPressed(Keyboard::Escape)){
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Return)){
			paused = false;
			score = 0;
			timeRemaining = 6.0;
			acceptInput = true;
			spriteRIP.setPosition(3000, 3000);
			spritePlayer.setPosition(spriteTree.getPosition().x, 700);
			spriteAxe.setPosition(spritePlayer.getPosition().x - 140, spritePlayer.getPosition().y + 115);
		}

		if(acceptInput)
		{
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				spritePlayer.setPosition(spriteTree.getPosition().x, 700);
				spriteAxe.setPosition(spritePlayer.getPosition().x - 140, spritePlayer.getPosition().y + 115);
				spritePlayer.setRotation(0);
				playerSide = side::LEFT;
				updateBranches(score);
				score++;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right)){
				spritePlayer.setPosition(spriteTree.getPosition().x + spriteTree.getLocalBounds().width+120, 700);
				spriteAxe.setPosition(spritePlayer.getPosition().x - 10, spritePlayer.getPosition().y );
				playerSide = side::RIGHT;
				// spritePlayer.setRotation(180);
				// spritePlayer.setOrigin(180,20);
				// spritePlayer.setScale(-1,1);
				updateBranches(score);
				score++;
			}
		}

		// if(playerSide == branchPositions[5])
		// {
		// 	messageText.setString("Player has been Squished");
		// 	acceptInput = false;
		// 	paused = true;
		// }


		if (!paused)
		{
			Time dt = clock.restart();
			// Time remaining
			timeRemaining -= dt.asSeconds();
			// TimeBar changes with respect to time
			timeBar.setSize(Vector2f(timeBarWidthPerSecond*timeRemaining,timeBarHeight));  


			// when time remainaing is 0 then the game will automatically paused
			if(timeRemaining <= 0.0f)
			{
				paused = true;
				messageText.setString("out of time!!!");

				FloatRect textRext  = messageText.getLocalBounds();
				messageText.setOrigin(textRext.left + textRext.width/2.0f,textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920/2.0f,1080/2.0f);
				
				spritePlayer.setPosition(3000,3000); 
				spriteAxe.setPosition(3000,3000);
				spriteRIP.setPosition(660, 700);

				acceptInput = false;
			}
			
			

			

			if (!beeActive){
				srand((int)time(0) * 10);
				beeSpeed = (rand() % 200) + 200;

				srand((int)time(0) * 10);
				float height = (rand() % 500) + 500;
				spriteBee.setPosition(2000, height);
				beeActive = true;
			}
			else{ // Bee is moving
			
				spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);

				if (spriteBee.getPosition().x < -100){
					beeActive = false;
				}
			}

			if (!cloud1Active){
				srand((int)time(0) * 10);
				cloud1Speed = (rand() % 100) + 200;

				srand((int)time(0) * 10);
				spriteCloud1.setPosition(-500, 0);
				cloud1Active = true;
			}
			else{
				spriteCloud1.setPosition(spriteCloud1.getPosition().x + cloud1Speed * dt.asSeconds(), spriteCloud1.getPosition().y);

				if (spriteCloud1.getPosition().x > 2000){
					cloud1Active = false;
				}
			}

			if (!cloud2Active){
				srand((int)time(0) * 50);
				cloud2Speed = (rand() % 100) + 200;

				srand((int)time(0) * 50);
				spriteCloud2.setPosition(2100, 0);
				cloud2Active = true;
			}
			else{
				spriteCloud2.setPosition(spriteCloud2.getPosition().x - cloud2Speed * dt.asSeconds(), spriteCloud2.getPosition().y);

				if (spriteCloud2.getPosition().x < -350){
					cloud2Active = false;
				}
			}

			if (!cloud3Active){
				srand((int)time(0) * 10);
				cloud3Speed = (rand() % 100) + 280;

				srand((int)time(0) * 30);
				spriteCloud3.setPosition(-600, 200);
				cloud3Active = true;
			}
			else{
				spriteCloud3.setPosition(spriteCloud3.getPosition().x + cloud3Speed * dt.asSeconds(), spriteCloud3.getPosition().y);

				if (spriteCloud3.getPosition().x > 2000){
					cloud3Active = false;
				}
			}

			stringstream ss;
			ss << "Score : " << score;
			scoreText.setString(ss.str());

			for (int i = 0; i < NUM_BRANCHES; i++)
			{

				float height = i * 150;

				if (branchPositions[i] == side::LEFT)
				{
					// Move the sprite to the left side
					branches[i].setPosition(610, height);
					// Flip the sprite round the other way
					branches[i].setOrigin(220,40);
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					// Move the sprite to the right side
					branches[i].setPosition(1330, height);
					// Set the sprite rotation to normal
					branches[i].setRotation(0);

				}
				else
				{
					// Hide the branch
					branches[i].setPosition(3000, height);
				}
			}
		}

		// Clear everything from the last frame
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Draw the tree
		window.draw(spriteTree);

		// Draw the bee
		window.draw(spriteBee);

		// Draw clouds
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		// Draw the branch
		// window.draw(spriteBranch1);
		// window.draw(spriteBranch2);


		// Draw all Branches
		for(int i=0;i<NUM_BRANCHES;i++)
		{
			window.draw(branches[i]);
		}

		// Draw the player
		window.draw(spritePlayer);

		// Draw RIP
		window.draw(spriteRIP);

		

		// Draw the Axe
		window.draw(spriteAxe);

		// Draw the scoreText
		window.draw(scoreText);

		//Draw the timeBar
		window.draw(timeBar);

		if(paused){
			window.draw(messageText);
		}
		// Show everything we just drew
		window.display();
	}

	return 0;
}


void updateBranches(int seed)
{
	for(int j=NUM_BRANCHES-1;j>0;j--)
	{
		branchPositions[j] = branchPositions[j-1];
	}

	//spwan new Branches at position 0

	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r)
	{
		case 0:
			branchPositions[0] = side::LEFT;
			break;
		
		case 1:
			branchPositions[0] = side::RIGHT;
			break;
		default:
			branchPositions[0] = side::NONE;
			break;
	}
}