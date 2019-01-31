#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "Animation.h"

class ResourceManager
{
public:
	static ResourceManager& getInstance();
	///loads a texture into memory and maps it to a name
	///@param name The name this should be mapped to 
	///@param fileName The fileName/path of the texture to load
	void loadTexture(std::string name, std::string fileName);
	///loads a texture with a defined transparent color into memory and maps it to name
	///@param name The name this should be mapped to 
	///@param fileName The fileName/path of the texture to load
	void loadTextureWithTransparentColor(std::string name, std::string fileName, sf::Color transparentColor);
	///loads a font into memory and maps it to a name
	///@param name The name this should be mapped to 
	///@param fileName The fileName/path of the font to load
	void loadFont(std::string name, std::string fileName);
	///loads a texture into memory and maps it to a name
	///@param name The name this should be mapped to 
	///@param fileName The fileName/path of the file to load
	void loadSound(std::string name, std::string fileName);
	void addAnimation(std::string name,Animation& anim);
	///frees all resources loaded into memory
	void freeResources();
	///@return A pointer pointing to the texture with the passed name
	std::shared_ptr<sf::Texture> getTexture(std::string name);
	///@return A pointer pointing to the font with the passed name
	std::shared_ptr<sf::Font> getFont(std::string name);
	///@return A pointer pointing to the sound with the passed name
	std::shared_ptr<sf::SoundBuffer> getSound(std::string name);
	std::shared_ptr<Animation> getAnimation(std::string name);
private:
	ResourceManager() = default;
	~ResourceManager() = default;
	ResourceManager(const ResourceManager& p) = delete;
	ResourceManager& operator=(ResourceManager const&) = delete;
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;
	std::map<std::string, std::shared_ptr<sf::Font>> fonts;
	std::map<std::string, std::shared_ptr<sf::SoundBuffer>> sounds;
	std::map<std::string, std::shared_ptr<Animation>> animations;
};
