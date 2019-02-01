#include "pch.h"
#include "ScoreComponent.h"
#include <SFML/Graphics/Text.hpp>
#include "ResourceManager.h"
#include "GameStateManager.h"


ScoreComponent::ScoreComponent(GameObject& owner):RenderComponent(owner)
{
}

void ScoreComponent::initialize()
{
	redText.setFont(*ResourceManager::getInstance().getFont("arial"));
	redText.setFillColor(sf::Color::Red);
	blueText.setFont(*ResourceManager::getInstance().getFont("arial"));
	blueText.setFillColor(sf::Color::Blue);
	blueText.setPosition(-50, 0);
	redText.setPosition(100, 0);

	timeText.setFont(*ResourceManager::getInstance().getFont("arial"));
	timeText.setFillColor(sf::Color::Black);
	timeText.setPosition(0, 0);

	winnerText.setFont(*ResourceManager::getInstance().getFont("arial"));
	winnerText.setFillColor(sf::Color::Black);
	winnerText.setPosition(-50, 250);
	clock = sf::Clock();
}

void ScoreComponent::update(float deltaTime)
{
	if (clock.getElapsedTime().asSeconds() >= gameLength)
	{
		if (scoreBlueTeam > scoreRedTeam)
		{
			winnerText.setString("BLUE WON!");
		}
		else if (scoreBlueTeam < scoreRedTeam)
		{
			winnerText.setString("RED WON!");
		}
		else
		{
			winnerText.setString("DRAW!");
		}
		GameStateManager::getInstance().getCurrentState()->pause = true;
		return;
	}
	redText.setString(std::to_string(scoreRedTeam));
	blueText.setString(std::to_string(scoreBlueTeam));
	timeText.setString(std::to_string((int)(gameLength - clock.getElapsedTime().asSeconds())));
	
}

void ScoreComponent::render(sf::RenderWindow & window)
{
	window.draw(blueText,gameObject.getTransform());
	window.draw(redText, gameObject.getTransform());
	window.draw(winnerText, gameObject.getTransform());
	window.draw(timeText, gameObject.getTransform());
}

void ScoreComponent::incrementScore(Team team, int amount)
{
	switch(team)
	{
	case Team::RedTeam:
		scoreRedTeam += amount;
		break;
	case Team::BlueTeam:
		scoreBlueTeam += amount;
		break;
	}
}
