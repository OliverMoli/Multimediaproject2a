#include "pch.h"
#include "RigidBodyComponent.h"
#include "ColliderComponent.h"

RigidBodyComponent::RigidBodyComponent(GameObject& owner,float mass) :Component(owner)
{
	this->mass = mass;
	invMass = (mass == 0.0f) ? 0.0f : 1.0f / mass;
}

void RigidBodyComponent::onCollision(ICollisionObserver::CollisionInfo colInfo)
{
	for(auto observer : colObservers)
	{
		observer->onCollision(colInfo);
	}
}

void RigidBodyComponent::addObserver(std::shared_ptr<ICollisionObserver> observer)
{
	colObservers.push_back(observer);
}

void RigidBodyComponent::addCollider(std::shared_ptr<ColliderComponent> collider)
{
	colliders.push_back(collider);
}

std::vector<std::shared_ptr<ColliderComponent>>& RigidBodyComponent::getColliders()
{
	return colliders;
}

void RigidBodyComponent::initialize()
{
}

void RigidBodyComponent::update(float deltaTime)
{
}

float RigidBodyComponent::getMass()
{
	return mass;
}

float RigidBodyComponent::getInvMass()
{
	return invMass;
}

sf::Vector2f RigidBodyComponent::getAcceleration()
{
	return acceleration;
}

sf::Vector2f RigidBodyComponent::getVelocity()
{
	return velocity;
}

std::vector<sf::Vector2f>& RigidBodyComponent::getForces()
{
	return forces;
}

std::vector<sf::Vector2f>& RigidBodyComponent::getImpulses()
{
	return impulses;
}

void RigidBodyComponent::setVelocity(sf::Vector2f vel)
{
	velocity = vel;
}

void RigidBodyComponent::setAcceleration(sf::Vector2f acc)
{
	acceleration = acc;
}

void RigidBodyComponent::setFriction(float friction)
{
	this->friction = friction;
}

float RigidBodyComponent::getFriction() const
{
	return friction;
}

void RigidBodyComponent::addImpulse(sf::Vector2f impulse)
{
	impulses.push_back(impulse);
}

void RigidBodyComponent::addForce(sf::Vector2f force)
{
	forces.push_back(force);
}
