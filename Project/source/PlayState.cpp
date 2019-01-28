#include "pch.h"
#include "PlayState.h"
#include "MapLoader.h"

void PlayState::initialize()
{
	ResourceManager::getInstance().loadTextureWithTransparentColor("redOrc1", "../assets/RedPlayer1.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("redOrc2", "../assets/RedPlayer2.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("redOrc3", "../assets/RedPlayer3.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("blueOrc1", "../assets/BluePlayer1.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("blueOrc2", "../assets/BluePlayer2.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("blueOrc3", "../assets/BluePlayer3.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("flag", "../assets/Flag.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("ball", "../assets/Ball32.png", sf::Color(255, 128, 255));
	MapLoader::getInstance().loadMap("Map.tmx", sf::Vector2f(0, 0));

}

void PlayState::update(float deltaTime)
{
	GameState::update(deltaTime);
}

void PlayState::render(sf::RenderWindow & window)
{
	GameState::render(window);
}

void PlayState::exit()
{
	GameState::exit();
}
