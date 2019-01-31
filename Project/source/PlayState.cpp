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

	ResourceManager::getInstance().loadTextureWithTransparentColor("ro1", "../assets/RedOrc1.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("ro2", "../assets/RedOrc2.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("ro3", "../assets/RedOrc3.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("bo1", "../assets/BlueOrc1.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("bo2", "../assets/BlueOrc2.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("bo3", "../assets/BlueOrc3.png", sf::Color(255, 128, 255));

	ResourceManager::getInstance().loadTextureWithTransparentColor("flag", "../assets/Flag.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("neutralBall", "../assets/Ballneutral32.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("redBall", "../assets/Ballred32.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("blueBall", "../assets/Ballblue32.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("flagPickupBlue", "../assets/FlagPickedUpBlue.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("flagPickupRed", "../assets/FlagPickedUpRed.png", sf::Color(255, 128, 255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("stunStars", "../assets/Stunstars.png", sf::Color(255,128,255));
	ResourceManager::getInstance().loadTextureWithTransparentColor("starAnimation", "../assets/StarAnimation.png", sf::Color(255, 128, 255));
	createAnimations();
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
		while (getline(setupFile, line))
		{
			std::string params[3] = { "","","" };
			std::string delimiter = ",";
			size_t pos = 0;
			int i = 0;
			while ((pos = line.find(delimiter)) != std::string::npos) {
				params[i] = line.substr(0, pos);
				line.erase(0, pos + delimiter.length());
				i++;
			}
			Team team;
			if (params[2] == "red")
			{
				team = Team::RedTeam;
			}
			else
			{
				team = Team::BlueTeam;
			}
			possessCharacter(params[0], stoi(params[1]), team);
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
	characterObj->getComponent<MovementComponent>()->initAnims(characterName);
}

void PlayState::createAnimations()
{
	createOrcAnimationHelper("bo1", "Player 2");
	createOrcAnimationHelper("bo2", "Player 4");
	createOrcAnimationHelper("bo3", "Player 6");
	createOrcAnimationHelper("ro1", "Player 1");
	createOrcAnimationHelper("ro2", "Player 3");
	createOrcAnimationHelper("ro3", "Player 5");

}

void PlayState::createOrcAnimationHelper(std::string textureName, std::string animName)
{
	Animation walkingDown;
	walkingDown.setSpriteSheet(*ResourceManager::getInstance().getTexture(textureName));
	walkingDown.addFrame(sf::IntRect(0, 0, 51, 72));
	walkingDown.addFrame(sf::IntRect(51, 0, 51, 72));
	walkingDown.addFrame(sf::IntRect(102, 0, 51, 72));
	ResourceManager::getInstance().addAnimation(animName + "WalkingDown", walkingDown);
	Animation walkingLeft;
	walkingLeft.setSpriteSheet(*ResourceManager::getInstance().getTexture(textureName));
	walkingLeft.addFrame(sf::IntRect(0, 72, 51, 72));
	walkingLeft.addFrame(sf::IntRect(51, 72, 51, 72));
	walkingLeft.addFrame(sf::IntRect(102, 72, 51, 72));
	ResourceManager::getInstance().addAnimation(animName + "WalkingLeft", walkingLeft);
	Animation walkingRight;
	walkingRight.setSpriteSheet(*ResourceManager::getInstance().getTexture(textureName));
	walkingRight.addFrame(sf::IntRect(0, 144, 51, 72));
	walkingRight.addFrame(sf::IntRect(51, 144, 51, 72));
	walkingRight.addFrame(sf::IntRect(102, 144, 51, 72));
	ResourceManager::getInstance().addAnimation(animName + "WalkingRight", walkingRight);
	Animation walkingUp;
	walkingUp.setSpriteSheet(*ResourceManager::getInstance().getTexture(textureName));
	walkingUp.addFrame(sf::IntRect(0, 0, 215, 72));
	walkingUp.addFrame(sf::IntRect(51, 0, 215, 72));
	walkingUp.addFrame(sf::IntRect(102, 0, 215, 72));
	ResourceManager::getInstance().addAnimation(animName + "WalkingUp", walkingUp);
}

void PlayState::createStarAnimationHelper(std::string textureName, std::string animName)
{
	Animation star;
	//star.
}
