#pragma once
#include "Component.h"
#include "ICollisionObserver.h"


class BallComponent : public Component, public ICollisionObserver
{
	public:
		BallComponent(GameObject& owner, std::string owningPlayfieldName);
		void initialize() override;
		void update(float deltaTime) override;
		void onCollision(CollisionInfo colInfo) override;
		std::string getOwningPlayfieldName();
		void resetComponent();

	private:
		void respawnRandomly();
		std::string owningPlayfieldName;
		
};