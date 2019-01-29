#include "pch.h"
#include "SetupState.h"
#include <SFML/Window/Joystick.hpp>
#include "InputManager.h"
#include "GameStateManager.h"


void SetupState::initialize()
{
	createSettingsUi();
}

void SetupState::update(float deltaTime)
{
	GameState::update(deltaTime);
	if(sf::Joystick::isButtonPressed(0,(int)InputManager::XboxButtons::Start))
	{
		GameStateManager::getInstance().setState("PlayState");
	}
	if (sf::Joystick::isButtonPressed(0, (int)InputManager::XboxButtons::B))
	{
		GameStateManager::getInstance().setState("MainMenuState");
	}
}

void SetupState::render(sf::RenderWindow & window)
{
	GameState::render(window);
}

void SetupState::exit()
{
	GameState::exit();
}

void SetupState::createSettingsUi()
{
}
