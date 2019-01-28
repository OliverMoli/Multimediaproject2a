#pragma once
#include "RigidBodyComponent.h"
#include <SFML/System/Vector2.hpp>

struct Manifold
{
	RigidBodyComponent* body1;
	RigidBodyComponent* body2;
	float penetration;
	sf::Vector2f normal;
};
class PhysicsManager
{
public:
	static PhysicsManager& getInstance();
	void addRigidbodyComponent(std::shared_ptr<RigidBodyComponent> comp);
	void freeResources();
	void update(float deltaTime);
	void checkCollisions();
	void resolveCollisions();
	void addManifold(Manifold manifold);
	void integrate(float deltaTime);
	std::vector<std::shared_ptr<RigidBodyComponent>> getRigidbodies();
	void resetFirstFrame();
private:
	PhysicsManager() = default;
	~PhysicsManager() = default;
	PhysicsManager(const PhysicsManager& p) = delete;
	PhysicsManager& operator=(const PhysicsManager& rhs) = delete;
	std::vector<std::shared_ptr<RigidBodyComponent>> rigidBodies;
	std::vector<Manifold> manifolds;
	bool firstFrame = true;
};
