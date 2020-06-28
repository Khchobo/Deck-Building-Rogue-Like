#pragma once
#include <unordered_map>
#include <string>

//shifted binomial distribution
struct ShiftedBinomialDist
{
	unsigned int n;
	float p;
	int shift;
};

//explict discrete distribution
struct ExplicitDiscreteDist
{
	float& operator[](std::string key)
	{
		return map[key];
	}

	std::unordered_map<std::string, float> map;
};

struct CardDists
{
	CardDists(){}

	ExplicitDiscreteDist classDistribution;
	ExplicitDiscreteDist shapeDistribution;
	ShiftedBinomialDist radiusDistribution;
	ShiftedBinomialDist attackEmanationSpeedDistribution;
	ShiftedBinomialDist persistenceDistribution;
	ShiftedBinomialDist attackDamageDistribution;
	float costMutationPlusMinus;
	float costMutationWeight;
};