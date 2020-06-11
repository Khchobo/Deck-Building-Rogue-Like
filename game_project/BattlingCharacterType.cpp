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
	{"endMotion",endMotion}, {"triggerDeath",triggerDeath} };

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
