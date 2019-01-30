#include "pch.h"
#include "BallComponent.h"
#include "GameObjectManager.h"
#include "PlayFieldComponent.h"
#include "InputManager.h"
#include "CharacterInfoComponent.h"
#include "AABBColliderComponent.h"
#include "RigidBodyComponent.h"
#include "MathHelper.h"

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
				gameObject.getComponent<AABBColliderComponent>()->setEnabled(true);
			}
		}
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
	if(characterInfo->getHasBall()|| characterInfo->getHasFlag())
	{
		return;
	}
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



