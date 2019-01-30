#pragma once
#include "Component.h"
#include "ICollisionObserver.h"
#include "CharacterInfoComponent.h"
#include "PlayerControllerComponent.h"


class BallComponent : public Component, public ICollisionObserver
{
public:
	BallComponent(GameObject& owner, std::string owningPlayfieldName, float ballSpeed,float resetLastDelay,float stunDuration,float neutralVelocityCutoff,float velocityFactorOnEnemyHit);
	void initialize() override;
	void update(float deltaTime) override;
	void onCollision(CollisionInfo colInfo) override;
	void resetComponent();
	void respawnRandomly();
	void enableCollisionAfterDelay();
	void throwBall(sf::Vector2f direction);
private:
	void onPlayerPickup(CollisionInfo colInfo);
	void onPlayerDamage(CollisionInfo colInfo);
	GameObject* playfield = nullptr;
	GameObject* ballHolder = nullptr;
	GameObject* lastHolder = nullptr;
	CharacterInfoComponent* characterInfo = nullptr;
	IController* controller;
	sf::Vector2f ballPositionOffset = sf::Vector2f(8, 25);
	sf::Vector2f aimOffset;
	sf::Clock clock;
	int chargeCounter = 0;
	Team owningTeam = Team::Neutral;
	float throwTime = 0;
	float hitTime = 0;
	float resetLastDelay = 0.1f;
	float hitDelay;
	float stunDurationPerCharge;
	float ballSpeed;
	float neutralVelocityCutoff;
	float velocityFactorOnEnemyHit;
	std::vector<GameObject*> hadBall;
};
