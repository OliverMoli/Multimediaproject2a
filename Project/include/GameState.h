#pragma once
#include "GameObject.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "ResourceManager.h"

class GameState {
public:
	virtual void initialize(){};
	virtual void update(float deltaTime);
	virtual void render(sf::RenderWindow& window);
	virtual void exit();
	///Adds a gameobject to the state
	///@param go The gameobject to add
	void addGameObject(std::shared_ptr<GameObject> go);
	///@return all gameobjects existing in the current gamestate
	std::vector<std::shared_ptr<GameObject>>& getGameObjects();

	bool pause = false;
private:
	std::vector<std::shared_ptr<GameObject>> gameObjects;
};
