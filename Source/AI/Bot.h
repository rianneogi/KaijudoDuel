#pragma once

#include "Game/Duel.h"
// #include <NNInclude.h>

class Bot
{
public:
	// Board mBoard;
	Duel* mDuel;

	Bot();
	~Bot();

	Message getBestMove();
};
