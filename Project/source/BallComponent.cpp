#include "pch.h"
#include "BallComponent.h"
#include "GameObjectManager.h"
#include "PlayFieldComponent.h"
#include "InputManager.h"
#include "CharacterInfoComponent.h"
#include "AABBColliderComponent.h"
#include "RigidBodyComponent.h"
#include "MathHelper.h"

BallComponent::BallComponent(GameObject& owner, std::string owningPlayFieldName, float ballSpeed) : Component(owner)
{
	this->owningPlayfieldName = owningPlayFieldName;
	this->ballSpeed = ballSpeed;
}

void BallComponent::initialize()
{
	
}

void BallComponent::update(float deltaTime)
{	
	
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
	
		if (sf::Joystick::isButtonPressed(characterInfo->getPlayerIndex(), (int)InputManager::XboxButtons::LB))
		{
			gameObject.getComponent<RigidBodyComponent>()->addImpulse(sf::Vector2f(aimOffset.x * ballSpeed, aimOffset.y * ballSpeed));
			ballHolder = nullptr;
		}
	}

	

}

void BallComponent::onCollision(CollisionInfo colInfo)
{
	if (colInfo.otherCol->getType() == "Player")
	{
		onPlayerPickup(colInfo);
		
	}

}

void BallComponent::onPlayerPickup(CollisionInfo colInfo)
{
	characterInfo = colInfo.otherCol->getComponent<CharacterInfoComponent>().get();
	colInfo.otherCol->getComponent<CharacterInfoComponent>()->setHasBall(true);
	gameObject.getComponent<AABBColliderComponent>()->setEnabled(false);
	ballHolder = colInfo.otherCol;

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



