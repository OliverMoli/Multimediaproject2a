#include "pch.h"
#include "RenderManager.h"
#include "GameObject.h"

RenderManager& RenderManager::getInstance()
{
	static RenderManager instance;
	return instance;
}

void RenderManager::render(sf::RenderWindow& window)
{
	for (auto renderComp : renderComponents)
	{
		//window.setView(currentView);
		if (renderComp->getGameObject().isActive()) {
			renderComp->render(window);
		}
	}
	gui->draw();
}

void RenderManager::addRenderComponent(std::shared_ptr<RenderComponent> comp)
{
	renderComponents.push_back(comp);
	sortByLayer();
}

void RenderManager::setCurrentView(sf::View& view)
{
	currentView = view;
}

void RenderManager::freeResources()
{
	renderComponents.clear();
}

void RenderManager::sortByLayer()
{
	std::sort(renderComponents.begin(), renderComponents.end(), [](const std::shared_ptr<RenderComponent> comp1, const std::shared_ptr<RenderComponent> comp2) {return comp1->getLayer() < comp2->getLayer(); });
}

void RenderManager::setGui(tgui::Gui* gui)
{
	this->gui = gui;
}

tgui::Gui* RenderManager::getGui() const
{
	return gui;
}
