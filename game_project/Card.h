#ifndef CARD_HEADER
#define CARD_HEADER

#include <vector>
#include "BattlingCharacterType.h"

enum class AttackType {circle, cross, line};
enum class AttackElement {ethereal,corporeal,metaphysical};


class Card
{
public:
	Card(BattlingCharacterType* type);
	long double id;
	std::string name;
	AttackType attackType;
	AttackElement attackElement;
	//max distance travelled by attack
	int attackRadius;
	//speed at which new action points are activated
	float attackEmanationSpeed;
	//How long the action points exist after being activated
	float persistence;
	float attackDamage;
	int cardPointCost;
	//Keeps track of the current most recently assigned ID
	static long int uniqueIdTrack;

private:
	//TODO move into data file
	const std::vector<std::string> adjectives = {"Flowing","Graceful","Evil","Dangerous","Beautiful",
											"Shining","Dancing","Shaky","Ghastly",
											"Mysterious","Puzzling",
											"Strange","Peculiar","Curious","Queer","Odd","Enigmatic"
											,"Inscrutable","Terrible","Horrible","Grim","Awful","Dire","Frightening","Forceful","Fickle", "Unreliable"};

	const std::vector<std::string> nouns = { "Force","Powder","Energy","Liquid","Particles","Fog","Air","Power","Trance",
										"Enchantment","Potion","Brew","Ointment","Concoction","Substance","Goo","Gem","Incantation",
	"Chant","Invocation","Conjuration","Recitation","Rune","Mixture","Exixir","Philtre","Decotion","Crystal","Matter","Haze","Spell"};

	//assigns the card a unique ID
	void assignID();
	//Pick a random name using the adjective and noun list
	void assignName();
	float getRandomMutationModifier(BattlingCharacterType* type, std::string cardType);
};

#endif