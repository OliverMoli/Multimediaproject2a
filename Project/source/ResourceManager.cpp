#include "pch.h"
#include "ResourceManager.h"

ResourceManager& ResourceManager::getInstance()
{
	static ResourceManager instance;
	return instance;
}

void ResourceManager::loadTexture(std::string name,std::string fileName)
{
	if(textures.find(name)!=textures.end())
	{
		std::cout << "Careful! you are overriding the Texture Resource with name [ " << name << " ]" << std::endl;
	}
	sf::Texture value;
	if(value.loadFromFile(fileName))
	{
		textures[name] = std::make_shared<sf::Texture>(value);
	}
}

void ResourceManager::loadTextureWithTransparentColor(std::string name, std::string fileName,sf::Color transparentColor)
{
	if (textures.find(name) != textures.end())
	{
		std::cout << "Careful! you are overriding the Texture Resource with name [ " << name << " ]" << std::endl;
	}
	sf::Image image;
	if(image.loadFromFile(fileName))
	{
		image.createMaskFromColor(transparentColor);
		sf::Texture value;
		if (value.loadFromImage(image))
		{
			textures[name] = std::make_shared<sf::Texture>(value);
		}
	}

}

void ResourceManager::loadFont(std::string name,std::string fileName)
{
	if (fonts.find(name) != fonts.end())
	{
		std::cout << "Careful! you are overriding the Font Resource with name [ " << name << " ]" << std::endl;
	}
	sf::Font value;
	if (value.loadFromFile(fileName))
	{
		fonts[name] = std::make_shared<sf::Font>(value);
	}
}

void ResourceManager::loadSound(std::string name, std::string fileName)
{
	if (sounds.find(name) != sounds.end())
	{
		std::cout << "Careful! you are overriding the Sound Resource with name [ " << name << " ]" << std::endl;
	}
	sf::SoundBuffer value;
	if (value.loadFromFile(fileName))
	{
		sounds[name] = std::make_shared<sf::SoundBuffer>(value);
	}
}

void ResourceManager::freeResources()
{
	textures.clear();
	fonts.clear();
	sounds.clear();
}

std::shared_ptr<sf::Texture> ResourceManager::getTexture(std::string name)
{
	if(textures.find(name)!=textures.end())
	{
		return textures[name];
	}
	std::cout << "Careful! The TextureResource named [" << name << "] you tried to get does not exist! Returned nullptr instead";
	return nullptr;
}

std::shared_ptr<sf::Font> ResourceManager::getFont(std::string name)
{
	if (fonts.find(name) != fonts.end())
	{
		return fonts[name];
	}
	std::cout << "Careful! The FontResource named [" << name << "] you tried to get does not exist! Returned nullptr instead";
	return nullptr;
}

std::shared_ptr<sf::SoundBuffer> ResourceManager::getSound(std::string name)
{
	if (sounds.find(name) != sounds.end())
	{
		return sounds[name];
	}
	std::cout << "Careful! The Sound Resource named [" << name << "] you tried to get does not exist! Returned nullptr instead";
	return nullptr;
}


