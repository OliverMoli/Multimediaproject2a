#pragma once
#include "Component.h"
#include "BallComponent.h"

class BallFireComponent : public Component
{
public:
	BallFireComponent(GameObject& owner,BallComponent& ball);
	void initialize() override;
	void update(float deltaTime) override;
private:
	BallComponent* ball;
	AnimatedSprite animSprite;
	Animation* currentAnim;
};

