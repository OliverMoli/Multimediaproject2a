#include "pch.h"
#include "StunStarComponent.h"
#include "ResourceManager.h"
#include "SpriteRenderComponent.h"
#include "RigidBodyComponent.h"
#include "Game.h"
#include "PlayerControllerComponent.h"


StunStarComponent::StunStarComponent(GameObject& owner) :Component(owner)
{
	stunStars = *ResourceManager::getInstance().getTexture("stunStars");
	
}

void StunStarComponent::initialize()
{

}

void StunStarComponent::update(float deltaTime)
{
	if(stunnedPlayer != nullptr)
	{
		gameObject.setPosition(stunnedPlayer->getPosition() + starPositionOffset);
		gameObject.getComponent<SpriteRenderComponent>()->setTexture(stunStars);
	}
}
void StunStarComponent::onCollision(CollisionInfo colInfo)
{
	if(colInfo.otherCol->getType() == "Ball")
	{
		onPlayerStun(colInfo);
	}
}

void StunStarComponent::onPlayerStun(CollisionInfo colInfo)
{
	stunnedPlayer = colInfo.otherCol;
}

sf::Vector2f StunStarComponent::getStarPositionOffset() const
{
	return starPositionOffset;
}

void StunStarComponent::setStarPositionOffSet(sf::Vector2f offset)
{
	starPositionOffset = offset;
}






