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

class DeckBuilderUI : public GameWindow
{
public:
	std::vector<std::string> mDecks;
	int mActiveDeckId;
	DeckData mActiveDeckData;
	
	std::vector<CardModel*> mCardModels;
	std::vector<CardModel*> mCollectionModels;
	
	Camera mCamera;
	Model mTableModel;
	
	int mDeckScrollPos;
	int mCollectionScrollPos;
	
	DeckBuilderUI();
	~DeckBuilderUI();

	void init();
	void update(int deltaTime);
	void render();
	int handleEvent(const SDL_Event& event, int callback);
	
	void updateDeckCard(CardModel* model, int pos, int size, int hovercard);
	void updateCollectionCard(CardModel* model, int pos, int size, int hovercard);
};
