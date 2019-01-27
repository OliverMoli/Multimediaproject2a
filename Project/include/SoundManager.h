#pragma once
#include <SFML/Audio/SoundBuffer.hpp>

class SoundManager
{
public:
	static SoundManager& getInstance();
	///@param name The name of the sound resource to play
	///@param volume Playback volume
	///@param pitch The pitch of the sound
	///@param loop Should the playback be looped
	void playSound(std::string name, float volume = 100.0f, float pitch = 1.0f, bool loop = false);
	void freeResources();
private:
	SoundManager() = default;
	~SoundManager() = default;
	SoundManager(const SoundManager& p) = delete;
	SoundManager& operator=(const SoundManager& rhs) = delete;
	std::vector<std::shared_ptr<sf::Sound>> sounds;
	const int MAX_SOUNDS = 50;
};

