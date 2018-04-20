#pragma once

#include "BattleZoneRenderer.h"

enum DuelState { DUELSTATE_DUEL, DUELSTATE_MENU, DUELSTATE_SINGLE, DUELSTATE_MULTI };
enum DuelType { DUELTYPE_SINGLE, DUELTYPE_MULTI, DUELTYPE_AI };

//extern sf::TcpSocket Socket;

class DuelInterface //: public GameWindow
{
public:
	Duel* mDuel;
	Bot* mBot;

	std::vector<CardModel*> mCardModels;
	//ZoneRenderer* mZoneRenderers[2][6];
	BattleZoneRenderer* mBattleZoneRenderers[2];
	ManaZoneRenderer* mManaZoneRenderers[2];
	ShieldZoneRenderer* mShieldZoneRenderers[2];
	GraveyardRenderer* mGraveyardRenderers[2];
	DeckRenderer* mDeckRenderers[2];
	HandRenderer* mHandRenderers[2];

	int mDuelType;
	int duelstate;

	int myPlayer;

	int selectedcard;
	int selectedcardzone;
	int iscardevo;

	int mHoverCardId;
	int mSelectedCardId;
	int mHoverException;
	int mHighlightCardId;
	Timer mHoverTimer;

	Camera mCamera;
	Model mTableModel;
	Model mEndTurnModel;
	Model mButton2Model;

	TextRenderer mTextRenderer;

	int mousearrow;

	int deckschosen;

	DuelInterface();
	DuelInterface(Duel* duel);
	~DuelInterface();

	int handleMessage(Message& msg);
	void dispatchMessage(Message& msg);
	void parseMessages(unsigned int deltatime);
	void update(int deltaTime);
	void render();
    int handleEvent(const SDL_Event& event, int callback);
	void endturn();
	void button2();
	//int receivePacket(sf::Packet& packet, int callback);

	ZoneRenderer* getZoneRenderer(int player, int zone);

	void setDecklist();

	void undoSelection();
	void setMyPlayer(int p);
};

//int mainLoop(sf::RenderWindow& window, int callback);

