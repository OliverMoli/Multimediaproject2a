#pragma once
#include "Component.h"
#include "ICollisionObserver.h"
#include "CharacterInfoComponent.h"
#include "PlayerControllerComponent.h"


class BallComponent : public Component, public ICollisionObserver
{
public:
	BallComponent(GameObject& owner, std::string owningPlayfieldName, float ballSpeed,float resetLastDelay);
	void initialize() override;
	void update(float deltaTime) override;
	void onCollision(CollisionInfo colInfo) override;
	void resetComponent();
	void respawnRandomly();
	void enableCollisionAfterDelay();
	void throwBall(sf::Vector2f direction);
private:
	GameObject* playfield = nullptr;
	float ballSpeed;
	void onPlayerPickup(CollisionInfo colInfo);
	GameObject* ballHolder = nullptr;
	GameObject* lastHolder = nullptr;
	CharacterInfoComponent* characterInfo = nullptr;
	IController* controller;
	sf::Vector2f ballPositionOffset = sf::Vector2f(8, 25);
	sf::Vector2f aimOffset;
	sf::Clock clock;
	float throwTime = 0;
	float resetLastDelay = 0.1f;
	int chargeCounter = 0;
	Team owningTeam;
};
