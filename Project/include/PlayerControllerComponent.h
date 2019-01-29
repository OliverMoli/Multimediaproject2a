#pragma once
#include "Component.h"
#include "IController.h"
#include "CharacterInfoComponent.h"

class PlayerControllerComponent : public Component, public IController
{
public:
	PlayerControllerComponent(GameObject& owner);
	void initialize() override;
	void update(float deltaTime) override;
private:
	float deadZoneX = 20, deadZoneY = 20;
	CharacterInfoComponent* characterInfo;
	float lastDashTime;
	sf::Clock clock;
	
};

