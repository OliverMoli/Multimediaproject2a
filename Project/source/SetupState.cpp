#include "pch.h"
#include "SetupState.h"


void SetupState::initialize()
{
}

void SetupState::update(float deltaTime)
{
	GameState::update(deltaTime);
}

void SetupState::render(sf::RenderWindow & window)
{
	GameState::render(window);
}

void SetupState::exit()
{
	GameState::exit();
}
