#pragma once
#include "Component.h"
#include "ICollisionObserver.h"

class FlagComponent : public Component,public ICollisionObserver
{
public:
	FlagComponent(GameObject& owner);
	void initialize() override;
	void update(float deltaTime) override;
	void onCollision(CollisionInfo colInfo) override;
	int getScorePerTick() const;
	float getTickDuration() const;
	void setScorePerTick(int score);
	void setTickDuration(float duration);
private:
	int scorePerTick = 5;
	float tickDuration = 3;
};
