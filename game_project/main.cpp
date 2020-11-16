#include "game.h"
#include "ImageManager.h"
#include <filesystem>

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

		for (unsigned int i = 0; i < image.getSize().y; i++)
		{
			collision << "[";
			for (unsigned int j = 0; j < image.getSize().x; j++)
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

float frameTime;
float runTime=0;
WindowInfo windowInfo=WindowInfo();

int main()
{
	srand((unsigned int)time(NULL));

	ImageManager imageManager;
	
	Json::Value gameData = standaloneFunctions::loadJsonFile("assets/data/gameData.json");

	windowInfo.fullscreen = gameData["fullscreen"].asBool();

	bool openInMapGenMode = gameData["openInMapGenMode"].asBool();
	int windowedWidth = 35;
	int windowedHeight = 28;

	windowInfo.setWindowedWidth(windowedWidth);
	windowInfo.setWindowedHeight(windowedHeight);

	windowInfo.UIWidth = 8;
	windowInfo.UIHeight = 4;

	if (openInMapGenMode == 0)
	{
		//TODO move this into an entity handler class
		std::map<std::string, BattlingCharacterType> battlingCharacterTypes;

		//iterate over each enemy and load its data from the folder into the BattlingCharacterType object
		for (auto& p : std::filesystem::directory_iterator("assets/data/characters"))
		{
			std::string fileName = p.path().u8string().erase(0, 23);

			std::cout << fileName << std::endl;

			battlingCharacterTypes.insert(std::pair<std::string, BattlingCharacterType>(fileName, BattlingCharacterType(fileName)));

		}

		Game game(windowedWidth, windowedHeight,battlingCharacterTypes,gameData, &imageManager);

		game.loop();
	}
	else if (openInMapGenMode == 1)
	{
		MapFromImage mapFromImage("assets/map.png");
	}

	return 0;
}