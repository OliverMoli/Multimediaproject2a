#pragma once
#include "GameState.h"
#include <TGUI/Widgets/Panel.hpp>

class SetupState : public GameState
{
public:
	void initialize() override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
	void exit() override;
private:
	void createSettingsUi();
	std::shared_ptr<tgui::Panel> player1, player2, player3, player4, player5, player6;
};

