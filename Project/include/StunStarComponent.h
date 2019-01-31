#pragma once
#include "Component.h"
#include <SFML/System/Clock.hpp>
#include "AnimatedSprite.h"


class StunStarComponent : public Component
{
public:
	StunStarComponent(GameObject& owner, float duration);
	void initialize() override;
	void update(float deltaTime) override;
	void initAnims(std::string name);


private:
	float duration;
	float startTime;
	sf::Clock clock;
	AnimatedSprite animSprite;
	Animation* currentAnimation;
	Animation starAnim;

};
