#pragma once
#include <SFML/Window/Event.hpp>

class InputManager
{
public:
	///Button ids mapped to their respective X-BOX 360 name.
	enum class XboxButtons
	{
		A = 0,
		B = 1,
		X = 2,
		Y = 3,
		LB = 4,
		RB = 5,
		Back = 6,
		Start = 7,
		L3 = 8,
		R3 = 9
	};
	static InputManager& getInstance();
	///returns true when the button was pressed this frame but not last
	bool isKeyDown(std::string action, int playerIndex);
	///returns true when the button was pressed last frame but not this
	bool isKeyUp(std::string action, int playerIndex);
	///returns true as long as the button is pressed
	bool isKeyPressed(std::string action, int playerIndex);
	///returns true as long as the button is released
	bool isKeyReleased(std::string action, int playerIndex);
	///binds an action name and its keycode to a playerIndex
	bool bind(std::string name, int keyCode, int playerIndex);
	///unbinds a mapping from a player based on the mappings name
	bool unbind(std::string name, int playerIndex);
	///fills key states based on incoming events
	void processKeyEvent(sf::Event& keyEvent);
	void setLastKeyState();
	///frees all resources
	void freeResources();
	///clears keystates for example between state transitions
	void clearKeystates();
private:
	InputManager() = default;
	~InputManager() = default;
	InputManager(const InputManager& p) = delete;
	InputManager& operator=(InputManager const&) = delete;
	//<action,playerIndex>,keycode>>
	std::map<std::pair<std::string,int>,int> keyBindings;
	std::map<int, bool> keyStateThisFrame,keyStateLastFrame;
};
