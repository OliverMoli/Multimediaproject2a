#include "pch.h"
#include "Component.h"

Component::Component(GameObject& owner):gameObject(owner){
}

GameObject& Component::getGameObject()
{
	return gameObject;
}
