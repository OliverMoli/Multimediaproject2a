#include "pch.h"
#include "LayerComponent.h"
#include "RenderComponent.h"

LayerComponent::LayerComponent(GameObject& owner, RenderLayer layer) : RenderComponent(owner)
{
	this->layer = layer;
}

void LayerComponent::initialize()
{
}

void LayerComponent::update(float deltaTime)
{
}

void LayerComponent::render(sf::RenderWindow & window)
{
	for(auto tileSprite: layerSprites)
	{
		window.draw(*tileSprite);
	}
}

void LayerComponent::addSprite(std::shared_ptr<sf::Sprite> sprite)
{
	layerSprites.push_back(sprite);
}

