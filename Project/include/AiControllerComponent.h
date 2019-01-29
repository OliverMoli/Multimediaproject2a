#pragma once
#include "GameObject.h"

class AiControllerComponent : public Component
{
public:
	AiControllerComponent(GameObject& owner);
	void initialize() override;
	void update(float deltaTime) override;
};

