#pragma once
#include "Component.h"
#include "RenderComponent.h"
#include "CharacterInfoComponent.h"

class ScoreComponent : public RenderComponent
{
public:
	ScoreComponent(GameObject& owner);
	void initialize() override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
	void incrementScore(Team team,int amount);
private:
	int scoreRedTeam, scoreBlueTeam;
};