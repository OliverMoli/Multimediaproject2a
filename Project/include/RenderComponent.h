#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Component.h"


enum RenderLayer{Background = 0, ObjectLayer = 1, Midground = 2, Foreground = 3, CollisionTriggerLayer = 4, CollisionLayer = 5};

class RenderComponent : public Component
{
public:
	RenderComponent(GameObject& owner);
	virtual void render(sf::RenderWindow& window)=0;
	void setLayer(RenderLayer layer);
	RenderLayer getLayer() const;
protected:
	RenderLayer layer = Foreground;
};
