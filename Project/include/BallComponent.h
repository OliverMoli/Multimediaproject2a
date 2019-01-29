#pragma once
#include "Component.h"
#include "ICollisionObserver.h"
#include "CharacterInfoComponent.h"


class BallComponent : public Component, public ICollisionObserver
{
	public:
		BallComponent(GameObject& owner, std::string owningPlayfieldName, float ballSpeed);
		void initialize() override;
		void update(float deltaTime) override;
		void onCollision(CollisionInfo colInfo) override;
		std::string getOwningPlayfieldName();
		void resetComponent();
		void respawnRandomly();

	private:
		
		std::string owningPlayfieldName;
		float ballSpeed;
		void onPlayerPickup(CollisionInfo colInfo);
		GameObject* ballHolder = nullptr;
		sf::Vector2f ballPositionOffset = sf::Vector2f(8, 25);
		CharacterInfoComponent* characterInfo = nullptr;
		sf::Vector2f aimOffset;
		float deadZoneU = 20;
		float deadZoneV = 20;
		
};
