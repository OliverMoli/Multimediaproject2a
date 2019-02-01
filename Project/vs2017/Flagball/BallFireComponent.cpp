#include "pch.h"
#include "BallFireComponent.h"
#include "SpriteRenderComponent.h"
#include "ResourceManager.h"


BallFireComponent::BallFireComponent(GameObject& owner,BallComponent& ball):Component(owner)
{
	this->ball = &ball;
}

void BallFireComponent::initialize()
{
	animSprite = AnimatedSprite(sf::seconds(0.2), true, false);
	currentAnim = ResourceManager::getInstance().getAnimation("bigFireAnim").get();
}

void BallFireComponent::update(float deltaTime)
{
	gameObject.getComponent<SpriteRenderComponent>()->getSprite()->setScale(2.5f, 2.5f);
	gameObject.setPosition(ball->getGameObject().getPosition()+sf::Vector2f(56,56));
	animSprite.play(*currentAnim);
	animSprite.update(sf::seconds(deltaTime));
	gameObject.getComponent<SpriteRenderComponent>()->setTextureAndBounds(*animSprite.sprite.getTexture(), animSprite.sprite.getTextureRect());
}
