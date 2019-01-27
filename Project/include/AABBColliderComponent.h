#pragma once
#include "ColliderComponent.h"
#include <SFML/Graphics/Rect.hpp>

class AABBColliderComponent : public ColliderComponent
{
public:
	AABBColliderComponent(GameObject& owner,float width,float height,bool isTrigger,sf::Vector2f positionOffset);
	void initialize() override;
	void update(float deltaTime) override;
	///Checks for intersections with another collider
	///@param otherCol the collider to test this collider against
	bool intersect(std::shared_ptr<ColliderComponent> otherCol) override;
	sf::FloatRect getBounds() const;
private:
	bool vsAABB(std::shared_ptr<AABBColliderComponent> otherCol);
	sf::FloatRect bounds;
	sf::Vector2f positionOffset;
};
