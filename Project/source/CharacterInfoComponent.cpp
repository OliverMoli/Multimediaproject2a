#include "pch.h"
#include "CharacterInfoComponent.h"
#include "GameObjectManager.h"
#include "ScoreComponent.h"

CharacterInfoComponent::CharacterInfoComponent(GameObject & owner) :Component(owner)
{
}

void CharacterInfoComponent::initialize()
{
	flagComponent = GameObjectManager::getInstance().GetGameObjectByName("Flag")->getComponent<FlagComponent>().get();
	clock = sf::Clock();
	lastTickTime = clock.getElapsedTime().asSeconds();
}

void CharacterInfoComponent::update(float deltaTime)
{
	if (hasFlag && clock.getElapsedTime().asSeconds() > lastTickTime + flagComponent->getTickDuration())
	{
		GameObjectManager::getInstance().GetGameObjectByName("Score")->getComponent<ScoreComponent>()->incrementScore(team, flagComponent->getScorePerTick());
		lastTickTime = clock.getElapsedTime().asSeconds();
	}
}

void CharacterInfoComponent::setHasFlag(bool val)
{
	this->hasFlag = val;
}

bool CharacterInfoComponent::getHasFlag() const
{
	return hasFlag;
}

void CharacterInfoComponent::setTeam(Team team)
{
	this->team = team;
}

Team CharacterInfoComponent::getTeam() const
{
	return team;
}

void CharacterInfoComponent::setPlayerIndex(int index)
{
	playerIndex = index;
}

int CharacterInfoComponent::getPlayerIndex() const
{
	return playerIndex;
}

void CharacterInfoComponent::setDashForce(float force)
{
	dashForce = force;
}

float CharacterInfoComponent::getDashForce() const
{
	return dashForce;
}

void CharacterInfoComponent::setDashCooldown(float cd)
{
	dashCooldown = cd;
}

float CharacterInfoComponent::getDashCooldown() const
{
	return dashCooldown;
}
