#pragma once
#include "Component.h"
#include "ICollisionObserver.h"
#include <SFML/Graphics/Texture.hpp>

class FlagComponent : public Component,public ICollisionObserver
{
public:
	FlagComponent(GameObject& owner,int scorePerTick, float tickDuration);
	void initialize() override;
	void update(float deltaTime) override;
	void onCollision(CollisionInfo colInfo) override;
	int getScorePerTick() const;
	float getTickDuration() const;
	void setScorePerTick(int score);
	void setTickDuration(float duration);
	sf::Vector2f getFlagPositionOffset() const;
	void setFlagPositionOffset(sf::Vector2f offset);
	GameObject* getFlagHolder() const;
	void setFlagHolder(GameObject* holder);
	void useDefaultFlag();
private:
	void onPlayerPickup(CollisionInfo colInfo);
	int scorePerTick;
	float tickDuration;
	float normalFriction;
	float flagHolderFriction;
	GameObject* flagHolder= nullptr;
	sf::Vector2f flagPositionOffset = sf::Vector2f(0, -40);
	sf::Texture redFlagPickup, blueFlagPickup;
};

