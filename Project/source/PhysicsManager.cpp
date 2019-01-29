#include "pch.h"
#include "PhysicsManager.h"
#include "AABBColliderComponent.h"
#include "GameObject.h"

PhysicsManager & PhysicsManager::getInstance()
{
	static PhysicsManager instance;
	return instance;
}

void PhysicsManager::addRigidbodyComponent(std::shared_ptr<RigidBodyComponent> comp)
{
	rigidBodies.push_back(comp);
}

void PhysicsManager::freeResources()
{
	rigidBodies.clear();
	manifolds.clear();
}

void PhysicsManager::update(float deltaTime)
{
	manifolds.clear();
	checkCollisions();
	resolveCollisions();
	integrate(deltaTime);
}

void PhysicsManager::checkCollisions()
{
	if(firstFrame)
	{
		firstFrame = false;
		return;
	}
	for (auto rb1 = rigidBodies.begin(); rb1 != rigidBodies.end(); ++rb1)
	{
		if (!(*rb1)->getGameObject().isActive())
		{
			continue;
		}
		for (auto rb2 = rb1 + 1; rb2 != rigidBodies.end(); ++rb2)
		{
			if(!(*rb2)->getGameObject().isActive())
			{
				continue;
			}
			bool collisionEventSent = false;
			if ((*rb1)->getMass() == 0 && (*rb2)->getMass() == 0)
				continue;
			for (auto col1 : (*rb1)->getColliders())
			{
				for (auto col2 : (*rb2)->getColliders())
				{
					if (col1->intersect(col2) && !collisionEventSent)
					{
						ICollisionObserver::CollisionInfo colInfo;
						colInfo.otherCol = &(*rb2)->getGameObject();
						(*rb1)->onCollision(colInfo);
						colInfo.otherCol = &(*rb1)->getGameObject();
						(*rb2)->onCollision(colInfo);
						collisionEventSent = true;
					}
				}
			}
		}
	}
}

void PhysicsManager::resolveCollisions()
{
	for (auto man : manifolds)
	{
		if((man.body1->getGameObject().getType()=="Player"&&man.body2->getGameObject().getType()=="Ball")|| (man.body2->getGameObject().getType() == "Player"&&man.body1->getGameObject().getType() == "Ball"))
		{
			continue;
		}
		
		// Calculate relative velocity
		sf::Vector2f rv = man.body1->getVelocity() - man.body2->getVelocity();

		// Calculate relative velocity in terms of the normal direction (length through vector projection)
		float velAlongNormal = rv.x * man.normal.x + rv.y * man.normal.y;

		// Do not resolve if velocities are separating

		// Calculate impulse scalar
		float e = 0.7f; //< 1.0 = all objects are bouncy
		float j = -(1 + e) * velAlongNormal;
		j /= man.body1->getInvMass() + man.body2->getInvMass();

		// Apply impulse
		sf::Vector2f impulse = j * man.normal;

		// impulse proportional to mass
		man.body1->setVelocity(man.body1->getVelocity() + impulse * man.body1->getInvMass());
		man.body2->setVelocity(man.body2->getVelocity() - impulse * man.body2->getInvMass());

		const bool positionalCorrection = true;
		if (positionalCorrection)
		{
			const float percent = 0.4f; // usually 20% to 80%
			const float slop = 0.01f; // usually 0.01 to 0.1
			sf::Vector2f correction = std::max(man.penetration - slop, 0.0f) /
				(man.body1->getInvMass() + man.body2->getInvMass()) * percent * man.normal;
			// Apply directly to position
			man.body1->getGameObject().setPosition(man.body1->getGameObject().getPosition()+ man.body1->getInvMass() * correction);
			man.body2->getGameObject().setPosition(man.body2->getGameObject().getPosition() - man.body2->getInvMass() * correction);
		}
	}
}

void PhysicsManager::addManifold(Manifold manifold)
{
	manifolds.push_back(manifold);
}

void PhysicsManager::integrate(float deltaTime)
{
	for (auto body : rigidBodies)
	{
		sf::Vector2f forces{};
		for (const auto& f : body->getForces())
			forces += f;
		for (const auto& i : body->getImpulses())
			forces += i;
		body->getImpulses().clear();
		if(!body->getGameObject().isActive())
		{
			body->setVelocity(sf::Vector2f(0, 0));
			body->setAcceleration(sf::Vector2f(0, 0));
			continue;
		}
		body->setAcceleration(forces * body->getInvMass());
		body->setVelocity(body->getVelocity()*body->getFriction() + body->getAcceleration() * deltaTime);
		body->getGameObject().setPosition(body->getGameObject().getPosition() + body->getVelocity()* deltaTime);
	}
}

std::vector<std::shared_ptr<RigidBodyComponent>> PhysicsManager::getRigidbodies()
{
	return rigidBodies;
}

void PhysicsManager::resetFirstFrame()
{
	firstFrame = true;
}
