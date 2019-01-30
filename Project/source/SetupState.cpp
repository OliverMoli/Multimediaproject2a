#include "pch.h"
#include "SetupState.h"
#include <SFML/Window/Joystick.hpp>
#include "InputManager.h"
#include "GameStateManager.h"
#include <TGUI/Loading/Theme.hpp>
#include "RenderManager.h"
#include <TGUI/Widgets/HorizontalLayout.hpp>
#include <TGUI/Widgets/Picture.hpp>
#include <tgui/Widgets/Label.hpp>

void SetupState::initialize()
{
	clock = sf::Clock();
	lastFocusChange = -100;
	createSettingsUi();
	
}

void SetupState::update(float deltaTime)
{
	GameState::update(deltaTime);
	if(sf::Joystick::isButtonPressed(0,(int)InputManager::XboxButtons::Start))
	{
		RenderManager::getInstance().getGui()->removeAllWidgets();
		GameStateManager::getInstance().setState("PlayState");
		RenderManager::getInstance().getGui()->removeAllWidgets();
	}
	if (sf::Joystick::isButtonPressed(0, (int)InputManager::XboxButtons::B))
	{
		GameStateManager::getInstance().setState("MainMenuState");
		RenderManager::getInstance().getGui()->removeAllWidgets();
	}

	if(sf::Joystick::isButtonPressed(0,(int)InputManager::XboxButtons::X))
	{
		player1->remove(label);
		player1->add(characters[counter]);
	}
	
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) == 100 && clock.getElapsedTime().asSeconds() > lastFocusChange + focusDelay)
		{
			lastFocusChange = clock.getElapsedTime().asSeconds();
			std::cout << counter << std::endl;

			if(counter >= 5)
			{
				player1->remove(characters[counter]);
				counter = 0;
				player1->add(characters[counter]);
			}
			else
			{
				counter++;
				player1->remove(characters[counter - 1]);
				player1->add(characters[counter]);
			}
		}

		if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) == -100 && clock.getElapsedTime().asSeconds() > lastFocusChange + focusDelay)
		{
			lastFocusChange = clock.getElapsedTime().asSeconds();
			std::cout << counter << std::endl;

			if (counter <= 0)
			{
				player1->remove(characters[counter]);
				counter = 5;
				player1->add(characters[counter]);
			}
			else
			{
				counter--;
				player1->remove(characters[counter + 1]);
				player1->add(characters[counter]);
			}
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
	horiTop->setSize("90%", "40%");
	horiTop->setPosition("5%", "7.5%");
	player1 = tgui::Panel::create("33%");
	player2 = tgui::Panel::create("33%");
	player3 = tgui::Panel::create("33%");
	horiTop->add(player1, "sas");
	horiTop->addSpace(0.1f);
	horiTop->add(player2, "sas");
	horiTop->addSpace(0.1f);
	horiTop->add(player3, "sas");
	horiTop->addSpace(0.1f);

	horiBot->setSize("90%", "40%");
	horiBot->setPosition("5%", "52.5%");
	player4 = tgui::Panel::create("33%");
	player5 = tgui::Panel::create("33%");
	player6 = tgui::Panel::create("33%");
	horiBot->add(player4, "sas");
	horiBot->addSpace(0.1f);
	horiBot->add(player5, "sas");
	horiBot->addSpace(0.1f);
	horiBot->add(player6, "sas");
	horiBot->addSpace(0.1f);

	blueOrc1 = tgui::Picture::create("../assets/BluePlayer1.png");
	blueOrc2 = tgui::Picture::create("../assets/BluePlayer2.png");
	blueOrc3 = tgui::Picture::create("../assets/BluePlayer3.png");
	blueOrc1->setSize("50%", "50%");
	blueOrc1->setPosition("25%", "15%");	
	blueOrc2->setSize("50%", "50%");
	blueOrc2->setPosition("25%", "15%");	
	blueOrc3->setSize("50%", "50%");
	blueOrc3->setPosition("25%", "15%");

	redOrc1 = tgui::Picture::create("../assets/RedPlayer1.png");
	redOrc2 = tgui::Picture::create("../assets/RedPlayer2.png");
	redOrc3 = tgui::Picture::create("../assets/RedPlayer3.png");
	redOrc1->setSize("50%", "50%");
	redOrc1->setPosition("25%", "15%");
	redOrc2->setSize("50%", "50%");
	redOrc2->setPosition("25%", "15%");
	redOrc3->setSize("50%", "50%");
	redOrc3->setPosition("25%", "15%");

	label = tgui::Label::create("PRESS A TO JOIN");
	player1->add(label);
	player2->add(label);
	player3->add(label);
	player4->add(label);
	player5->add(label);
	player6->add(label);
	label->setTextSize(25);
	label->setPosition("17.0%", "45%");
	
	characters.push_back(blueOrc1);
	characters.push_back(blueOrc2);
	characters.push_back(blueOrc3);
	characters.push_back(redOrc1);
	characters.push_back(redOrc2);
	characters.push_back(redOrc3);
	
	

	RenderManager::getInstance().getGui()->add(horiTop);
	RenderManager::getInstance().getGui()->add(horiBot);

}


