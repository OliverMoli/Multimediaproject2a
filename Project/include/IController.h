#pragma once
#include "MovementComponent.h"

class IController
{
protected:
	MovementComponent* owner = nullptr;
};

