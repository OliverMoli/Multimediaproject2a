#include "pch.h"
#include "PlayState.h"
#include "MapLoader.h"
#include "GameObjectFactory.h"
#include "GameObjectManager.h"
#include "PlayerControllerComponent.h"
#include "AiControllerComponent.h"
#include "fstream"


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
	ResourceManager::getInstance().loadTextureWithTransparentColor("stunStars", "../assets/Stunstars.png", sf::Color(255,128,255));
	MapLoader::getInstance().loadMap("Map.tmx", sf::Vector2f(0, 0));
	GameObjectFactory::CreateScore();
	loadSetup();
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

void PlayState::loadSetup()
{
	ifstream setupFile;
	setupFile.open("../assets/setup.txt");
	string output;
	if (setupFile.is_open()) {
		std::string line;
		while (getline(setupFile, line) )
		{
			std::string params[3] = {"","",""};
			std::string delimiter = ",";
			size_t pos = 0;
			int i = 0;
			while ((pos = line.find(delimiter)) != std::string::npos) {
				params[i] = line.substr(0, pos);
				std::cout << params[i] << std::endl;
				line.erase(0, pos + delimiter.length());
				i++;
			}
			Team team;
			if(params[2] == "red")
			{
				team = Team::RedTeam;
			}else
			{
				team = Team::BlueTeam;
			}
			possessCharacter(params[0], stoi(params[1]),team );
		}
	}
	setupFile.close();

}

void PlayState::possessCharacter(std::string characterName, int playerIndex, Team team)
{
	auto characterObj = GameObjectManager::getInstance().GetGameObjectByName(characterName);
	characterObj->getComponent<CharacterInfoComponent>()->setTeam(team);
	characterObj->getComponent<CharacterInfoComponent>()->setPlayerIndex(playerIndex);
	if (playerIndex == -1)
	{
		characterObj->addComponent(std::make_shared<AiControllerComponent>(*characterObj));
	}
	else
	{
		characterObj->addComponent(std::make_shared<PlayerControllerComponent>(*characterObj));
	}
}
