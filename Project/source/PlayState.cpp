#include "pch.h"
#include "PlayState.h"
#include "MapLoader.h"
#include "GameObjectFactory.h"
#include "GameObjectManager.h"
#include "PlayerControllerComponent.h"
#include "AiControllerComponent.h"


void PlayState::initialize()
{
	ResourceManager::getInstance().loadFont("arial", "../assets/arial.ttf");
	ResourceManager::getInstance().loadTextureWithTransparentColor("redOrc1", "../assets/RedPlayer1.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("redOrc2", "../assets/RedPlayer2.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("redOrc3", "../assets/RedPlayer3.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("blueOrc1", "../assets/BluePlayer1.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("blueOrc2", "../assets/BluePlayer2.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("blueOrc3", "../assets/BluePlayer3.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("flag", "../assets/Flag.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("neutralBall", "../assets/Ballneutral32.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("redBall", "../assets/Ballred32.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("blueBall", "../assets/Ballblue32.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("flagPickupBlue", "../assets/FlagPickedUpBlue.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("flagPickupRed", "../assets/FlagPickedUpRed.png", sf::Color(255, 128, 255));
	MapLoader::getInstance().loadMap("Map.tmx", sf::Vector2f(0, 0));
	GameObjectFactory::CreateScore();
	possessCharacter("Player 1", 0, Team::RedTeam);
	possessCharacter("Player 2", -1, Team::BlueTeam);
	possessCharacter("Player 3", 1, Team::RedTeam);
	possessCharacter("Player 4", -1, Team::BlueTeam);
	possessCharacter("Player 5", -1, Team::RedTeam);
	possessCharacter("Player 6", -1, Team::BlueTeam);
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

void PlayState::possessCharacter(std::string characterName, int playerIndex, Team team)
{
	auto characterObj = GameObjectManager::getInstance().GetGameObjectByName(characterName);
	characterObj->getComponent<CharacterInfoComponent>()->setTeam(team);
	characterObj->getComponent<CharacterInfoComponent>()->setPlayerIndex(playerIndex);
	if(playerIndex == -1)
	{
		characterObj->addComponent(std::make_shared<AiControllerComponent>(*characterObj));
	}else
	{
		characterObj->addComponent(std::make_shared<PlayerControllerComponent>(*characterObj));
	}
}
