#pragma once

#include "Game/MessageManager.h"

class SoundManager
{
public:
	//std::vector<sf::Sound> sounds;

	SoundManager();
	~SoundManager();

	void playSound(int soundid);
};

extern SoundManager* SoundMngr;
