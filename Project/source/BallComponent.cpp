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

BallComponent::BallComponent(GameObject& owner, std::string owningPlayFieldName, float ballSpeed,float resetLastDelay) : Component(owner)
{
	this->playfield = GameObjectManager::getInstance().GetGameObjectByName(owningPlayFieldName);
	this->ballSpeed = ballSpeed;
	this->resetLastDelay = resetLastDelay;
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
	}
}

void BallComponent::onCollision(CollisionInfo colInfo)
{

	if (colInfo.otherCol->getType() == "Player" && !(colInfo.otherCol == lastHolder))
	{
		onPlayerPickup(colInfo);
	}
	else if (colInfo.otherCol->getType() == "Obstacle")
	{
		lastHolder = nullptr;
	}
}

void BallComponent::onPlayerPickup(CollisionInfo colInfo)
{
	characterInfo = colInfo.otherCol->getComponent<CharacterInfoComponent>().get();
	if(characterInfo->getHasBall() || characterInfo->getHasFlag())
	{
		return;
	}
	if(colInfo.otherCol->getComponent<PlayerControllerComponent>())
	{
		controller = colInfo.otherCol->getComponent<PlayerControllerComponent>().get();
	}
	if (colInfo.otherCol->getComponent<AiControllerComponent>())
	{
		controller = colInfo.otherCol->getComponent<AiControllerComponent>().get();
	}
	controller->setBall(&gameObject);
	colInfo.otherCol->getComponent<CharacterInfoComponent>()->setHasBall(true);
	gameObject.getComponent<AABBColliderComponent>()->setEnabled(false);
	ballHolder = colInfo.otherCol;
	lastHolder = ballHolder;
	gameObject.getComponent<RigidBodyComponent>()->setVelocity(sf::Vector2f(0, 0));
	gameObject.getComponent<RigidBodyComponent>()->setAcceleration(sf::Vector2f(0, 0));
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
	if(clock.getElapsedTime().asSeconds()>(throwTime +resetLastDelay) && ballHolder == nullptr)
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



