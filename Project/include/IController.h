#pragma once
#include "MovementComponent.h"

class BallComponent;

class IController
{
public:
	virtual void setBall(GameObject* go);
protected:
	MovementComponent* owner = nullptr;
	GameObject* ball = nullptr;
};

