#include "pch.h"
#include "PlayState.h"

void PlayState::initialize()
{
}

void PlayState::update(float deltaTime)
{
	std::cout << "works";
	GameState::update(deltaTime);
}

void PlayState::render(sf::RenderWindow & window)
{
	GameState::render(window);
}

void PlayState::exit()
{
	GameState::exit();
}
