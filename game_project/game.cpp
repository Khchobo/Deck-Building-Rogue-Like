#include "game.h"

const float INF = std::numeric_limits<float>::infinity();

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
				std::cout << 1/frameTime << std::endl<<std::endl;
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
	windowInfo.UIWidth = 8;
	windowInfo.UIHeight = 4;
	player.cardsInDeck.resetDeck();
	cardActionMap.reset();
	player.cardsInHand.initialise(player.cardsInDeck.cardsInDeck, player.cardsInDeck.cardsRemaining, windowInfo,player.type->identifier);

	windowInfo.setactiveSceneWidth(sf::VideoMode::getDesktopMode().width / (windowInfo.tileSize*windowInfo.pixelSize) - windowInfo.UIWidth);
	windowInfo.setactiveSceneHeight(sf::VideoMode::getDesktopMode().height / (windowInfo.tileSize*windowInfo.pixelSize) - windowInfo.UIHeight);

	player.cardPointsNumber.xPos = windowInfo.activeSceneWidthPixels + 4 * 32;
	player.cardPointsNumber.yPos = windowInfo.getWindowHeight() - 32;
}

void Game::resize()
{
	if (windowInfo.fullscreen == 0)
	{

		window.create(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "SFMLtest", sf::Style::Fullscreen);

		//window.setFramerateLimit(30);
		window.setVerticalSyncEnabled(true);
		windowInfo.fullscreen = 1;
	}
	else
	{

		if (playerDistanceFromEdgeY > windowInfo.windowedHeightPixels-windowInfo.tileSizeInPixels - 80)
		{
			playerDistanceFromEdgeY = windowInfo.windowedHeightPixels - windowInfo.tileSizeInPixels - 80;
		}

		if (playerDistanceFromEdgeX > windowInfo.windowedWidthPixels - windowInfo.tileSizeInPixels - 80)
		{
			playerDistanceFromEdgeX = windowInfo.windowedWidthPixels - windowInfo.tileSizeInPixels - 80;
		}

		
		window.create(sf::VideoMode(windowInfo.windowedWidthPixels, windowInfo.windowedHeightPixels),
						"SFMLtest", sf::Style::Default);

		//window.setFramerateLimit(60);
		window.setVerticalSyncEnabled(true);
		windowInfo.fullscreen = 0;

	}

	resizeActiveScene();
	player.resize(windowInfo);
}

void Game::resizeActiveScene()
{
	if (windowInfo.fullscreen == 1)
	{
		//sets window size in tiles to desktop size
		windowInfo.setactiveSceneWidth(sf::VideoMode::getDesktopMode().width / (windowInfo.tileSize*windowInfo.pixelSize) - windowInfo.UIWidth);
		windowInfo.setactiveSceneHeight(sf::VideoMode::getDesktopMode().height / (windowInfo.tileSize*windowInfo.pixelSize) - windowInfo.UIHeight);
	}
	else
	{
		//sets window size to preset values
		windowInfo.setactiveSceneWidth(windowInfo.windowedWidthTiles - windowInfo.UIWidth);
		windowInfo.setactiveSceneHeight(windowInfo.windowedHeightTiles - windowInfo.UIHeight);

	}
}

void Game::action()
{

	window.clear(sf::Color::Black);
	tileMap.initiateMap();

	//toggles between fullscreen and windowed mode. the function resize executes any code on the graphics to resize them accordingly
	if (keyboardArray[sf::Keyboard::F11] && renderModeTimeout > 10)
	{
		keyboardArray[sf::Keyboard::F11] = false;
		resize();
		renderModeTimeout = 0;
	}
				
	if (keyboardArray[sf::Keyboard::F1] && renderModeTimeout > 10)
	{
		if (renderMode == 0)
		{
			initialiseBattleMode();
		}
		else if (renderMode == 1)
		{
			renderMode = 0;
			windowInfo.UIWidth = 0;
			windowInfo.UIHeight = 0;
		}

		resizeActiveScene();
		renderModeTimeout = 0;
	}

	
	player.action(keyboardArray, playerDistanceFromEdgeX, playerDistanceFromEdgeY, collision, windowInfo, renderMode, cardActionMap);

	std::vector<Point> activationPoints, destructionPoints;
	cardActionMap.updateAllCardActions(frameTime, activationPoints, destructionPoints);

	//TODO only call this when the room is first loaded
	for (int i = 0; i < collision.size(); i++)
	{
		for (int j = 0; j < collision[0].size(); j++)
		{
			activePlayerActionPoints[i][j] = 0;

			if (collision[i][j] == 0)
			{
				activePlayerActionPoints[i][j] = 1;
			}
		}
	}

	//update player action points map
	for (int i = 0; i < activationPoints.size(); i++)
	{
		activePlayerActionPoints[activationPoints[i].x][activationPoints[i].y] = 1;
	}
	for (int i = 0; i < destructionPoints.size(); i++)
	{
		activePlayerActionPoints[activationPoints[i].x][activationPoints[i].y] = 0;
	}
	
	

	tileMap.cardActionUpdateMap(cardActionMap);

	//DEBUG testing pathfinding working correctly
	AStar::CoordinateList path=testEnemy.action(player.currentXTilePos, player.currentYTilePos, windowInfo, activePlayerActionPoints);
	tileMap.testDrawPath(path);

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
	texture.create(mapWidth*windowInfo.tileSize*windowInfo.pixelSize, mapHeight*windowInfo.tileSize*windowInfo.pixelSize);

	tileMap.draw(texture);
	//player.draw(texture);

	sf::Sprite sprite;
	sprite.setTexture(texture);

	//TODO - case when screen size is larger than map size

		//positioning of the overall texture relative to the window
	float xPosition, yPosition;

	//determined by the players position as well as their distance from edge. however cant be further in either direction than the edge of the map
	xPosition = max(static_cast<float>(-((mapWidth - windowInfo.activeSceneWidthTiles)*static_cast<int>(windowInfo.tileSizeInPixels))),
		min(static_cast<float>(0), playerDistanceFromEdgeX - player.xPos));
	yPosition = max(static_cast<float>(-((mapHeight - windowInfo.activeSceneHeightTiles) * static_cast<int>(windowInfo.tileSizeInPixels))),
		min(static_cast<float>(0), playerDistanceFromEdgeY - player.yPos));

	//TODO see if you can make the position definitions in this block more readable by using the new WindowInfo methods
	if (windowInfo.fullscreen == 1)
	{
		int desktopWidthPixels = sf::VideoMode::getDesktopMode().width;
		int desktopHeightPixels = sf::VideoMode::getDesktopMode().height;

		//width and height of the fullscreen window measured in tiles (rounded to nearest tile)
		int desktopWidthTiles = desktopWidthPixels / (windowInfo.tileSize*windowInfo.pixelSize);
		int desktopHeightTiles = desktopHeightPixels / (windowInfo.tileSize*windowInfo.pixelSize);

		//if the fullscreen window is larger, centre it 
		if (mapWidth < desktopWidthTiles)
		{
			xPosition = (sf::VideoMode::getDesktopMode().width / 2) - (((mapWidth+ windowInfo.UIWidth)*static_cast<int>(windowInfo.tileSizeInPixels)) / 2);
		}
		//otherwise, position as normal (using the exact desktop pixel size rather than rounded to the nearest tile)
		else
		{
			xPosition = max(static_cast<float>(-(((mapWidth+ windowInfo.UIWidth)*static_cast<int>(windowInfo.tileSizeInPixels)) - desktopWidthPixels)), min(static_cast<float>(0), playerDistanceFromEdgeX - player.xPos));
		}


		if (mapHeight < desktopHeightTiles)
		{
			yPosition = (sf::VideoMode::getDesktopMode().height / 2) - ((mapHeight*static_cast<int>(windowInfo.tileSizeInPixels)) / 2);
		}
		else
		{
			yPosition = max(static_cast<float>(-(((mapHeight+ windowInfo.UIHeight)*static_cast<int>(windowInfo.tileSizeInPixels)) - desktopHeightPixels)), min(static_cast<float>(0), playerDistanceFromEdgeY - player.yPos));
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
		sf::RectangleShape blackoutRectBottom(sf::Vector2f(windowInfo.activeSceneWidthPixels, windowInfo.tileSizeInPixels*windowInfo.UIHeight));
		sf::RectangleShape blackoutRectRight(sf::Vector2f(windowInfo.tileSizeInPixels*windowInfo.UIWidth, (windowInfo.activeSceneHeightTiles+ windowInfo.UIHeight)*windowInfo.tileSizeInPixels));

		//creates a line white line to delineate the bottom and right parts of screen
		sf::RectangleShape delineatingLineBottom(sf::Vector2f(windowInfo.activeSceneWidthPixels, 1));
		sf::RectangleShape delineatingLineRight(sf::Vector2f(1,(windowInfo.activeSceneHeightTiles+ windowInfo.UIHeight+1)*windowInfo.tileSizeInPixels));

		sf::RectangleShape cardPoints(sf::Vector2f((player.cardPoints/player.type->cardPointsMax)*6*32,16));
		cardPoints.setFillColor(sf::Color::White);

		blackoutRectBottom.setFillColor(sf::Color::Black);
		blackoutRectRight.setFillColor(sf::Color::Black);

		delineatingLineBottom.setFillColor(sf::Color::White);
		delineatingLineRight.setFillColor(sf::Color::White);

		//if fullscreen, set position according to exact distance frm edge of screen (not tile aligned)
		if (windowInfo.fullscreen == 1)
		{
			blackoutRectBottom.setPosition(0, (sf::VideoMode::getDesktopMode().height)- windowInfo.UIHeight*windowInfo.tileSizeInPixels);
			blackoutRectRight.setPosition(sf::VideoMode::getDesktopMode().width - (windowInfo.UIWidth * windowInfo.tileSizeInPixels), 0);

			delineatingLineBottom.setPosition(0, (sf::VideoMode::getDesktopMode().height) - windowInfo.UIHeight * windowInfo.tileSizeInPixels);
			delineatingLineRight.setPosition((sf::VideoMode::getDesktopMode().width) - windowInfo.UIWidth * windowInfo.tileSizeInPixels,0);

		}

		//if windowed, use tile alignment
		else
		{
			blackoutRectBottom.setPosition(0, windowInfo.activeSceneHeightPixels);
			blackoutRectRight.setPosition(windowInfo.activeSceneWidthPixels, 0);

			delineatingLineBottom.setPosition(0, windowInfo.activeSceneHeightPixels);
			delineatingLineRight.setPosition(windowInfo.activeSceneWidthPixels,0);

			
		}

		cardPoints.setPosition(windowInfo.activeSceneWidthPixels +windowInfo.tileSizeInPixels, windowInfo.getWindowHeight() - 32);
		
		//draw them to the window
		window.draw(blackoutRectBottom);
		window.draw(blackoutRectRight);

		window.draw(delineatingLineBottom);
		window.draw(delineatingLineRight);

		window.draw(cardPoints);
		
		player.cardPointsNumber.draw(window);

		player.cardsInHand.draw(window, player.cardsInDeck.cardsInDeck);

	}
	
}

void Game::initialise()
	{
		player.type->identifier = "player";
		tileMap.initialise();
		initialiseBattleMode();
	}

