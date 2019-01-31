#pragma once
#include "Component.h"
#include "FlagComponent.h"


class BallComponent;

enum class Team
{
	BlueTeam = 0,
	RedTeam = 1,
	Neutral = 2
};
class CharacterInfoComponent :public Component
{
public:
	CharacterInfoComponent(GameObject& owner);
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
	void setLastDashTime(float time);
	float getLastDashTime() const;
	void setBallComp(BallComponent* ball);
	BallComponent* getBallComp();
private:
	bool hasFlag = false;
	bool hasBall = false;
	Team team;
	FlagComponent* flagComponent;
	float lastTickTime;
	sf::Clock clock;
	int playerIndex;
	float lastDashTime;
	BallComponent* ballComponent;
};

