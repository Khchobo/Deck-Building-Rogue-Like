#include "BattlingCharacterType.h"

BattlingCharacterType::BattlingCharacterType() {};

BattlingCharacterType::BattlingCharacterType(std::string typeName)
{

	std::string filePath = "assets/data/characters/" + typeName + "/animations/state.json";
	animationStateMachine = standaloneFunctions::loadJsonFile(filePath.c_str());

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

