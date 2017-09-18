#include "Duel.h"

std::mutex gMutex;

Duel::Duel()
{
	mTurn = 0;
	mManaUsed = 0;
	mNextUniqueId = 0;

	mPlayerType[0] = PLAYER_HUMAN;
	mPlayerType[1] = PLAYER_AI;

	int Factor[2] = { -1, 1 };
	int Factor2[2] = { 1,0 };
	for (int i = 0; i < 2; i++)
	{
		mDecks[i].mRandomGen = &mRandomGen; //set random function for deck shuffling

		mDecks[i].mOwner = i;
		mBattlezones[i].mOwner = i;
		mGraveyards[i].mOwner = i;
		mHands[i].mOwner = i;
		mManazones[i].mOwner = i;
		mShields[i].mOwner = i;

	//	decks[i].x = ZONE2X;
	//	graveyards[i].x = ZONE2X;
	//	hands[i].x = ZONE1X;
	//	manazones[i].x = ZONE1X;
	//	shields[i].x = ZONE1X;
	//	battlezones[i].x = ZONE1X;

	//	hands[i].y = CENTER + ZONEYOFFSET*Factor[i] * 4 - ZONEYOFFSET*Factor2[i];
	//	decks[i].y = CENTER + ZONEYOFFSET*Factor[i] * 3 - ZONEYOFFSET*Factor2[i];
	//	manazones[i].y = CENTER + ZONEYOFFSET*Factor[i] * 3 - ZONEYOFFSET*Factor2[i];
	//	shields[i].y = CENTER + ZONEYOFFSET*Factor[i] * 2 - ZONEYOFFSET*Factor2[i];
	//	graveyards[i].y = CENTER + ZONEYOFFSET*Factor[i] * 2 - ZONEYOFFSET*Factor2[i];
	//	battlezones[i].y = CENTER + ZONEYOFFSET*Factor[i] - ZONEYOFFSET*Factor2[i];

	//	decks[i].rect = sf::RectangleShape(sf::Vector2f(CARDSEPERATION + CARDZONEOFFSET, CARDSEPERATION + CARDZONEOFFSET));
	//	graveyards[i].rect = sf::RectangleShape(sf::Vector2f(CARDSEPERATION + CARDZONEOFFSET, CARDSEPERATION + CARDZONEOFFSET));
	//	hands[i].rect = sf::RectangleShape(sf::Vector2f(ZONE2X - ZONE1X - 10, CARDSEPERATION + CARDZONEOFFSET));
	//	manazones[i].rect = sf::RectangleShape(sf::Vector2f(ZONE2X - ZONE1X - 10, CARDSEPERATION + CARDZONEOFFSET));
	//	shields[i].rect = sf::RectangleShape(sf::Vector2f(ZONE2X - ZONE1X - 10, CARDSEPERATION + CARDZONEOFFSET));
	//	battlezones[i].rect = sf::RectangleShape(sf::Vector2f(ZONE2X - ZONE1X - 10, CARDSEPERATION + CARDZONEOFFSET));

	//	decks[i].rect.setPosition(decks[i].x, decks[i].y);
	//	hands[i].rect.setPosition(hands[i].x, hands[i].y);
	//	manazones[i].rect.setPosition(manazones[i].x, manazones[i].y);
	//	graveyards[i].rect.setPosition(graveyards[i].x, graveyards[i].y);
	//	battlezones[i].rect.setPosition(battlezones[i].x, battlezones[i].y);
	//	shields[i].rect.setPosition(shields[i].x, shields[i].y);

	//	decks[i].rect.setFillColor(sf::Color(255, 255, 255));
	//	hands[i].rect.setFillColor(sf::Color(255, 255, 255));
	//	manazones[i].rect.setFillColor(sf::Color(255, 255, 255));
	//	graveyards[i].rect.setFillColor(sf::Color(255, 255, 255));
	//	battlezones[i].rect.setFillColor(sf::Color(255, 255, 255));
	//	shields[i].rect.setFillColor(sf::Color(255, 255, 255));

	//	decks[i].rect.setOutlineColor(DECKBORDERCOLOR);
	//	hands[i].rect.setOutlineColor(HANDBORDERCOLOR);
	//	manazones[i].rect.setOutlineColor(MANABORDERCOLOR);
	//	graveyards[i].rect.setOutlineColor(GRAVEYARDBORDERCOLOR);
	//	battlezones[i].rect.setOutlineColor(BATTLEBORDERCOLOR);
	//	shields[i].rect.setOutlineColor(SHIELDBORDERCOLOR);

	//	decks[i].rect.setOutlineThickness(ZONEBORDERSIZE);
	//	hands[i].rect.setOutlineThickness(ZONEBORDERSIZE);
	//	manazones[i].rect.setOutlineThickness(ZONEBORDERSIZE);
	//	graveyards[i].rect.setOutlineThickness(ZONEBORDERSIZE);
	//	battlezones[i].rect.setOutlineThickness(ZONEBORDERSIZE);
	//	shields[i].rect.setOutlineThickness(ZONEBORDERSIZE);
	}

	mAttackphase = PHASE_NONE;
	mAttacker = -1;
	mDefender = -1;
	mBreakCount = -1;
	
	mCastingCard = -1;
	mCastingCiv = -1;
	mCastingCost = -1;
	mCastingCivTapped = false;

	mIsChoiceActive = false;
	mChoiceCard = -1;
	mChoicePlayer = -1;

	mWinner = -1;

	mCurrentMoveCount = 0;

	mRandomGen.Randomize();

	mIsSimulation = false;
}

Duel::~Duel()
{
	for (int i = 0; i < mCardList.size(); i++)
	{
		if (mCardList.at(i) != NULL)
			delete mCardList.at(i);
	}
	if (mChoice != NULL)
		delete mChoice;
}

void Duel::copyFrom(Duel* duel) //incomplete, not used
{
	mTurn = duel->mTurn;
	mManaUsed = duel->mManaUsed;
	mNextUniqueId = duel->mNextUniqueId;

	mAttackphase = duel->mAttackphase;
	mAttacker = duel->mAttacker;
	mDefender = duel->mDefender;
	mBreakCount = duel->mBreakCount;

	mCastingCard = duel->mCastingCard;
	mCastingCiv = duel->mCastingCiv;
	mCastingCost = duel->mCastingCost;
	mCastingCivTapped = duel->mCastingCivTapped;

	mIsChoiceActive = duel->mIsChoiceActive;
	mChoiceCard = duel->mChoiceCard;
	mChoicePlayer = duel->mChoicePlayer;

	mWinner = duel->mWinner;

	mNextUniqueId = duel->mNextUniqueId;

	for (std::vector<int>::iterator i = duel->mShieldTargets.begin(); i != duel->mShieldTargets.end(); i++)
	{
		mShieldTargets.push_back(*i);
	}

	for (std::vector<Card*>::iterator i = duel->mCardList.begin(); i != duel->mCardList.end(); i++)
	{
		Card* c = new Card(**i);
		mCardList.push_back(c);
	}
	for (int i = 0; i < 2; i++)
	{
		for (int z = 0; z < 6; z++)
		{
			for (std::vector<Card*>::iterator j = duel->getZone(i, z)->mCards.begin(); j != duel->getZone(i, z)->mCards.end(); j++)
			{
				for (std::vector<Card*>::iterator k = mCardList.begin(); k != mCardList.end(); k++)
				{
					if ((*k)->mUniqueId == (*j)->mUniqueId)
					{
						getZone(i, z)->mCards.push_back(*k);
						break;
					}
				}
			}
		}
	}
	mChoice->copyFrom(duel->mChoice);
}

int Duel::handleMessage(Message& msg)
{
	MsgHistoryItem k;
	k.msg = msg;
	k.move = mCurrentMoveCount;
	mMessageHistory.push_back(k);
	if (msg.getType() == "cardmove")
	{
		int cid = msg.getInt("card");
		int tozone = msg.getInt("to");
		Card* c = mCardList.at(cid);
		int owner = c->mOwner;
		getZone(owner, c->mZone)->removeCard(c);
		if (tozone == ZONE_BATTLE && getIsEvolution(cid) == 1) //evolution creatures
		{
			int evobait = msg.getInt("evobait");
			if (evobait == -1)
			{
				getZone(owner, tozone)->addCard(c);
				mBattlezones[owner].addCard(c);
			}
			else
			{
				mBattlezones[owner].evolveCard(c, evobait);
			}
		}
		else
		{
			getZone(owner, tozone)->addCard(c);
		}
		c->mZone = tozone;
		if (tozone != ZONE_BATTLE)
		{
			for (int i = c->mEvoStack.size()-1; i >= 0; i--) //move all cards in stack to the zone seperately
			{
				Message m("cardmove");
				m.addValue("card", c->mEvoStack.at(i)->mUniqueId);
				m.addValue("from", c->mEvoStack.at(i)->mZone);
				m.addValue("to", tozone);
				mMsgMngr.sendMessage(m);
				c->mEvoStack.pop_back();
			}
		}
		if (c->mZone == ZONE_BATTLE && c->mType == TYPE_SPELL)
		{
			c->callOnCast(); //cast the spell
			Message m("cardmove");
			m.addValue("card", cid);
			m.addValue("from", mCardList.at(cid)->mZone);
			m.addValue("to", ZONE_GRAVEYARD);
			mMsgMngr.sendMessage(m);
		}
		if (mDecks[owner].mCards.size() == 0)
		{
			//player loses game
			mWinner = getOpponent(mTurn);
		}
	}
	else if (msg.getType() == "creaturedestroy")
	{
		Message m("cardmove");
		int cid = msg.getInt("creature");
		m.addValue("card", cid);
		m.addValue("from", mCardList.at(cid)->mZone);
		m.addValue("to", msg.getInt("zoneto"));
		mMsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "carddiscard")
	{
		Message m("cardmove");
		int cid = msg.getInt("card");
		m.addValue("card", cid);
		m.addValue("from", mCardList.at(cid)->mZone);
		m.addValue("to", msg.getInt("zoneto"));
		mMsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "manadestroy")
	{
		Message m("cardmove");
		int cid = msg.getInt("card");
		m.addValue("card", cid);
		m.addValue("from", mCardList.at(cid)->mZone);
		m.addValue("to", msg.getInt("zoneto"));
		mMsgMngr.sendMessage(m);
	}
	/*else if (msg.getType() == "carddiscard")
	{
		Message m("cardmove");
		m.addValue("card", msg.getInt("card"));
		m.addValue("to", ZONE_GRAVEYARD);
		MsgMngr.sendMessage(m);
	}*/
	/*else if (msg.getType() == "carddraw") //carddraw is replaced by cardmove with to=ZONE_HAND
	{
		int plyr = msg.getInt("player");
		Message m("cardmove");
		m.addValue("card", decks[plyr].getTopCard());
		m.addValue("to", ZONE_HAND);
		MsgMngr.sendMessage(m);
	}*/
	else if (msg.getType() == "cardplay")
	{
		int cid = msg.getInt("card");
		int eb = msg.getInt("evobait");
		
		Message m("cardmove");
		m.addValue("card", cid);
		m.addValue("from", mCardList.at(cid)->mZone);
		m.addValue("to", ZONE_BATTLE);
		m.addValue("evobait", eb);
		mMsgMngr.sendMessage(m);
		//if (!isSimulation)
		//	SoundMngr->playSound(SOUND_PLAY);
		/*if (eb != -1)
		{
			Message msg4("creatureevolve");
			msg4.addValue("evolution", cid);
			msg4.addValue("evobait", eb);
			MsgMngr.sendMessage(msg4);
		}*/
	}
	else if (msg.getType() == "cardmana")
	{
		mManaUsed = 1;
		int cid = msg.getInt("card");
		Message m("cardmove");
		m.addValue("card", cid);
		m.addValue("from", mCardList.at(cid)->mZone);
		m.addValue("to", ZONE_MANA);
		mMsgMngr.sendMessage(m);
		//if (!isSimulation)
		//	SoundMngr->playSound(SOUND_PLAY);
	}
	else if (msg.getType() == "creatureattack")
	{
		/*int type = msg.getInt("defendertype");
		if (type == DEFENDER_CREATURE)
		{
			Message m("creaturebattle");
			m.addValue("attacker", msg.getInt("attacker"));
			m.addValue("defender", msg.getInt("defender"));
			MsgMngr.sendMessage(m);
		}
		else if (type == DEFENDER_PLAYER)
		{
			Message m("creaturebreakshield");
			m.addValue("attacker", msg.getInt("attacker"));
			m.addValue("defender", msg.getInt("defender"));
			MsgMngr.sendMessage(m);
		}*/
		mAttacker = msg.getInt("attacker");
		mDefender = msg.getInt("defender");
		mDefenderType = msg.getInt("defendertype");
		//cout << "attack " << attacker << " " << defender << " " << defendertype << endl;
		//attackphase = PHASE_BLOCK;
		Message m("changeattackphase");
		m.addValue("phase", PHASE_BLOCK);
		m.addValue("oldphase", mAttackphase);
		mMsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "creatureblock")
	{
		Message m("creaturebattle");
		m.addValue("attacker", msg.getInt("attacker"));
		m.addValue("defender", msg.getInt("blocker"));
		mMsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "creaturebreakshield")
	{
		Message m("breakshield");
		m.addValue("player", msg.getInt("defender"));
		m.addValue("shield", msg.getInt("shield"));
		m.addValue("cantrigger", 1);
		mMsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "breakshield")
	{
		Message m("cardmove");
		int cid = msg.getInt("shield");
		m.addValue("card", cid);
		m.addValue("from", mCardList.at(cid)->mZone);
		m.addValue("to", ZONE_HAND);
		mMsgMngr.sendMessage(m);
		/*if (msg.getInt("cantrigger") == 1)
		{
			attackphase = PHASE_TRIGGER;
			shieldtargets.push_back(shields[plyr].cards.at(shields[plyr].cards.size() - 1)->UniqueId);
		}*/
	}
	else if (msg.getType() == "creaturebattle")
	{
		battle(msg.getInt("attacker"), msg.getInt("defender"));
	}
	else if (msg.getType() == "creatureusetapability")
	{
		int cid = msg.getInt("creature");

		Message m("cardtap");
		m.addValue("card", cid);
		mMsgMngr.sendMessage(m);

		//mMsgMngr.sendMessage(msg);
	}
	//else if (msg.getType() == "creatureevolve")
	//{
	//	int eb = msg.getInt("evobait");
	//	Card* cid = CardList.at(eb);
	//	//getZone(cid->Owner, cid->Zone)->removeCard(cid);
	//	if (cid->Zone != ZONE_BATTLE)
	//	{
	//		cout << "WARNING: attempting to evolve on card that is not in battlezone" << endl;
	//	}
	//	//battlezones[cid->Owner].removeBait(cid);
	//	cid->Zone = ZONE_EVOLVED;
	//	CardList.at(msg.getInt("evolution"))->evostack.push_back(cid);
	//}
	else if (msg.getType() == "cardtap")
	{
		mCardList.at(msg.getInt("card"))->tap();
		//if (!isSimulation)
		//	SoundMngr->playSound(SOUND_TAP);
	}
	else if (msg.getType() == "carduntap")
	{
		mCardList.at(msg.getInt("card"))->untap();
		//if (!isSimulation)
		//	SoundMngr->playSound(SOUND_UNTAP);
	}
	else if (msg.getType() == "endturn")
	{
		mTurn = (mTurn + 1) % 2;
		mManaUsed = 0;
		Message m("startturn");
		m.addValue("player", mTurn);
		mMsgMngr.sendMessage(m);
		//if (!isSimulation)
		//	SoundMngr->playSound(SOUND_ENDTURN);
	}
	else if (msg.getType() == "startturn")
	{
		int plyr = msg.getInt("player");
		std::vector<Card*>::iterator i;
		for (i = mBattlezones[plyr].mCards.begin(); i != mBattlezones[plyr].mCards.end(); i++) //untap creatures
		{
			Message m("carduntap");
			m.addValue("card", (*i)->mUniqueId);
			mMsgMngr.sendMessage(m);
			(*i)->mSummoningSickness = 0;
		}
		for (i = mManazones[plyr].mCards.begin(); i != mManazones[plyr].mCards.end(); i++) //untap mana
		{
			Message m("carduntap");
			m.addValue("card", (*i)->mUniqueId);
			mMsgMngr.sendMessage(m);
		}
		//Message m("carddraw"); //draw card
		//m.addValue("player", plyr);
		//MsgMngr.sendMessage(m);
		drawCards(plyr, 1);
	}
	else if (msg.getType() == "modifiercreate")
	{
		int uid = msg.getInt("card");
		int ref = msg.getInt("funcref");
		Modifier* modifier = new Modifier(ref);
		mCardList.at(uid)->mModifiers.push_back(modifier);
	}
	else if (msg.getType() == "modifierdestroy")
	{
		int uid = msg.getInt("card");
		int mid = msg.getInt("modifier");
		Modifier* modifier = mCardList.at(uid)->mModifiers.at(mid);
		mCardList.at(uid)->mModifiers.erase(mCardList.at(uid)->mModifiers.begin() + mid);
		delete modifier;
	}
	else if (msg.getType() == "changeattackphase")
	{
		mAttackphase = msg.getInt("phase");
	}
	else if (msg.getType() == "resetattack")
	{
		resetAttack();
	}
	else if (msg.getType() == "deckshuffle")
	{
		mDecks[msg.getInt("player")].shuffle();
	}
	else if (msg.getType() == "carddiscardatrandom")
	{
		int plyr = msg.getInt("player");
		if (mHands[plyr].mCards.size() > 0)
		{
			Message m("carddiscard");
			m.addValue("card", mHands[plyr].mCards.at(mRandomGen.Random(mHands[plyr].mCards.size()))->mUniqueId);
			m.addValue("zoneto", ZONE_GRAVEYARD);
			mMsgMngr.sendMessage(m);
		}
	}
	else if (msg.getType() == "evolutionseperate")
	{
		int cid = msg.getInt("evolution");
		mBattlezones[mCardList.at(cid)->mOwner].seperateEvolution(mCardList.at(cid));
	}
	return 0;
}

void Duel::undoLastMove()
{
	if (mMessageHistory.size() == 0)
		return;
	for (int i = mMessageHistory.size() - 1; i >= 0; i--)
	{
		MsgHistoryItem m = mMessageHistory.at(i);
		if (m.move == mCurrentMoveCount)
		{
			mMessageHistory.pop_back();
			undoMessage(m.msg);
			//cout << "undoing " << m.msg.getType() << " for " << MoveHistory.at(MoveHistory.size() - 1).getType() << endl;
		}
		else
		{
			break;
		}
	}

	Message m = mMoveHistory.at(mMoveHistory.size() - 1);
	if (m.getType() == "cardplay")
	{
		resetCasting();
	}
	else if (m.getType() == "manatap")
	{

	}
	mMoveHistory.pop_back();
	mCurrentMoveCount--;
}

void Duel::undoMessage(Message& msg)
{
	std::string type = msg.getType();
	if (type == "cardmove")
	{
		int cid = msg.getInt("card");
		int fromzone = msg.getInt("from");
		int tozone = msg.getInt("to");
		Card* c = mCardList.at(cid);
		int owner = c->mOwner;
		getZone(owner, fromzone)->addCard(c);
		if (tozone == ZONE_BATTLE && getIsEvolution(cid) == 1) //evolution creatures
		{
			int evobait = msg.getInt("evobait");
			if (evobait == -1)
			{
				getZone(owner, tozone)->removeCard(c);
				mBattlezones[owner].removeCard(c);
			}
			else
			{
				mBattlezones[owner].evolveCard(c, evobait);
			}
		}
		else
		{
			getZone(owner, tozone)->removeCard(c);
		}
		c->mZone = fromzone;
		mWinner = -1;
	}
	else if (msg.getType() == "cardtap")
	{
		mCardList.at(msg.getInt("card"))->untap();
	}
	else if (msg.getType() == "carduntap")
	{
		mCardList.at(msg.getInt("card"))->tap();
	}
	else if (msg.getType() == "endturn")
	{
		mTurn = (mTurn + 1) % 2;

		int flag = 0;
		for (std::vector<MsgHistoryItem>::reverse_iterator i = mMessageHistory.rbegin(); i != mMessageHistory.rend(); i++)
		{
			if ((*i).msg.getType() == "endturn")
			{
				mManaUsed = 0;
				flag = 1;
				break;
			}
			if ((*i).msg.getType() == "cardmana")
			{
				mManaUsed = 1;
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			mManaUsed = 0;
		}
	}
	else if (msg.getType() == "cardmana")
	{
		mManaUsed = 0;
	}
	else if (msg.getType() == "changeattackphase")
	{
		mAttackphase = msg.getInt("oldphase");
	}
}

int Duel::getPlayerToMove()
{
	if (mIsChoiceActive)
		return mChoicePlayer;
	if (mAttackphase == PHASE_BLOCK || mAttackphase == PHASE_TRIGGER)
		return getOpponent(mTurn);
	return mTurn;
}

std::vector<Message> Duel::getPossibleMoves()
{
	std::vector<Message> moves(0);
	int player = getPlayerToMove();
	if (mTurn == player && mAttackphase == PHASE_NONE && !(mIsChoiceActive) && mCastingCard == -1)
	{
		Message m("endturn");
		m.addValue("player", mTurn);
		moves.push_back(m);
	}
	else if (mIsChoiceActive && player == mChoicePlayer)
	{
		if (mChoice->mButtonCount > 0)
		{
			Message msg("choiceselect");
			msg.addValue("selection", RETURN_BUTTON1);
			moves.push_back(msg);
		}
		if (mChoice->mButtonCount > 1)
		{
			Message msg("choiceselect");
			msg.addValue("selection", RETURN_BUTTON2);
			moves.push_back(msg);
		}
		for (std::vector<Card*>::iterator i = mCardList.begin(); i != mCardList.end(); i++)
		{
			if ((*i)->mZone != ZONE_EVOLVED)
			{
				if (mChoice->callvalid(mChoiceCard, (*i)->mUniqueId) == 1)
				{
					Message msg("choiceselect");
					msg.addValue("selection", (*i)->mUniqueId);
					moves.push_back(msg);
				}
			}
		}
	}
	else if (mAttackphase == PHASE_TRIGGER && player == getOpponent(mTurn)) //use shield triggers
	{
		for (std::vector<Card*>::iterator i = mHands[getOpponent(mTurn)].mCards.begin(); i != mHands[getOpponent(mTurn)].mCards.end(); i++)
		{
			for (std::vector<int>::iterator j = mShieldTargets.begin(); j != mShieldTargets.end(); j++)
			{
				if (*j == (*i)->mUniqueId)
				{
					if (getIsShieldTrigger(*j) && canUseShieldTrigger(*j) && getCardCanCast(*j))
					{
						Message msg("triggeruse");
						msg.addValue("trigger", *j);
						moves.push_back(msg);
					}
				}
			}
		}
		Message m("triggerskip");
		moves.push_back(m);
	}
	else if (mAttackphase == PHASE_TARGET && player == mTurn) //target shields
	{
		for (std::vector<Card*>::iterator i = mShields[getOpponent(mTurn)].mCards.begin(); i != mShields[getOpponent(mTurn)].mCards.end(); i++)
		{
			Message m("targetshield");
			m.addValue("attacker", mAttacker);
			m.addValue("shield", (*i)->mUniqueId);
			moves.push_back(m);
		}
	}
	else if (mAttackphase == PHASE_BLOCK && player == getOpponent(mTurn)) //block
	{
		for (std::vector<Card*>::iterator i = mBattlezones[getOpponent(mTurn)].mCards.begin(); i != mBattlezones[getOpponent(mTurn)].mCards.end(); i++)
		{
			if (getCreatureCanBlock(mAttacker, (*i)->mUniqueId) && (*i)->mIsTapped == false
				&& ((*i)->mUniqueId != mDefender || mDefenderType == DEFENDER_PLAYER))
			{
				/*Message msg2("cardtap");
				msg2.addValue("card", (*i)->UniqueId);
				MsgMngr.sendMessage(msg2);*/

				Message msg("creatureblock");
				msg.addValue("attacker", mAttacker);
				msg.addValue("blocker", (*i)->mUniqueId);
				moves.push_back(msg);
			}
		}
		Message m("blockskip");
		moves.push_back(m);
	}
	else if (mCastingCard != -1 && player == mTurn) //tap mana
	{
		for (std::vector<Card*>::iterator i = mManazones[mTurn].mCards.begin(); i != mManazones[mTurn].mCards.end(); i++)
		{
			if ((*i)->mIsTapped == false)
			{
				if (mCastingCost == 1) //last card to be tapped
				{
					if (getCardCivilization((*i)->mUniqueId) == mCastingCiv || mCastingCivTapped)
					{
						Message m("manatap");
						m.addValue("card", (*i)->mUniqueId);
						moves.push_back(m);
					}
				}
				else
				{
					Message m("manatap");
					m.addValue("card", (*i)->mUniqueId);
					moves.push_back(m);
				}
			}
		}
	}

	if (player == mTurn && !mIsChoiceActive)
	{
		for (std::vector<Card*>::iterator i = mHands[mTurn].mCards.begin(); i != mHands[mTurn].mCards.end(); i++)
		{
			if (getCardCost((*i)->mUniqueId) <= mManazones[mTurn].getUntappedMana()
				&& isThereUntappedManaOfCiv(mTurn, getCardCivilization((*i)->mUniqueId)) && getCardCanCast((*i)->mUniqueId) == 1)
			{
				if (getIsEvolution((*i)->mUniqueId) == 1)
				{
					for (std::vector<Card*>::iterator j = mBattlezones[mTurn].mCards.begin(); j != mBattlezones[mTurn].mCards.end(); j++)
					{
						if (getCreatureCanEvolve((*i)->mUniqueId, (*j)->mUniqueId) == 1)
						{
							Message msg("cardplay");
							msg.addValue("card", (*i)->mUniqueId);
							msg.addValue("evobait", (*j)->mUniqueId);
							moves.push_back(msg);
						}
					}
				}
				else
				{
					Message msg("cardplay");
					msg.addValue("card", (*i)->mUniqueId);
					msg.addValue("evobait", -1);
					moves.push_back(msg);
				}
			}
			if (mManaUsed == 0)
			{
				Message msg("cardmana");
				msg.addValue("card", (*i)->mUniqueId);
				moves.push_back(msg);
			}
		}
	}

	if (player == mTurn && !mIsChoiceActive)
	{
		for (std::vector<Card*>::iterator i = mBattlezones[mTurn].mCards.begin(); i != mBattlezones[mTurn].mCards.end(); i++)
		{
			int canattack = getCreatureCanAttackPlayers((*i)->mUniqueId);
			if ((canattack == CANATTACK_ALWAYS ||
				((mCardList.at((*i)->mUniqueId)->mSummoningSickness == 0 || getIsSpeedAttacker((*i)->mUniqueId) == 1) && (canattack == CANATTACK_TAPPED || canattack == CANATTACK_UNTAPPED)))
				&& mCardList.at((*i)->mUniqueId)->mIsTapped == false)
			{
				Message msg("creatureattack");
				msg.addValue("attacker", (*i)->mUniqueId);
				msg.addValue("defender", getOpponent(mTurn));
				msg.addValue("defendertype", DEFENDER_PLAYER);
				moves.push_back(msg);
			}
			for (std::vector<Card*>::iterator j = mBattlezones[getOpponent(mTurn)].mCards.begin(); j != mBattlezones[getOpponent(mTurn)].mCards.end(); j++)
			{
				int canattack = getCreatureCanAttackCreature((*i)->mUniqueId, (*j)->mUniqueId);
				if (((*j)->mIsTapped == true || canattack == CANATTACK_UNTAPPED)
					&& canattack <= CANATTACK_UNTAPPED
					&& mCardList.at((*i)->mUniqueId)->mSummoningSickness == 0
					&& mCardList.at((*i)->mUniqueId)->mIsTapped == false)
				{
					Message msg("creatureattack");
					msg.addValue("attacker", (*i)->mUniqueId);
					msg.addValue("defender", (*j)->mUniqueId);
					msg.addValue("defendertype", DEFENDER_CREATURE);
					moves.push_back(msg);
				}
			}
		}
	}

	return moves;
}

int Duel::handleInterfaceInput(Message& msg)
{
	mCurrentMoveCount++;
	mMoveHistory.push_back(msg);
	std::string type = msg.getType();
	printf("handling interface input: %s\n", msg.getType().c_str());
	if (type == "cardplay")
	{
		int whichCard = msg.getInt("card");
		int manacost = getCardCost(whichCard);
		if (mManazones[mTurn].getUntappedMana() >= manacost && isThereUntappedManaOfCiv(mTurn, getCardCivilization(whichCard)) && getCardCanCast(whichCard)==1) //has appropriate mana
		{
			int eb = msg.getInt("evobait");
			int e = getIsEvolution(whichCard);
			if ((getCreatureCanEvolve(whichCard, eb) == 1 && e == 1) || e == 0) //can evolve if its an evolution
			{
				mCastingCard = whichCard;
				mCastingCiv = getCardCivilization(mCastingCard);
				mCastingCost = getCardCost(mCastingCard);
				mCastingCivTapped = false;
				mCastingEvobait = msg.getInt("evobait");
			}
			//MsgMngr.sendMessage(msg);
		}
	}
	else if (type == "cardmana")
	{
		if (mManaUsed == 0)
		{
			mMsgMngr.sendMessage(msg);
		}
	}
	else if (type == "endturn")
	{
		if (mAttackphase == PHASE_NONE && !mIsChoiceActive && mCastingCard == -1)
		{
			nextTurn();
		}
	}
	else if (type == "creatureattack")
	{
		int attck = msg.getInt("attacker");
		int defen = msg.getInt("defender");
		if (msg.getInt("defendertype") == DEFENDER_PLAYER)
		{
			int canattack = getCreatureCanAttackPlayers(attck);
			if ((canattack == CANATTACK_ALWAYS || 
				((mCardList.at(attck)->mSummoningSickness == 0 || getIsSpeedAttacker(attck) == 1) && (canattack == CANATTACK_TAPPED || canattack == CANATTACK_UNTAPPED)))
				&& mCardList.at(attck)->mIsTapped == false)
			{
				Message msg2("cardtap");
				msg2.addValue("card", msg.getInt("attacker"));
				mMsgMngr.sendMessage(msg2);
				mMsgMngr.sendMessage(msg);
			}
		}
		else if (msg.getInt("defendertype") == DEFENDER_CREATURE)
		{
			int canattack = getCreatureCanAttackCreature(attck, defen);
			if ((mCardList.at(defen)->mIsTapped == true || canattack == CANATTACK_UNTAPPED)
				&& canattack <= CANATTACK_UNTAPPED
				&& mCardList.at(attck)->mIsTapped == false
				&& mCardList.at(attck)->mSummoningSickness == 0)
			{
				Message msg2("cardtap");
				msg2.addValue("card", msg.getInt("attacker"));
				mMsgMngr.sendMessage(msg2);
				mMsgMngr.sendMessage(msg);
			}
		}
	}
	else if (type == "creatureblock")
	{
		if (mAttackphase == PHASE_BLOCK)
		{
			int blocker = msg.getInt("blocker");
			if (getCreatureCanBlock(mAttacker, blocker) && mCardList.at(blocker)->mIsTapped == false
				&& (blocker != mDefender || mDefenderType == DEFENDER_PLAYER))
			{
				Message msg2("cardtap");
				msg2.addValue("card", blocker);
				mMsgMngr.sendMessage(msg2);
				Message msg("creaturebattle");
				msg.addValue("attacker", mAttacker);
				msg.addValue("defender", blocker);
				mMsgMngr.sendMessage(msg);
				//resetAttack();
				Message msg3("resetattack");
				mMsgMngr.sendMessage(msg3);
			}
		}
	}
	else if (type == "blockskip")
	{
		if (mAttackphase == PHASE_BLOCK)
		{
			printf("mDefenderType: %d\n", mDefenderType);
			if (mDefenderType == DEFENDER_CREATURE)
			{
				Message m("creaturebattle");
				m.addValue("attacker", mAttacker);
				m.addValue("defender", mDefender);
				mMsgMngr.sendMessage(m);
				//resetAttack();
				Message msg3("resetattack");
				mMsgMngr.sendMessage(msg3);
			}
			else if (mDefenderType == DEFENDER_PLAYER)
			{
				printf("defender: %d\n", mDefender);
				if (mShields[mDefender].mCards.size() == 0)
				{
					mWinner = getOpponent(mDefender);
					printf("Winner: %d\n", mWinner);
				}
				else
				{
					//attackphase = PHASE_TARGET;
					printf("changing phase\n");
					Message m("changeattackphase");
					m.addValue("phase", PHASE_TARGET);
					m.addValue("oldphase", mAttackphase);
					mMsgMngr.sendMessage(m);
					mBreakCount = getCreatureBreaker(mAttacker);
				}
			}
		}
	}
	else if (type == "targetshield")
	{
		if (mAttackphase == PHASE_TARGET)
		{
			int shield = msg.getInt("shield");
			mShieldTargets.push_back(shield);

			if (mShieldTargets.size() >= mBreakCount || mShields[mCardList.at(shield)->mOwner].mCards.size() <= 1)
			{
				Message m("changeattackphase");
				m.addValue("phase", PHASE_TRIGGER);
				m.addValue("oldphase", mAttackphase);
				mMsgMngr.sendMessage(m);
			}

			Message m("creaturebreakshield");
			m.addValue("attacker", mAttacker);
			m.addValue("defender", mDefender);
			m.addValue("shield", shield);
			mMsgMngr.sendMessage(m);
		}
	}
	else if (type == "triggeruse")
	{
		if (mAttackphase == PHASE_TRIGGER)
		{
			for (std::vector<int>::iterator j = mShieldTargets.begin(); j != mShieldTargets.end(); j++)
			{
				int trigger = msg.getInt("trigger");
				if (*j == trigger)
				{
					if (getIsShieldTrigger(trigger) && canUseShieldTrigger(trigger) && getCardCanCast(trigger))
					{
						Message m("cardplay");
						m.addValue("card", trigger);
						m.addValue("evobait", -1);
						mMsgMngr.sendMessage(m);
					}
				}
			}
		}
	}
	else if (type == "triggerskip")
	{
		if (mAttackphase == PHASE_TRIGGER)
		{
			//resetAttack();
			Message msg3("resetattack");
			mMsgMngr.sendMessage(msg3);
		}
	}
	else if (type == "manatap")
	{
		int card = msg.getInt("card");
		if (mCardList.at(card)->mIsTapped == false && mCastingCard != -1)
		{
			if (mCastingCost == 1) //last card to be tapped
			{
				if (getCardCivilization(card) == mCastingCiv || mCastingCivTapped)
				{
					Message msg2("cardtap");
					msg2.addValue("card", card);
					mMsgMngr.sendMessage(msg2);
					mCastingCost--;
					mCastingCivTapped = true;

					Message msg3("cardplay");
					msg3.addValue("card", mCastingCard);
					msg3.addValue("evobait", mCastingEvobait);
					mMsgMngr.sendMessage(msg3);

					resetCasting();
				}
			}
			else
			{
				Message msg2("cardtap");
				msg2.addValue("card", card);
				mMsgMngr.sendMessage(msg2);
				mCastingCost--;
				if (getCardCivilization(card) == mCastingCiv)
				{
					mCastingCivTapped = true;
				}
			}
		}
	}
	else if (type == "choiceselect")
	{
		int sid = msg.getInt("selection");
		if (sid < 0 || choiceCanBeSelected(sid) == 1)
		{
			int chcard = mChoiceCard;
			resetChoice();
			Choice* c = mChoice;
			//c->callaction(chcard, sid);
			if (c != NULL)
			{
				if (mChoice == c)
					mChoice = NULL;
				delete c;
				c = NULL;
				mMsgMngr.sendMessage(msg);
			}
		}
	}
	else if (type == "creatureusetapability")
	{
		int cid = msg.getInt("creature");
		if (getCreatureHasTapAbility(cid) == 1)
		{
			mMsgMngr.sendMessage(msg);
		}
	}
	/*else if (type == "choicebutton1")
	{
		if (choice.buttoncount >= 1 && isChoiceActive)
		{
			int chcard = choiceCard;
			resetChoice();
			choice.callbutton1(chcard);
		}
	}
	else if (type == "choicebutton2")
	{
		if (choice.buttoncount >= 2 && isChoiceActive)
		{
			int chcard = choiceCard;
			resetChoice();
			choice.callbutton2(chcard);
		}
	}*/
	return 0;
}

void Duel::loopInput()
{
	for (int i = 0; ; i++)
	{
		if (i % 100000 == 0)
		{
			gMutex.lock();
			//printf("dispatching\n");
			dispatchAllMessages();
			gMutex.unlock();
		}
	}
}

int Duel::waitForChoice()
{
	gMutex.unlock();
	int choice = -1;
	for (int i = 0;; i++)
	{
		if (i % 100000 == 0)
		{
			//printf("mutex\n");
			gMutex.lock();
			if (mMsgMngr.hasMoreMessages())
			{
				Message msg = mMsgMngr.peekMessage();
				mMsgMngr.dispatch();
				if (!mIsSimulation)
				{
					printf("Dispatching Message:\n");
					for (std::map<std::string, std::string>::iterator i = msg.map.begin(); i != msg.map.end(); i++)
					{
						printf("	%s %s\n", (i->first).c_str(), (i->second).c_str());
					}
					printf("\n");
				}
				dispatchMessage(msg);
				if (msg.getType() == "choiceselect")
				{
					choice = msg.getInt("selection");
					break;
				}
			} 
			gMutex.unlock();
		}
	}
	//gMutex.lock();
	//printf("break\n");
	return choice;
}

//void Duel::parseMessages(unsigned int deltatime)
//{
//	if (!isChoiceActive)
//	{
//		bool worldchanged = dispatchAllMessages();
//		if (worldchanged)
//		{
//			for (std::vector<Card*>::iterator i = mCardList.begin(); i != mCardList.end(); i++)
//			{
//				if ((*i)->Zone == ZONE_BATTLE)
//				{
//					(*i)->updatePower(getCreaturePower((*i)->UniqueId));
//				}
//			}
//		}
//	}
//}

bool Duel::dispatchAllMessages()
{
	bool worldchanged = false;
	while (mMsgMngr.hasMoreMessages())
	{
		Message msg = mMsgMngr.peekMessage();
		mMsgMngr.dispatch();
		if (!mIsSimulation)
		{
			printf("Dispatching Message:\n");
			for (std::map<std::string, std::string>::iterator i = msg.map.begin(); i != msg.map.end(); i++)
			{
				printf("	%s %s\n", (i->first).c_str(), (i->second).c_str());
			}
			printf("\n");
		}
		dispatchMessage(msg);
		worldchanged = true;
	}
	return worldchanged;
}

void Duel::dispatchMessage(Message& msg)
{
	std::string type = msg.getString("msgtype");
	std::vector<Card*>::iterator i;

	mCurrentMessage = msg;

	mCurrentMessage.addValue("msgtype", "mod " + type);
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(msg);
	}

	//std::cout << "  mod\n";
	if (mCurrentMessage.getInt("msgContinue") == 0) //do we continue?
		return;

	mCurrentMessage.addValue("msgtype", "pre " + type);
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(msg);
	}

	//std::cout << "  pre\n";
	if (mCurrentMessage.getInt("msgContinue") == 0)
		return;

	mCurrentMessage.addValue("msgtype", type);
	handleMessage(mCurrentMessage);
	//std::cout << "  in\n";

	mCurrentMessage.addValue("msgtype", "post " + type);
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(msg);
	}

	//std::cout << "  post\n";
}

void Duel::addChoice(std::string info, int skip, int card, int player, int validref, int actionref)
{
	/*if (choice != NULL)
	{
		delete choice;
		choice = NULL;
	}*/
	mChoice = new Choice(info, skip, validref, actionref);
	mChoiceCard = card;
	mChoicePlayer = player;
	mIsChoiceActive = true;
	//cout << "choice set: " << CardList.at(choiceCard)->Name << ": " << info << endl;
}

int Duel::choiceCanBeSelected(int sid)
{
	return mChoice->callvalid(mChoiceCard, sid);
}

void Duel::checkChoiceValid()
{
	int count = 0;
	for (std::vector<Card*>::iterator i = mCardList.begin(); i != mCardList.end(); i++)
	{
		if (choiceCanBeSelected((*i)->mUniqueId) == 1)
		{
			count++;
		}
	}
	if (count == 0) //no valid targets
	{
		//cout << "no valid targets" << endl;
		resetChoice();
	}
}

void Duel::battle(int att, int def)
{
	Card* a = mCardList.at(att);
	Card* d = mCardList.at(def);
	int p1 = getCreaturePower(a->mUniqueId);
	int p2 = getCreaturePower(d->mUniqueId);
	if (p1 >= p2)
	{
		Message msg("creaturedestroy");
		msg.addValue("creature", def);
		msg.addValue("zoneto", ZONE_GRAVEYARD);
		mMsgMngr.sendMessage(msg);
	}
	if (p2 >= p1)
	{
		Message msg("creaturedestroy");
		msg.addValue("creature", att);
		msg.addValue("zoneto", ZONE_GRAVEYARD);
		mMsgMngr.sendMessage(msg);
	}
}

int Duel::getCreaturePower(int uid)
{
	Message oldmsg = mCurrentMessage;
	mCurrentMessage = Message("get creaturepower");
	mCurrentMessage.addValue("power", mCardList.at(uid)->mPower);
	mCurrentMessage.addValue("creature", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(mCurrentMessage);
	}
	int c = mCurrentMessage.getInt("power");
	mCurrentMessage = oldmsg;
	return c;
}

int Duel::getCreatureBreaker(int uid)
{
	Message oldmsg = mCurrentMessage;
	mCurrentMessage = Message("get creaturebreaker");
	mCurrentMessage.addValue("breaker", mCardList.at(uid)->mBreaker);
	mCurrentMessage.addValue("creature", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(mCurrentMessage);
	}
	int c = mCurrentMessage.getInt("breaker");
	mCurrentMessage = oldmsg;
	return c;
}

//int Duel::getCreatureCanAttack(int uid)
//{
//	Message oldmsg = currentMessage;
//	currentMessage = Message("get creaturecanattack");
//	currentMessage.addValue("canattack", 1);
//	currentMessage.addValue("creature", uid);
//
//	vector<Card*>::iterator i;
//	for (i = CardList.begin(); i != CardList.end(); i++)
//	{
//		(*i)->handleMessage(currentMessage);
//	}
//	int c = currentMessage.getInt("canattack");
//	currentMessage = oldmsg;
//	return c;
//}

//int Duel::getCreatureCanBeAttacked(int attckr, int dfndr)
//{
//	Message oldmsg = currentMessage;
//	currentMessage = Message("get creaturecanbeattacked");
//	currentMessage.addValue("canbeattacked", 1);
//	currentMessage.addValue("attacker", attckr);
//	currentMessage.addValue("defender", dfndr);
//
//	vector<Card*>::iterator i;
//	for (i = CardList.begin(); i != CardList.end(); i++)
//	{
//		(*i)->handleMessage(currentMessage);
//	}
//	int c = currentMessage.getInt("canbeattacked");
//	currentMessage = oldmsg;
//	return c;
//}

int Duel::getCreatureIsBlocker(int uid)
{
	Message oldmsg = mCurrentMessage;
	mCurrentMessage = Message("get creatureisblocker");
	mCurrentMessage.addValue("isblocker", mCardList.at(uid)->mIsBlocker);
	mCurrentMessage.addValue("creature", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(mCurrentMessage);
	}
	int c = mCurrentMessage.getInt("isblocker");
	mCurrentMessage = oldmsg;
	return c;
}

int Duel::getCreatureCanBlock(int attckr,int blckr)
{
	Message oldmsg = mCurrentMessage;
	mCurrentMessage = Message("get creaturecanblock");
	mCurrentMessage.addValue("canblock", getCreatureIsBlocker(blckr));
	mCurrentMessage.addValue("blocker", blckr);
	mCurrentMessage.addValue("attacker", attckr);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(mCurrentMessage);
	}
	int c = mCurrentMessage.getInt("canblock");
	mCurrentMessage = oldmsg;
	return c;
}

//int Duel::getCreatureCanBeBlocked(int uid)
//{
//	Message oldmsg = currentMessage;
//	currentMessage = Message("get creaturecanbeblocked");
//	currentMessage.addValue("canbeblocked", 1);
//	currentMessage.addValue("creature", uid);
//
//	vector<Card*>::iterator i;
//	for (i = CardList.begin(); i != CardList.end(); i++)
//	{
//		(*i)->handleMessage(currentMessage);
//	}
//	int c = currentMessage.getInt("canbeblocked");
//	currentMessage = oldmsg;
//	return c;
//}

int Duel::getCreatureCanAttackPlayers(int uid)
{
	Message oldmsg = mCurrentMessage;
	mCurrentMessage = Message("get creaturecanattackplayers");
	mCurrentMessage.addValue("canattack", CANATTACK_TAPPED);
	mCurrentMessage.addValue("attacker", uid);

	int big = CANATTACK_TAPPED;

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(mCurrentMessage);
		if (mCurrentMessage.getInt("canattack") > big)
		{
			big = mCurrentMessage.getInt("canattack");
		}
		else
		{
			mCurrentMessage.addValue("canattack", big);
		}
	}
	int c = mCurrentMessage.getInt("canattack");
	mCurrentMessage = oldmsg;
	return c;
}

int Duel::getCreatureCanAttackCreature(int attckr, int dfndr)
{
	Message oldmsg = mCurrentMessage;
	mCurrentMessage = Message("get creaturecanattackcreature");
	mCurrentMessage.addValue("canattack", CANATTACK_TAPPED);
	mCurrentMessage.addValue("attacker", attckr);
	mCurrentMessage.addValue("defender", dfndr);

	int big = CANATTACK_TAPPED;

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(mCurrentMessage);
		if (mCurrentMessage.getInt("canattack") > big)
		{
			big = mCurrentMessage.getInt("canattack");
		}
		else
		{
			mCurrentMessage.addValue("canattack", big);
		}
	}
	int c = mCurrentMessage.getInt("canattack");
	mCurrentMessage = oldmsg;
	return c;
}

//int Duel::getCreatureCanAttackCreatures(int uid)
//{
//	Message oldmsg = currentMessage;
//	currentMessage = Message("get creaturecanattackcreatures");
//	currentMessage.addValue("canattack", 1);
//	currentMessage.addValue("creature", uid);
//
//	vector<Card*>::iterator i;
//	for (i = CardList.begin(); i != CardList.end(); i++)
//	{
//		(*i)->handleMessage(currentMessage);
//	}
//	int c = currentMessage.getInt("canattack");
//	currentMessage = oldmsg;
//	return c;
//}

//int Duel::getCreatureCanAttackTarget(int attckr, int dfndr)
//{
//	Message oldmsg = currentMessage;
//	currentMessage = Message("get creaturecanattacktarget");
//	currentMessage.addValue("canattack", 1);
//	currentMessage.addValue("attacker", attckr);
//	currentMessage.addValue("defender", attckr);
//
//	vector<Card*>::iterator i;
//	for (i = CardList.begin(); i != CardList.end(); i++)
//	{
//		(*i)->handleMessage(currentMessage);
//	}
//	int c = currentMessage.getInt("canattack");
//	currentMessage = oldmsg;
//	return c;
//}

//int Duel::getCreatureCanAttackUntappedCreatures(int uid)
//{
//	Message oldmsg = currentMessage;
//	currentMessage = Message("get creaturecanattackuntappedcreatures");
//	currentMessage.addValue("canattackuntappedcreatures", 0);
//	currentMessage.addValue("creature", uid);
//
//	vector<Card*>::iterator i;
//	for (i = CardList.begin(); i != CardList.end(); i++)
//	{
//		(*i)->handleMessage(currentMessage);
//	}
//	int c = currentMessage.getInt("canattackuntappedcreatures");
//	currentMessage = oldmsg;
//	return c;
//}

int Duel::getCardCost(int uid)
{
	Message oldmsg = mCurrentMessage;
	mCurrentMessage = Message("get cardcost");
	mCurrentMessage.addValue("cost", mCardList.at(uid)->mManaCost);
	mCurrentMessage.addValue("card", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(mCurrentMessage);
	}
	int c = mCurrentMessage.getInt("cost");
	mCurrentMessage = oldmsg;
	return c;
}

int Duel::getIsShieldTrigger(int uid)
{
	Message oldmsg = mCurrentMessage;
	mCurrentMessage = Message("get cardshieldtrigger");
	mCurrentMessage.addValue("shieldtrigger", mCardList.at(uid)->mIsShieldTrigger);
	mCurrentMessage.addValue("card", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(mCurrentMessage);
	}
	int c = mCurrentMessage.getInt("shieldtrigger");
	mCurrentMessage = oldmsg;
	return c;
}

int Duel::canUseShieldTrigger(int uid)
{
	Message oldmsg = mCurrentMessage;
	mCurrentMessage = Message("get canuseshieldtrigger");
	mCurrentMessage.addValue("canuse", 1);
	mCurrentMessage.addValue("card", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(mCurrentMessage);
	}
	int c = mCurrentMessage.getInt("canuse");
	mCurrentMessage = oldmsg;
	return c;
}

int Duel::getIsEvolution(int uid)
{
	Message oldmsg = mCurrentMessage;
	mCurrentMessage = Message("get creatureisevolution");
	mCurrentMessage.addValue("isevolution", 0);
	mCurrentMessage.addValue("creature", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(mCurrentMessage);
	}
	int c = mCurrentMessage.getInt("isevolution");
	mCurrentMessage = oldmsg;
	return c;
}

int Duel::getIsSpeedAttacker(int uid)
{
	Message oldmsg = mCurrentMessage;
	mCurrentMessage = Message("get creatureisspeedattacker");
	mCurrentMessage.addValue("isspeedattacker", 0);
	mCurrentMessage.addValue("creature", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(mCurrentMessage);
	}
	int c = mCurrentMessage.getInt("isspeedattacker");
	mCurrentMessage = oldmsg;
	return c;
}

int Duel::getCardCanCast(int uid)
{
	Message oldmsg = mCurrentMessage;
	mCurrentMessage = Message("get cardcancast");
	mCurrentMessage.addValue("cancast", 1);
	mCurrentMessage.addValue("card", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(mCurrentMessage);
	}
	int c = mCurrentMessage.getInt("cancast");
	mCurrentMessage = oldmsg;
	return c;
}

int Duel::getCardCivilization(int uid)
{
	return mCardList.at(uid)->mCivilization;
}

int Duel::isCreatureOfRace(int uid, std::string race)
{
	std::string r = getCreatureRace(uid);
	//printf("race %s %s\n", r.c_str(), race.c_str());
	int f = r.find(race);
	if (f != std::string::npos)
	{
		if (f == 0 || r.at(f-1) == ' ' || r.at(f-1) == '/')
		{
			int s1 = race.size();
			int s2 = r.size();
			if (s1+f == s2 || r.at(f+s1) == ' ' || r.at(f+s1) == '/')
			{
				return 1;
			}
		}
	}
	return 0;
}

std::string Duel::getCreatureRace(int uid)
{
	return mCardList.at(uid)->mRace;
}

int Duel::getCreatureCanEvolve(int evo, int bait)
{
	Message oldmsg = mCurrentMessage;
	mCurrentMessage = Message("get creaturecanevolve");
	mCurrentMessage.addValue("canevolve", 0);
	mCurrentMessage.addValue("evolution", evo);
	mCurrentMessage.addValue("evobait", bait);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(mCurrentMessage);
	}
	int c = mCurrentMessage.getInt("canevolve");
	mCurrentMessage = oldmsg;
	return c;
}

int Duel::getCreatureHasTapAbility(int uid)
{
	Message oldmsg = mCurrentMessage;
	mCurrentMessage = Message("get creaturehastapability");
	mCurrentMessage.addValue("hastapability", 1);
	mCurrentMessage.addValue("creature", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(mCurrentMessage);
	}
	int c = mCurrentMessage.getInt("hastapability");
	mCurrentMessage = oldmsg;
	return c;
}

bool Duel::isThereUntappedManaOfCiv(int player,int civ)
{
	for (std::vector<Card*>::iterator i = mManazones[player].mCards.begin(); i != mManazones[player].mCards.end(); i++)
	{
		if ((*i)->mIsTapped == false && getCardCivilization((*i)->mUniqueId) == civ)
			return true;
	}
	return false;
}

void Duel::drawCards(int player, int count)
{
	count = count < mDecks[player].mCards.size() ? count : mDecks[player].mCards.size();
	for (int i = 0; i < count; i++)
	{
		Message msg("cardmove");
		msg.addValue("card", mDecks[player].mCards.at(mDecks[player].mCards.size() - i - 1)->mUniqueId);
		msg.addValue("from", mDecks[player].mCards.at(mDecks[player].mCards.size() - i - 1)->mZone);
		msg.addValue("to", ZONE_HAND);
		mMsgMngr.sendMessage(msg);
	}
}

void Duel::setDecks(std::string p1, std::string p2)
{
	loadDeck(p1, 0);
	loadDeck(p2, 1);

	/*decks[0].x = ZONE2X;
	decks[1].x = ZONE2X;
	decks[0].y = CENTER - ZONEYOFFSET * 4;
	decks[1].y = CENTER + ZONEYOFFSET * 3;*/
}

void Duel::loadDeck(std::string s, int p)
{
	mDecks[p].mCards.empty();
	std::fstream file;
	file.open(s, std::ios::in | std::ios::out);
	std::string str;

	if (!file.is_open())
	{
		//cout << "ERROR opening deck: " << s << endl;
		printf("ERROR opening deck %s\n", s.c_str());
	}

	while (!file.eof())
	{
		getline(file, str);
		if (str == "")
			continue;
		//if (!isSimulation)
		//	cout << "loading card " << str << endl;
		for (int i = 0; i < str.size(); i++)
		{
			if (str.at(i) == ' ')
			{
				int count = atoi(str.substr(0, i).c_str());
				std::string name = str.substr(i + 1);
				for (int j = 0; j < count; j++)
				{
					printf("added %s\n", name.c_str());
					Card* c = new Card(mNextUniqueId, getCardIdFromName(name), p);
					mCardList.push_back(c);
					mDecks[p].addCard(c);
					mNextUniqueId++;
				}
				break;
			}
		}
	}

	file.close();

	mDeckNames[p] = s;
}

//void Duel::loadDeck(string s, int p)
//{
//	decks[p].cards.empty();
//	fstream file;
//	file.open(s, ios::in | ios::out);
//	string str;
//
//	while (!file.eof())
//	{
//		getline(file, str);
//		if (str == "")
//			continue;
//		cout << "loading card " << str << endl;
//		Card* c = new Card(nextUniqueId, getCardIdFromName(str), p);
//		CardList.push_back(c);
//		decks[p].addCard(c);
//		nextUniqueId++;
//	}
//
//	file.close();
//}

void Duel::startDuel()
{
	mTurn = 0;
	mManaUsed = 0;
	for (int i = 0; i < 2; i++)
	{
		if (mDecks[i].mCards.size() < 40)
		{
			printf("WARNING: Deck card count less than 40\n");
		}
		mDecks[i].shuffle();
		for (int j = 0; j < 5; j++)
		{
			/*Card* c = decks[i].draw();
			shields[i].addCard(c);*/
			Message msg("cardmove");
			msg.addValue("card", mDecks[i].mCards.at(mDecks[i].mCards.size() - 1 - j)->mUniqueId);
			msg.addValue("from", ZONE_DECK);
			msg.addValue("to", ZONE_SHIELD);
			mMsgMngr.sendMessage(msg);
		}
		for (int j = 0; j < 5; j++)
		{
			/*Card* c = decks[i].draw();
			hands[i].addCard(c);*/
			Message msg("cardmove");
			msg.addValue("card", mDecks[i].mCards.at(mDecks[i].mCards.size() - 6 - j)->mUniqueId);
			msg.addValue("from", ZONE_DECK);
			msg.addValue("to", ZONE_HAND);
			mMsgMngr.sendMessage(msg);
		}
	}
}

void Duel::nextTurn()
{
	Message msg("endturn");
	msg.addValue("player", mTurn);
	mMsgMngr.sendMessage(msg);
}

void Duel::resetAttack()
{
	//cout << "attackreset" << endl;
	mAttackphase = PHASE_NONE;
	mAttacker = -1;
	mDefender = -1;
	mBreakCount = -1;
	mShieldTargets.clear();
}

void Duel::resetCasting()
{
	//cout << "casting reset" << endl;
	mCastingCard = -1;
	mCastingCiv = -1;
	mCastingCivTapped = false;
	mCastingCost = -1;
	mCastingEvobait = -1;
}

void Duel::clearCards()
{
	for (int i = 0; i < 2; i++)
	{
		mDecks[i].mCards.clear();
		mGraveyards[i].mCards.clear();
		mHands[i].mCards.clear();
		mManazones[i].mCards.clear();
		mShields[i].mCards.clear();
		mBattlezones[i].mCards.clear();

		mShields[i].mSlotsUsed = 0;
	}
	mCardList.clear();
	mNextUniqueId = 0;
}

void Duel::resetChoice()
{
	mChoiceCard = -1;
	mChoicePlayer = -1;
	mIsChoiceActive = false;
	//cout << "choice reset" << endl;
}

Zone* Duel::getZone(int player, int zone)
{
	if (zone == ZONE_BATTLE)
	{
		return &mBattlezones[player];
	}
	else if (zone == ZONE_MANA)
	{
		return &mManazones[player];
	}
	else if (zone == ZONE_HAND)
	{
		return &mHands[player];
	}
	else if (zone == ZONE_DECK)
	{
		return &mDecks[player];
	}
	else if (zone == ZONE_SHIELD)
	{
		return &mShields[player];
	}
	else if (zone == ZONE_GRAVEYARD)
	{
		return &mGraveyards[player];
	}
	else if (zone == ZONE_EVOLVED)
	{
		return &mBattlezones[player];
	}
	printf("WARNING: getZone called with unknown zone type: %d\n", zone);
	return NULL;
}

void Duel::flipCard(int cid)
{
	mCardList.at(cid)->flip();
}

void Duel::unflipCard(int cid)
{
	mCardList.at(cid)->unflip();
}

void Duel::setCardVisibility(int cid, int player, int visibility)
{
	mCardList[cid]->setVisibility(player, visibility);
}

void Duel::destroyCard(Card* c)
{
	//moveCard(c, ZONE_GRAVEYARD);
}

int getOpponent(int turn)
{
	return (turn + 1) % 2;
}