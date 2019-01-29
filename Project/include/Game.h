#pragma once
#include <TGUI/TGUI.hpp>
class Game {
public:
	Game(std::string gameTitle);
	void initialize(int windowWidth, int windowHeight);
	void update();
	void render();
	void shutdown();
private:
	sf::RenderWindow window;
	std::string gameTitle;
	tgui::Gui gui;
};