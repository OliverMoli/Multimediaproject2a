#include "pch.h"
#include "ScoreComponent.h"
#include <SFML/Graphics/Text.hpp>
#include "ResourceManager.h"


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
	redText.setPosition(50, 0);
}

void ScoreComponent::update(float deltaTime)
{
	redText.setString(std::to_string(scoreRedTeam));
	blueText.setString(std::to_string(scoreBlueTeam));
}

void ScoreComponent::render(sf::RenderWindow & window)
{
	window.draw(blueText,gameObject.getTransform());
	window.draw(redText, gameObject.getTransform());
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
