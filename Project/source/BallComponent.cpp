#include "pch.h"
#include "BallComponent.h"
#include "GameObjectManager.h"
#include "PlayFieldComponent.h"
#include "CharacterInfoComponent.h"
#include "AABBColliderComponent.h"
#include "RigidBodyComponent.h"
#include "MathHelper.h"
#include "PlayerControllerComponent.h"
#include "AiControllerComponent.h"
#include "SpriteRenderComponent.h"
#include "ResourceManager.h"
#include "RespawnHelperComponent.h"
#include "GameStateManager.h"
#include <SFML/Window/Joystick.hpp>
#include "SoundManager.h"

BallComponent::BallComponent(GameObject& owner, std::string owningPlayFieldName, float ballVelocityPerCharge, float resetLastDelay, float stunDuration, float neutralVelocityCutoff, float velocityFactorOnEnemyHit, GameObject& arrow1, GameObject& arrow2) : Component(owner)
{
	this->playfield = GameObjectManager::getInstance().GetGameObjectByName(owningPlayFieldName);
	this->ballVelocityPerCharge = ballVelocityPerCharge;
	this->resetLastDelay = resetLastDelay;
	this->stunDurationPerCharge = stunDuration;
	this->neutralVelocityCutoff = neutralVelocityCutoff;
	this->velocityFactorOnEnemyHit = velocityFactorOnEnemyHit;
	arrows.push_back(&arrow1);
	arrows.push_back(&arrow2);
}

void BallComponent::initialize()
{
	clock = sf::Clock();
}

void BallComponent::update(float deltaTime)
{
	arrows[0]->setActive(false);
	arrows[1]->setActive(false);
	enableCollisionAfterDelay();
	if (ballHolder != nullptr)
	{
		gameObject.setPosition(ballHolder->getPosition() + ballPositionOffset);
		showNextMarker();
	}
	else
	{
		if (MathHelper::length(gameObject.getComponent<RigidBodyComponent>()->getVelocity()) < neutralVelocityCutoff || owningTeam == Team::Neutral)
		{
			chargeCounter = 0;
			owningTeam = Team::Neutral;
			gameObject.getComponent<SpriteRenderComponent>()->setTexture(*ResourceManager::getInstance().getTexture("neutralBall"));
				
		}
	}
	if (owningTeam == Team::Neutral)
	{
		hadBall.clear();
	}
	chargeCounter = hadBall.size() - 1;
}

void BallComponent::onCollision(CollisionInfo colInfo)
{

	if (colInfo.otherCol->getType() == "Player" && !(colInfo.otherCol == lastHolder))
	{
		if (owningTeam == Team::Neutral || owningTeam == colInfo.otherCol->getComponent<CharacterInfoComponent>()->getTeam()) {
			onPlayerPickup(colInfo);
		}
		else
		{
			onPlayerDamage(colInfo);
		}
	}
	else if (colInfo.otherCol->getType() == "Obstacle")
	{
		lastHolder = nullptr;
	}
}

void BallComponent::onPlayerPickup(CollisionInfo colInfo)
{
	if (colInfo.otherCol->getComponent<PlayerControllerComponent>())
	{
		controller = colInfo.otherCol->getComponent<PlayerControllerComponent>().get();

	}
	else if (colInfo.otherCol->getComponent<AiControllerComponent>())
	{
		controller = colInfo.otherCol->getComponent<AiControllerComponent>().get();
	}
	if (controller->isStunned() || colInfo.otherCol->getComponent<CharacterInfoComponent>().get()->getHasBall() || colInfo.otherCol->getComponent<CharacterInfoComponent>().get()->getHasFlag())
	{
		controller = nullptr;
		return;
	}
	characterInfo = colInfo.otherCol->getComponent<CharacterInfoComponent>().get();
	owningTeam = characterInfo->getTeam();
	switch (owningTeam)
	{
	case Team::RedTeam:
		gameObject.getComponent<SpriteRenderComponent>()->setTexture(*ResourceManager::getInstance().getTexture("redBall"));
		break;
	case Team::BlueTeam:
		gameObject.getComponent<SpriteRenderComponent>()->setTexture(*ResourceManager::getInstance().getTexture("blueBall"));
		break;
	}
	if (std::find(hadBall.begin(), hadBall.end(), colInfo.otherCol) == hadBall.end())
	{
		hadBall.push_back(colInfo.otherCol);
	}
	controller->setBall(&gameObject);
	colInfo.otherCol->getComponent<CharacterInfoComponent>()->setHasBall(true);
	gameObject.getComponent<AABBColliderComponent>()->setEnabled(false);
	ballHolder = colInfo.otherCol;
	lastHolder = ballHolder;
	gameObject.getComponent<RigidBodyComponent>()->setVelocity(sf::Vector2f(0, 0));
	gameObject.getComponent<RigidBodyComponent>()->setAcceleration(sf::Vector2f(0, 0));
	colInfo.otherCol->getComponent<CharacterInfoComponent>()->setBallComp(this);

	
}

void BallComponent::onPlayerDamage(CollisionInfo colInfo)
{
	if (colInfo.otherCol->getComponent<PlayerControllerComponent>())
	{
		if (chargeCounter < 2) {
			colInfo.otherCol->getComponent<PlayerControllerComponent>()->stun(stunDurationPerCharge*(chargeCounter + 1));
		}
		else {
			respawnPlayer(5, colInfo.otherCol);
			//SoundManager::getInstance().playSound("orcstun", 100, 1, false);
		}
	}
	else if (colInfo.otherCol->getComponent<AiControllerComponent>())
	{
		if (chargeCounter < 2) {
			colInfo.otherCol->getComponent<AiControllerComponent>()->stun(stunDurationPerCharge*(chargeCounter + 1));
		}
		else
		{
			respawnPlayer(5, colInfo.otherCol);
		}
	}
	chargeCounter = 0;
	gameObject.getComponent<RigidBodyComponent>()->setVelocity(MathHelper::getInverseVector(gameObject.getComponent<RigidBodyComponent>()->getVelocity())*velocityFactorOnEnemyHit);
	owningTeam = Team::Neutral;
}



void BallComponent::enableCollisionAfterDelay()
{
	if (clock.getElapsedTime().asSeconds() > (throwTime + resetLastDelay) && ballHolder == nullptr)
	{
		lastHolder = nullptr;
	}
}

void BallComponent::throwBall(sf::Vector2f direction)
{
	gameObject.getComponent<RigidBodyComponent>()->addImpulse(ballHolder->getComponent<RigidBodyComponent>()->getVelocity() + direction * (ballVelocityPerCharge*(chargeCounter + 1)));
	ballHolder = nullptr;
	throwTime = clock.getElapsedTime().asSeconds();
	characterInfo->setHasBall(false);
	characterInfo->setBallComp(nullptr);
	gameObject.getComponent<AABBColliderComponent>()->setEnabled(true);
	controller->setBall(nullptr);

	if (chargeCounter == 1)
	{
		SoundManager::getInstance().playSound("ballOnFire", 100, 1, false);
	}
	if (chargeCounter == 2)
	{
		SoundManager::getInstance().playSound("ballFullCharged", 100, 1, false);
	}
		
}

void BallComponent::respawnPlayer(float delay, GameObject* player)
{
	player->getComponent<CharacterInfoComponent>()->setHasFlag(false);
	auto flagComp = GameObjectManager::getInstance().GetGameObjectByName("Flag")->getComponent<FlagComponent>();
	if (flagComp->getFlagHolder() == player) {
		flagComp->getFlagHolder()->getComponent<MovementComponent>()->useNormalValues();
		flagComp->setFlagHolder(nullptr);
		flagComp->useDefaultFlag();
		flagComp->getGameObject().getComponent<AABBColliderComponent>()->setEnabled(true);
		flagComp->getGameObject().setPosition(player->getPosition() + sf::Vector2f(5, 0));
		flagComp->getGameObject().getComponent<RigidBodyComponent>()->setVelocity(MathHelper::getNormalizedVec2f(MathHelper::getRandomDir())*500.0f);
	}
	if(player->getComponent<CharacterInfoComponent>()->getHasBall())
	{
		player->getComponent<CharacterInfoComponent>()->getBallComp()->setOwningTeam(Team::Neutral);
		player->getComponent<CharacterInfoComponent>()->getBallComp()->gameObject.getComponent<AABBColliderComponent>()->setEnabled(true);
		player->getComponent<CharacterInfoComponent>()->getBallComp()->gameObject.getComponent<RigidBodyComponent>()->setVelocity(MathHelper::getNormalizedVec2f(MathHelper::getRandomDir())*500.0f);
		player->getComponent<CharacterInfoComponent>()->getBallComp()->setBallHolder(nullptr);
		player->getComponent<CharacterInfoComponent>()->getBallComp()->resetChargeCounter();
		player->getComponent<CharacterInfoComponent>()->setHasBall(false);
		player->getComponent<CharacterInfoComponent>()->setBallComp(nullptr);
		
	}
	auto helper = std::make_shared<GameObject>();
	helper->addComponent(std::make_shared<RespawnHelperComponent>(*helper, *player, delay));
	GameStateManager::getInstance().getCurrentState()->addGameObject(helper);
}

void BallComponent::setOwningTeam(Team team)
{
	owningTeam = team;
}

void BallComponent::resetChargeCounter()
{
	chargeCounter = 0;
}

void BallComponent::setBallHolder(GameObject * go)
{
	ballHolder = go;
}

void BallComponent::showNextMarker()
{
	std::vector<GameObject*> needBall;
	auto players = GameObjectManager::getInstance().GetByType("Player");
	for (auto player : players)
	{
		if (player->getComponent<CharacterInfoComponent>()->getTeam() != owningTeam)
		{
			continue;
		}
		if (std::find(hadBall.begin(), hadBall.end(), player) == hadBall.end())
		{
			needBall.push_back(player);
		}
	}
	for (int i=0;i<needBall.size();i++)
	{
		arrows[i]->setActive(true);
		arrows[i]->setPosition(gameObject.getPosition()+sf::Vector2f(16,16));
		sf::Vector2f curPos = arrows[i]->getPosition();
		sf::Vector2f position = needBall[i]->getPosition()+sf::Vector2f(24,36);
		const float PI = 3.14159265;
		float dx = curPos.x - position.x;
		float dy = curPos.y - position.y;
		float rotation = (atan2(dy, dx)) * 180 / PI;
		arrows[i]->getComponent<SpriteRenderComponent>()->getSprite()->setRotation(rotation+180);
	}
}

int BallComponent::getChargeCounter()
{
	return chargeCounter;
}



