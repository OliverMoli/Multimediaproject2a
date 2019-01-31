#include "pch.h"
#include "StunStarComponent.h"
#include "SpriteRenderComponent.h"
#include "RigidBodyComponent.h"



StunStarComponent::StunStarComponent(GameObject& owner, float duration) :Component(owner)
{
	this->duration = duration;
	
}

void StunStarComponent::initialize()
{
	clock = sf::Clock();
	startTime = clock.getElapsedTime().asSeconds();
}

void StunStarComponent::update(float deltaTime)
{
	if (clock.getElapsedTime().asSeconds() > (startTime + duration))
	{
		gameObject.setActive(false);
	}
}









