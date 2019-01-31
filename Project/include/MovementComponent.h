#pragma once
#include "Component.h"
#include <SFML/System/Vector2.hpp>
#include "RigidBodyComponent.h"
#include "AnimatedSprite.h"

class IController;

class MovementComponent : public Component
{
public:
	MovementComponent(GameObject& owner, float normalMaxVelocity, float normalMaxSteeringForce, float flagHolderMaxVelocity, float flagHolderMaxSteeringForce,float normalDashForce,float normalDashCooldown,float flagHolderDashForce,float flagHolderDashCooldown);
	void initialize() override;
	void update(float deltaTime) override;
	void setController(std::shared_ptr<IController> controller)
	{
		this->controller = controller;
	}
	void setSteering(sf::Vector2f steering);
	void useFlagValues();
	void useNormalValues();
	void initAnims(std::string name);
	float getMaxVelocity() const;
	float getMaxSteeringForce() const;
	float getDashForce() const;
	float getDashCooldown() const;
private:
	std::shared_ptr<IController> controller;
	RigidBodyComponent* rigidBody;
	sf::Vector2f steering;
	float maxVelocity,maxSteeringForce;
	float normalMaxVelocity, normalMaxSteeringForce, flagHolderMaxVelocity,flagHolderMaxSteeringForce;
	float normalDashForce;
	float normalDashCooldown;
	float flagHolderDashForce;
	float flagHolderDashCooldown;
	float dashForce;
	float dashCooldown;
	AnimatedSprite animSprite;
	Animation* currentAnimation;
	Animation walkDown;
	Animation walkLeft;
	Animation walkRight; 
	Animation walkUp;
};