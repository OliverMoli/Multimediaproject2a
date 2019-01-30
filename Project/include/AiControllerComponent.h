#pragma once
#include "IController.h"

class AiControllerComponent : public Component, public IController
{
public:
	AiControllerComponent(GameObject& owner);
	void initialize() override;
	void update(float deltaTime) override;
	void setBall(GameObject* go) override;
	void setStunned(bool stunned) override;
	bool isStunned() const override;
	void stun(float duration);
private:
	sf::Clock clock;
	float unstunTime = 0;
};

