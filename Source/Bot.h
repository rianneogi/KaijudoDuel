#pragma once

#include "Duel.h"
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
