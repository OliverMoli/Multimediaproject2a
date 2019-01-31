#pragma once
#include "GameState.h"
#include "CharacterInfoComponent.h"

class PlayState : public GameState
{
public:
	void initialize() override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
	void exit() override;
	void loadSetup();
private:
	void possessCharacter(std::string characterName, int playerIndex, Team team);
	void createAnimations();
	void createOrcAnimationHelper(std::string textureName,std::string animName);
};

