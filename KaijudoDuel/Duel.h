#pragma once

#include "Choice.h"

enum AttackPhase { PHASE_NONE, PHASE_BLOCK, PHASE_TARGET, PHASE_TRIGGER };
enum CanAttack { CANATTACK_TAPPED, CANATTACK_UNTAPPED, CANATTACK_NO, CANATTACK_ALWAYS };
enum ReturnValue { RETURN_BUTTON1 = -1, RETURN_BUTTON2 = -2, RETURN_NOVALID = -3, RETURN_NOTHING = -4, RETURN_QUIT = -5 };

struct MsgHistoryItem
{
	Message msg;
	int move;
};

class Duel
{
public:
	Deck decks[2];
	Hand hands[2];
	ManaZone manazones[2];
	Graveyard graveyards[2];
	ShieldZone shields[2];
	BattleZone battlezones[2];

	std::vector<Card*> mCardList;

	std::string decknames[2];

	bool isSimulation;
	std::vector<MsgHistoryItem> MessageHistory;
	std::vector<Message> MoveHistory;
	int currentMoveCount;

	CRandom RandomGen;

	int attacker;
	int defender;
	int defendertype;
	int breakcount;
	std::vector<int> shieldtargets;
	int attackphase;

	int castingcard;
	int castingciv;
	int castingcost;
	int castingevobait;
	bool castingcivtapped;

	Choice* choice;
	int choiceCard;
	int choicePlayer;
	bool isChoiceActive;

	int winner;

	int nextUniqueId;

	MessageManager MsgMngr;
	Message currentMessage;

	int turn;
	int manaUsed;

	Duel();
	~Duel();

	void copyFrom(Duel* duel);

	void setDecks(std::string p1, std::string p2);
	void loadDeck(std::string s, int p);
	void startDuel();
	void nextTurn();

	//Game Messages
	int handleMessage(Message& msg);
	bool dispatchAllMessages();
	void dispatchMessage(Message& msg);
	void parseMessages(unsigned int deltatime);

	//Interface Messages
	int handleInterfaceInput(Message& msg);

	//For AI
	int getPlayerToMove();
	std::vector<Message> getPossibleMoves();
	void undoLastMove();
	void undoMessage(Message& msg);

	void addChoice(std::string info, int skip, int card, int player, int validref, int actionref);
	void checkChoiceValid();
	int choiceCanBeSelected(int sid);

	//void undoSelection();
	void resetAttack();
	void resetCasting();
	void resetChoice();
	void clearCards();

	void setMyPlayer(int p);

	bool isThereUntappedManaOfCiv(int player, int civ);

	Zone* getZone(int player, int zone);
	void destroyCard(Card* c);
	void battle(int att, int def);
	Card* getCard(int player, int zone, int id);

	void flipCardForPlayer(int cid, int p);
	void unflipCardForPlayer(int cid, int p);

	void drawCards(int player, int count);

	int getCreaturePower(int uid);
	int getCreatureBreaker(int uid);
	int getCreatureIsBlocker(int uid);
	int getCreatureCanBlock(int attckr, int blckr);
	//int getCreatureCanAttack(int uid);
	int getCreatureCanAttackPlayers(int uid);
	//int getCreatureCanAttackCreatures(int uid);
	//int getCreatureCanAttackTarget(int attckr, int dfndr);
	int getCreatureCanAttackCreature(int attckr, int dfndr);
	//int getCreatureCanBeAttacked(int attckr, int dfndr);
	//int getCreatureCanBeBlocked(int uid);
	//int getCreatureCanAttackUntappedCreatures(int uid);
	int getCardCost(int uid);
	int getCardCivilization(int uid);
	int getIsShieldTrigger(int uid);
	int canUseShieldTrigger(int uid);
	int getIsEvolution(int uid);
	int getIsSpeedAttacker(int uid);
	int getCardCanCast(int uid);
	int isCreatureOfRace(int uid, std::string race); //finds if the word race exists in the creature's race
	std::string getCreatureRace(int uid); //returns the full race string of the creature
	int getCreatureCanEvolve(int evo, int bait);
};

extern Duel* ActiveDuel;