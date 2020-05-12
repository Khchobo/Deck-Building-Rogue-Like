#include "game.h"

using namespace std;

class Tile : public sf::Drawable
{
public:

	std::vector<int> pixelColourMapOld;
	std::vector<std::vector<int>> pixelColourMap;

	//constructor
	Tile() {}

	//Create vertex array of size large enough depending on tileSize
	Tile(unsigned int tileSize) : quads(sf::Quads, tileSize*tileSize * 4), tileSize(tileSize)
	{
	}

	//Set vertex positions for this tile
	//TODO remove flag, unused
	void setVertexPositions(sf::Vector2u relativeLocation, unsigned int pixelSize, bool flag)
	{
		//Over each pixel


		for (unsigned int i = 0; i < tileSize*tileSize; i++)
		{
			/*
				//Determins which x and y we are on based on i value
				int xPos = i % tileSize;
				int yPos = floor(i / static_cast<float>(tileSize));



					quads[4 * i].position = sf::Vector2f(relativeLocation.x + xPos * pixelSize, relativeLocation.y + yPos * pixelSize);
					quads[4 * i + 1].position = sf::Vector2f(relativeLocation.x + xPos * pixelSize + pixelSize, relativeLocation.y + yPos * pixelSize);
					quads[4 * i + 3].position = sf::Vector2f(relativeLocation.x + xPos * pixelSize, relativeLocation.y + yPos * pixelSize + pixelSize);
					quads[4 * i + 2].position = sf::Vector2f(relativeLocation.x + xPos * pixelSize + pixelSize, relativeLocation.y + yPos * pixelSize + pixelSize);

				*/
		}

	}

	void setVertexColour(sf::Vector2u relativeLocation, unsigned int pixelSize)
	{
		for (unsigned int i = 0; i < tileSize*tileSize; i++)
		{
			if (pixelColourMapOld[i] == 1)
			{
				int xPos = i % tileSize;
				int yPos = i / tileSize;



				quads[4 * i].position = sf::Vector2f(relativeLocation.x + xPos * pixelSize, relativeLocation.y + yPos * pixelSize);
				quads[4 * i + 1].position = sf::Vector2f(relativeLocation.x + xPos * pixelSize + pixelSize, relativeLocation.y + yPos * pixelSize);
				quads[4 * i + 3].position = sf::Vector2f(relativeLocation.x + xPos * pixelSize, relativeLocation.y + yPos * pixelSize + pixelSize);
				quads[4 * i + 2].position = sf::Vector2f(relativeLocation.x + xPos * pixelSize + pixelSize, relativeLocation.y + yPos * pixelSize + pixelSize);
			}

		}
	}

	void setVertexColourNew()
	{
		for (unsigned int i = 0; i < tileSize*tileSize * 4; i++)
		{
			quads[i].color = sf::Color::Black;
		}

		for (unsigned int i = 0; i < pixelColourMap.size(); i++)
		{
			quads[4 * pixelColourMap[i][0]].color = sf::Color(pixelColourMap[i][1], pixelColourMap[i][2], pixelColourMap[i][3]);
			quads[4 * pixelColourMap[i][0] + 1].color = sf::Color(pixelColourMap[i][1], pixelColourMap[i][2], pixelColourMap[i][3]);
			quads[4 * pixelColourMap[i][0] + 2].color = sf::Color(pixelColourMap[i][1], pixelColourMap[i][2], pixelColourMap[i][3]);
			quads[4 * pixelColourMap[i][0] + 3].color = sf::Color(pixelColourMap[i][1], pixelColourMap[i][2], pixelColourMap[i][3]);


		}
	}

private:

	bool test()
	{
		return 1;
	}



	sf::VertexArray quads;
	unsigned int tileSize;
	//TODO ONLY DRAW IF NONBLACK
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(quads);
	}

};

struct PixelColourMapsOld
{


	const std::vector<int> tic_tac =
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0,
0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,
0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};
};

void ArrayFromImageMethod2(std::string filename)
{
	sf::Image image;
	image.loadFromFile(filename + ".png");

	ofstream myfile;
	myfile.open(filename + ".txt");

	myfile << "{";

	int count = 0;
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			if (image.getPixel(j, i) != sf::Color(0, 0, 0))
			{
				myfile << "{" << count << "," << (int)image.getPixel(j, i).r
					<< "," << (int)image.getPixel(j, i).g << "," << (int)image.getPixel(j, i).b << "},";

			}
			count++;
		}

	}
	myfile << "};";
	myfile.close();
}

class ArrayFromImageMethod1
{
public:
	ArrayFromImageMethod1(std::string filename)
	{
		//sf::RenderWindow window;
		//window.create(sf::VideoMode(16,16), "ArrayFromImage", sf::Style::Default);
		sf::Image image;
		image.loadFromFile(filename);

		ofstream myfile;
		myfile.open("example.txt");

		myfile << "{";

		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (image.getPixel(j, i) == sf::Color(255, 255, 255))
				{
					myfile << "1";
				}
				else {
					myfile << "0";
				}
				myfile << ",";
			}

			myfile << "\n";
		}
		myfile << "};";
		myfile.close();
	}


};

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

int main()
{
	srand(time(NULL));

	

	//0 is gameplay, one for tile to text conversion, 2 for map to text conversion
	int openingMode = 0;

	int windowedWidth = 35;
	int windowedHeight = 28;

	int mapXSize = 40;
	int mapYSize = 35;

	//std::vector<TileType> gameMapInfo(xSize*ySize, TileType::wall);

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

		/*
		for(int i=0;i<100;i++)
		{
			cout.precision(200);
			long double numb = 1;
			for (int j = 0; j < 10; j++)
			{
				numb = numb * static_cast<long double>(rand());
			}
			std::cout << numb << std::endl;
		}
		*/
		game.loop();
	}
	else if (openingMode == 1)
	{
		ArrayFromImageMethod2("tic_tac");
		ArrayFromImageMethod2("rock_0");
		ArrayFromImageMethod2("air_0");
		ArrayFromImageMethod2("flowers_0");
	}
	else if (openingMode == 2)
	{
		MapFromImage mapFromImage("map.png");
	}

	return 0;
}