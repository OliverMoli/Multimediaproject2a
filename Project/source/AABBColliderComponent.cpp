#include "pch.h"
#include "AABBColliderComponent.h"
#include "GameObject.h"
#include "DebugDraw.h"
#include "PhysicsManager.h"

AABBColliderComponent::AABBColliderComponent(GameObject & owner,float width,float height,bool isTrigger,sf::Vector2f positionOffset):ColliderComponent(owner,isTrigger)
{
	bounds.width = width;
	bounds.height = height;
	this->positionOffset = positionOffset;
}

void AABBColliderComponent::initialize()
{
}

void AABBColliderComponent::update(float deltaTime)
{
	bounds.left = gameObject.getPosition().x+positionOffset.x;
	bounds.top = gameObject.getPosition().y+positionOffset.y;
	sf::Color debugColor = sf::Color(255, 0, 0, 255);
	if(isTrigger())
	{
		debugColor = sf::Color(0, 0, 255, 255);
	}
	if(!enabled)
	{
		debugColor = sf::Color(128, 128, 128, 255);
	}
	DebugDraw::getInstance().drawRectangle(sf::Vector2f(bounds.left, bounds.top), sf::Vector2f(bounds.width, bounds.height), debugColor);
}

bool AABBColliderComponent::intersect(std::shared_ptr<ColliderComponent> otherCol)
{
	std::shared_ptr<AABBColliderComponent> cmp = std::dynamic_pointer_cast<AABBColliderComponent>(otherCol);
	if(cmp != nullptr)
	{
		return vsAABB(cmp);
	}
	return false;
}

sf::FloatRect AABBColliderComponent::getBounds() const
{
	return bounds;
}

void AABBColliderComponent::setEnabled(bool enabled)
{
	this->enabled = enabled;
}

bool AABBColliderComponent::isEnabled() const
{
	return enabled;
}

bool AABBColliderComponent::vsAABB(std::shared_ptr<AABBColliderComponent> otherCol)
{
	if(!enabled||!otherCol->enabled)
	{
		return false;
	}
	auto getCenter = [](const sf::FloatRect& rect) -> sf::Vector2f
	{
		return sf::Vector2f(rect.left, rect.top) + 0.5f * sf::Vector2f(rect.width, rect.height);
	};

	sf::Vector2f n = getCenter(otherCol->getBounds()) - getCenter(bounds);		// Vector from A to B
	float a_extent = bounds.width * 0.5f;			    // Calculate half extents along x axis
	float b_extent = otherCol->getBounds().width * 0.5f;
	float x_overlap = a_extent + b_extent - abs(n.x);		// Calculate overlap on x axis
															// SAT test on x axis
	if (x_overlap > 0) {
		float a_extent = bounds.height * 0.5f;		// Calculate half extents along y axis
		float b_extent = otherCol->getBounds().height * 0.5f;
		float y_overlap = a_extent + b_extent - abs(n.y);	// Calculate overlap on y axis
		
		sf::Vector2f normal;
		float penetration;
		Manifold manifold;
		
		if (y_overlap > 0) {
			// Find out which axis is axis of least penetration
			if (x_overlap < y_overlap) {
				// Point towards B knowing that n points from A to B
				if (n.x < 0)
					normal = sf::Vector2f(1.0f, 0.0f);
				else
					normal = sf::Vector2f(-1.0f, 0.0f);
				penetration = x_overlap;
				manifold.body1 = gameObject.getComponent<RigidBodyComponent>().get();
				manifold.body2 = otherCol->getGameObject().getComponent<RigidBodyComponent>().get();
				manifold.normal = normal;
				manifold.penetration = penetration;
				if (!isTrigger() && !otherCol->isTrigger()) {
					PhysicsManager::getInstance().addManifold(manifold);
				}
				return true;
			}
			else {
				// Point towards B knowing that n points from A to B
				if (n.y < 0)
					normal = sf::Vector2f(0, 1);
				else
					normal = sf::Vector2f(0, -1);
				penetration = y_overlap;
				manifold.body1 = gameObject.getComponent<RigidBodyComponent>().get();
				manifold.body2 = otherCol->getGameObject().getComponent<RigidBodyComponent>().get();
				manifold.normal = normal;
				manifold.penetration = penetration;
				if (!isTrigger() && !otherCol->isTrigger()) {
					PhysicsManager::getInstance().addManifold(manifold);
				}
				return true;
			}
		}
	}
	return false;
}

