#pragma once
#include <unordered_map>
#include <string>
#include <random>

//shifted binomial distribution
struct ShiftedBinomialDist
{
	unsigned int n;
	float p;
	int shift;
};

//explict discrete distribution
class ExplicitDiscreteDist
{
public:
	float& operator[](std::string key)
	{
		return map[key];
	}

	std::map<std::string, float> map;

	std::string randomKeyFromDist()
	{
		//TODO theres a way to do this in logn time but I'm too lazy right now

		std::uniform_real_distribution<float> uniform(0.0,1.0);
		std::random_device rd;
		std::mt19937 gen(rd());
		float random = uniform(gen);

		float sum = 0;
		int index = 0;
		for (std::map<std::string,float>::iterator it=map.begin();it!=map.end();it++)
		{
			sum += it->second;
			if (random <= sum)
			{
				return it->first;

			}


		}
	}
};

struct CardDists
{
	CardDists(){}

	ExplicitDiscreteDist elementDistribution;
	ExplicitDiscreteDist shapeDistribution;
	ShiftedBinomialDist radiusDistribution;
	ShiftedBinomialDist attackEmanationSpeedDistribution;
	ShiftedBinomialDist persistenceDistribution;
	ShiftedBinomialDist attackDamageDistribution;
	int costMutationPlusMinus;
	int costMutationWeight;
};