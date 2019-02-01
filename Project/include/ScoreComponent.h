#pragma once
#include "Component.h"
#include "RenderComponent.h"
#include "CharacterInfoComponent.h"
#include <SFML/Graphics/Text.hpp>

class ScoreComponent : public RenderComponent
{
public:
	ScoreComponent(GameObject& owner);
	void initialize() override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
	void incrementScore(Team team,int amount);
private:
	int scoreRedTeam =0, scoreBlueTeam=0;
	sf::Text redText, blueText,timeText,winnerText;
	float gameLength = 180;
	sf::Clock clock;
};
