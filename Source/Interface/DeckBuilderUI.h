#pragma once

#include "DuelInterface.h"

struct DeckData
{
	std::string mName;
	std::vector<int> mCards;
	std::vector<int> mCounts; 
	
	void addCard(int cid);
	void removeCard(int cid);
	
	void load(std::string path);
	void save(std::string path);
};

class DeckBuilderUI
{
public:
	std::vector<std::string> mDecks;
	int mActiveDeckId;
	DeckData mActiveDeckData;
	
	std::vector<CardModel*> mCardModels;
	
	DeckBuilderUI();
	~DeckBuilderUI();

	void init();
	void update(int deltaTime);
	void render();
	int handleEvent(const SDL_Event& event, int callback);
};
