#include "pch.h"
#include "RespawnHelperComponent.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "MathHelper.h"
#include "PlayFieldComponent.h"

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
	auto playField = GameObjectManager::getInstance().GetGameObjectByName("playField");
	go->setPosition(playField->getPosition() + sf::Vector2f(MathHelper::random(50, playField->getComponent<PlayFieldComponent>()->getWidth() - 50), MathHelper::random(50, playField->getComponent<PlayFieldComponent>()->getHeight() - 50)));
}

void RespawnHelperComponent::update(float deltaTime)
{
	if(clock.getElapsedTime().asSeconds()> (startTime + duration))
	{
		go->setActive(true);
		gameObject.markComponentForDeletion(gameObject.getComponent<RespawnHelperComponent>());
	}
}

