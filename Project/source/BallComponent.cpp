#include "pch.h"
#include "BallComponent.h"
#include "GameObjectManager.h"
#include "PlayFieldComponent.h"
#include "InputManager.h"
#include "CharacterInfoComponent.h"
#include "AABBColliderComponent.h"
#include "RigidBodyComponent.h"
#include "MathHelper.h"
#include "PlayerControllerComponent.h"
#include "AiControllerComponent.h"
#include "SpriteRenderComponent.h"
#include "ResourceManager.h"

BallComponent::BallComponent(GameObject& owner, std::string owningPlayFieldName, float ballSpeed, float resetLastDelay,float stunDuration,float neutralVelocityCutoff,float velocityFactorOnEnemyHit) : Component(owner)
{
	this->playfield = GameObjectManager::getInstance().GetGameObjectByName(owningPlayFieldName);
	this->ballSpeed = ballSpeed;
	this->resetLastDelay = resetLastDelay;
	this->stunDurationPerCharge = stunDuration;
	this->neutralVelocityCutoff = neutralVelocityCutoff;
	this->velocityFactorOnEnemyHit = velocityFactorOnEnemyHit;
}

void BallComponent::initialize()
{
	clock = sf::Clock();
}

void BallComponent::update(float deltaTime)
{
	enableCollisionAfterDelay();
	if (ballHolder != nullptr)
	{
		gameObject.setPosition(ballHolder->getPosition() + ballPositionOffset);
	}else
	{
		if(MathHelper::length(gameObject.getComponent<RigidBodyComponent>()->getVelocity())<neutralVelocityCutoff || owningTeam == Team::Neutral)
		{
			chargeCounter = 0;
			owningTeam = Team::Neutral;
			gameObject.getComponent<SpriteRenderComponent>()->setTexture(*ResourceManager::getInstance().getTexture("neutralBall"));
		}
	}
	if(owningTeam== Team::Neutral)
	{
		hadBall.clear();
	}
	chargeCounter = hadBall.size()-1;
}

void BallComponent::onCollision(CollisionInfo colInfo)
{

	if (colInfo.otherCol->getType() == "Player" && !(colInfo.otherCol == lastHolder))
	{
		if (owningTeam == Team::Neutral) {
			onPlayerPickup(colInfo);
		}
		else if (owningTeam == colInfo.otherCol->getComponent<CharacterInfoComponent>()->getTeam())
		{
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
	if (controller->isStunned()||colInfo.otherCol->getComponent<CharacterInfoComponent>().get()->getHasBall() || colInfo.otherCol->getComponent<CharacterInfoComponent>().get()->getHasFlag())
	{
		controller = nullptr;
		return;
	}
	characterInfo = colInfo.otherCol->getComponent<CharacterInfoComponent>().get();
	owningTeam = characterInfo->getTeam();
	switch(owningTeam)
	{
	case Team::RedTeam:
		gameObject.getComponent<SpriteRenderComponent>()->setTexture(*ResourceManager::getInstance().getTexture("redBall"));
		break;
	case Team::BlueTeam:
		gameObject.getComponent<SpriteRenderComponent>()->setTexture(*ResourceManager::getInstance().getTexture("blueBall"));
		break;
	}
	if(std::find(hadBall.begin(),hadBall.end(),colInfo.otherCol)==hadBall.end())
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
	
}

void BallComponent::onPlayerDamage(CollisionInfo colInfo)
{
	if (colInfo.otherCol->getComponent<PlayerControllerComponent>())
	{
		if (chargeCounter < 2) {
			colInfo.otherCol->getComponent<PlayerControllerComponent>()->stun(stunDurationPerCharge*(chargeCounter + 1));
		}
		else{
			
		}
	}
	else if (colInfo.otherCol->getComponent<AiControllerComponent>())
	{
		if (chargeCounter < 2) {
			colInfo.otherCol->getComponent<AiControllerComponent>()->stun(stunDurationPerCharge*(chargeCounter + 1));
		}else
		{
			
		}
	}
	chargeCounter = 0;
	gameObject.getComponent<RigidBodyComponent>()->setVelocity(MathHelper::getInverseVector(gameObject.getComponent<RigidBodyComponent>()->getVelocity())*velocityFactorOnEnemyHit);
	owningTeam = Team::Neutral;
}


void BallComponent::resetComponent()
{
}

void BallComponent::respawnRandomly()
{
	sf::Vector2f newPos = playfield->getPosition();
	newPos.x += rand() % playfield->getComponent<PlayFieldComponent>()->getWidth();
	newPos.y += rand() % playfield->getComponent<PlayFieldComponent>()->getHeight();
	gameObject.setPosition(newPos);

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
	gameObject.getComponent<RigidBodyComponent>()->addImpulse(ballHolder->getComponent<RigidBodyComponent>()->getVelocity() + direction * ballSpeed);
	ballHolder = nullptr;
	throwTime = clock.getElapsedTime().asSeconds();
	characterInfo->setHasBall(false);
	gameObject.getComponent<AABBColliderComponent>()->setEnabled(true);
	controller->setBall(nullptr);
}



