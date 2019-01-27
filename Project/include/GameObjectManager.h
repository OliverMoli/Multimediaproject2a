#pragma once
#include "GameObject.h"

class GameObjectManager
{
public:
	static GameObjectManager& getInstance();
	std::vector<GameObject *> GetByType(std::string type);
	GameObject* GetGameObjectByName(std::string name);
private:
	GameObjectManager() = default;
	~GameObjectManager() = default;
	GameObjectManager(const GameObjectManager& p) = delete;
	GameObjectManager& operator=(GameObjectManager const&) = delete;
};

