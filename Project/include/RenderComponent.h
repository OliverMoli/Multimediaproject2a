#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Component.h"


enum RenderLayer{Ground = 0, OnGroundLayer = 1, Player = 2, Items = 3, Obstacles = 4};

class RenderComponent : public Component
{
public:
	RenderComponent(GameObject& owner);
	virtual void render(sf::RenderWindow& window)=0;
	void setLayer(RenderLayer layer);
	RenderLayer getLayer() const;
protected:
	RenderLayer layer = Ground;
};
