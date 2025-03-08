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



	// Load tree and display on the screen
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	spriteTree.setPosition(810,0);

	// Draw bee in the screen
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);
	spriteBee.setPosition(0,800);


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

		if(!beeActive)
		{
			srand((int)time(0) * 10);
			beeSpeed = (rand() % 200) + 200;

			srand((int)time(0) * 10);
			float height = (rand() % 500) + 500;
			spriteBee.setPosition(2000,height);
			beeActive = true;
		}
		else
		{  // Bee is moving

			spriteBee.setPosition(spriteBee.getPosition().x-(beeSpeed * dt.asSeconds()),spriteBee.getPosition().y);

			if(spriteBee.getPosition().x < -100) 
			{
				beeActive = false;
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
		window .draw(spriteTree);

		// Draw the bee
		window.draw(spriteBee);

		// Show everything we just drew
		window.display();


	}

	return 0;
}


