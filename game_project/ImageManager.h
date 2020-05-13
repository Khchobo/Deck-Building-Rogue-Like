#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include <map>

class ImageManager
{
public:
	ImageManager();
	~ImageManager();

	const sf::Texture& getImage(const std::string& filename);

	void deleteImage(const std::string& filename);
private:
	std::map<std::string, sf::Texture> images;
};

struct ImageNotFound : public std::exception
{
	const char * what() const throw ()
	{
		return "Could not find the image in the file";
	}
};