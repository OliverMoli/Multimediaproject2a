#pragma once
#include "Component.h"
#include "FlagComponent.h"

enum class Team
{
	BlueTeam = 0,
	RedTeam = 1
};
class CharacterInfoComponent :public Component
{
public:
	CharacterInfoComponent(GameObject& owner, float dashForce, float dashCooldown);
	void initialize() override;
	void update(float deltaTime) override;
	void setHasFlag(bool val);
	bool getHasFlag() const;
	void setHasBall(bool val);
	bool getHasBall() const;
	void setTeam(Team team);
	Team getTeam() const;
	void setPlayerIndex(int index);
	int getPlayerIndex() const;
	void setDashForce(float force);
	float getDashForce() const;
	void setDashCooldown(float cd);
	float getDashCooldown() const;
	void setLastDashTime(float time);
	float getLastDashTime() const;
private:
	bool hasFlag = false;
	bool hasBall = false;
	Team team;
	FlagComponent* flagComponent;
	float lastTickTime;
	sf::Clock clock;
	int playerIndex;
	float dashForce;
	float dashCooldown;
	float lastDashTime;
};

