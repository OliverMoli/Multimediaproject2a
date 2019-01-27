#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "RenderComponent.h"

class RenderManager
{
public:
	static RenderManager& getInstance();
	void render(sf::RenderWindow& window);
	void addRenderComponent(std::shared_ptr<RenderComponent> comp);
	void setCurrentView(sf::View& view);
	void freeResources();
	void sortByLayer();
private:
	RenderManager() = default;
	~RenderManager() = default;
	RenderManager(const RenderManager& p) = delete;
	RenderManager& operator=(const RenderManager& rhs) = delete;
	std::vector<std::shared_ptr<RenderComponent>> renderComponents;
	sf::View currentView;
};