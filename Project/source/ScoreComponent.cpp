#include "pch.h"
#include "ScoreComponent.h"


ScoreComponent::ScoreComponent(GameObject& owner):RenderComponent(owner)
{
}

void ScoreComponent::initialize()
{
}

void ScoreComponent::update(float deltaTime)
{
}

void ScoreComponent::render(sf::RenderWindow & window)
{

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
