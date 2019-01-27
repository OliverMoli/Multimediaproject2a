#include "pch.h"
#include "ColliderComponent.h"

ColliderComponent::ColliderComponent(GameObject& owner,bool isTrigger) :Component(owner)
{
	this->trigger = isTrigger;
}

void ColliderComponent::initialize()
{
}

void ColliderComponent::update(float deltaTime)
{
}

bool ColliderComponent::isTrigger() const
{
	return trigger;
}
