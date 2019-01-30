#pragma once
#include "Component.h"
#include "ICollisionObserver.h"
#include "CharacterInfoComponent.h"


class BallComponent : public Component, public ICollisionObserver
{
public:
	BallComponent(GameObject& owner, std::string owningPlayfieldName, float ballSpeed,float resetLastDelay);
	void initialize() override;
	void update(float deltaTime) override;
	void onCollision(CollisionInfo colInfo) override;
	std::string getOwningPlayfieldName();
	void resetComponent();
	void respawnRandomly();
	void enableCollisionAfterDelay();
private:
	GameObject* playfield = nullptr;
	float ballSpeed;
	void onPlayerPickup(CollisionInfo colInfo);
	GameObject* ballHolder = nullptr;
	GameObject* lastHolder = nullptr;
	CharacterInfoComponent* characterInfo = nullptr;
	sf::Vector2f ballPositionOffset = sf::Vector2f(8, 25);
	sf::Vector2f aimOffset;
	sf::Clock clock;
	float deadZoneU = 20;
	float deadZoneV = 20;
	float throwTime = 0;
	float resetLastDelay = 0.1f;
	
};
