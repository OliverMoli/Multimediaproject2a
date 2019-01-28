#pragma once
#include "ICollisionObserver.h"
#include <SFML/System/Vector2.hpp>
#include "ColliderComponent.h"

class RigidBodyComponent : public Component
{
public:
	RigidBodyComponent(GameObject& owner, float mass);
	void onCollision(ICollisionObserver::CollisionInfo colInfo);
	void addObserver(std::shared_ptr<ICollisionObserver> observer);
	void addCollider(std::shared_ptr<ColliderComponent> collider);
	std::vector<std::shared_ptr<ColliderComponent>>& getColliders();
	void initialize() override;
	void update(float deltaTime) override;
	float getMass();
	float getInvMass();
	sf::Vector2f getAcceleration();
	sf::Vector2f getVelocity();
	std::vector<sf::Vector2f>& getForces();
	std::vector<sf::Vector2f>& getImpulses();
	void setVelocity(sf::Vector2f vel);
	void setAcceleration(sf::Vector2f acc);
	void setFriction(float friction);
	float getFriction() const;
	void addImpulse(sf::Vector2f impulse);
	void addForce(sf::Vector2f force);
private:
	std::vector<std::shared_ptr<ICollisionObserver>> colObservers;
	std::vector<std::shared_ptr<ColliderComponent>> colliders;

	float mass;
	float invMass;
	float friction = 1.0f;

	sf::Vector2f acceleration;
	sf::Vector2f velocity;
	
	std::vector<sf::Vector2f> forces;
	std::vector<sf::Vector2f> impulses;

};
