#pragma once

#include "Choice.h"

#include <fstream>

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
	Deck mDecks[2];
	Hand mHands[2];
	ManaZone mManazones[2];
	Graveyard mGraveyards[2];
	ShieldZone mShields[2];
	BattleZone mBattlezones[2];

	std::vector<Card*> mCardList;

	std::string mDeckNames[2];

	bool mIsSimulation;
	std::vector<MsgHistoryItem> mMessageHistory;
	std::vector<Message> mMoveHistory;
	int mCurrentMoveCount;

	CRandom mRandomGen;

	int mAttacker;
	int mDefender;
	int mDefenderType;
	int mBreakCount;
	std::vector<int> mShieldTargets;
	int mAttackphase;

	int mCastingCard;
	int mCastingCiv;
	int mCastingCost;
	int mCastingEvobait;
	bool mCastingCivTapped;

	Choice* mChoice;
	int mChoiceCard;
	int mChoicePlayer;
	bool mIsChoiceActive;

	int mWinner;

	int mNextUniqueId;

	MessageManager mMsgMngr;
	Message mCurrentMessage;

	int mTurn;
	int mManaUsed;

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
	//void parseMessages(unsigned int deltatime);

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