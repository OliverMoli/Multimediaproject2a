#pragma once
#include "MovementComponent.h"

class BallComponent;

class IController
{
public:
	virtual void setBall(GameObject* go);
	virtual bool isStunned() const;
	virtual void setStunned(bool stunned);
protected:
	MovementComponent* owner = nullptr;
	GameObject* ball = nullptr;
	bool stunned = false;
};

