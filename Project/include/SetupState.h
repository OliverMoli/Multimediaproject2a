#pragma once
#include "GameState.h"

class SetupState : public GameState
{
public:
	void initialize() override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
	void exit() override;
};

