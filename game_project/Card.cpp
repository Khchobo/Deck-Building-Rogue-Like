
#include "Card.h"
#include <stdlib.h>
#include <random>

Card::Card(BattlingCharacterType* type)
{

		assignID();
		assignName();
		std::string cardType = type->cardTypeDistribution.randomKeyFromDist();
		std::string elementType = type->cardDistributions[cardType].elementDistribution.randomKeyFromDist();

		if (elementType == "ethereal")
		{
			attackElement = AttackElement::ethereal;
		}
		else if (elementType == "corporeal")
		{
			attackElement = AttackElement::corporeal;
		}
		else if (elementType == "metaphysical")
		{
			attackElement = AttackElement::metaphysical;
		}
		else
		{
			throw std::invalid_argument("");
		}

		std::string shapeType = type->cardDistributions[cardType].shapeDistribution.randomKeyFromDist();
		std::binomial_distribution<int> radBinom(type->cardDistributions[cardType].radiusDistribution.n, type->cardDistributions[cardType].radiusDistribution.p);

		std::random_device rd;
		std::mt19937 gen(rd());
		int shapeCost;

		if (shapeType == "circle")
		{
			shapeCost = 100;
			attackType = AttackType::circle;
			attackRadius = radBinom(gen) + type->cardDistributions[cardType].radiusDistribution.shift;
		}
		else if (shapeType == "line")
		{
			shapeCost = -20;
			attackType = AttackType::line;
			attackRadius = radBinom(gen) + type->cardDistributions[cardType].radiusDistribution.shift;
		}
		else if (shapeType == "cross")
		{
			shapeCost = 30;
			attackType = AttackType::cross;
			attackRadius = radBinom(gen) + type->cardDistributions[cardType].radiusDistribution.shift;
		}

		std::binomial_distribution<int> eminationBinom(type->cardDistributions[cardType].attackEmanationSpeedDistribution.n,
			type->cardDistributions[cardType].attackEmanationSpeedDistribution.p);
		std::binomial_distribution<int> persistenceBinom(type->cardDistributions[cardType].persistenceDistribution.n,
			type->cardDistributions[cardType].persistenceDistribution.p);

		//TODO may want to adjust these values or move them to data later
		attackEmanationSpeed = (eminationBinom(gen) + type->cardDistributions[cardType].attackEmanationSpeedDistribution.shift) / 10.0f;
		persistence = (persistenceBinom(gen) + type->cardDistributions[cardType].persistenceDistribution.shift) / 60.0f;

		std::binomial_distribution<int> attackDamageBinom(type->cardDistributions[cardType].attackDamageDistribution.n,
			type->cardDistributions[cardType].attackDamageDistribution.p);

		attackDamage = attackDamageBinom(gen) + type->cardDistributions[cardType].attackDamageDistribution.shift;

		cardPointCost = (int)floor(((shapeCost + attackRadius * 7 + (attackEmanationSpeed * 3) + (persistence * 5)) / 1.5)*getRandomMutationModifier(type, cardType));

	
}

void Card::assignID()
{
	id = uniqueIdTrack;
	uniqueIdTrack++;
}

void Card::assignName()
{
	int index1 = rand() % adjectives.size();
	int index2 = rand() % nouns.size();
	name = adjectives[index1] + " " + nouns[index2];
}

float Card::getRandomMutationModifier(BattlingCharacterType* type,std::string cardType)
{
	int base =1000-type->cardDistributions[cardType].costMutationPlusMinus * 1000;
	float max = type->cardDistributions[cardType].costMutationPlusMinus * 2000+ type->cardDistributions[cardType].costMutationWeight;
	float rando = rand() % base + max;
	return rando / 1000.0f;
}

long int Card::uniqueIdTrack;