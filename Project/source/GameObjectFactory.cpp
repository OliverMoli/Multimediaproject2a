#include "pch.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "SpriteRenderComponent.h"
#include "ResourceManager.h"
#include "GameStateManager.h"
#include "RigidBodyComponent.h"
#include "AABBColliderComponent.h"
#include "FlagComponent.h"
#include "ScoreComponent.h"
#include "MovementComponent.h"
#include "PlayerControllerComponent.h"


void GameObjectFactory::CreatePlayer(NLTmxMapObject object)
{
	auto playerObject = make_shared<GameObject>(object.name, object.type);

	struct PlayerValues
	{
		string textureName;
		string team;
		sf::Vector2f colOffset;
	};

	PlayerValues values;
	for (auto property : object.properties)
	{
		auto name = property->name;

		if (name == "textureName")
		{
			values.textureName = property->value;
		}
		else if (name == "team")
		{
			values.team = property->value;
		}
		else if (name == "colOffsetX")
		{
			values.colOffset.x = stof(property->value);
		}
		else if (name == "colOffsetY")
		{
			values.colOffset.y = stof(property->value);
		}
	}
	playerObject->setPosition(object.x, object.y);
	playerObject->addComponent(std::make_shared<SpriteRenderComponent>(*playerObject, *ResourceManager::getInstance().getTexture(values.textureName)));
	playerObject->getComponent<SpriteRenderComponent>()->setLayer(Player);
	playerObject->addComponent(std::make_shared<RigidBodyComponent>(*playerObject, 1.0f));
	playerObject->addComponent(std::make_shared<AABBColliderComponent>(*playerObject, object.width, object.height, false, values.colOffset));
	playerObject->addComponent(std::make_shared<MovementComponent>(*playerObject));
	playerObject->addComponent(std::make_shared<PlayerControllerComponent>(*playerObject));
	GameStateManager::getInstance().getCurrentState()->addGameObject(playerObject);

}

void GameObjectFactory::CreateFlag(NLTmxMapObject object)
{
	auto flagObject = make_shared<GameObject>(object.name, object.type);

	struct FlagValues
	{
		string textureName;
	};

	FlagValues values;
	for (auto property : object.properties)
	{
		auto name = property->name;

		if (name == "textureName")
		{
			values.textureName = property->value;
		}
	}

	flagObject->setPosition(object.x, object.y);
	flagObject->addComponent(std::make_shared<SpriteRenderComponent>(*flagObject, *ResourceManager::getInstance().getTexture(values.textureName)));
	flagObject->getComponent<SpriteRenderComponent>()->setLayer(Items);
	flagObject->addComponent(std::make_shared<RigidBodyComponent>(*flagObject, 0));
	flagObject->addComponent(std::make_shared<AABBColliderComponent>(*flagObject, object.width, object.height, true));
	flagObject->addComponent(std::make_shared<FlagComponent>(*flagObject));
	GameStateManager::getInstance().getCurrentState()->addGameObject(flagObject);
}

void GameObjectFactory::CreateScore()
{
	auto scoreObject = std::make_shared<GameObject>("Score", "Score");
	scoreObject->addComponent(std::make_shared<ScoreComponent>(*scoreObject));
	GameStateManager::getInstance().getCurrentState()->addGameObject(scoreObject);
}



bool GameObjectFactory::stob(string value)
{
	if (value == "true")
	{
		return true;
	}
	else if (value == "false")
	{
		return false;
	}
}


