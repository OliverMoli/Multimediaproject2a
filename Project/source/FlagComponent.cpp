#include "pch.h"
#include "FlagComponent.h"
#include "CharacterInfoComponent.h"
#include "RigidBodyComponent.h"

FlagComponent::FlagComponent(GameObject& owner):Component(owner)
{

}

void FlagComponent::initialize()
{
}

void FlagComponent::update(float deltaTime)
{

}

void FlagComponent::onCollision(CollisionInfo colInfo)
{
	if(colInfo.otherCol->getType() == "Player")
	{
		colInfo.otherCol->getComponent<CharacterInfoComponent>()->setHasFlag(true);
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
