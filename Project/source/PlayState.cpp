#include "pch.h"
#include "PlayState.h"
#include "MapLoader.h"
#include "GameObjectFactory.h"
#include "GameObjectManager.h"
#include "PlayerControllerComponent.h"
#include "AiControllerComponent.h"
#include "fstream"
#include "GameStateManager.h"
#include "SpriteRenderComponent.h"
#include "SetupState.h"


void PlayState::initialize()
{
	ResourceManager::getInstance().loadFont("arial", "../assets/arial.ttf");
	ResourceManager::getInstance().loadFont("pixelFont", "../assets/Minimal5x7.ttf");
	ResourceManager::getInstance().loadTexture("redOrc1", "../assets/RedPlayer1.png");
	ResourceManager::getInstance().loadTexture("redOrc2", "../assets/RedPlayer2.png" );
	ResourceManager::getInstance().loadTexture("redOrc3", "../assets/RedPlayer3.png");
	ResourceManager::getInstance().loadTexture("blueOrc1", "../assets/BluePlayer1.png");
	ResourceManager::getInstance().loadTexture("blueOrc2", "../assets/BluePlayer2.png");
	ResourceManager::getInstance().loadTexture("blueOrc3", "../assets/BluePlayer3.png");

	ResourceManager::getInstance().loadTexture("ro1", "../assets/RedOrc1.png");
	ResourceManager::getInstance().loadTexture("ro2", "../assets/RedOrc2.png");
	ResourceManager::getInstance().loadTexture("ro3", "../assets/RedOrc3.png");
	ResourceManager::getInstance().loadTexture("bo1", "../assets/BlueOrc1.png");
	ResourceManager::getInstance().loadTexture("bo2", "../assets/BlueOrc2.png");
	ResourceManager::getInstance().loadTexture("bo3", "../assets/BlueOrc3.png");

	ResourceManager::getInstance().loadTexture("P1", "../assets/P1.png");
	ResourceManager::getInstance().loadTexture("P2", "../assets/P2.png");
	ResourceManager::getInstance().loadTexture("P3", "../assets/P3.png");
	ResourceManager::getInstance().loadTexture("P4", "../assets/P4.png");
	ResourceManager::getInstance().loadTexture("P5", "../assets/P5.png");
	ResourceManager::getInstance().loadTexture("P6", "../assets/P6.png");

	ResourceManager::getInstance().loadTexture("flag", "../assets/Flag.png");
	ResourceManager::getInstance().loadTexture("neutralBall", "../assets/Ballneutral32.png");
	ResourceManager::getInstance().loadTexture("redBall", "../assets/Ballred32.png");
	ResourceManager::getInstance().loadTexture("blueBall", "../assets/Ballblue32.png");
	ResourceManager::getInstance().loadTexture("flagPickupBlue", "../assets/FlagPickedUpBlue.png");
	ResourceManager::getInstance().loadTexture("flagPickupRed", "../assets/FlagPickedUpRed.png");
	ResourceManager::getInstance().loadTexture("stunStars", "../assets/Stunstars.png");
	ResourceManager::getInstance().loadTexture("starAnimation", "../assets/StarAnimation.png");
	ResourceManager::getInstance().loadTexture("marker", "../assets/marker.png");
	ResourceManager::getInstance().loadTexture("smallFire", "../assets/FlameSmallAnim.png");
	ResourceManager::getInstance().loadTexture("bigFire", "../assets/FlameBigAnim.png");
	
	ResourceManager::getInstance().loadSound("ballOnFire", "../assets/SFX/Ballonfire.wav");
	ResourceManager::getInstance().loadSound("throwBall", "../assets/SFX/Impact 2.wav");
	ResourceManager::getInstance().loadSound("ballFullCharged", "../assets/SFX/Throwballonfire.wav");
	ResourceManager::getInstance().loadSound("matchend", "../assets/SFX/Match_ends.wav");
	ResourceManager::getInstance().loadSound("orcstun", "../assets/SFX/Orcstunned.wav");
	ResourceManager::getInstance().loadSound("orcdeath", "../assets/SFX/Orcdeath.wav");
	
	if (!music.openFromFile("../assets/Music/Ingame/JDB Artist - Inspirational Vol.2 - 28 Bring It On (Action).wav"))
	{
		return; // error
	}

	music.play();
	music.setVolume(5.f);
	music.setLoop(true);
	
	createAnimations();
	MapLoader::getInstance().loadMap("Map.tmx", sf::Vector2f(0, 0));
	GameObjectFactory::CreateScore();
	loadSetup();

	sf::View view(sf::FloatRect(0, 0, 1232, 800));
	GameStateManager::getInstance().getWindow()->setView(view);
	
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
	std::string test = "P" + to_string(pHelper+1);
	auto playerText = std::make_shared<SpriteRenderComponent>(*characterObj, *ResourceManager::getInstance().getTexture("P" + to_string(pHelper+1)), 10, -25);
	playerText->setLayer(Playfield);
	characterObj->addComponent(playerText);
	pHelper++;
}

void PlayState::createAnimations()
{
	createOrcAnimationHelper("bo1", "Player 2");
	createOrcAnimationHelper("bo2", "Player 4");
	createOrcAnimationHelper("bo3", "Player 6");
	createOrcAnimationHelper("ro1", "Player 1");
	createOrcAnimationHelper("ro2", "Player 3");
	createOrcAnimationHelper("ro3", "Player 5");
	createStarAnimationHelper("starAnimation", "star");
	createFireAnimationHelper();
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
	walkingUp.addFrame(sf::IntRect(0, 216, 51, 72));
	walkingUp.addFrame(sf::IntRect(51, 216, 51, 72));
	walkingUp.addFrame(sf::IntRect(102, 216, 51, 72));
	ResourceManager::getInstance().addAnimation(animName + "WalkingUp", walkingUp);
}

void PlayState::createStarAnimationHelper(std::string textureName, std::string animName)
{
	Animation star;
	star.setSpriteSheet(*ResourceManager::getInstance().getTexture(textureName));
	star.addFrame(sf::IntRect(0, 0, 42, 32));
	star.addFrame(sf::IntRect(42, 0, 42, 32));
	star.addFrame(sf::IntRect(84, 0, 42, 32));
	star.addFrame(sf::IntRect(126, 0, 42, 32));
	star.addFrame(sf::IntRect(168, 0, 42, 32));
	star.addFrame(sf::IntRect(210, 0, 42, 32));
	ResourceManager::getInstance().addAnimation(animName, star);

}

void PlayState::createFireAnimationHelper()
{
	Animation smallFire;
	smallFire.setSpriteSheet(*ResourceManager::getInstance().getTexture("smallFire"));
	smallFire.addFrame(sf::IntRect(0, 0, 32, 32));
	smallFire.addFrame(sf::IntRect(32, 0, 32, 32));
	smallFire.addFrame(sf::IntRect(64, 0, 32, 32));
	smallFire.addFrame(sf::IntRect(96, 0, 32, 32));
	ResourceManager::getInstance().addAnimation("smallFireAnim", smallFire);

	Animation bigFire;
	bigFire.setSpriteSheet(*ResourceManager::getInstance().getTexture("bigFire"));
	bigFire.addFrame(sf::IntRect(0, 0, 32, 32));
	bigFire.addFrame(sf::IntRect(32, 0, 32, 32));
	bigFire.addFrame(sf::IntRect(64, 0, 32, 32));
	bigFire.addFrame(sf::IntRect(96, 0, 32, 32));
	ResourceManager::getInstance().addAnimation("bigFireAnim", smallFire);
}
