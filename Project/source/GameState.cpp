#include "pch.h"
#include "GameState.h"
#include "RenderManager.h"
#include "DebugDraw.h"
#include "PhysicsManager.h"
#include "InputManager.h"
#include "SoundManager.h"

void GameState::update(float deltaTime)
{
	for (auto go : gameObjects)
	{
		if(!go->isActive())
		{
			continue;
		}
		go->update(deltaTime);
	}
	if (InputManager::getInstance().isKeyDown("Debug", 0))
	{
		DebugDraw::getInstance().setEnabled(!DebugDraw::getInstance().isEnabled());
	}
}

void GameState::render(sf::RenderWindow& window)
{
	RenderManager::getInstance().render(window);
	DebugDraw::getInstance().draw(window);
}

void GameState::exit()
{
	gameObjects.clear();
	ResourceManager::getInstance().freeResources();
	RenderManager::getInstance().freeResources();
	PhysicsManager::getInstance().freeResources();
	InputManager::getInstance().clearKeystates();
	SoundManager::getInstance().freeResources();
}

void GameState::addGameObject(std::shared_ptr<GameObject> go)
{
	gameObjects.push_back(go);
}

std::vector<std::shared_ptr<GameObject>>& GameState::getGameObjects()
{
	return gameObjects;
}
