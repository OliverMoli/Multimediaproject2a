#pragma once
#include "Component.h"
#include "IController.h"

class PlayerControllerComponent : public Component, public IController
{
public:
	PlayerControllerComponent(GameObject& owner);
	void initialize() override;
	void update(float deltaTime) override;
private:
	float deadZoneX = 20, deadZoneY = 20;
};

