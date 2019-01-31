#include "pch.h"
#include "RespawnHelperComponent.h"
#include "GameObject.h"

RespawnHelperComponent::RespawnHelperComponent(GameObject& owner, GameObject& goToDestroy,float duration):Component(owner)
{
	this->go = &goToDestroy;
	this->duration = duration;
}

void RespawnHelperComponent::initialize()
{
	clock = sf::Clock();
	startTime = clock.getElapsedTime().asSeconds();
	go->setActive(false);
	
}

void RespawnHelperComponent::update(float deltaTime)
{
	if(clock.getElapsedTime().asSeconds()> (startTime + duration))
	{
		go->setActive(true);
		gameObject.markComponentForDeletion(gameObject.getComponent<RespawnHelperComponent>());
	}
}

