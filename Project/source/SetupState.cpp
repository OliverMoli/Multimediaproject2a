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
#include <fstream>

void SetupState::initialize()
{
	clock = sf::Clock();
	for (int i = 0; i < 6; i++)
	{
		individualPlayerFocusChange[i] = -100;
		individualPlayerInPreCharState[i] = true;
		counter[i] = -1;
		isSelected[i] = false;
	}
	createSettingsUi();
}

void SetupState::update(float deltaTime)
{
	GameState::update(deltaTime);
	if (sf::Joystick::isButtonPressed(0, (int)InputManager::XboxButtons::Start))
	{
		createSetupFile();
		RenderManager::getInstance().getGui()->removeAllWidgets();
		GameStateManager::getInstance().setState("PlayState");
	}
	if (sf::Joystick::isButtonPressed(0, (int)InputManager::XboxButtons::B))
	{
		RenderManager::getInstance().getGui()->removeAllWidgets();
		GameStateManager::getInstance().setState("MainMenuState");

	}

	for (int i = 0; i < 6; i++)
	{

		if (sf::Joystick::isButtonPressed(i, (int)InputManager::XboxButtons::X) && individualPlayerInPreCharState[i])
		{
			counter[i] = getNextFree(-1, true);
			players[i]->remove(label);
			players[i]->add(characters[counter[i]]);
			individualPlayerInPreCharState[i] = false;
			isSelected[counter[i]] = true;
		}
		if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) >= 90 && clock.getElapsedTime().asSeconds() > individualPlayerFocusChange[i] + focusDelay && !individualPlayerInPreCharState[i])
		{

			individualPlayerFocusChange[i] = clock.getElapsedTime().asSeconds();
			players[i]->remove(characters[counter[i]]);
			isSelected[counter[i]] = false;
			counter[i] = getNextFree(counter[i], true);
			players[i]->add(characters[counter[i]]);
			isSelected[counter[i]] = true;
		}

		if (sf::Joystick::getAxisPosition(i, sf::Joystick::Axis::X) <= -90 && clock.getElapsedTime().asSeconds() > individualPlayerFocusChange[i] + focusDelay && !individualPlayerInPreCharState[i])
		{
			individualPlayerFocusChange[i] = clock.getElapsedTime().asSeconds();
			isSelected[counter[i]] = false;
			players[i]->remove(characters[counter[i]]);
			counter[i] = getNextFree(counter[i], false);
			players[i]->add(characters[counter[i]]);
			isSelected[counter[i]] = true;
		}
	}


}

void SetupState::render(sf::RenderWindow & window)
{
	GameState::render(window);
}

void SetupState::exit()
{
	players.clear();
	characters.clear();
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

	label = tgui::Label::create("PRESS X TO JOIN");
	player1->add(label);
	player2->add(label);
	player3->add(label);
	player4->add(label);
	player5->add(label);
	player6->add(label);
	label->setTextSize(25);
	label->setPosition("17.0%", "45%");

	players.push_back(player1);
	players.push_back(player2);
	players.push_back(player3);
	players.push_back(player4);
	players.push_back(player5);
	players.push_back(player6);

	characters.push_back(redOrc1);
	characters.push_back(blueOrc1);
	characters.push_back(redOrc2);
	characters.push_back(blueOrc2);
	characters.push_back(redOrc3);
	characters.push_back(blueOrc3);



	RenderManager::getInstance().getGui()->add(horiTop);
	RenderManager::getInstance().getGui()->add(horiBot);

}

int SetupState::getNextFree(int start, bool right)
{
	int index = 0;
	if (right)
	{
		index = start + 1;
		if (index > 5)
		{
			index = 0;
		}
	}
	else
	{
		index = start - 1;
		if (index < 0)
		{
			index = 5;
		}
	}
	while (isSelected[index])
	{
		if (right) {
			index++;
			if (index > 5)
			{
				index = 0;
			}
		}
		else
		{
			index--;
			if (index < 0)
			{
				index = 5;
			}
		}
	}
	return index;
}

void SetupState::createSetupFile()
{
	std::ofstream setupFile;
	setupFile.open("../assets/setup.txt");
	for (int i = 0; i < 6; i++)
	{
		setupFile << "Player " << i + 1 << ",";
		int playerIndex = -1;
		for (int j = 0; j < 6; j++)
		{
			if (i == counter[j])
			{
				playerIndex = j;
			}
		}
		setupFile << std::to_string(playerIndex);
		setupFile << ",";
		if ((i + 1) % 2 == 0)
		{
			setupFile << "blue";
		}
		else
		{
			setupFile << "red";
		}
		if (i < 5)
		{
			setupFile << ",\n";
		}

	}
	setupFile.close();
}



