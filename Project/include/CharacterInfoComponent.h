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
	CharacterInfoComponent(GameObject& owner);
	void initialize() override;
	void update(float deltaTime) override;
	void setHasFlag(bool val);
	bool getHasFlag() const;
	void setTeam(Team team);
	Team getTeam() const;

private:
	bool hasFlag = false;
	Team team;
	FlagComponent* flagComponent;
};

