#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include "Component.h"
#include "RenderComponent.h"

class SpriteRenderComponent : public RenderComponent
{
public:
	SpriteRenderComponent(GameObject& owner,sf::Texture& texture,float posX =0.0f,float posY=0.0f, bool centerOriginAroundTexture=false);
	void initialize() override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
	void setTexture(const sf::Texture& texture);
	void setTextureAndBounds(const sf::Texture& texture,const sf::IntRect rect);
	sf::Sprite* getSprite();
private:
	sf::Sprite sprite;
};