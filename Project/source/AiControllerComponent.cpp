#include "pch.h"
#include "AiControllerComponent.h"
#include <SFML/System/Clock.hpp>
#include "GameObjectFactory.h"

AiControllerComponent::AiControllerComponent(GameObject & owner):Component(owner)
{
}

void AiControllerComponent::initialize()
{
	clock = sf::Clock();
}

void AiControllerComponent::update(float deltaTime)
{
	if (stunned)
	{
		if (clock.getElapsedTime().asSeconds() > unstunTime)
		{
			stunned = false;
		}
		else {
			return;
		}
	}
}

void AiControllerComponent::setBall(GameObject * go)
{
	IController::setBall(ball);
}

void AiControllerComponent::setStunned(bool stunned)
{
	IController::setStunned(stunned);
}


bool AiControllerComponent::isStunned() const
{
	return IController::isStunned();
}

void AiControllerComponent::stun(float duration)
{
	stunned = true;
	unstunTime = clock.getElapsedTime().asSeconds() + duration;
	GameObjectFactory::CreateStunStar(&gameObject, duration);
	gameObject.getComponent<RigidBodyComponent>()->setVelocity(sf::Vector2f(0, 0));
	gameObject.getComponent<RigidBodyComponent>()->setAcceleration(sf::Vector2f(0, 0));
}
