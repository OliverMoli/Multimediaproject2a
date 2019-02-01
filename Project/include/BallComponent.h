#pragma once
#include "Component.h"
#include "ICollisionObserver.h"
#include "PlayerControllerComponent.h"


class BallComponent : public Component, public ICollisionObserver
{
public:
	BallComponent(GameObject& owner, std::string owningPlayfieldName, float ballSpeed,float resetLastDelay,float stunDuration,float neutralVelocityCutoff,float velocityFactorOnEnemyHit,GameObject& arrow1,GameObject& arrow2);
	void initialize() override;
	void update(float deltaTime) override;
	void onCollision(CollisionInfo colInfo) override;
	void enableCollisionAfterDelay();
	void throwBall(sf::Vector2f direction);
	void respawnPlayer(float delay,GameObject* player);
	void setOwningTeam(Team team);
	void resetChargeCounter();
	void setBallHolder(GameObject* go);
	void showNextMarker();
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
	float neutralVelocityCutoff;
	float velocityFactorOnEnemyHit;
	float ballVelocityPerCharge;
	std::vector<GameObject*> hadBall;
	std::vector<GameObject*> arrows;
};
