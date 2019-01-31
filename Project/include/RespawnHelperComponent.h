#pragma once
#include "Component.h"
#include <SFML/System/Clock.hpp>

class RespawnHelperComponent : public Component
{
public:
	RespawnHelperComponent(GameObject& owner,GameObject& goToDestroy,float duration);
	void initialize() override;
	void update(float deltaTime) override;
private:
	GameObject* go;
	sf::Clock clock;
	float startTime;
	float duration;
};

