#include "BattlingCharacterType.h"

BattlingCharacterType::BattlingCharacterType() {};

BattlingCharacterType::BattlingCharacterType(std::string typeName)
{

	std::string filePath = "assets/data/characters/" + typeName + "/animations/state.json";
	Json::Value transitionData = standaloneFunctions::loadJsonFile(filePath.c_str());

	assignDataToMap(transitionData);

	std::map<std::string, Dir> directionMap = { {"front",Dir::Front},{"left",Dir::Left}
											,{"right",Dir::Right} ,{"back",Dir::Back} };

	filePath = "assets/data/characters/" + typeName + "Data.json";
	Json::Value data = standaloneFunctions::loadJsonFile(filePath.c_str());

	cardPointsMax = data["cardPointsMax"].asFloat();
	identifier = data["identifier"].asString();
	cardPointRecoveryRate= data["cardPointRecoveryRate"].asFloat();
	motionTime= data["motionTime"].asFloat();
	maxHealth = data["maxHealth"].asFloat();

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

void BattlingCharacterType::assignDataToMap(Json::Value data)
{

	int animType = data["type"].asInt();

	std::shared_ptr<StateAnimation> anim;

	switch (animType)
	{
	case 0:
		//anim.reset(new SpriteAnimation);
		break;
	case 1:
		anim.reset(new SquashAnimation);
	}

	std::unordered_map<std::string, BehaviourTrigger> triggerMap =
	{ {"useCard",useCard}, {"drawCardFromDeck",drawCardFromDeck}, {"initiateMotion",initiateMotion},
	{"directionChange",directionChange }, {"destroySelf",destroySelf}, {"takeDamage",takeDamage},
	{"endMotion",endMotion}, {"triggerDeath",triggerDeath} };


	for (Json::ValueIterator itr = data["transitions"].begin(); itr != data["transitions"].end(); itr++)
	{
		animationTransitions.map.insert(std::pair<std::string, std::unordered_map<BehaviourTrigger, std::string>>(itr.key.asString(), std::unordered_map<BehaviourTrigger, std::string>()));
		for (Json::Value::ArrayIndex index = 0; index < itr->size(); index++)
		{
			animationTransitions[itr.key.asString()].insert(std::pair< BehaviourTrigger, std::string>(triggerMap[itr->operator[](index)[0].asString()], itr->operator[](index)[1].asString()));
		}
	}

}
