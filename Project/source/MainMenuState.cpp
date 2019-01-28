#include "pch.h"
#include "MainMenuState.h"
#include "InputManager.h"
#include "GameStateManager.h"

void MainMenuState::initialize()
{
}

void MainMenuState::update(float deltaTime)
{
	GameState::update(deltaTime);
	if(InputManager::getInstance().isKeyDown("Play",0))
	{
		GameStateManager::getInstance().setState("PlayState");
	}
}

void MainMenuState::render(sf::RenderWindow & window)
{
	GameState::render(window);
}

void MainMenuState::exit()
{
	GameState::exit();
}
