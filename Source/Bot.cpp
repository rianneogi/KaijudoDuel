#include "Bot.h"

Bot::Bot()
{
}

Bot::~Bot()
{
}

Message Bot::getBestMove()
{
	std::vector<Message> moves = mDuel->getPossibleMoves();

	return moves[rand()%moves.size()];
}
