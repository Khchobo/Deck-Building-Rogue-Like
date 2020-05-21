
#include "Card.h"
#include <stdlib.h>
#include <random>

Card::Card()
{
	id = 1;
	for (int i = 0; i < 11; i++) {
		id *= static_cast<long double>(rand());
	}
	while (id>(1*pow(10,40)))
	{
		id /= 10;
	}

	int index1 = rand() % adjectives.size();
    int index2 = rand() % nouns.size();
	name = adjectives[index1] + " " + nouns[index2];

	// chooses a shape at random and assigns a relevant cost

	std::random_device rd;
	std::mt19937 gen(rd());

	std::binomial_distribution<int> d(8, 0.65);

	int rando = rand() % 3;

	switch (rando) 
	{
	case(0):
		attackElement = AttackElement::ethereal;
		break;
	case(1):
		attackElement = AttackElement::physical;
		break;
	case(2):
		attackElement = AttackElement::psychic;
		break;
	}

	rando = rand() % 3;
	//rando = 1;

	int shapeCost;

	switch (rando)
	{
	case(0):
		shapeCost = 100;
		attackType = AttackType::circle;
		attackRadius = d(gen) +2;
		break;
	case(1):
		shapeCost = -20;
		attackType = AttackType::line;
		attackRadius = d(gen) + 2;
		break;
	case(2):
		shapeCost = 30;
		attackType = AttackType::cross;
		attackRadius = d(gen) + 2;
		break;
	}

	
	std::binomial_distribution<int> e(40, 0.5);
	std::binomial_distribution<int> f(80, 0.5);

	attackEmanationSpeed = e(gen)/10.0;
	persistence = f(gen) / 60.0;

	//assigns a cost
	//random percentage change in cost. defaults at +-10%. TODO implement ability to change this with luck and mutation chance stats
	rando = rand() % 200 + 900;
	float mutationMod =rando/1000.0;
	cardPointCost = floor(((shapeCost + attackRadius*7 + (attackEmanationSpeed * 3) + (persistence * 5))/1.5)*mutationMod);
}

