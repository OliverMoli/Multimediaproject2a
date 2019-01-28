#pragma once
#include "Component.h"

class PlayerControllerComponent:public Component
{
public:
	PlayerControllerComponent(GameObject& owner);
	void initialize() override;
	void update(float deltaTime) override;
};

