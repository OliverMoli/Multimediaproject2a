#include "pch.h"
#include "GameObjectManager.h"
#include "GameStateManager.h"


GameObjectManager& GameObjectManager::getInstance()
{
	static GameObjectManager instance;
	return instance;
}

std::vector<GameObject *> GameObjectManager::GetByType(std::string type)
{
	std::vector<GameObject*> result;
	for (auto go : GameStateManager::getInstance().getCurrentState()->getGameObjects())
	{
		if (go->getType() == type) {
			result.push_back(go.get());
		}
	}
	return result;
}

GameObject * GameObjectManager::GetGameObjectByName(std::string name)
{
	for (auto go : GameStateManager::getInstance().getCurrentState()->getGameObjects())
	{
		if (go->getName() == name)
		{
			return go.get();
		}
	}
	return nullptr;
}
