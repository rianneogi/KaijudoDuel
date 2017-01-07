#pragma once

#include "CardData.h"
#include "SoundManager.h"

#include <vector>

enum ZoneType { ZONE_HAND, ZONE_DECK, ZONE_BATTLE, ZONE_MANA, ZONE_SHIELD, ZONE_GRAVEYARD, ZONE_EVOLVED };
enum Civilization { CIV_LIGHT, CIV_NATURE, CIV_WATER, CIV_FIRE, CIV_DARKNESS };
enum CardType { TYPE_CREATURE, TYPE_SPELL };
enum DefenderType { DEFENDER_CREATURE, DEFENDER_PLAYER };

extern std::vector<std::string> gCardNames;

class Card
{
public:
	int UniqueId;
	int CardId;

	std::vector<Modifier*> modifiers;
	std::vector<Card*> evostack;

	std::string Name;
	std::string Race;
	int Civilization;
	int Type;
	int ManaCost;
	int Power;
	int Breaker;
	int Owner;
	int Zone;
	int isBlocker;
	int isShieldTrigger;
	bool isTapped;
	bool isFlipped;
	int summoningSickness;

	//sf::Sprite sprite;
	//sf::Text powertext;
	bool isVisible[2];
	//CardModel mModel;
	//int displayPower;
	
	Card();
	Card(int uid, int cid, int owner);
	~Card();

	void copyFrom(Card* c);

	//void render(int myPlayer);
	//void update(int deltaTime);
	//bool rayTrace(Vector2i mousePos, const glm::mat4& projview, const Vector2i& screenDimensions);
	//void handleEvent(const SDL_Event& e);
	//void setPosition(glm::vec3 pos);
	//void move(Orientation target, int time);
	//void hover(Orientation target, int time);
	//void updatePower(int pow);
	//sf::FloatRect getBounds();

	int handleMessage(Message& msg);
	void callOnCast();
	void flip();
	void unflip();
	void flipForPlayer(int p);
	void unflipForPlayer(int p);
	void tap();
	void untap();
};

int getCardIdFromName(std::string s);
bool initCards();
void cleanupCards();

int getOpponent(int turn);



