#ifndef CARDSPRITE_HEADER
#define CARDSPRITE_HEADER

#include "Entity.h"
#include "WindowInfo.h"

class CardSprite : public Entity
{
public:

	//whether the card is currently undergoing an animation. 
	//if so, the position variable tracks which direction
	//it should be moving in
	bool inMotion;

	float offset = 0;

	//0 is not selected, 1 is selected. Only switches once the in motion
	//variable is set to false, so for example if inMotion is true and 
	//position is set to 0, we know the card is currently moving upwards
	int position;

	//the ID of the card in the deck
	long double id;

	CardSprite()
	{
		
		texture.loadFromFile("card2.png");
		
		sprite.setTexture(texture);
		position = 0;
		inMotion = 0;
	}

	void initialise(Entity deckSprite);

	void draw(sf::RenderWindow& window);

	void move(float frameTime, int i, WindowInfo windowInfo);


	//the location before this motion was initiated
	float previousXPos;
	float previousYPos;

private:

	//how long tile motion takes for tile based motion
	float motionTime;

	//how far the motion the player is, 0 in beginning and 1 is end.
	float motionPercentage = 0;

	//the difference in motion percentage between the last frame and this one
	float motionDifference = 0;
	
};

#endif