#pragma once
#include "Component.h"
#include <SFML/Graphics/Texture.hpp>
#include "ICollisionObserver.h"


class StunStarComponent : public Component, public ICollisionObserver
{
public:
	StunStarComponent(GameObject& owner);
	void initialize() override;
	void update(float deltaTime) override;
	sf::Vector2f getStarPositionOffset() const;
	void setStarPositionOffSet(sf::Vector2f offset);
	void onCollision(CollisionInfo colInfo) override;



private:
	void onPlayerStun(CollisionInfo colInfo);
	sf::Vector2f starPositionOffset = sf::Vector2f(0, -40);
	sf::Texture stunStars;
	GameObject* stunnedPlayer = nullptr;
};