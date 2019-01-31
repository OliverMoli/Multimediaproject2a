#include "pch.h"
#include "FlagComponent.h"
#include "CharacterInfoComponent.h"
#include "RigidBodyComponent.h"
#include "Game.h"
#include "AABBColliderComponent.h"
#include "ResourceManager.h"
#include "SpriteRenderComponent.h"
#include "MovementComponent.h"

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
	if(colInfo.otherCol->getComponent<CharacterInfoComponent>()->getHasBall())
	{
		return;
	}
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
	flagHolder->getComponent<MovementComponent>()->useFlagValues();
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

GameObject * FlagComponent::getFlagHolder() const
{
	return flagHolder;
}

void FlagComponent::setFlagHolder(GameObject * holder)
{
	flagHolder = holder;
}

void FlagComponent::useDefaultFlag()
{
	gameObject.getComponent<SpriteRenderComponent>()->setTexture(*ResourceManager::getInstance().getTexture("flag"));
}


