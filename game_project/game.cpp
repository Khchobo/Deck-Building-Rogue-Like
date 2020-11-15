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
				//std::cout << 1/frameTime << std::endl;
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
	cardActionMap.reset();
	player.initialiseBattleMode();
	std::cout << sf::VideoMode::getDesktopMode().width / (windowInfo.tileSize*windowInfo.pixelSize) - windowInfo.UIWidth << std::endl;

	windowInfo.setactiveSceneWidth(sf::VideoMode::getDesktopMode().width / (windowInfo.tileSize*windowInfo.pixelSize) - windowInfo.UIWidth);
	windowInfo.setactiveSceneHeight(sf::VideoMode::getDesktopMode().height / (windowInfo.tileSize*windowInfo.pixelSize) - windowInfo.UIHeight);
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
		
		window.create(sf::VideoMode(windowInfo.windowedWidthPixels, windowInfo.windowedHeightPixels),
						"SFMLtest", sf::Style::Default);

		//window.setFramerateLimit(60);
		window.setVerticalSyncEnabled(true);
		windowInfo.fullscreen = 0;

	}

	resizeActiveScene();
	player.resize();
	playerDistanceFromEdgeX = min(max(static_cast<float>(200), playerDistanceFromEdgeX), static_cast<float>((windowInfo.activeSceneWidthPixels - windowInfo.tileSizeInPixels) - 200));
	playerDistanceFromEdgeY = min(max(static_cast<float>(200), playerDistanceFromEdgeY), static_cast<float>((windowInfo.activeSceneHeightPixels - windowInfo.tileSizeInPixels) - 200));
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
	//tileMap.initiateMap();

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

	
	player.action(keyboardArray, playerDistanceFromEdgeX, playerDistanceFromEdgeY, collisionMap, renderMode, cardActionMap, imageManager);

	cardActionMap.updateAllCardActions(frameTime);

	tileMap.cardActionUpdateMap(cardActionMap);

	//DEBUG testing pathfinding working correctly
	
	for (auto& enemy : enemies)
	{
		enemy.action(player.currentTilePos, cardActionMap, collisionMap);
		if (gameData["debugSettings"]["drawAIPath"].asBool())
		{
			tileMap.testDrawPath(enemy.currentPath);
		}
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
	//fixedColourShader.setUniform("runTime", runTime);

	window.draw(sprite,&fixedColourShader);
	window.display();

}

void Game::draw()
{

	setBackgroundTexturePosition();

	tileMap.updateVertexMap();
	tileMap.setPosition(windowInfo.backgroundTexturePosition);
	//draw the background
	window.draw(tileMap);

	player.draw(window);

	for (auto& enemy : enemies)
	{
		enemy.draw(window);

		//draw cards if in battle mode
		if (renderMode == 1)
		{
			//occludes the bottom and right part of the screen
			sf::RectangleShape blackoutRectBottom(sf::Vector2f(static_cast<float>(windowInfo.activeSceneWidthPixels),
				static_cast<float>(windowInfo.tileSizeInPixels*windowInfo.UIHeight)
			)
			);
			sf::RectangleShape blackoutRectRight(sf::Vector2f(static_cast<float>(windowInfo.tileSizeInPixels*windowInfo.UIWidth),
				windowInfo.getWindowWidth()
			)
			);

			//creates a line white line to delineate the bottom and right parts of screen
			sf::RectangleShape delineatingLineBottom(sf::Vector2f(static_cast<float>(windowInfo.activeSceneWidthPixels), 1.0f));
			sf::RectangleShape delineatingLineRight(sf::Vector2f(1.0f, windowInfo.getWindowWidth()));

			float cardPointsPercent = player.cardPoints / player.type->cardPointsMax;
			float healthPointsPercent = player.health / player.type->maxHealth;

			sf::RectangleShape cardPointsBar(sf::Vector2f(cardPointsPercent *6.0f* windowInfo.tileSizeInPixels, windowInfo.tileSizeInPixels / 2.0f));
			cardPointsBar.setFillColor(sf::Color::White);

			sf::RectangleShape healthBar(sf::Vector2f(healthPointsPercent * 6.0f * windowInfo.tileSizeInPixels, windowInfo.tileSizeInPixels / 2.0f));
			cardPointsBar.setFillColor(sf::Color::White);

			blackoutRectBottom.setFillColor(sf::Color::Black);
			blackoutRectRight.setFillColor(sf::Color::Black);

			delineatingLineBottom.setFillColor(sf::Color::White);
			delineatingLineRight.setFillColor(sf::Color::White);

			//if fullscreen, set position according to exact distance frm edge of screen (not tile aligned)
			if (windowInfo.fullscreen == 1)
			{
				blackoutRectBottom.setPosition(0.0f, static_cast<float>((sf::VideoMode::getDesktopMode().height) - windowInfo.UIHeight*windowInfo.tileSizeInPixels));
				blackoutRectRight.setPosition(static_cast<float>(sf::VideoMode::getDesktopMode().width - (windowInfo.UIWidth * windowInfo.tileSizeInPixels)), 0.0f);

				delineatingLineBottom.setPosition(0.0f, static_cast<float>((sf::VideoMode::getDesktopMode().height) - windowInfo.UIHeight * windowInfo.tileSizeInPixels));
				delineatingLineRight.setPosition(static_cast<float>((sf::VideoMode::getDesktopMode().width) - windowInfo.UIWidth * windowInfo.tileSizeInPixels), 0.0f);

			}

			//if windowed, use tile alignment
			else
			{
				blackoutRectBottom.setPosition(0.0f, static_cast<float>(windowInfo.activeSceneHeightPixels));
				blackoutRectRight.setPosition(static_cast<float>(windowInfo.activeSceneWidthPixels), 0.0f);

				delineatingLineBottom.setPosition(0.0f, static_cast<float>(windowInfo.activeSceneHeightPixels));
				delineatingLineRight.setPosition(static_cast<float>(windowInfo.activeSceneWidthPixels), 0.0f);


			}

			cardPointsBar.setPosition(static_cast<float>(windowInfo.activeSceneWidthPixels + windowInfo.tileSizeInPixels), windowInfo.getWindowHeight() - 32.0f);
			healthBar.setPosition(static_cast<float>(windowInfo.activeSceneWidthPixels + windowInfo.tileSizeInPixels), windowInfo.getWindowHeight() - 64.0f);

			//draw them to the window
			window.draw(blackoutRectBottom);
			window.draw(blackoutRectRight);

			window.draw(delineatingLineBottom);
			window.draw(delineatingLineRight);

			window.draw(cardPointsBar);
			window.draw(healthBar);

		}

	}
}

void Game::setBackgroundTexturePosition()
{
	//positioning of the overall texture relativeto the window
	sf::Vector2f backgroundTexturePosition;

	int desktopTileOffsetX = static_cast<int>(windowInfo.getWindowWidth()) % 32;
	int desktopTileOffsetY = static_cast<int>(windowInfo.getWindowHeight()) % 32;

	//determined by the players position as well as their distance from edge. however cant be further in either direction than the edge of the map
	backgroundTexturePosition.x = max(static_cast<float>(-(mapWidth*windowInfo.tileSizeInPixels - windowInfo.activeSceneWidthPixels - desktopTileOffsetX)),
		min(static_cast<float>(0), playerDistanceFromEdgeX - player.position.x));
	backgroundTexturePosition.y = max(static_cast<float>(-(mapHeight*windowInfo.tileSizeInPixels - windowInfo.activeSceneHeightPixels - desktopTileOffsetY)),
		min(static_cast<float>(0), playerDistanceFromEdgeY - player.yPosNoOffset));
	//if the fullscreen window is larger, centre it 
	if (mapWidth*windowInfo.tileSizeInPixels < windowInfo.activeSceneWidthPixels)
	{
		backgroundTexturePosition.x = (windowInfo.getWindowWidth() / 2) - (((mapWidth + windowInfo.UIWidth)*static_cast<int>(windowInfo.tileSizeInPixels)) / 2);
	}
	if (mapHeight*windowInfo.tileSizeInPixels < windowInfo.activeSceneHeightPixels)
	{
		backgroundTexturePosition.y = (windowInfo.getWindowHeight() / 2) - ((mapHeight*static_cast<int>(windowInfo.tileSizeInPixels)) / 2);
	}

	windowInfo.backgroundTexturePosition = backgroundTexturePosition;
}

void Game::initialise()
	{
		player.type->identifier = "player";
		tileMap.initialise();
		initialiseBattleMode();
	}

void Game::loadTestMap()
{
	Json::Value mapDataJson = loadJsonFile("assets/data/levels/testMap.json");

	mapWidth = mapDataJson["mapXSize"].asInt();
	mapHeight = mapDataJson["mapYSize"].asInt();

	tileTypeMap= std::vector<TileType>(mapDataJson["tileTypeMap"].size());
	collisionMap= std::vector<std::vector<int>>(mapHeight);

	for (unsigned int i = 0; i < mapDataJson["tileTypeMap"].size(); i++)
	{
		int tileTypeID= mapDataJson["tileTypeMap"][i].asInt();
		switch (tileTypeID)
		{
		case(0):
			tileTypeMap[i] = TileType::air;
			break;
		case(1):
			tileTypeMap[i] = TileType::wall;
			break;
		case(2):
			tileTypeMap[i] = TileType::flowers;
			break;
		default:
			std::stringstream errMsg;
			std::cout << std::to_string(tileTypeID) + " is an invalid Tile ID";
			errMsg << "Invalid Tile ID";
			throw std::exception(errMsg.str().c_str());
			break;
		}
	}

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			collisionMap[i].push_back(mapDataJson["collisionMap"][i][j].asInt());
		}
	}

	tileMap = TileMap(mapWidth, mapHeight, 16, tileTypeMap, collisionMap);



}
;