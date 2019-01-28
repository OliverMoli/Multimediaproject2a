#include "pch.h"
#include "RigidBodyComponent.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(GameObject & owner, float maxVelocity, float maxSteeringForce) :Component(owner)
{
	this->maxVelocity = maxVelocity;
	this->maxSteeringForce = maxSteeringForce;
}

void MovementComponent::initialize()
{
	rigidBody = gameObject.getComponent<RigidBodyComponent>().get();
}

void MovementComponent::update(float deltaTime)
{

}

void MovementComponent::setSteering(sf::Vector2f steering)
{
	rigidBody->addImpulse(steering);
}

float MovementComponent::getMaxVelocity() const
{
	return maxVelocity;
}

float MovementComponent::getMaxSteeringForce() const
{
	return maxSteeringForce;
}