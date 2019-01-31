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
	int getNextFree(int index,bool right);
	void createSetupFile();
	float focusDelay = 0.15;
	float lastFocusChange = -100;
	sf::Clock clock;
	std::shared_ptr<tgui::Panel> player1, player2, player3, player4, player5, player6;
	void showUnit();
	std::shared_ptr<tgui::Label> label;
	std::shared_ptr<tgui::Picture> blueOrc1, blueOrc2, blueOrc3, redOrc1, redOrc2, redOrc3, arrowLeft, arrowRight;
	std::vector<std::shared_ptr<tgui::Picture>> characters;
	std::vector<std::shared_ptr<tgui::Panel>> players;
	float individualPlayerFocusChange[6] = { -100,-100, -100,-100,-100, -100 };
	bool individualPlayerInPreCharState[6] = { true,true,true,true,true, true };
	int counter[6] = {-100,-100,-100,-100,-100,-100};
	bool inPreCharState = true;
	bool isSelected[6] = { false,false,false,false,false,false };
};

