#include "pch.h"
#include "SpriteAnimationComponent.h"
#include "InputManager.h"
#include "AnimatedSprite.h"

SpriteAnimationComponent::SpriteAnimationComponent(GameObject& owner, sf::Texture& texture, float posX, float posY) :RenderComponent(owner)
{
	sprite.setTexture(texture);
}

void SpriteAnimationComponent::initialize()
{

}

void SpriteAnimationComponent::update(float deltaTime)
{
	
}

void SpriteAnimationComponent::render(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void SpriteAnimationComponent::setTexture(sf::Texture& texture)
{
	sprite.setTexture(texture);
}

void SpriteAnimationComponent::animate(sf::Texture& texture)
{
	walkingAnimationDown.setSpriteSheet(texture);
	walkingAnimationDown.addFrame(sf::IntRect(48, 0, 48, 72));
	walkingAnimationDown.addFrame(sf::IntRect(96, 0, 48, 72));
	walkingAnimationDown.addFrame(sf::IntRect(48, 0, 48, 72));
	walkingAnimationDown.addFrame(sf::IntRect(0, 0, 48, 72));

	walkingAnimationLeft.setSpriteSheet(texture);
	walkingAnimationLeft.addFrame(sf::IntRect(48, 48, 48, 72));
	walkingAnimationLeft.addFrame(sf::IntRect(96, 48, 48, 72));
	walkingAnimationLeft.addFrame(sf::IntRect(48, 48, 48, 72));
	walkingAnimationLeft.addFrame(sf::IntRect(0, 48, 48, 72));

	walkingAnimationRight.setSpriteSheet(texture);
	walkingAnimationRight.addFrame(sf::IntRect(48, 96, 48, 72));
	walkingAnimationRight.addFrame(sf::IntRect(96, 96, 48, 72));
	walkingAnimationRight.addFrame(sf::IntRect(48, 96, 48, 72));
	walkingAnimationRight.addFrame(sf::IntRect(0, 96, 48, 72));

	walkingAnimationUp.setSpriteSheet(texture);
	walkingAnimationUp.addFrame(sf::IntRect(48, 144, 48, 72));
	walkingAnimationUp.addFrame(sf::IntRect(96, 144, 48, 72));
	walkingAnimationUp.addFrame(sf::IntRect(48,144, 48, 72));
	walkingAnimationUp.addFrame(sf::IntRect(0, 144, 48, 72));

	currentAnimation = &walkingAnimationDown;
	animationSpeed = 80.0f;

	AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
	animatedSprite.setPosition(texture.getSize().x, texture.getSize().y);

	frameTime = clock.restart();

	if(sf::Joystick::getAxisPosition((0),sf::Joystick::Axis::X) == 100)
	{
		currentAnimation = &walkingAnimationRight;
		animationMovement.x += animationSpeed;
		neutralState = false;
	}

	if (sf::Joystick::getAxisPosition((0), sf::Joystick::Axis::X) == -100)
	{
		currentAnimation = &walkingAnimationLeft;
		animationMovement.x -= animationSpeed;
		neutralState = false;
	}

	if (sf::Joystick::getAxisPosition((0), sf::Joystick::Axis::Y) == 100)
	{
		currentAnimation = &walkingAnimationUp;
		animationMovement.y += animationSpeed;
		neutralState = false;
	}

	if (sf::Joystick::getAxisPosition((0), sf::Joystick::Axis::X) == -100)
	{
		currentAnimation = &walkingAnimationDown;
		animationMovement.y -= animationSpeed;
		neutralState = false;
	}

	animatedSprite.play(*currentAnimation);
	animatedSprite.move(animationMovement*frameTime.asSeconds());

	if(neutralState)
	{
		animatedSprite.stop();
	}
	neutralState = true;


}


