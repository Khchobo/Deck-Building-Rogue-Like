#include "BattlingCharacterType.h"

BattlingCharacterType::BattlingCharacterType() {};

BattlingCharacterType::BattlingCharacterType(std::string typeName)
{
	std::ifstream file;
	Json::Value data;
	std::string temp = "assets/data/characters/" + typeName + "/data.json";
	file.open("assets/data/characters/" + typeName + "/data.json");
	if (file.fail())
	{
		std::cout << "loading file " + typeName + " failed" << std::endl;
		assert(false);
	}
	file >> data;
	cardPointsMax = data["cardPointsMax"].asFloat();
	identifier = data["identifier"].asString();
	cardPointRecoveryRate= data["cardPointRecoveryRate"].asFloat();
	motionTime= data["motionTime"].asFloat();
}

