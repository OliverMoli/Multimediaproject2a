#pragma once
#include "Component.h"
#include <SFML/System/Vector2.hpp>
#include "RigidBodyComponent.h"

class IController;

class MovementComponent : public Component
{
public:
	MovementComponent(GameObject& owner, float maxVelocity, float maxSteeringForce);
	void initialize() override;
	void update(float deltaTime) override;
	void setController(std::shared_ptr<IController> controller)
	{
		this->controller = controller;
	}
	void setSteering(sf::Vector2f steering);
	float getMaxVelocity() const;
	float getMaxSteeringForce() const;
private:
	std::shared_ptr<IController> controller;
	RigidBodyComponent* rigidBody;
	sf::Vector2f steering;
	float maxVelocity, maxSteeringForce;
};