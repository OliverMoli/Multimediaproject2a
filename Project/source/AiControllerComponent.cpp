#include "pch.h"
#include "AiControllerComponent.h"

AiControllerComponent::AiControllerComponent(GameObject & owner):Component(owner)
{
}

void AiControllerComponent::initialize()
{
}

void AiControllerComponent::update(float deltaTime)
{
}

void AiControllerComponent::setBall(GameObject * go)
{
	IController::setBall(ball);
}
