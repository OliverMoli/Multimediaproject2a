#pragma once
#include "Component.h"
#include "IController.h"
#include "CharacterInfoComponent.h"
#include "StunStarComponent.h"
#include <SFML/System/Clock.hpp>


class PlayerControllerComponent : public Component, public IController
{
public:
	PlayerControllerComponent(GameObject& owner);
	void initialize() override;
	void update(float deltaTime) override;
	void setBall(GameObject* go) override;
	void setStunned(bool stunned) override;
	bool isStunned() const override;
	void stun(float duration);
private:
	float deadZoneX = 20, deadZoneY = 20;
	CharacterInfoComponent* characterInfo;
	float lastDashTime;
	sf::Clock clock;
	float deadZoneU = 20;
	float deadZoneV = 20;
	float unstunTime =0;
	//StunStarComponent* stunStar;
	
};

