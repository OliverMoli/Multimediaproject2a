#include "pch.h"
#include "PlayerControllerComponent.h"
#include "InputManager.h"
#include "MathHelper.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "MovementComponent.h"
#include "BallComponent.h"
#include "SpriteRenderComponent.h"
#include "ResourceManager.h"
#include "StunStarComponent.h"
#include "GameObjectFactory.h"
#include "DebugDraw.h"

PlayerControllerComponent::PlayerControllerComponent(GameObject & owner) :Component(owner)
{
}



void PlayerControllerComponent::initialize()
{
	owner = gameObject.getComponent<MovementComponent>().get();
	characterInfo = gameObject.getComponent<CharacterInfoComponent>().get();
	clock = sf::Clock();
	
}

void PlayerControllerComponent::update(float deltaTime)
{
	if (stunned)
	{	
		if(clock.getElapsedTime().asSeconds() > unstunTime)
		{
			stunned = false;
		}
		else {
			return;
		}
	}
	float gamepadX = sf::Joystick::getAxisPosition(characterInfo->getPlayerIndex(), sf::Joystick::Axis::X);
	float gamepadY = sf::Joystick::getAxisPosition(characterInfo->getPlayerIndex(), sf::Joystick::Axis::Y);
	float gamepadU = sf::Joystick::getAxisPosition(characterInfo->getPlayerIndex(), sf::Joystick::Axis::U);
	float gamepadV = sf::Joystick::getAxisPosition(characterInfo->getPlayerIndex(), sf::Joystick::Axis::V);

	gamepadX = abs(0 - gamepadX) > deadZoneX ? gamepadX : 0;
	gamepadY = abs(0 - gamepadY) > deadZoneY ? gamepadY : 0;
	gamepadU = abs(0 - gamepadU) > deadZoneU ? gamepadU : 0;
	gamepadV = abs(0 - gamepadV) > deadZoneV ? gamepadV : 0;

	sf::Vector2f inputOffset = MathHelper::getNormalizedVec2f(sf::Vector2f(gamepadX, gamepadY));
	sf::Vector2f desiredVelocity = MathHelper::getNormalizedVec2f((gameObject.getPosition() + inputOffset) - gameObject.getPosition())*owner->getMaxVelocity()*deltaTime;
	sf::Vector2f steering = desiredVelocity - gameObject.getComponent<RigidBodyComponent>()->getVelocity();
	MathHelper::truncate(steering, owner->getMaxSteeringForce()*deltaTime);
	owner->setSteering(steering);

	if (sf::Joystick::isButtonPressed(characterInfo->getPlayerIndex(), (int)InputManager::XboxButtons::RB) && clock.getElapsedTime().asSeconds() > (characterInfo->getGameObject().getComponent<MovementComponent>()->getDashCooldown() + characterInfo->getLastDashTime()))
	{
		gameObject.getComponent<RigidBodyComponent>()->addImpulse(inputOffset*characterInfo->getGameObject().getComponent<MovementComponent>()->getDashForce());
		characterInfo->setLastDashTime(clock.getElapsedTime().asSeconds());
	}



	sf::Vector2f aimOffset = MathHelper::getNormalizedVec2f(sf::Vector2f(gamepadU, gamepadV));
	if (ball != nullptr && sf::Joystick::isButtonPressed(characterInfo->getPlayerIndex(), (int)InputManager::XboxButtons::LB) && MathHelper::length(aimOffset) > 0)
	{
		ball->getComponent<BallComponent>()->throwBall(aimOffset);
		
		//gameObject.getPosition(), aimOffset, sf::Color(255, 255, 255), 1);
	}

	if(ball != nullptr && MathHelper::length(aimOffset) > 0)
	{
		//ball->addComponent(std::make_shared<SpriteRenderComponent>(*ball, *ResourceManager::getInstance().getTexture("aimArrow"),aimOffset.x,aimOffset.y,true));
	}
}

void PlayerControllerComponent::setBall(GameObject * go)
{
	IController::setBall(go);
}

void PlayerControllerComponent::setStunned(bool stunned)
{
	IController::setStunned(stunned);
}


bool PlayerControllerComponent::isStunned() const
{
	return IController::isStunned();
}

void PlayerControllerComponent::stun(float duration)
{
	stunned = true;
	unstunTime = clock.getElapsedTime().asSeconds() + duration;
	GameObjectFactory::CreateStunStar(&gameObject, duration);
	gameObject.getComponent<RigidBodyComponent>()->setVelocity(sf::Vector2f(0, 0));
	gameObject.getComponent<RigidBodyComponent>()->setAcceleration(sf::Vector2f(0, 0));
}
