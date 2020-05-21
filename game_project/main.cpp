#include "game.h"
#include "ImageManager.h"
using namespace std;

class MapFromImage
{
public:

	MapFromImage(std::string filename) {
		sf::Image image;
		image.loadFromFile(filename);

		ofstream myfile;
		ofstream myfile2;
		myfile2.open("collision.txt");
		myfile.open("map.txt");

		myfile << "{";
		myfile2 << "{";

		for (int i = 0; i < image.getSize().y; i++)
		{
			myfile2 << "{";
			for (int j = 0; j < image.getSize().x; j++)
			{
				if (image.getPixel(j, i) == sf::Color(255, 255, 255))
				{
					myfile << "TileType::wall";
					myfile2 << "1";
				}
				else if (image.getPixel(j, i) == sf::Color(255, 0, 0)) {
					myfile << "TileType::flowers";
					myfile2 << "0";
				}
				else
				{
					myfile << "TileType::air";
					myfile2 << "0";
				}
				myfile << ",";
				if (!(j == (image.getSize().x - 1)))
				{
					myfile2 << ",";
				}
			}
			myfile2 << "},\n";
			myfile << "\n";
		}
		myfile2 << "};";
		myfile << "};";
		myfile.close();
		myfile2.close();
	}
};

ImageManager imageManager;
float frameTime;
float runTime;

int main()
{
	srand(time(NULL));

	//0 is gameplay, one for tile to text conversion, 2 for map to text conversion
	int openingMode = 0;

	int windowedWidth = 35;
	int windowedHeight = 28;

	int mapXSize = 40;
	int mapYSize = 35;

	std::vector<TileType> gameMapInfo1 =
	{ TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::air,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::wall,TileType::air,TileType::wall,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::flowers,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::air,TileType::wall,
TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,TileType::wall,
	};

	std::vector<std::vector<int>> map1Collision =
	{ {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	if (openingMode == 0)
	{
		Game game(windowedWidth, windowedHeight, gameMapInfo1, mapXSize, mapYSize, map1Collision);

		game.loop();
	}
	else if (openingMode == 1)
	{
		MapFromImage mapFromImage("map.png");
	}

	return 0;
}