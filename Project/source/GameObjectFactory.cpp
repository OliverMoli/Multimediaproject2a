#include "pch.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "SpriteRenderComponent.h"
#include "ResourceManager.h"
#include "GameStateManager.h"


void GameObjectFactory::CreatePlayer(NLTmxMapObject object)
{
	auto playerObject = make_shared<GameObject>(object.name, object.type);

	struct PlayerValues
	{
		string textureName;
		string team;
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
	}
		playerObject->setPosition(object.x, object.y);
		playerObject->addComponent(std::make_shared<SpriteRenderComponent>(*playerObject, *ResourceManager::getInstance().getTexture(values.textureName)));
		playerObject->getComponent<SpriteRenderComponent>()->setLayer(Player);
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
	GameStateManager::getInstance().getCurrentState()->addGameObject(flagObject);
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


