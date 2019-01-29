#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "RenderComponent.h"
#include <TGUI/Gui.hpp>

class RenderManager
{
public:
	static RenderManager& getInstance();
	void render(sf::RenderWindow& window);
	void addRenderComponent(std::shared_ptr<RenderComponent> comp);
	void setCurrentView(sf::View& view);
	void freeResources();
	void sortByLayer();
	void setGui(tgui::Gui& gui);
	tgui::Gui* getGui() const;
private:
	RenderManager() = default;
	~RenderManager() = default;
	RenderManager(const RenderManager& p) = delete;
	RenderManager& operator=(const RenderManager& rhs) = delete;
	std::vector<std::shared_ptr<RenderComponent>> renderComponents;
	sf::View currentView;
	tgui::Gui* gui;
};
