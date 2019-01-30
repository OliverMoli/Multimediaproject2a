#include "pch.h"
#include "IController.h"

void IController::setBall(GameObject * go)
{
	this->ball = go;
}

bool IController::isStunned() const
{
	return stunned;
}

void IController::setStunned(bool stunned)
{
	this->stunned = stunned;
}
