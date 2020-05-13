#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <thread>
#include <assert.h>
#include <time.h>
#include "CardsInHand.h"
#include "WindowInfo.h"
#include "NumberEntity.h"
#include "globalVariables.h"
using namespace std;

class Player : public Entity
{
public:

	Player(unsigned int pixelSize, unsigned int tileSize) :  pixelSize(pixelSize), tileSize(tileSize)
	{
		texture.loadFromFile("assets/tic_tac.png");

		currentXTilePos = 2;
		currentYTilePos = 2;

		xPos = currentXTilePos * pixelSize*tileSize;
		yPos = currentYTilePos * pixelSize*tileSize;

	}

	void action(std::map<int, bool> keyboardArray, float& playerDistanceFromEdgeX, float& playerDistanceFromEdgeY,
		std::vector<std::vector<int>>& collision, WindowInfo windowInfo);

	void move(unsigned int direction, float& playerDistanceFromEdgeX,
		float& playerDistanceFromEdgeY, std::vector<std::vector<int>>& collision, WindowInfo windowInfo);

	void draw(sf::RenderWindow& window, float backgroundXPos, float backgroundYPos);

	//direction player is facing, 0 is up and then proceed counter clockwise
	int direction;

	//current tile alignment or tile alignment before current motion began
	int currentXTilePos;
	int currentYTilePos;

	float cardPoints=50;
	float cardPointsMax=200;
	float cardPointRecoveryRate=12.5; //in points per second

	NumberEntity cardPointsNumber;

private:

	int cardPointsStepCost = 5;

	//0 for classic continuous movement (unused), 1 for new discrete jumping
	unsigned int movementMode=1;
	
	unsigned int pixelSize;
	unsigned int tileSize;

	//movement speed for continuous motion
	const float speed = 400;

	int futureXTilePos;
	int futureYTilePos;

	//for discrete motion, determines whether a motion animation is already occurring
	bool inMotion = false;
	//how far the motion the player is, 0 in beginning and 1 is end.
	float motionPercentage;
	//how long tile motion takes for tile based motion
	float motionTime = 0.1;
};