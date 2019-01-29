#include "pch.h"
#include "BallComponent.h"
#include "GameObjectManager.h"
#include "PlayFieldComponent.h"
#include "InputManager.h"
#include "CharacterInfoComponent.h"
#include "AABBColliderComponent.h"
#include "RigidBodyComponent.h"
#include "MathHelper.h"

BallComponent::BallComponent(GameObject& owner, std::string owningPlayFieldName, float ballSpeed,float positionOffsetOnObstacleHit,float velocityLossOnObstacleHit,float throwColDelay) : Component(owner)
{
	this->owningPlayfieldName = owningPlayFieldName;
	this->ballSpeed = ballSpeed;
	this->positionOffsetOnObstacleHit = positionOffsetOnObstacleHit;
	this->velocityLossOnObstacleHit = velocityLossOnObstacleHit;
	this->throwColDelay = throwColDelay;
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
		float gamepadU = sf::Joystick::getAxisPosition(characterInfo->getPlayerIndex(), sf::Joystick::Axis::U);
		float gamepadV = sf::Joystick::getAxisPosition(characterInfo->getPlayerIndex(), sf::Joystick::Axis::V);

		if (abs(0 - gamepadU) > deadZoneU)
		{
			gamepadU = gamepadU;
		}
		else
		{
			gamepadU = 0;
		}
		if (abs(0 - gamepadV) > deadZoneV)
		{
			gamepadV = gamepadV;
		}
		else
		{
			gamepadV = 0;
		}

		sf::Vector2f aimOffset = MathHelper::getNormalizedVec2f(sf::Vector2f(gamepadU, gamepadV));
		if (MathHelper::length(aimOffset) > 0)
		{
			if (sf::Joystick::isButtonPressed(characterInfo->getPlayerIndex(), (int)InputManager::XboxButtons::LB))
			{
				gameObject.getComponent<RigidBodyComponent>()->addImpulse(ballHolder->getComponent<RigidBodyComponent>()->getVelocity()+aimOffset*ballSpeed);
				ballHolder = nullptr;
				throwTime = clock.getElapsedTime().asSeconds();
				characterInfo->setHasBall(false);
			}
		}
	}
}

void BallComponent::onCollision(CollisionInfo colInfo)
{

	if (colInfo.otherCol->getType() == "Player")
	{
		onPlayerPickup(colInfo);
	}
	else if (colInfo.otherCol->getType() == "Obstacle")
	{
		//sf::Vector2f inverseVel = MathHelper::getInverseVector(gameObject.getComponent<RigidBodyComponent>()->getVelocity());
		/*gameObject.move(MathHelper::getNormalizedVec2f(inverseVel) * positionOffsetOnObstacleHit);
		gameObject.getComponent<RigidBodyComponent>()->setVelocity(inverseVel*velocityLossOnObstacleHit);*/
		//gameObject.getComponent<AABBColliderComponent>()->setTrigger(false);
	}
}

void BallComponent::onPlayerPickup(CollisionInfo colInfo)
{
	characterInfo = colInfo.otherCol->getComponent<CharacterInfoComponent>().get();
	if(characterInfo->getHasBall())
	{
		return;
	}
	colInfo.otherCol->getComponent<CharacterInfoComponent>()->setHasBall(true);
	gameObject.getComponent<AABBColliderComponent>()->setEnabled(false);
	ballHolder = colInfo.otherCol;
	gameObject.getComponent<RigidBodyComponent>()->setVelocity(sf::Vector2f(0, 0));
	gameObject.getComponent<RigidBodyComponent>()->setAcceleration(sf::Vector2f(0, 0));
}

std::string BallComponent::getOwningPlayfieldName()
{
	return owningPlayfieldName;
}

void BallComponent::resetComponent()
{
}

void BallComponent::respawnRandomly()
{
	auto owner = GameObjectManager::getInstance().GetGameObjectByName(owningPlayfieldName);
	sf::Vector2f newPos = owner->getPosition();
	newPos.x += rand() % owner->getComponent<PlayFieldComponent>()->getWidth();
	newPos.y += rand() % owner->getComponent<PlayFieldComponent>()->getHeight();
	gameObject.setPosition(newPos);

}

void BallComponent::enableCollisionAfterDelay()
{
	if(clock.getElapsedTime().asSeconds()>(throwTime +throwColDelay))
	{
		gameObject.getComponent<AABBColliderComponent>()->setEnabled(true);
	}
}



