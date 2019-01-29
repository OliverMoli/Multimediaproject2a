#include "pch.h"
#include "FlagComponent.h"
#include "CharacterInfoComponent.h"
#include "RigidBodyComponent.h"
#include "Game.h"
#include "AABBColliderComponent.h"
#include "ResourceManager.h"
#include "SpriteRenderComponent.h"

FlagComponent::FlagComponent(GameObject& owner, int scorePerTick, float tickDuration) :Component(owner)
{
	this->scorePerTick = scorePerTick;
	this->tickDuration = tickDuration;
	blueFlagPickup = *ResourceManager::getInstance().getTexture("flagPickupBlue");
	redFlagPickup = *ResourceManager::getInstance().getTexture("flagPickupRed");
}

void FlagComponent::initialize()
{
}

void FlagComponent::update(float deltaTime)
{
	if (flagHolder != nullptr)
	{
		gameObject.setPosition(flagHolder->getPosition() + flagPositionOffset);
	}
}

void FlagComponent::onCollision(CollisionInfo colInfo)
{
	if (colInfo.otherCol->getType() == "Player")
	{
		onPlayerPickup(colInfo);
	}
}

void FlagComponent::onPlayerPickup(CollisionInfo colInfo)
{
	colInfo.otherCol->getComponent<CharacterInfoComponent>()->setHasFlag(true);
	gameObject.getComponent<AABBColliderComponent>()->setEnabled(false);
	flagHolder = colInfo.otherCol;
	if (flagHolder->getComponent<CharacterInfoComponent>()->getTeam() == Team::BlueTeam)
	{
		gameObject.getComponent<SpriteRenderComponent>()->setTexture(blueFlagPickup);
	}
	else
	{
		gameObject.getComponent<SpriteRenderComponent>()->setTexture(redFlagPickup);
	}
}

int FlagComponent::getScorePerTick() const
{
	return scorePerTick;
}

float FlagComponent::getTickDuration() const
{
	return tickDuration;
}

void FlagComponent::setScorePerTick(int score)
{
	scorePerTick = score;
}

void FlagComponent::setTickDuration(float duration)
{
	tickDuration = duration;
}


sf::Vector2f FlagComponent::getFlagPositionOffset() const
{
	return flagPositionOffset;
}

void FlagComponent::setFlagPositionOffset(sf::Vector2f offset)
{
	flagPositionOffset = offset;
}


