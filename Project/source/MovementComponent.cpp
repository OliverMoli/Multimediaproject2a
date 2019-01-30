#include "pch.h"
#include "RigidBodyComponent.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(GameObject & owner, float normalMaxVelocity, float normalMaxSteeringForce,float flagHolderMaxVelocity,float flagHolderMaxSteeringForce,float normalDashForce, float normalDashCooldown, float flagHolderDashForce, float flagHolderDashCooldown) :Component(owner)
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
