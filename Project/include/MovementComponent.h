#pragma once
#include "Component.h"

class MovementComponent:public Component
{
public:
	MovementComponent(GameObject& owner);
	void initialize() override;
	void update(float deltaTime) override;
};

