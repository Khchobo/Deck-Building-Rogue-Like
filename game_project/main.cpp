#include "game.h"
#include "ImageManager.h"
using namespace std;

class MapFromImage
{
public:

	MapFromImage(std::string filename) {
		sf::Image image;
		image.loadFromFile(filename);

		stringstream map;
		stringstream collision;


		map << "[";
		collision << "[";

		for (int i = 0; i < image.getSize().y; i++)
		{
			collision << "[";
			for (int j = 0; j < image.getSize().x; j++)
			{
				if (image.getPixel(j, i) == sf::Color(255, 255, 255))
				{
					map << "1";
					collision << "1";
				}
				else if (image.getPixel(j, i) == sf::Color(255, 0, 0)) {
					map << "2";
					collision << "0";
				}
				else
				{
					map << "0";
					collision << "0";
				}
				map << ",";
				if (!(j == (image.getSize().x - 1)))
				{
					collision << ",";
				}
			}
			collision << "],\n";
			map << "\n";
		}
		collision << "]";
		map << "]";

		std::ofstream file;
		Json::Value data;
		file.open("assets/data/levels/testMap.json");
		file << "{\n\"tileTypeMap\":" << map.rdbuf() << ",\n\"collisionMap\":" << collision.rdbuf() << 
				",\n\"mapXSize\":" << image.getSize().x << ",\n\"mapYSize\":" << image.getSize().y << "}";
		file.close();
	}
};

ImageManager imageManager;
float frameTime;
float runTime;

int main()
{
	srand(time(NULL));

	
	Json::Value gameData = standaloneFunctions::loadJsonFile("assets/data/gameData.json");

	bool openInMapGenMode = gameData["openInMapGenMode"].asBool();
	int windowedWidth = 35;
	int windowedHeight = 28;

	if (openInMapGenMode == 0)
	{
		//TODO move this into an entity handler class
		std::map<std::string, BattlingCharacterType> battlingCharacterTypes;
		battlingCharacterTypes.insert(std::pair<std::string, BattlingCharacterType>("player", BattlingCharacterType("player")));

		Game game(windowedWidth, windowedHeight,battlingCharacterTypes,gameData);

		game.loop();
	}
	else if (openInMapGenMode == 1)
	{
		MapFromImage mapFromImage("assets/map.png");
	}

	return 0;
}