#pragma once
#include "GameObject.h"
///Components that should listen to collision events have to inherit from this
class ICollisionObserver
{
public:
	///Contains relevant information for Collisions
	struct CollisionInfo
	{
		///The other gameObject this gameobject collided with
		GameObject* otherCol;
	};
	virtual void onCollision(CollisionInfo colInfo) = 0;
};
