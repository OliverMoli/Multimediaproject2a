#include "pch.h"
#include "InputManager.h"
#include <SFML/Window/Event.hpp>

InputManager& InputManager::getInstance()
{
	static InputManager instance;
	return instance;
}

bool InputManager::isKeyDown(std::string action, int playerIndex)
{
	auto pair = std::make_pair(action, playerIndex);
	if (keyBindings.find(pair) != keyBindings.end()) {
		return (keyStateThisFrame[keyBindings[pair]] && !keyStateLastFrame[keyBindings[pair]]);
	} 
	else {
		std::cout << "ERROR! the keybinding [" << action << "]" << "of playerIndex " << playerIndex << " is used but not mapped!" << std::endl;
	}
	return false;
}

bool InputManager::isKeyUp(std::string action, int playerIndex)
{
	auto pair = std::make_pair(action, playerIndex);
	if (keyBindings.find(pair) != keyBindings.end()) {
		return (!keyStateThisFrame[keyBindings[pair]] && keyStateLastFrame[keyBindings[pair]]);
	}
	else {
		std::cout << "ERROR! the keybinding [" << action << "]" << "of playerIndex " << playerIndex << " is used but not mapped!" << std::endl;
	}
	return false;
}

bool InputManager::isKeyPressed(std::string action, int playerIndex) {
	auto pair = std::make_pair(action, playerIndex);
	if (keyBindings.find(pair) != keyBindings.end()) {
		if (keyStateThisFrame.find(keyBindings[pair]) != keyStateThisFrame.end())
		{
			return keyStateThisFrame[keyBindings[pair]];
		}
	}
	else {
		std::cout << "ERROR! the keybinding [" << action << "]" << "of playerIndex " << playerIndex << " is used but not mapped!" << std::endl;
	}
	return false;
}

bool InputManager::isKeyReleased(std::string action, int playerIndex)
{
	return !isKeyPressed(action, playerIndex);
}

bool InputManager::bind(std::string name, int keyCode, int playerIndex)
{
	auto pair = std::make_pair(name, playerIndex);
	if (keyBindings.find(pair) == keyBindings.end()) {
		keyBindings[pair] = keyCode;
		return true;
	}
	std::cout << "ERROR! the keybinding [" << name << "]" << "of playerIndex " << playerIndex << " already exists and was not mapped" << std::endl;
	return false;
}

bool InputManager::unbind(std::string name, int playerIndex)
{
	auto pair = std::make_pair(name, playerIndex);
	if (keyBindings.find(pair) != keyBindings.end()) {
		keyBindings.erase(pair);
		return true;
	}
	std::cout << "ERROR! the keybinding [" << name << "]" << "of playerIndex " << playerIndex << " does not exist and can't be unbinded" << std::endl;
	return false;
}

void InputManager::processKeyEvent(sf::Event& keyEvent)
{
	if (keyEvent.type == sf::Event::KeyPressed)
	{
		keyStateThisFrame[keyEvent.key.code] = true;
	}
	if (keyEvent.type == sf::Event::KeyReleased)
	{
		keyStateThisFrame[keyEvent.key.code] = false;
	}
}

void InputManager::setLastKeyState()
{
	keyStateLastFrame = keyStateThisFrame;
}

void InputManager::freeResources()
{
	keyBindings.clear();
	keyStateThisFrame.clear();
	keyStateLastFrame.clear();
}

void InputManager::clearKeystates()
{
	keyStateThisFrame.clear();
	keyStateLastFrame.clear();
}


