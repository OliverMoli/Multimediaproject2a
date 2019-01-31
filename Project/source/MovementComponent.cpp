#include "pch.h"
#include "RigidBodyComponent.h"
#include "MovementComponent.h"
#include "ResourceManager.h"
#include "SpriteRenderComponent.h"
#include <TGUI/Texture.hpp>
#include "RenderManager.h"

MovementComponent::MovementComponent(GameObject & owner, float normalMaxVelocity, float normalMaxSteeringForce, float flagHolderMaxVelocity, float flagHolderMaxSteeringForce, float normalDashForce, float normalDashCooldown, float flagHolderDashForce, float flagHolderDashCooldown) :Component(owner)
{
	this->normalMaxVelocity = normalMaxVelocity;
	this->normalMaxSteeringForce = normalMaxSteeringForce;
	this->flagHolderMaxVelocity = flagHolderMaxVelocity;
	this->flagHolderMaxSteeringForce = flagHolderMaxSteeringForce;
	this->normalDashForce = normalDashForce;
	this->normalDashCooldown = normalDashCooldown;
	this->flagHolderDashForce = flagHolderDashForce;
	this->flagHolderDashCooldown = flagHolderDashCooldown;
	maxVelocity = normalMaxVelocity;
	maxSteeringForce = normalMaxSteeringForce;
	dashForce = normalDashForce;
	dashCooldown = normalDashCooldown;

}

void MovementComponent::initialize()
{
	rigidBody = gameObject.getComponent<RigidBodyComponent>().get();
}

void MovementComponent::update(float deltaTime)
{
	float velX, velY;
	velX = gameObject.getComponent<RigidBodyComponent>()->getVelocity().x;
	velY = gameObject.getComponent<RigidBodyComponent>()->getVelocity().y;
	if (abs(velX) > abs(velY))
	{
		if(velX >0)
		{
			currentAnimation = &walkRight;
		}else
		{
			currentAnimation = &walkLeft;
		}
	}else
	{
		if (velY > 0)
		{
			currentAnimation = &walkDown;
		}
		else
		{
			currentAnimation = &walkUp;
		}
	}
	animSprite.play(*currentAnimation);
	animSprite.update(sf::seconds(deltaTime));
	gameObject.getComponent<SpriteRenderComponent>()->setTextureAndBounds(*animSprite.sprite.getTexture(), animSprite.sprite.getTextureRect());
}

void MovementComponent::setSteering(sf::Vector2f steering)
{
	rigidBody->addImpulse(steering);
}

void MovementComponent::useFlagValues()
{
	maxVelocity = flagHolderMaxVelocity;
	maxSteeringForce = flagHolderMaxSteeringForce;
	dashForce = flagHolderDashForce;
	dashCooldown = flagHolderDashCooldown;
	gameObject.getComponent<RigidBodyComponent>()->setVelocity(gameObject.getComponent<RigidBodyComponent>()->getVelocity()*0.1f);
	gameObject.getComponent<RigidBodyComponent>()->setAcceleration(sf::Vector2f(0, 0));
}

void MovementComponent::useNormalValues()
{
	maxVelocity = normalMaxVelocity;
	maxSteeringForce = normalMaxSteeringForce;
	dashForce = normalDashForce;
	dashCooldown = normalDashCooldown;
}

void MovementComponent::initAnims(std::string name)
{
	animSprite = AnimatedSprite(sf::seconds(0.2), true, false);
	walkDown = *ResourceManager::getInstance().getAnimation(name + "WalkingDown");
	walkRight = *ResourceManager::getInstance().getAnimation(name + "WalkingRight");
	walkLeft = *ResourceManager::getInstance().getAnimation(name + "WalkingLeft");
	walkUp = *ResourceManager::getInstance().getAnimation(name + "WalkingUp");
	currentAnimation = &walkRight;
}


float MovementComponent::getMaxVelocity() const
{
	return maxVelocity;
}

float MovementComponent::getMaxSteeringForce() const
{
	return maxSteeringForce;
}

float MovementComponent::getDashForce() const
{
	return dashForce;
}

float MovementComponent::getDashCooldown() const
{
	return dashCooldown;
}
