#include "ImageManager.h"

ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}

const sf::Texture& ImageManager::getImage(const std::string& filename)
{

	std::cout <<filename<< std::endl;
	
	for (std::map<std::string, sf::Texture>::const_iterator it = images.begin();
		it != images.end();
		++it)
	{
		if (filename == it->first)
		{
			std::cout << "returning " << it->first << std::endl;
			return it->second;
		}
	}
	sf::Texture image;
	if (image.loadFromFile("assets/" + filename))
		{
			std::cout << "a" <<filename<<" "<< image.getSize().x << std::endl;
			images[filename] = image;

			return images[filename];
	}

	throw ImageNotFound();
}
	

void ImageManager::deleteImage(const std::string& filename)
{
	std::map<std::string, sf::Texture>::const_iterator it = images.find(filename);
	if (it != images.end())
	{
		images.erase(it);
		return;
	}

	throw ImageNotFound();
}