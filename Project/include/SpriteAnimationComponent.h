#pragma once
#include "Component.h"
#include "RenderComponent.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "AnimatedSprite.hpp" 
#include <SFML/Graphics.hpp>

class SpriteAnimationComponent : public RenderComponent
{
public:
	SpriteAnimationComponent(GameObject& owner, sf::Texture& texture, float posX, float posY);
	void initialize() override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
	void setTexture(sf::Texture& texture);
	void animate(sf::Texture& texture);
	
	

private:
	sf::Sprite sprite;
	Animation walkingAnimationDown;
	Animation walkingAnimationLeft;
	Animation walkingAnimationRight;
	Animation walkingAnimationUp;
	Animation* currentAnimation;
	sf::Clock clock;
	bool neutralState = true;
	sf::Time frameTime;
	sf::Vector2f animationMovement;
	float animationSpeed;
	
	
};
