#include "pch.h"
#include "MainMenuState.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "ResourceManager.h"
#include "Game.h"

void MainMenuState::initialize()
{
	ResourceManager::getInstance().loadFont("arial", "../assets/arial.ttf");
	
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
	sf::Text text("I do work :)", *ResourceManager::getInstance().getFont("arial"));
	text.setFillColor(sf::Color::White);
	text.setPosition(250, 275);
	window.draw(text);
}

void MainMenuState::exit()
{
	GameState::exit();
}
