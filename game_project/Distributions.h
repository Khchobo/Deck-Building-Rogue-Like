#pragma once
#include <unordered_map>
#include <string>

//shifted binomial distribution
struct ShiftedBinom
{
	unsigned int n;
	unsigned int p;
	int shift;
};

//explict discrete distribution
struct ExpDiscDist
{
	float& operator[](std::string key)
	{
		return map[key];
	}

	std::unordered_map<std::string, float> map;
};

struct CardDists
{
	ExpDiscDist classDistribution;
	ExpDiscDist shapeDistribution;
	ShiftedBinom radiusDistribution;
	ShiftedBinom attackEmanationSpeedDistribution;
	ShiftedBinom persistenceDistribution;
	ShiftedBinom attackDamageDistribution;
	float costMutationPlusMinus;
	float costMutationWeight;
};