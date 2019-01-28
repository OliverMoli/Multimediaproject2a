#include "pch.h"
#include "GameStateManager.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "PhysicsManager.h"

GameStateManager& GameStateManager::getInstance()
{
	static GameStateManager instance;
	return instance;
}

bool GameStateManager::registerState(const std::string &name, std::shared_ptr<GameState> state)
{
	if (states.find(name) == states.end()) {
		states[name] = state;
		return true;
	}else
	{
		std::cout << "Error registering state. State [" << name << "] already exists!" << std::endl;
	}
	return false;
}

void GameStateManager::setState(const std::string &name)
{
	if (states.find(name) == states.end()) {
		std::cout << "Error setting state. State [" << std::string(name) << "] does not exist!" << std::endl;
	}
	else {
		std::shared_ptr<GameState> targetState = states[name];
		if (targetState != currentState) {
			if (currentState) {
				currentState->exit();
				//window->setView(window->getDefaultView());
			}
		}
		currentState = targetState;
		PhysicsManager::getInstance().resetFirstFrame();
		currentState->initialize();
	}
	
}

std::shared_ptr<GameState> GameStateManager::getCurrentState() const
{
	return currentState;
}

void GameStateManager::update(float deltaTime)
{
	if (currentState) {
		currentState->update(deltaTime);
	}
}

void GameStateManager::render(sf::RenderWindow& window)
{
	if (currentState) {
		currentState->render(window);
	}
	this->window = &window;
}


void GameStateManager::freeStates()
{
	if (currentState) {
		currentState->exit();
	}
	currentState = nullptr;
	states.clear();
	window = nullptr;
}
