#include "pch.h"
#include "PlayerControllerComponent.h"
#include "InputManager.h"
#include "MathHelper.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"
#include "MovementComponent.h"

PlayerControllerComponent::PlayerControllerComponent(GameObject & owner) :Component(owner)
{
}

void PlayerControllerComponent::initialize()
{
	owner = gameObject.getComponent<MovementComponent>().get();
}

void PlayerControllerComponent::update(float deltaTime)
{
	float gamepadX = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
	float gamepadY = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y);
	if(abs(0-gamepadX)>deadZoneX)
	{
		gamepadX = gamepadX;
	}else
	{
		gamepadX = 0;
	}
	if (abs(0 - gamepadY) > deadZoneY)
	{
		gamepadY = gamepadY;
	}else
	{
		gamepadY = 0;
	}
	sf::Vector2f inputOffset = sf::Vector2f(gamepadX,gamepadY);
	sf::Vector2f desiredVelocity = MathHelper::getNormalizedVec2f((gameObject.getPosition() + inputOffset) - gameObject.getPosition())*owner->getMaxVelocity()*deltaTime;
	sf::Vector2f steering = desiredVelocity - gameObject.getComponent<RigidBodyComponent>()->getVelocity();
	MathHelper::truncate(steering, owner->getMaxSteeringForce()*deltaTime);
	owner->setSteering(steering);

}

