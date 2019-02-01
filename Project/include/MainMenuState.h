#pragma once
#include "GameState.h"
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/Picture.hpp>
#include <TGUI/Widgets/Panel.hpp>

class MainMenuState : public GameState
{
public:
	void initialize() override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
	void exit() override;

private:
	void createMenuUi();
	void createCreditsUi();
	float focusDelay = 0.15;
	float lastFocusChange = -100;
	sf::Clock clock;
	std::shared_ptr<tgui::Button> startButton, creditsButton, exitButton;
	std::shared_ptr<tgui::Panel> panel;
	std::shared_ptr<tgui::Picture> fhLogo;
	bool inCredits = false;
	std::string creditsText = "      Flagball  \n\nMichael Cenger\nOliver Moholi";
	std::shared_ptr<GameObject> background;
	bool second = false;
};

