#include "game.h"

void Game::loop()
{
	{
		initialise();

		while (window.isOpen())
		{

			if (window.hasFocus()) {

				renderModeTimeout++;
				runTime += frameTime;
				
				
				sf::Time elapsed = clock.getElapsedTime();
				frameTime = elapsed.asSeconds();
				//std::cout << 1/frameTime << std::endl<<std::endl;
				clock.restart();


				// check all the window's events that were triggered since the last iteration of the loop
				sf::Event event;
				while (window.pollEvent(event))
				{

					switch (event.type) {
					case sf::Event::KeyPressed:
						keyboardArray[event.key.code] = true;
						break;
					case sf::Event::KeyReleased:
						keyboardArray[event.key.code] = false;
						break;
					default:
						break;
					}

					// "close requested" event: we close the window
					if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						window.close();
				}

				action();
			}
		}
	}
}

void Game::initialiseBattleMode()
{
	renderMode = 1;
	tileReductionX = 8;
	tileReductionY = 4;
	cardsInDeck.resetDeck();
	cardActionMap.reset();
	cardsInHand.initialise(cardsInDeck.cardsInDeck, cardsInDeck.cardsRemaining, windowedHeight, windowedWidth, fullscreen, tileReductionX);

	windowWidth = windowedWidth - tileReductionX;
	windowHeight = windowedHeight - tileReductionY;
}

void Game::resize()
{
	if (fullscreen == 0)
	{

		window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "SFMLtest", sf::Style::Fullscreen);

		//window.setFramerateLimit(30);
		window.setVerticalSyncEnabled(true);
		fullscreen = 1;
	}
	else
	{

		if (playerDistanceFromEdgeY > (windowedHeight - 1) * 16 * 2 - 80)
		{
			playerDistanceFromEdgeY = (windowedHeight - 1) * 16 * 2 - 80;
		}

		if (playerDistanceFromEdgeX > (windowedWidth - 1) * 16 * 2 - 80)
		{
			playerDistanceFromEdgeX = (windowedWidth - 1) * 16 * 2 - 80;
		}

		//TODO
		window.create(sf::VideoMode(windowedWidth *tileSize*pixelSize, windowedHeight *tileSize*pixelSize), "SFMLtest", sf::Style::Default);

		//window.setFramerateLimit(60);
		window.setVerticalSyncEnabled(true);
		fullscreen = 0;

	}
}

void Game::resizeVisibleField()
{
	if (fullscreen == 1)
	{
		//sets window size in tiles to desktop size
		windowWidth = sf::VideoMode::getDesktopMode().width / (tileSize*pixelSize) - tileReductionX;
		windowHeight = sf::VideoMode::getDesktopMode().height / (tileSize*pixelSize) - tileReductionY;
	}
	else
	{
		//sets window size to preset values
		windowWidth = windowedWidth - tileReductionX;
		windowHeight = windowedHeight - tileReductionY;

	}
}

void Game::action()
{

	window.clear(sf::Color::Black);
	tileMap.initiateMap();

	//toggles between fullscreen and windowed mode. the function resize executes any code on the graphics to resize them accordingly
	if (keyboardArray[sf::Keyboard::F11] && renderModeTimeout > 10)
	{
		std::cout << fullscreen;
		resize();
		resizeVisibleField();
		keyboardArray[sf::Keyboard::F11] = false;
		renderModeTimeout = 0;
	}

	windowInfo.fullscreen = fullscreen;
	windowInfo.tileReductionX = tileReductionX;
	windowInfo.tileReductionY = tileReductionY;
	windowInfo.windowedHeight = windowedHeight;
	windowInfo.windowedWidth = windowedWidth;
	windowInfo.windowHeight = windowHeight;
	windowInfo.windowWidth = windowWidth;

				
	if (keyboardArray[sf::Keyboard::F1] && renderModeTimeout > 10)
	{
		if (renderMode == 0)
		{
			initialiseBattleMode();
		}
		else if (renderMode == 1)
		{
			renderMode = 0;
			tileReductionX = 0;
			tileReductionY = 0;
		}

		resizeVisibleField();

		renderModeTimeout = 0;
	}

	
	player.action(keyboardArray, playerDistanceFromEdgeX, playerDistanceFromEdgeY, collision, windowInfo);

	//TODO get all this insidie functions
	if (renderMode == 1)
	{
		int cardIndex = 10000;

		player.cardPoints = min(static_cast<float>(player.cardPointsMax), player.cardPoints + player.cardPointRecoveryRate*frameTime);

		player.cardPointsNumber.xPos = windowWidth * pixelSize*tileSize + 4 * 32;
		player.cardPointsNumber.yPos = windowHeight * pixelSize*tileSize+3*32 ;
		player.cardPointsNumber.value = static_cast<int>(player.cardPoints);

		cardsInHand.action(keyboardArray, cardsInDeck.cardsInDeck, cardsInDeck.cardsRemaining, windowInfo, cardIndex, player.cardPoints);

		if (cardIndex != 10000)
		{
			cardActionMap.newAction(cardIndex, cardsInDeck, player.direction, player.currentXTilePos, player.currentYTilePos, collision);
		}


		cardActionMap.action(frameTime);

		tileMap.cardActionUpdateMap(cardActionMap);
	}

	draw();

	//draws everything to a texture so the shader can run on the entire screen
	sf::Texture finalImage;
	sf::Sprite sprite;
	finalImage.create(window.getSize().x, window.getSize().y);
	finalImage.update(window);
	sprite.setTexture(finalImage);
	sprite.setPosition(0, 0);

	//pass texture and runtime to shader
	fixedColourShader.setUniform("texture", finalImage);
	fixedColourShader.setUniform("runTime", runTime);

	window.draw(sprite,&fixedColourShader);
	window.display();

}

void Game::draw()
{

	sf::Texture texture;
	texture.create(mapWidth*tileSize*pixelSize, mapHeight*tileSize*pixelSize);

	tileMap.draw(texture);
	//player.draw(texture);

	sf::Sprite sprite;
	sprite.setTexture(texture);

	//TODO - case when screen size is larger than map size

		//positioning of the overall texture relative to the window
	float xPosition, yPosition;

	//determined by the players position as well as their distance from edge. however cant be further in either direction than the edge of the map
	xPosition = max(static_cast<float>(-((mapWidth - windowWidth)*static_cast<int>(tileSize)*static_cast<int>(pixelSize))), min(static_cast<float>(0), playerDistanceFromEdgeX - player.xPos));
	yPosition = max(static_cast<float>(-((mapHeight - windowHeight) * static_cast<int>(tileSize)*static_cast<int>(pixelSize))), min(static_cast<float>(0), playerDistanceFromEdgeY - player.yPos));


	if (fullscreen == 1)
	{
		int desktopWidthPixels = sf::VideoMode::getDesktopMode().width;
		int desktopHeightPixels = sf::VideoMode::getDesktopMode().height;

		//width and height of the fullscreen window measured in tiles (rounded to nearest tile)
		int desktopWidthTiles = desktopWidthPixels / (tileSize*pixelSize);
		int desktopHeightTiles = desktopHeightPixels / (tileSize*pixelSize);

		//if the fullscreen window is larger, centre it 
		if (mapWidth < desktopWidthTiles)
		{
			xPosition = (sf::VideoMode::getDesktopMode().width / 2) - (((mapWidth+tileReductionX)*static_cast<int>(tileSize)*static_cast<int>(pixelSize)) / 2);
		}
		//otherwise, position as normal (using the exact desktop pixel size rather than rounded to the nearest tile)
		else
		{
			xPosition = max(static_cast<float>(-(((mapWidth+tileReductionX)*static_cast<int>(tileSize)*static_cast<int>(pixelSize)) - desktopWidthPixels)), min(static_cast<float>(0), playerDistanceFromEdgeX - player.xPos));
		}


		if (mapHeight < desktopHeightTiles)
		{
			yPosition = (sf::VideoMode::getDesktopMode().height / 2) - ((mapHeight*static_cast<int>(tileSize)*static_cast<int>(pixelSize)) / 2);
		}
		else
		{
			yPosition = max(static_cast<float>(-(((mapHeight+tileReductionY)*static_cast<int>(tileSize)*static_cast<int>(pixelSize)) - desktopHeightPixels)), min(static_cast<float>(0), playerDistanceFromEdgeY - player.yPos));
		}
	}
	sprite.setPosition(xPosition, yPosition);

	//draw the background
	window.draw(sprite);
	player.draw(window,xPosition,yPosition);
	

	//draw cards if in battle mode
	if (renderMode == 1)
	{
		//occludes the bottom and right part of the screen
		sf::RectangleShape blackoutRectBottom(sf::Vector2f(windowWidth*pixelSize*tileSize,pixelSize*tileSize*tileReductionY));
		sf::RectangleShape blackoutRectRight(sf::Vector2f(pixelSize*tileSize*tileReductionX, (windowHeight+tileReductionY)*pixelSize*tileSize));

		//creates a line white line to delineate the bottom and right parts of screen
		sf::RectangleShape delineatingLineBottom(sf::Vector2f(windowWidth*pixelSize*tileSize, 1));
		sf::RectangleShape delineatingLineRight(sf::Vector2f(1,(windowHeight+tileReductionY+1)*pixelSize*tileSize));

		sf::RectangleShape cardPoints(sf::Vector2f((player.cardPoints/player.cardPointsMax)*6*32,16));
		cardPoints.setFillColor(sf::Color::White);

		blackoutRectBottom.setFillColor(sf::Color::Black);
		blackoutRectRight.setFillColor(sf::Color::Black);

		delineatingLineBottom.setFillColor(sf::Color::White);
		delineatingLineRight.setFillColor(sf::Color::White);

		//if fullscreen, set position according to exact distance frm edge of screen (not tile aligned)
		if (fullscreen == 1)
		{
			blackoutRectBottom.setPosition(0, (sf::VideoMode::getDesktopMode().height)-tileReductionY*pixelSize*tileSize);
			blackoutRectRight.setPosition(sf::VideoMode::getDesktopMode().width - (tileReductionX * pixelSize*tileSize), 0);

			delineatingLineBottom.setPosition(0, (sf::VideoMode::getDesktopMode().height) - tileReductionY * pixelSize*tileSize);
			delineatingLineRight.setPosition((sf::VideoMode::getDesktopMode().width) - tileReductionX * pixelSize*tileSize,0);

		}

		//if windowed, use tile alignment
		else
		{
			blackoutRectBottom.setPosition(0, windowHeight*pixelSize*tileSize);
			blackoutRectRight.setPosition(windowWidth*pixelSize*tileSize, 0);

			delineatingLineBottom.setPosition(0, windowHeight*pixelSize*tileSize);
			delineatingLineRight.setPosition(windowWidth*pixelSize*tileSize,0);

			
		}

		cardPoints.setPosition(windowWidth*pixelSize*tileSize + 1 * pixelSize*tileSize, windowHeight*pixelSize*tileSize + 96);

		//draw them to the window
		window.draw(blackoutRectBottom);
		window.draw(blackoutRectRight);

		window.draw(delineatingLineBottom);
		window.draw(delineatingLineRight);

		window.draw(cardPoints);
		
		player.cardPointsNumber.draw(window);

		cardsInHand.draw(window,cardsInDeck.cardsInDeck);

	}
	
}

void Game::initialise()
	{
		tileMap.initialise();
		initialiseBattleMode();
	}
