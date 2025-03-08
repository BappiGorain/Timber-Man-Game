#include <SFML/Graphics.hpp>

// Make code easier to type with "using namespace"
using namespace sf;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
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

	// initial value of clouds
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

	// Draw bee in the screen
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0, 800);

	// is bee active
	bool beeActive = false;

	// initial speed of the bee
	float beeSpeed = 0.0f;


	

	Clock clock;

	while (window.isOpen())
	{

		/*
		****************************************
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		/*
		****************************************
		Update the scene
		****************************************
		*/

		Time dt = clock.restart();

		if (!beeActive)
		{
			srand((int)time(0) * 10);
			beeSpeed = (rand() % 200) + 200;

			srand((int)time(0) * 10);
			float height = (rand() % 500) + 500;
			spriteBee.setPosition(2000, height);
			beeActive = true;
		}
		else
		{ // Bee is moving

			spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);

			if (spriteBee.getPosition().x < -100)
			{
				beeActive = false;
			}
		}

		if (!cloud1Active)
		{
			srand((int)time(0) * 10);
			cloud1Speed = (rand() % 100) + 200;

			srand((int)time(0) * 10);
			spriteCloud1.setPosition(-500, 0);
			cloud1Active = true;
		}
		else
		{
			spriteCloud1.setPosition(spriteCloud1.getPosition().x + cloud1Speed * dt.asSeconds(), spriteCloud1.getPosition().y);

			if (spriteCloud1.getPosition().x > 2000)
			{
				cloud1Active = false;
			}
		}

		if (!cloud2Active)
		{
			srand((int)time(0) * 50);
			cloud2Speed = (rand() % 100) + 200;

			srand((int)time(0) * 50);
			spriteCloud2.setPosition(2100, 0);
			cloud2Active = true;
		}
		else
		{
			spriteCloud2.setPosition(spriteCloud2.getPosition().x - cloud2Speed * dt.asSeconds(), spriteCloud2.getPosition().y);

			if (spriteCloud2.getPosition().x < -350)
			{
				cloud2Active = false;
			}
		}

		if (!cloud3Active)
		{
			srand((int)time(0) * 10);
			cloud3Speed = (rand() % 100) + 280;

			srand((int)time(0) * 30);
			spriteCloud3.setPosition(-600, 200);
			cloud3Active = true;
		}
		else
		{
			spriteCloud3.setPosition(spriteCloud3.getPosition().x + cloud3Speed * dt.asSeconds(), spriteCloud3.getPosition().y);

			if (spriteCloud3.getPosition().x > 2000)
			{
				cloud3Active = false;
			}
		}

		/*
		****************************************
		Draw the scene
		****************************************
		*/

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

		// Show everything we just drew
		window.display();
	}

	return 0;
}
