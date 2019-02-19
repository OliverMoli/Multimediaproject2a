#include "pch.h"
#include "Game.h"
#include "GameStateManager.h"
#include "InputManager.h"
#include "PhysicsManager.h"
#include "DebugDraw.h"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Window.hpp>
#include "MainMenuState.h"
#include "PlayState.h"
#include "SetupState.h"
#include "RenderManager.h"


Game::Game(std::string gameTitle)
{
	this->gameTitle = gameTitle;
}

void Game::initialize(int windowWidth, int windowHeight)
{
	window.create(sf::VideoMode(windowWidth, windowHeight), gameTitle);
	window.setFramerateLimit(60);
	gui.setTarget(window);
	gui.setFont("../assets/Minimal5x7.ttf");
	GameStateManager::getInstance().registerState("MainMenuState", std::make_shared<MainMenuState>());
	GameStateManager::getInstance().registerState("SetupState", std::make_shared<SetupState>());
	GameStateManager::getInstance().registerState("PlayState", std::make_shared<PlayState>());
	RenderManager::getInstance().setGui(&gui);
	GameStateManager::getInstance().setState("MainMenuState");
	InputManager::getInstance().bind("Debug", sf::Keyboard::Key::F1, 0);
	InputManager::getInstance().bind("Test", sf::Keyboard::P, 0);
	update();
}

void Game::update()
{
	sf::Clock clock;
	double lastTime = 0.0f;
	while (window.isOpen()) {
		sf::Event event;
		InputManager::getInstance().setLastKeyState();
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			InputManager::getInstance().processKeyEvent(event);
		}
		double newTime = clock.getElapsedTime().asSeconds();
		float deltaTime = newTime-lastTime;
		DebugDraw::getInstance().update(deltaTime);
		PhysicsManager::getInstance().update(deltaTime);
		GameStateManager::getInstance().update(deltaTime);
		render();
		lastTime = newTime;
	}
	shutdown();
}

void Game::render()
{
	window.clear();
	GameStateManager::getInstance().render(window);
	window.display();	
}

void Game::shutdown()
{
	GameStateManager::getInstance().freeStates();
	InputManager::getInstance().freeResources();
	DebugDraw::getInstance().freeResources();
}
