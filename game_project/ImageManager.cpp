#include "ImageManager.h"

ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
}

const sf::Texture& ImageManager::getImage(const std::string& filename)
{
	for (std::map<std::string, sf::Texture>::const_iterator it = images.begin();
		it != images.end();
		++it)
	{
		if (filename == it->first)
		{
			return it->second;
		}

		sf::Texture image;
		if (image.loadFromFile("assets/"+filename))
		{
			images[filename] = image;
			
			return images[filename];
		}

		throw ImageNotFound();
	}
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