#include "BattlingCharacterType.h"
#include <filesystem>

BattlingCharacterType::BattlingCharacterType() {};

BattlingCharacterType::BattlingCharacterType(std::string typeName)
{

	loadAnimationData(typeName);

	std::map<std::string, Dir> directionMap = { {"front",Dir::Front},{"left",Dir::Left}
											,{"right",Dir::Right} ,{"back",Dir::Back} };

	std::string filePath = "assets/data/characters/" + typeName + "/"+typeName+"Data.json";
	Json::Value data = standaloneFunctions::loadJsonFile(filePath.c_str());

	cardPointsMax = data["cardPointsMax"].asFloat();
	identifier = data["identifier"].asString();
	cardPointRecoveryRate= data["cardPointRecoveryRate"].asFloat();
	motionTime= data["motionTime"].asFloat();
	maxHealth = data["maxHealth"].asFloat();

	//ensures the characterType field is a valid value
	if (data["characterType"].asString() == "enemy")
	{
		characterType = CharType::enemy;
	}
	else if (data["characterType"].asString() == "player")
	{
		characterType = CharType::player;
	}
	else {
		std::cout << ("character type " + data["characterType"].asString() + " in " + identifier + "is invalid");
		throw std::invalid_argument("");
	}

	loadCardDistributions(data);

	//data for enemy ai only
	if (data["characterType"].asString() == "enemy")
	{
		movementTimeoutChase = data["movementTimeoutChase"].asFloat();
		cardPointConservation = data["cardPointConservation"].asFloat();
		attackVisionRadius = data["attackVisionRadius"].asInt();
		movementTimeoutFlee = data["movementTimeoutFlee"].asFloat();
		targetDirection = directionMap[data["targetDirection"].asString()];
		targetDistance = data["targetDistance"].asInt();

	}

}

void BattlingCharacterType::loadAnimationData(std::string typeName)
{
	std::unordered_map<std::string, BehaviourTrigger> triggerMap =

	{ {"useCard",useCard}, {"drawCardFromDeck",drawCardFromDeck}, {"initiateMotion",initiateMotion},
	{"directionChange",directionChange }, {"destroySelf",destroySelf}, {"takeDamage",takeDamage},
	{"endMotion",endMotion}, {"triggerDeath",triggerDeath},{"defaultAnimation",defaultAnimation } };

	std::string filePath = "assets/data/characters/" + typeName + "/animations/states.json";
	Json::Value transitionData = standaloneFunctions::loadJsonFile(filePath.c_str());

	assignTransitionDataToMap(transitionData,triggerMap);

	for (auto& p : std::filesystem::directory_iterator("assets/data/characters/" + typeName + "/animations") )
	{
		if (p.path().filename().u8string() == "states.json")
		{
			continue;
		}

		Json::Value animData = standaloneFunctions::loadJsonFile(p.path().u8string().c_str());

		int animType = animData["type"].asInt();
		std::shared_ptr<StateAnimation> anim;

		switch (animType)
		{
		case 0:
			//anim.reset(new SpriteAnimation); TODO
			break;
		case 1:
			anim.reset(new SquashAnimation);
			anim->name = animData["name"].asString();
			for (Json::Value::ArrayIndex index = 0; index < animData["keyframes"].size(); index++)
			{
				anim->keyframes.push_back(Keyframe(
					animData["keyframes"][index][0].asFloat(),
					sf::Vector2f(animData["keyframes"][index][1].asFloat(),
						animData["keyframes"][index][2].asFloat())
				)
				);

				if (animData["keyframes"][index][3].isMember("repeat"))
				{
					anim->keyframes[index].repeatTrigger = animData["keyframes"][index][3]["repeat"].asFloat();
				}

				if (animData["keyframes"][index][3].isMember("trigger"))
				{
					std::string behaviourTriggerName = animData["keyframes"][index][3]["trigger"].asString();
					anim->keyframes[index].behaviourTrigger = triggerMap[behaviourTriggerName];
				}
			}
		}

		animationMap[anim->name] = anim;

	}

}

void BattlingCharacterType::assignTransitionDataToMap(Json::Value data, std::unordered_map<std::string, BehaviourTrigger>& triggerMap)
{

	for (Json::ValueIterator itr = data["transitions"].begin(); itr != data["transitions"].end(); itr++)
	{

		animationTransitions.map[itr.name()] = std::map<BehaviourTrigger, std::string>();
		for (Json::Value::ArrayIndex index = 0; index < itr->size(); index++)
		{
			animationTransitions[itr.name()].insert(std::pair< BehaviourTrigger, std::string>
														(triggerMap[itr->operator[](index)[0].asString()],
														 itr->operator[](index)[1].asString())
												   );
		}
	}

}

void BattlingCharacterType::loadCardDistributions(Json::Value data)
{
	//just a rename for ease of reading and writing
	Json::Value& cardData = data["cards"];

	deckSize = cardData["deckSize"].asInt();
	maxHandSize = cardData["maxHandSize"].asInt();

	//assign the card type distribution to its variable
	for (Json::ValueIterator itr = cardData["typeDistribution"].begin(); itr != cardData["typeDistribution"].end(); itr++)
	{
		cardTypeDistribution[itr.name()]=itr->asFloat();
	}

	
	for (Json::ValueIterator itr = cardData["typeData"].begin(); itr != cardData["typeData"].end(); itr++)
	{
		cardDistributions[itr.name()]=CardDists();

		//TODO there is probably a nicer way of doing this
		cardDistributions[itr.name()].elementDistribution["ethereal"] = itr->operator[]("elementDistribution")["ethereal"].asFloat();
		cardDistributions[itr.name()].elementDistribution["corporeal"] = itr->operator[]("elementDistribution")["corporeal"].asFloat();
		cardDistributions[itr.name()].elementDistribution["metaphysical"] = itr->operator[]("elementDistribution")["metaphysical"].asFloat();

		cardDistributions[itr.name()].shapeDistribution["line"] = itr->operator[]("shapeDistribution")["line"].asFloat();
		cardDistributions[itr.name()].shapeDistribution["cross"] = itr->operator[]("shapeDistribution")["cross"].asFloat();
		cardDistributions[itr.name()].shapeDistribution["circle"] = itr->operator[]("shapeDistribution")["circle"].asFloat();

		cardDistributions[itr.name()].radiusDistribution.n = itr->operator[]("radiusDistribution")["n"].asInt();
		cardDistributions[itr.name()].radiusDistribution.p = itr->operator[]("radiusDistribution")["p"].asFloat();
		cardDistributions[itr.name()].radiusDistribution.shift = itr->operator[]("radiusDistribution")["shift"].asInt();

		cardDistributions[itr.name()].attackEmanationSpeedDistribution.n = itr->operator[]("attackEmanationSpeedDistribution")["n"].asInt();
		cardDistributions[itr.name()].attackEmanationSpeedDistribution.p = itr->operator[]("attackEmanationSpeedDistribution")["p"].asFloat();
		cardDistributions[itr.name()].attackEmanationSpeedDistribution.shift = itr->operator[]("attackEmanationSpeedDistribution")["shift"].asInt();

		cardDistributions[itr.name()].persistenceDistribution.n = itr->operator[]("persistenceDistribution")["n"].asInt();
		cardDistributions[itr.name()].persistenceDistribution.p = itr->operator[]("persistenceDistribution")["p"].asFloat();
		cardDistributions[itr.name()].persistenceDistribution.shift = itr->operator[]("persistenceDistribution")["shift"].asInt();

		cardDistributions[itr.name()].attackDamageDistribution.n = itr->operator[]("attackDamageDistribution")["n"].asInt();
		cardDistributions[itr.name()].attackDamageDistribution.p = itr->operator[]("attackDamageDistribution")["p"].asFloat();
		cardDistributions[itr.name()].attackDamageDistribution.shift = itr->operator[]("attackDamageDistribution")["shift"].asInt();

		cardDistributions[itr.name()].costMutationPlusMinus = itr->operator[]("costMutationDistribution")["plusMinus"].asInt();
		cardDistributions[itr.name()].costMutationWeight = itr->operator[]("costMutationDistribution")["weight"].asInt();
	}

}