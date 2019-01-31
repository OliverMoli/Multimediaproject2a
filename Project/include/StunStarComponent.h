#pragma once
#include "Component.h"
#include <SFML/System/Clock.hpp>


class StunStarComponent : public Component
{
public:
	StunStarComponent(GameObject& owner, float duration);
	void initialize() override;
	void update(float deltaTime) override;
	void removeStunStar(float duration);


private:
	float duration;
	float startTime;
	sf::Clock clock;

};
