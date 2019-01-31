#include "pch.h"
#include "SpriteRenderComponent.h"
#include "GameStateManager.h"

SpriteRenderComponent::SpriteRenderComponent(GameObject& owner,sf::Texture& texture, float posX, float posY,bool centerOriginAroundTexture):RenderComponent(owner)
{
	sprite.setTexture(texture);
	if(centerOriginAroundTexture)
	{
		sprite.setOrigin(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2);
	}
	sprite.setPosition(posX,posY);
}

void SpriteRenderComponent::initialize()
{
}

void SpriteRenderComponent::update(float deltaTime)
{
}

void SpriteRenderComponent::render(sf::RenderWindow & window)
{
	sf::Transform parentTransform = gameObject.getTransform();
	window.draw(sprite,parentTransform);
}

void SpriteRenderComponent::setTexture(const sf::Texture & texture)
{
	sprite.setTexture(texture);
	sf::IntRect newRect = sprite.getTextureRect();
	newRect.width = texture.getSize().x;
	newRect.height = texture.getSize().y;
	sprite.setTextureRect(newRect);
}

void SpriteRenderComponent::setTextureAndBounds(const sf::Texture & texture, const sf::IntRect rect)
{
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
}


