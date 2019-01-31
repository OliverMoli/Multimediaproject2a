#include "pch.h"
#include "StunStarComponent.h"
#include "SpriteRenderComponent.h"
#include "RigidBodyComponent.h"
#include "ResourceManager.h"



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

	animSprite.play(*currentAnimation);
	animSprite.update(sf::seconds(deltaTime));
	gameObject.getComponent<SpriteRenderComponent>()->setTextureAndBounds(*animSprite.sprite.getTexture(), animSprite.sprite.getTextureRect());
}

void StunStarComponent::initAnims(std::string name)
{
	animSprite = AnimatedSprite(sf::seconds(0.2), true, false);
	starAnim = *ResourceManager::getInstance().getAnimation(name);
	currentAnimation = &starAnim;
}









