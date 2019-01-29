#include "pch.h"
#include "SetupState.h"
#include <SFML/Window/Joystick.hpp>
#include "InputManager.h"
#include "GameStateManager.h"
#include <TGUI/Loading/Theme.hpp>
#include "RenderManager.h"
#include <TGUI/Widgets/HorizontalLayout.hpp>
#include <TGUI/Color.hpp>
#include <TGUI/Widgets/Picture.hpp>

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
	auto theme = std::make_shared<tgui::Theme>("../assets/Black.txt");
	tgui::Theme::setDefault(theme.get());
	auto horiTop = tgui::HorizontalLayout::create();
	auto horiBot = tgui::HorizontalLayout::create();
	horiTop->setSize("80%", "40%");
	horiTop->setPosition("10%", "7.5%");
	player1 = tgui::Panel::create("33%");
	player2 = tgui::Panel::create("33%");
	player3 = tgui::Panel::create("33%");
	horiTop->add(player1, "sas");
	horiTop->addSpace(0.1f);
	horiTop->add(player2, "sas");
	horiTop->addSpace(0.1f);
	horiTop->add(player3, "sas");
	horiTop->addSpace(0.1f);

	horiBot->setSize("80%", "40%");
	horiBot->setPosition("10%", "52.5%");
	player4 = tgui::Panel::create("33%");
	player5 = tgui::Panel::create("33%");
	player6 = tgui::Panel::create("33%");
	horiBot->add(player4, "sas");
	horiBot->addSpace(0.1f);
	horiBot->add(player5, "sas");
	horiBot->addSpace(0.1f);
	horiBot->add(player6, "sas");
	horiBot->addSpace(0.1f);

	auto bg = std::make_shared <tgui::Picture>("../assets/BluePlayer1.png");
	player1->add(bg);
	bg->setSize("50%", "50%");
	bg->setPosition("25%", "15%");

	RenderManager::getInstance().getGui()->add(horiTop);
	RenderManager::getInstance().getGui()->add(horiBot);

}
