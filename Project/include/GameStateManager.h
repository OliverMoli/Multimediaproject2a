#pragma once
#include "GameState.h"
#include <SFML/Graphics/RenderWindow.hpp>

class GameStateManager {
public:
	static GameStateManager& getInstance();
	///Registers a new gamestate under a unique name
	///@param name The name under which the state should be registered as
	///@param state The state to register
	bool registerState(const std::string &name, std::shared_ptr<GameState> state);
	///Sets the current gamestate
	///@param name The name of the gamestate
	void setState(const std::string &name);
	///@return the currently active gamestate
	std::shared_ptr<GameState> getCurrentState() const;
	void update(float deltaTime);
	void render(sf::RenderWindow& window);
	void freeStates();
	sf::RenderWindow* getWindow();
private:
	GameStateManager() = default;
	~GameStateManager() = default;
	GameStateManager(const GameStateManager& p) = delete;
	GameStateManager& operator=(GameStateManager const&) = delete;
	std::shared_ptr<GameState> currentState = nullptr;
	std::map<std::string, std::shared_ptr<GameState>> states;
	sf::RenderWindow* window;
};
