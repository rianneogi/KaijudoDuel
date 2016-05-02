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
	Duel duel;

	//AIInterface ai;

	int dueltype;
	int duelstate;

	int myPlayer;

	int MouseX;
	int MouseY;
	int selectedcard;
	int selectedcardzone;
	int iscardevo;

	//Button endturnbutton;

	/*Button cancelbutton;
	Button quitbutton;
	sf::Text infotext;

	Button cardCountBox;

	vector<Arrow> arrows;*/
	int mousearrow;

	//sf::Sprite hovercard;

	//ZoneList cardsearch;

	//List decklist;
	int deckschosen;

	DuelInterface();
	~DuelInterface();

	int handleMessage(Message& msg);
	void dispatchMessage(Message& msg);
	void parseMessages(unsigned int deltatime);
	void update(int deltaTime, Camera& camera, const Vector2i& mousePos);
	void render(Camera& camera, const Vector2i& mousePos);
    //int handleEvent(sf::Event event, int callback);
	//int receivePacket(sf::Packet& packet, int callback);

	void setDecklist();

	void undoSelection();
	void setMyPlayer(int p);
};

//int mainLoop(sf::RenderWindow& window, int callback);

