#include "pch.h"
#include "SoundManager.h"
#include "ResourceManager.h"
#include "SFML/Audio/Sound.hpp"

SoundManager& SoundManager::getInstance()
{
	static SoundManager instance;
	return instance;
}

void SoundManager::playSound(std::string name,float volume,float pitch,bool loop)
{
	auto soundBuffer = ResourceManager::getInstance().getSound(name);
	std::shared_ptr<sf::Sound> sound;
	//try to reuse an existing sound object as sfml has a limit on the amount of sound objects that exist
	if(sounds.size() >= MAX_SOUNDS)
	{
		for(auto soundIt : sounds)
		{
			if(soundIt->getStatus()== sf::SoundSource::Stopped)
			{
				sound = soundIt;
				break;
			}
		}
	}else
	{
		sound = std::make_shared<sf::Sound>();
		sounds.push_back(sound);
	}
	if(sound == nullptr)
	{
		std::cout << "Could not play sound [" << name << "]" << std::endl;
	}
	sound->setBuffer(*soundBuffer);
	sound->setVolume(volume);
	sound->setPitch(pitch);
	sound->setLoop(loop);
	sound->play();
}

void SoundManager::freeResources()
{
	for(auto sound : sounds)
	{
		sound->stop();
	}
	sounds.clear();
}
