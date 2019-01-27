#pragma once
#include "Component.h"
#include "RenderComponent.h"
#include <SFML/Graphics/Sprite.hpp>

class LayerComponent : public RenderComponent
{
public:
	LayerComponent(GameObject& owner, RenderLayer layer);
	void initialize() override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
	void addSprite(std::shared_ptr<sf::Sprite> sprite);
private:
	std::vector<std::shared_ptr<sf::Sprite>> layerSprites;
};
