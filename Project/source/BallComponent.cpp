#include "pch.h"
#include "BallComponent.h"
#include "GameObjectManager.h"
#include "PlayFieldComponent.h"
#include "InputManager.h"

BallComponent::BallComponent(GameObject& owner, std::string owningPlayFieldName) : Component(owner)
{
	this->owningPlayfieldName = owningPlayFieldName;
}

void BallComponent::initialize()
{
}

void BallComponent::update(float deltaTime)
{
	if (InputManager::getInstance().isKeyDown("Test", 0)) {
		respawnRandomly();
	}

}

void BallComponent::onCollision(CollisionInfo colInfo)
{
	if (colInfo.otherCol->getType() == "Player")
	{
		respawnRandomly();
	}
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

