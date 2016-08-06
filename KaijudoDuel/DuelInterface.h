#pragma once

#include "Duel.h"

enum DuelState { DUELSTATE_DUEL, DUELSTATE_MENU, DUELSTATE_SINGLE, DUELSTATE_MULTI };
enum DuelType { DUELTYPE_SINGLE, DUELTYPE_MULTI, DUELTYPE_AI };

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

//extern sf::TcpSocket Socket;

class DuelInterface //: public GameWindow
{
public:
	Duel mDuel;

	int dueltype;
	int duelstate;

	int myPlayer;

	int selectedcard;
	int selectedcardzone;
	int iscardevo;
	int mHoverCardId;
	int mSelectedCardId;

	Camera mCamera;
	Model mTableModel;
	Model mEndTurnModel;

	int mousearrow;

	int deckschosen;

	DuelInterface();
	~DuelInterface();

	int handleMessage(Message& msg);
	void dispatchMessage(Message& msg);
	void parseMessages(unsigned int deltatime);
	void update(int deltaTime);
	void render();
    int handleEvent(const SDL_Event& event, int callback);
	//int receivePacket(sf::Packet& packet, int callback);

	void setDecklist();

	void undoSelection();
	void setMyPlayer(int p);
};

//int mainLoop(sf::RenderWindow& window, int callback);

