#pragma once
#include "GameState.h"
#include <TGUI/Widgets/Panel.hpp>
#include <tgui/Widgets/Label.hpp>
#include <TGUI/Widgets/Picture.hpp>
#include <SFML/System/Clock.hpp>

class SetupState : public GameState
{
public:
	void initialize() override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
	void exit() override;
private:
	void createSettingsUi();
	float focusDelay = 0.15;
	float lastFocusChange = -100;
	sf::Clock clock;
	std::shared_ptr<tgui::Panel> player1, player2, player3, player4, player5, player6;
	void showUnit();
	std::shared_ptr<tgui::Label> label;
	std::shared_ptr<tgui::Picture> blueOrc1, blueOrc2, blueOrc3, redOrc1, redOrc2, redOrc3;
	std::vector<std::shared_ptr<tgui::Picture>> characters;
	int counter = 0;
};

