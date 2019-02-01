#include "pch.h"
#include "MainMenuState.h"
#include "InputManager.h"
#include "GameStateManager.h"
#include "ResourceManager.h"
#include "Game.h"
#include "RenderManager.h"
#include "SoundManager.h"


void MainMenuState::initialize()
{
	clock = sf::Clock();
	lastFocusChange = -100;
	createMenuUi();
	SoundManager::getInstance().playSound("startMusic", 20, 1, true);
}

void MainMenuState::update(float deltaTime)
{
	GameState::update(deltaTime);
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) >= 90 && clock.getElapsedTime().asSeconds() > lastFocusChange + focusDelay)
	{
		RenderManager::getInstance().getGui()->focusNextWidget();
		lastFocusChange = clock.getElapsedTime().asSeconds();
	}
	else if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) <= -90 && clock.getElapsedTime().asSeconds() > lastFocusChange + focusDelay)
	{
		RenderManager::getInstance().getGui()->focusPreviousWidget();
		lastFocusChange = clock.getElapsedTime().asSeconds();
	}

	if (sf::Joystick::isButtonPressed(0, (int)InputManager::XboxButtons::A))
	{
		if (startButton->isFocused())
		{
			RenderManager::getInstance().getGui()->removeAllWidgets();
			GameStateManager::getInstance().setState("SetupState");
		}
		else if (creditsButton->isFocused())
		{
			RenderManager::getInstance().getGui()->removeAllWidgets();
			creditsButton->setFocused(false);
			inCredits = true;
			createCreditsUi();
		}
		else if (exitButton->isFocused())
		{
			GameStateManager::getInstance().getWindow()->close();
		}
	}

	if (sf::Joystick::isButtonPressed(0, (int)InputManager::XboxButtons::B) && inCredits)
	{
		inCredits = false;
		RenderManager::getInstance().getGui()->removeAllWidgets();
		createMenuUi();
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

void MainMenuState::createMenuUi()
{
	
	auto theme = std::make_shared<tgui::Theme>("../assets/Black.txt");
	tgui::Theme::setDefault(theme.get());
	auto vert = tgui::VerticalLayout::create();
	vert->setSize("50%", "100%");
	vert->setPosition("25%", 0);
	startButton = tgui::Button::create("Start");
	creditsButton = tgui::Button::create("Credits");
	exitButton = tgui::Button::create("Exit");
	startButton->setTextSize(50);
	creditsButton->setTextSize(50);
	exitButton->setTextSize(50);
	
	vert->addSpace(1.0f);
	vert->add(startButton, "button_start");
	vert->addSpace(0.1f);
	vert->add(creditsButton, "button_options");
	vert->addSpace(0.1f);
	vert->add(exitButton, "button_exit");
	vert->addSpace(1.0f);
	startButton->setTextSize(40);
	

	
	
	
	/*auto hori = tgui::VerticalLayout::create();
	
	hori->setSize("10%", "10%");
	hori->setPosition("20%", "10%");
	hori->add(panel);
	panel->setSize("100%", "100%");
	panel->setPosition("0%", "0%");

	
	fhLogo = tgui::Picture::create("../assets/BluePlayer1.png");
	fhLogo->setSize("10%", "10%");
	fhLogo->setPosition("-20%", "0%");
	hori->add(fhLogo); */
	
	
	
	

	RenderManager::getInstance().getGui()->add(vert);
	//RenderManager::getInstance().getGui()->add(hori);
	RenderManager::getInstance().getGui()->focusNextWidget();

}

void MainMenuState::createCreditsUi()
{
	auto theme = std::make_shared<tgui::Theme>("../assets/Black.txt");
	tgui::Theme::setDefault(theme.get());
	auto vert = tgui::VerticalLayout::create();
	vert->setSize("33%", "100%");
	vert->setPosition("33%", 0);
	std::shared_ptr<tgui::Label> creditsLabel = tgui::Label::create(creditsText);
	creditsLabel->setTextSize(50);
	vert->add(creditsLabel);
	RenderManager::getInstance().getGui()->add(vert);
}
