#include "Duel.h"

Duel::Duel()
{
	turn = 0;
	manaUsed = 0;
	nextUniqueId = 0;

	int Factor[2] = { -1, 1 };
	int Factor2[2] = { 1,0 };
	for (int i = 0; i < 2; i++)
	{
		decks[i].RandomGen = &RandomGen; //set random function for deck shuffling

		decks[i].owner = i;
		battlezones[i].owner = i;
		graveyards[i].owner = i;
		hands[i].owner = i;
		manazones[i].owner = i;
		shields[i].owner = i;

		decks[i].mPos = glm::vec3(-2*CONST_CARDSEPERATION, CONST_CARDELEVATION, Factor[i] * (1*CONST_CARDSEPERATION+Factor2[i]*CONST_CARDSEPERATION));
		graveyards[i].mPos = glm::vec3(-2*CONST_CARDSEPERATION, CONST_CARDELEVATION, Factor[i] * (2*CONST_CARDSEPERATION+Factor2[i]*CONST_CARDSEPERATION));
		hands[i].mPos = glm::vec3(-2*CONST_CARDSEPERATION, CONST_CARDELEVATION, Factor[i] * (3 * CONST_CARDSEPERATION + Factor2[i] * CONST_CARDSEPERATION));
		manazones[i].mPos = glm::vec3(-2*CONST_CARDSEPERATION, CONST_CARDELEVATION, Factor[i] * (2 * CONST_CARDSEPERATION + Factor2[i] * CONST_CARDSEPERATION));
		shields[i].mPos = glm::vec3(-2*CONST_CARDSEPERATION, CONST_CARDELEVATION, Factor[i] * (1 * CONST_CARDSEPERATION + Factor2[i] * CONST_CARDSEPERATION));
		battlezones[i].mPos = glm::vec3(-2*CONST_CARDSEPERATION, CONST_CARDELEVATION, Factor[i] * (0 * CONST_CARDSEPERATION + Factor2[i] * CONST_CARDSEPERATION));

		decks[i].mHeight = CONST_CARDSEPERATION;
		graveyards[i].mHeight = CONST_CARDSEPERATION;
		hands[i].mHeight = CONST_CARDSEPERATION;
		manazones[i].mHeight = CONST_CARDSEPERATION;
		shields[i].mHeight = CONST_CARDSEPERATION;
		battlezones[i].mHeight = CONST_CARDSEPERATION;

		decks[i].mWidth = CONST_CARDSEPERATION;
		graveyards[i].mWidth = CONST_CARDSEPERATION;
		hands[i].mWidth = CONST_CARDSEPERATION;
		manazones[i].mWidth = CONST_CARDSEPERATION*5;
		shields[i].mWidth = CONST_CARDSEPERATION*5;
		battlezones[i].mWidth = CONST_CARDSEPERATION*5;

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

	attackphase = PHASE_NONE;
	attacker = -1;
	defender = -1;
	breakcount = -1;
	
	castingcard = -1;
	castingciv = -1;
	castingcost = -1;
	castingcivtapped = false;

	isChoiceActive = false;
	choiceCard = -1;
	choicePlayer = -1;

	winner = -1;

	currentMoveCount = 0;

	RandomGen.Randomize();

	isSimulation = false;
}

Duel::~Duel()
{
	for (int i = 0; i < mCardList.size(); i++)
	{
		if (mCardList.at(i) != NULL)
			delete mCardList.at(i);
	}
	if (choice != NULL)
		delete choice;
}

void Duel::copyFrom(Duel* duel) //incomplete, not used
{
	turn = duel->turn;
	manaUsed = duel->manaUsed;
	nextUniqueId = duel->nextUniqueId;

	attackphase = duel->attackphase;
	attacker = duel->attacker;
	defender = duel->defender;
	breakcount = duel->breakcount;

	castingcard = duel->castingcard;
	castingciv = duel->castingciv;
	castingcost = duel->castingcost;
	castingcivtapped = duel->castingcivtapped;

	isChoiceActive = duel->isChoiceActive;
	choiceCard = duel->choiceCard;
	choicePlayer = duel->choicePlayer;

	winner = duel->winner;

	nextUniqueId = duel->nextUniqueId;

	for (std::vector<int>::iterator i = duel->shieldtargets.begin(); i != duel->shieldtargets.end(); i++)
	{
		shieldtargets.push_back(*i);
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
			for (std::vector<Card*>::iterator j = duel->getZone(i, z)->cards.begin(); j != duel->getZone(i, z)->cards.end(); j++)
			{
				for (std::vector<Card*>::iterator k = mCardList.begin(); k != mCardList.end(); k++)
				{
					if ((*k)->UniqueId == (*j)->UniqueId)
					{
						getZone(i, z)->cards.push_back(*k);
						break;
					}
				}
			}
		}
	}
	choice->copyFrom(duel->choice);
}

int Duel::handleMessage(Message& msg)
{
	MsgHistoryItem k;
	k.msg = msg;
	k.move = currentMoveCount;
	MessageHistory.push_back(k);
	if (msg.getType() == "cardmove")
	{
		int cid = msg.getInt("card");
		int tozone = msg.getInt("to");
		Card* c = mCardList.at(cid);
		int owner = c->Owner;
		getZone(owner, c->Zone)->removeCard(c);
		if (tozone == ZONE_BATTLE && getIsEvolution(cid) == 1) //evolution creatures
		{
			int evobait = msg.getInt("evobait");
			if (evobait == -1)
			{
				getZone(owner, tozone)->addCard(c);
				battlezones[owner].addCard(c);
			}
			else
			{
				battlezones[owner].evolveCard(c, evobait);
			}
		}
		else
		{
			getZone(owner, tozone)->addCard(c);
		}
		c->Zone = tozone;
		if (tozone != ZONE_BATTLE)
		{
			for (int i = c->evostack.size()-1; i >= 0; i--) //move all cards in stack to the zone seperately
			{
				Message m("cardmove");
				m.addValue("card", c->evostack.at(i)->UniqueId);
				m.addValue("from", c->evostack.at(i)->Zone);
				m.addValue("to", tozone);
				MsgMngr.sendMessage(m);
				c->evostack.pop_back();
			}
		}
		if (c->Zone == ZONE_BATTLE && c->Type == TYPE_SPELL)
		{
			c->callOnCast(); //cast the spell
			Message m("cardmove");
			m.addValue("card", cid);
			m.addValue("from", mCardList.at(cid)->Zone);
			m.addValue("to", ZONE_GRAVEYARD);
			MsgMngr.sendMessage(m);
		}
		if (decks[owner].cards.size() == 0)
		{
			//player loses game
			winner = getOpponent(turn);
		}
	}
	else if (msg.getType() == "creaturedestroy")
	{
		Message m("cardmove");
		int cid = msg.getInt("creature");
		m.addValue("card", cid);
		m.addValue("from", mCardList.at(cid)->Zone);
		m.addValue("to", msg.getInt("zoneto"));
		MsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "carddiscard")
	{
		Message m("cardmove");
		int cid = msg.getInt("card");
		m.addValue("card", cid);
		m.addValue("from", mCardList.at(cid)->Zone);
		m.addValue("to", msg.getInt("zoneto"));
		MsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "manadestroy")
	{
		Message m("cardmove");
		int cid = msg.getInt("card");
		m.addValue("card", cid);
		m.addValue("from", mCardList.at(cid)->Zone);
		m.addValue("to", msg.getInt("zoneto"));
		MsgMngr.sendMessage(m);
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
		m.addValue("from", mCardList.at(cid)->Zone);
		m.addValue("to", ZONE_BATTLE);
		m.addValue("evobait", eb);
		MsgMngr.sendMessage(m);
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
		manaUsed = 1;
		int cid = msg.getInt("card");
		Message m("cardmove");
		m.addValue("card", cid);
		m.addValue("from", mCardList.at(cid)->Zone);
		m.addValue("to", ZONE_MANA);
		MsgMngr.sendMessage(m);
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
		attacker = msg.getInt("attacker");
		defender = msg.getInt("defender");
		defendertype = msg.getInt("defendertype");
		//cout << "attack " << attacker << " " << defender << " " << defendertype << endl;
		//attackphase = PHASE_BLOCK;
		Message m("changeattackphase");
		m.addValue("phase", PHASE_BLOCK);
		m.addValue("oldphase", attackphase);
		MsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "creatureblock")
	{
		Message m("creaturebattle");
		m.addValue("attacker", msg.getInt("attacker"));
		m.addValue("defender", msg.getInt("blocker"));
		MsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "creaturebreakshield")
	{
		Message m("breakshield");
		m.addValue("player", msg.getInt("defender"));
		m.addValue("shield", msg.getInt("shield"));
		m.addValue("cantrigger", 1);
		MsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "breakshield")
	{
		Message m("cardmove");
		int cid = msg.getInt("shield");
		m.addValue("card", cid);
		m.addValue("from", mCardList.at(cid)->Zone);
		m.addValue("to", ZONE_HAND);
		MsgMngr.sendMessage(m);
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
		turn = (turn + 1) % 2;
		manaUsed = 0;
		Message m("startturn");
		m.addValue("player", turn);
		MsgMngr.sendMessage(m);
		//if (!isSimulation)
		//	SoundMngr->playSound(SOUND_ENDTURN);
	}
	else if (msg.getType() == "startturn")
	{
		int plyr = msg.getInt("player");
		std::vector<Card*>::iterator i;
		for (i = battlezones[plyr].cards.begin(); i != battlezones[plyr].cards.end(); i++) //untap creatures
		{
			Message m("carduntap");
			m.addValue("card", (*i)->UniqueId);
			MsgMngr.sendMessage(m);
			(*i)->summoningSickness = 0;
		}
		for (i = manazones[plyr].cards.begin(); i != manazones[plyr].cards.end(); i++) //untap mana
		{
			Message m("carduntap");
			m.addValue("card", (*i)->UniqueId);
			MsgMngr.sendMessage(m);
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
		mCardList.at(uid)->modifiers.push_back(modifier);
	}
	else if (msg.getType() == "modifierdestroy")
	{
		int uid = msg.getInt("card");
		int mid = msg.getInt("modifier");
		Modifier* modifier = mCardList.at(uid)->modifiers.at(mid);
		mCardList.at(uid)->modifiers.erase(mCardList.at(uid)->modifiers.begin() + mid);
		delete modifier;
	}
	else if (msg.getType() == "changeattackphase")
	{
		attackphase = msg.getInt("phase");
	}
	else if (msg.getType() == "resetattack")
	{
		resetAttack();
	}
	else if (msg.getType() == "deckshuffle")
	{
		decks[msg.getInt("player")].shuffle();
	}
	else if (msg.getType() == "carddiscardatrandom")
	{
		int plyr = msg.getInt("player");
		if (hands[plyr].cards.size() > 0)
		{
			Message m("carddiscard");
			m.addValue("card", hands[plyr].cards.at(RandomGen.Random(hands[plyr].cards.size()))->UniqueId);
			m.addValue("zoneto", ZONE_GRAVEYARD);
			MsgMngr.sendMessage(m);
		}
	}
	else if (msg.getType() == "evolutionseperate")
	{
		int cid = msg.getInt("evolution");
		battlezones[mCardList.at(cid)->Owner].seperateEvolution(mCardList.at(cid));
	}
	return 0;
}

void Duel::undoLastMove()
{
	if (MessageHistory.size() == 0)
		return;
	for (int i = MessageHistory.size() - 1; i >= 0; i--)
	{
		MsgHistoryItem m = MessageHistory.at(i);
		if (m.move == currentMoveCount)
		{
			MessageHistory.pop_back();
			undoMessage(m.msg);
			//cout << "undoing " << m.msg.getType() << " for " << MoveHistory.at(MoveHistory.size() - 1).getType() << endl;
		}
		else
		{
			break;
		}
	}

	Message m = MoveHistory.at(MoveHistory.size() - 1);
	if (m.getType() == "cardplay")
	{
		resetCasting();
	}
	else if (m.getType() == "manatap")
	{

	}
	MoveHistory.pop_back();
	currentMoveCount--;
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
		int owner = c->Owner;
		getZone(owner, fromzone)->addCard(c);
		if (tozone == ZONE_BATTLE && getIsEvolution(cid) == 1) //evolution creatures
		{
			int evobait = msg.getInt("evobait");
			if (evobait == -1)
			{
				getZone(owner, tozone)->removeCard(c);
				battlezones[owner].removeCard(c);
			}
			else
			{
				battlezones[owner].evolveCard(c, evobait);
			}
		}
		else
		{
			getZone(owner, tozone)->removeCard(c);
		}
		c->Zone = fromzone;
		winner = -1;
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
		turn = (turn + 1) % 2;

		int flag = 0;
		for (std::vector<MsgHistoryItem>::reverse_iterator i = MessageHistory.rbegin(); i != MessageHistory.rend(); i++)
		{
			if ((*i).msg.getType() == "endturn")
			{
				manaUsed = 0;
				flag = 1;
				break;
			}
			if ((*i).msg.getType() == "cardmana")
			{
				manaUsed = 1;
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			manaUsed = 0;
		}
	}
	else if (msg.getType() == "cardmana")
	{
		manaUsed = 0;
	}
	else if (msg.getType() == "changeattackphase")
	{
		attackphase = msg.getInt("oldphase");
	}
}

int Duel::getPlayerToMove()
{
	if (isChoiceActive)
		return choicePlayer;
	if (attackphase == PHASE_BLOCK || attackphase == PHASE_TRIGGER)
		return getOpponent(turn);
	return turn;
}

std::vector<Message> Duel::getPossibleMoves()
{
	std::vector<Message> moves(0);
	int player = getPlayerToMove();
	if (turn == player && attackphase == PHASE_NONE && !(isChoiceActive) && castingcard == -1)
	{
		Message m("endturn");
		m.addValue("player", turn);
		moves.push_back(m);
	}
	else if (isChoiceActive && player == choicePlayer)
	{
		if (choice->buttoncount > 0)
		{
			Message msg("choiceselect");
			msg.addValue("selection", RETURN_BUTTON1);
			moves.push_back(msg);
		}
		if (choice->buttoncount > 1)
		{
			Message msg("choiceselect");
			msg.addValue("selection", RETURN_BUTTON2);
			moves.push_back(msg);
		}
		for (std::vector<Card*>::iterator i = mCardList.begin(); i != mCardList.end(); i++)
		{
			if ((*i)->Zone != ZONE_EVOLVED)
			{
				if (choice->callvalid(choiceCard, (*i)->UniqueId) == 1)
				{
					Message msg("choiceselect");
					msg.addValue("selection", (*i)->UniqueId);
					moves.push_back(msg);
				}
			}
		}
	}
	else if (attackphase == PHASE_TRIGGER && player == getOpponent(turn)) //use shield triggers
	{
		for (std::vector<Card*>::iterator i = hands[getOpponent(turn)].cards.begin(); i != hands[getOpponent(turn)].cards.end(); i++)
		{
			for (std::vector<int>::iterator j = shieldtargets.begin(); j != shieldtargets.end(); j++)
			{
				if (*j == (*i)->UniqueId)
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
	else if (attackphase == PHASE_TARGET && player == turn) //target shields
	{
		for (std::vector<Card*>::iterator i = shields[getOpponent(turn)].cards.begin(); i != shields[getOpponent(turn)].cards.end(); i++)
		{
			Message m("targetshield");
			m.addValue("attacker", attacker);
			m.addValue("shield", (*i)->UniqueId);
			moves.push_back(m);
		}
	}
	else if (attackphase == PHASE_BLOCK && player == getOpponent(turn)) //block
	{
		for (std::vector<Card*>::iterator i = battlezones[getOpponent(turn)].cards.begin(); i != battlezones[getOpponent(turn)].cards.end(); i++)
		{
			if (getCreatureCanBlock(attacker, (*i)->UniqueId) && (*i)->isTapped == false
				&& ((*i)->UniqueId != defender || defendertype == DEFENDER_PLAYER))
			{
				/*Message msg2("cardtap");
				msg2.addValue("card", (*i)->UniqueId);
				MsgMngr.sendMessage(msg2);*/

				Message msg("creatureblock");
				msg.addValue("attacker", attacker);
				msg.addValue("blocker", (*i)->UniqueId);
				moves.push_back(msg);
			}
		}
		Message m("blockskip");
		moves.push_back(m);
	}
	else if (castingcard != -1 && player == turn) //tap mana
	{
		for (std::vector<Card*>::iterator i = manazones[turn].cards.begin(); i != manazones[turn].cards.end(); i++)
		{
			if ((*i)->isTapped == false)
			{
				if (castingcost == 1) //last card to be tapped
				{
					if (getCardCivilization((*i)->UniqueId) == castingciv || castingcivtapped)
					{
						Message m("manatap");
						m.addValue("card", (*i)->UniqueId);
						moves.push_back(m);
					}
				}
				else
				{
					Message m("manatap");
					m.addValue("card", (*i)->UniqueId);
					moves.push_back(m);
				}
			}
		}
	}

	if (player == turn && !isChoiceActive)
	{
		for (std::vector<Card*>::iterator i = hands[turn].cards.begin(); i != hands[turn].cards.end(); i++)
		{
			if (getCardCost((*i)->UniqueId) <= manazones[turn].getUntappedMana()
				&& isThereUntappedManaOfCiv(turn, getCardCivilization((*i)->UniqueId)) && getCardCanCast((*i)->UniqueId) == 1)
			{
				if (getIsEvolution((*i)->UniqueId) == 1)
				{
					for (std::vector<Card*>::iterator j = battlezones[turn].cards.begin(); j != battlezones[turn].cards.end(); j++)
					{
						if (getCreatureCanEvolve((*i)->UniqueId, (*j)->UniqueId) == 1)
						{
							Message msg("cardplay");
							msg.addValue("card", (*i)->UniqueId);
							msg.addValue("evobait", (*j)->UniqueId);
							moves.push_back(msg);
						}
					}
				}
				else
				{
					Message msg("cardplay");
					msg.addValue("card", (*i)->UniqueId);
					msg.addValue("evobait", -1);
					moves.push_back(msg);
				}
			}
			if (manaUsed == 0)
			{
				Message msg("cardmana");
				msg.addValue("card", (*i)->UniqueId);
				moves.push_back(msg);
			}
		}
	}

	if (player == turn && !isChoiceActive)
	{
		for (std::vector<Card*>::iterator i = battlezones[turn].cards.begin(); i != battlezones[turn].cards.end(); i++)
		{
			int canattack = getCreatureCanAttackPlayers((*i)->UniqueId);
			if ((canattack == CANATTACK_ALWAYS ||
				((mCardList.at((*i)->UniqueId)->summoningSickness == 0 || getIsSpeedAttacker((*i)->UniqueId) == 1) && (canattack == CANATTACK_TAPPED || canattack == CANATTACK_UNTAPPED)))
				&& mCardList.at((*i)->UniqueId)->isTapped == false)
			{
				Message msg("creatureattack");
				msg.addValue("attacker", (*i)->UniqueId);
				msg.addValue("defender", getOpponent(turn));
				msg.addValue("defendertype", DEFENDER_PLAYER);
				moves.push_back(msg);
			}
			for (std::vector<Card*>::iterator j = battlezones[getOpponent(turn)].cards.begin(); j != battlezones[getOpponent(turn)].cards.end(); j++)
			{
				int canattack = getCreatureCanAttackCreature((*i)->UniqueId, (*j)->UniqueId);
				if (((*j)->isTapped == true || canattack == CANATTACK_UNTAPPED)
					&& canattack <= CANATTACK_UNTAPPED
					&& mCardList.at((*i)->UniqueId)->summoningSickness == 0
					&& mCardList.at((*i)->UniqueId)->isTapped == false)
				{
					Message msg("creatureattack");
					msg.addValue("attacker", (*i)->UniqueId);
					msg.addValue("defender", (*j)->UniqueId);
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
	currentMoveCount++;
	MoveHistory.push_back(msg);
	std::string type = msg.getType();
	printf("handling interface input: %s\n", msg.getType().c_str());
	if (type == "cardplay")
	{
		int whichCard = msg.getInt("card");
		int manacost = getCardCost(whichCard);
		if (manazones[turn].getUntappedMana() >= manacost && isThereUntappedManaOfCiv(turn, getCardCivilization(whichCard)) && getCardCanCast(whichCard)==1) //has appropriate mana
		{
			int eb = msg.getInt("evobait");
			int e = getIsEvolution(whichCard);
			if ((getCreatureCanEvolve(whichCard, eb) == 1 && e == 1) || e == 0) //can evolve if its an evolution
			{
				castingcard = whichCard;
				castingciv = getCardCivilization(castingcard);
				castingcost = getCardCost(castingcard);
				castingcivtapped = false;
				castingevobait = msg.getInt("evobait");
			}
			//MsgMngr.sendMessage(msg);
		}
	}
	else if (type == "cardmana")
	{
		if (manaUsed == 0)
		{
			MsgMngr.sendMessage(msg);
		}
	}
	else if (type == "endturn")
	{
		if (attackphase == PHASE_NONE && !isChoiceActive && castingcard == -1)
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
				((mCardList.at(attck)->summoningSickness == 0 || getIsSpeedAttacker(attck) == 1) && (canattack == CANATTACK_TAPPED || canattack == CANATTACK_UNTAPPED)))
				&& mCardList.at(attck)->isTapped == false)
			{
				Message msg2("cardtap");
				msg2.addValue("card", msg.getInt("attacker"));
				MsgMngr.sendMessage(msg2);
				MsgMngr.sendMessage(msg);
			}
		}
		else if (msg.getInt("defendertype") == DEFENDER_CREATURE)
		{
			int canattack = getCreatureCanAttackCreature(attck, defen);
			if ((mCardList.at(defen)->isTapped == true || canattack == CANATTACK_UNTAPPED)
				&& canattack <= CANATTACK_UNTAPPED
				&& mCardList.at(attck)->isTapped == false
				&& mCardList.at(attck)->summoningSickness == 0)
			{
				Message msg2("cardtap");
				msg2.addValue("card", msg.getInt("attacker"));
				MsgMngr.sendMessage(msg2);
				MsgMngr.sendMessage(msg);
			}
		}
	}
	else if (type == "creatureblock")
	{
		if (attackphase == PHASE_BLOCK)
		{
			int blocker = msg.getInt("blocker");
			if (getCreatureCanBlock(attacker, blocker) && mCardList.at(blocker)->isTapped == false
				&& (blocker != defender || defendertype == DEFENDER_PLAYER))
			{
				Message msg2("cardtap");
				msg2.addValue("card", blocker);
				MsgMngr.sendMessage(msg2);
				Message msg("creaturebattle");
				msg.addValue("attacker", attacker);
				msg.addValue("defender", blocker);
				MsgMngr.sendMessage(msg);
				//resetAttack();
				Message msg3("resetattack");
				MsgMngr.sendMessage(msg3);
			}
		}
	}
	else if (type == "blockskip")
	{
		if (attackphase == PHASE_BLOCK)
		{
			if (defendertype == DEFENDER_CREATURE)
			{
				Message m("creaturebattle");
				m.addValue("attacker", attacker);
				m.addValue("defender", defender);
				MsgMngr.sendMessage(m);
				//resetAttack();
				Message msg3("resetattack");
				MsgMngr.sendMessage(msg3);
			}
			else if (defendertype == DEFENDER_PLAYER)
			{
				//int def = msg.getInt("defender");
				if (shields[defender].cards.size() == 0)
				{
					winner = getOpponent(defender);
				}
				else
				{
					//attackphase = PHASE_TARGET;
					Message m("changeattackphase");
					m.addValue("phase", PHASE_TARGET);
					m.addValue("oldphase", attackphase);
					MsgMngr.sendMessage(m);
					breakcount = getCreatureBreaker(attacker);
				}
			}
		}
	}
	else if (type == "targetshield")
	{
		if (attackphase == PHASE_TARGET)
		{
			int shield = msg.getInt("shield");
			shieldtargets.push_back(shield);

			if (shieldtargets.size() >= breakcount || shields[mCardList.at(shield)->Owner].cards.size() <= 1)
			{
				Message m("changeattackphase");
				m.addValue("phase", PHASE_TRIGGER);
				m.addValue("oldphase", attackphase);
				MsgMngr.sendMessage(m);
			}

			Message m("creaturebreakshield");
			m.addValue("attacker", attacker);
			m.addValue("defender", defender);
			m.addValue("shield", shield);
			MsgMngr.sendMessage(m);
		}
	}
	else if (type == "triggeruse")
	{
		if (attackphase == PHASE_TRIGGER)
		{
			for (std::vector<int>::iterator j = shieldtargets.begin(); j != shieldtargets.end(); j++)
			{
				int trigger = msg.getInt("trigger");
				if (*j == trigger)
				{
					if (getIsShieldTrigger(trigger) && canUseShieldTrigger(trigger) && getCardCanCast(trigger))
					{
						Message m("cardplay");
						m.addValue("card", trigger);
						m.addValue("evobait", -1);
						MsgMngr.sendMessage(m);
					}
				}
			}
		}
	}
	else if (type == "triggerskip")
	{
		if (attackphase == PHASE_TRIGGER)
		{
			//resetAttack();
			Message msg3("resetattack");
			MsgMngr.sendMessage(msg3);
		}
	}
	else if (type == "manatap")
	{
		int card = msg.getInt("card");
		if (mCardList.at(card)->isTapped == false && castingcard != -1)
		{
			if (castingcost == 1) //last card to be tapped
			{
				if (getCardCivilization(card) == castingciv || castingcivtapped)
				{
					Message msg2("cardtap");
					msg2.addValue("card", card);
					MsgMngr.sendMessage(msg2);
					castingcost--;
					castingcivtapped = true;

					Message msg3("cardplay");
					msg3.addValue("card", castingcard);
					msg3.addValue("evobait", castingevobait);
					MsgMngr.sendMessage(msg3);

					resetCasting();
				}
			}
			else
			{
				Message msg2("cardtap");
				msg2.addValue("card", card);
				MsgMngr.sendMessage(msg2);
				castingcost--;
				if (getCardCivilization(card) == castingciv)
				{
					castingcivtapped = true;
				}
			}
		}
	}
	else if (type == "choiceselect")
	{
		int sid = msg.getInt("selection");
		if (sid < 0 || choiceCanBeSelected(sid) == 1)
		{
			int chcard = choiceCard;
			resetChoice();
			Choice* c = choice;
			c->callaction(chcard, sid);
			if (c != NULL)
			{
				if (choice == c)
					choice = NULL;
				delete c;
				c = NULL;
			}
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

void Duel::parseMessages(unsigned int deltatime)
{
	if (!isChoiceActive)
	{
		bool worldchanged = dispatchAllMessages();
		if (worldchanged)
		{
			for (std::vector<Card*>::iterator i = mCardList.begin(); i != mCardList.end(); i++)
			{
				if ((*i)->Zone == ZONE_BATTLE)
				{
					(*i)->updatePower(getCreaturePower((*i)->UniqueId));
				}
			}
		}
	}
}

bool Duel::dispatchAllMessages()
{
	bool worldchanged = false;
	while (MsgMngr.hasMoreMessages())
	{
		Message msg = MsgMngr.peekMessage();
		MsgMngr.dispatch();
		if (!isSimulation)
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

	currentMessage = msg;

	currentMessage.addValue("msgtype", "mod " + type);
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(msg);
	}

	//std::cout << "  mod\n";
	if (currentMessage.getInt("msgContinue") == 0) //do we continue?
		return;

	currentMessage.addValue("msgtype", "pre " + type);
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(msg);
	}

	//std::cout << "  pre\n";
	if (currentMessage.getInt("msgContinue") == 0)
		return;

	currentMessage.addValue("msgtype", type);
	handleMessage(currentMessage);
	//std::cout << "  in\n";

	currentMessage.addValue("msgtype", "post " + type);
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
	choice = new Choice(info, skip, validref, actionref);
	choiceCard = card;
	choicePlayer = player;
	isChoiceActive = true;
	//cout << "choice set: " << CardList.at(choiceCard)->Name << ": " << info << endl;
}

int Duel::choiceCanBeSelected(int sid)
{
	return choice->callvalid(choiceCard, sid);
}

void Duel::checkChoiceValid()
{
	int count = 0;
	for (std::vector<Card*>::iterator i = mCardList.begin(); i != mCardList.end(); i++)
	{
		if (choiceCanBeSelected((*i)->UniqueId) == 1)
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
	int p1 = getCreaturePower(a->UniqueId);
	int p2 = getCreaturePower(d->UniqueId);
	if (p1 >= p2)
	{
		Message msg("creaturedestroy");
		msg.addValue("creature", def);
		msg.addValue("zoneto", ZONE_GRAVEYARD);
		MsgMngr.sendMessage(msg);
	}
	if (p2 >= p1)
	{
		Message msg("creaturedestroy");
		msg.addValue("creature", att);
		msg.addValue("zoneto", ZONE_GRAVEYARD);
		MsgMngr.sendMessage(msg);
	}
}

int Duel::getCreaturePower(int uid)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get creaturepower");
	currentMessage.addValue("power", mCardList.at(uid)->Power);
	currentMessage.addValue("creature", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("power");
	currentMessage = oldmsg;
	return c;
}

int Duel::getCreatureBreaker(int uid)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get creaturebreaker");
	currentMessage.addValue("breaker", mCardList.at(uid)->Breaker);
	currentMessage.addValue("creature", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("breaker");
	currentMessage = oldmsg;
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
	Message oldmsg = currentMessage;
	currentMessage = Message("get creatureisblocker");
	currentMessage.addValue("isblocker", mCardList.at(uid)->isBlocker);
	currentMessage.addValue("creature", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("isblocker");
	currentMessage = oldmsg;
	return c;
}

int Duel::getCreatureCanBlock(int attckr,int blckr)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get creaturecanblock");
	currentMessage.addValue("canblock", getCreatureIsBlocker(blckr));
	currentMessage.addValue("blocker", blckr);
	currentMessage.addValue("attacker", attckr);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("canblock");
	currentMessage = oldmsg;
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
	Message oldmsg = currentMessage;
	currentMessage = Message("get creaturecanattackplayers");
	currentMessage.addValue("canattack", CANATTACK_TAPPED);
	currentMessage.addValue("attacker", uid);

	int big = CANATTACK_TAPPED;

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
		if (currentMessage.getInt("canattack") > big)
		{
			big = currentMessage.getInt("canattack");
		}
		else
		{
			currentMessage.addValue("canattack", big);
		}
	}
	int c = currentMessage.getInt("canattack");
	currentMessage = oldmsg;
	return c;
}

int Duel::getCreatureCanAttackCreature(int attckr, int dfndr)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get creaturecanattackcreature");
	currentMessage.addValue("canattack", CANATTACK_TAPPED);
	currentMessage.addValue("attacker", attckr);
	currentMessage.addValue("defender", dfndr);

	int big = CANATTACK_TAPPED;

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
		if (currentMessage.getInt("canattack") > big)
		{
			big = currentMessage.getInt("canattack");
		}
		else
		{
			currentMessage.addValue("canattack", big);
		}
	}
	int c = currentMessage.getInt("canattack");
	currentMessage = oldmsg;
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
	Message oldmsg = currentMessage;
	currentMessage = Message("get cardcost");
	currentMessage.addValue("cost", mCardList.at(uid)->ManaCost);
	currentMessage.addValue("card", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("cost");
	currentMessage = oldmsg;
	return c;
}

int Duel::getIsShieldTrigger(int uid)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get cardshieldtrigger");
	currentMessage.addValue("shieldtrigger", mCardList.at(uid)->isShieldTrigger);
	currentMessage.addValue("card", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("shieldtrigger");
	currentMessage = oldmsg;
	return c;
}

int Duel::canUseShieldTrigger(int uid)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get canuseshieldtrigger");
	currentMessage.addValue("canuse", 1);
	currentMessage.addValue("card", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("canuse");
	currentMessage = oldmsg;
	return c;
}

int Duel::getIsEvolution(int uid)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get creatureisevolution");
	currentMessage.addValue("isevolution", 0);
	currentMessage.addValue("creature", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("isevolution");
	currentMessage = oldmsg;
	return c;
}

int Duel::getIsSpeedAttacker(int uid)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get creatureisspeedattacker");
	currentMessage.addValue("isspeedattacker", 0);
	currentMessage.addValue("creature", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("isspeedattacker");
	currentMessage = oldmsg;
	return c;
}

int Duel::getCardCanCast(int uid)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get cardcancast");
	currentMessage.addValue("cancast", 1);
	currentMessage.addValue("card", uid);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("cancast");
	currentMessage = oldmsg;
	return c;
}

int Duel::getCardCivilization(int uid)
{
	return mCardList.at(uid)->Civilization;
}

int Duel::isCreatureOfRace(int uid, std::string race)
{
	std::string r = getCreatureRace(uid);
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
	return mCardList.at(uid)->Race;
}

int Duel::getCreatureCanEvolve(int evo, int bait)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get creaturecanevolve");
	currentMessage.addValue("canevolve", 0);
	currentMessage.addValue("evolution", evo);
	currentMessage.addValue("evobait", bait);

	std::vector<Card*>::iterator i;
	for (i = mCardList.begin(); i != mCardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("canevolve");
	currentMessage = oldmsg;
	return c;
}

bool Duel::isThereUntappedManaOfCiv(int player,int civ)
{
	for (std::vector<Card*>::iterator i = manazones[player].cards.begin(); i != manazones[player].cards.end(); i++)
	{
		if ((*i)->isTapped == false && getCardCivilization((*i)->UniqueId) == civ)
			return true;
	}
	return false;
}

void Duel::drawCards(int player, int count)
{
	count = count < decks[player].cards.size() ? count : decks[player].cards.size();
	for (int i = 0; i < count; i++)
	{
		Message msg("cardmove");
		msg.addValue("card", decks[player].cards.at(decks[player].cards.size() - i - 1)->UniqueId);
		msg.addValue("from", decks[player].cards.at(decks[player].cards.size() - i - 1)->Zone);
		msg.addValue("to", ZONE_HAND);
		MsgMngr.sendMessage(msg);
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
	decks[p].cards.empty();
	std::fstream file;
	file.open(s, std::ios::in | std::ios::out);
	std::string str;

	if (!file.is_open())
	{
		//cout << "ERROR opening deck: " << s << endl;
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
					//printf("added %s\n", name.c_str());
					Card* c = new Card(nextUniqueId, getCardIdFromName(name), p);
					mCardList.push_back(c);
					decks[p].addCard(c);
					nextUniqueId++;
				}
				break;
			}
		}
	}

	file.close();

	decknames[p] = s;
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
	turn = 0;
	manaUsed = 0;
	for (int i = 0; i < 2; i++)
	{
		if (decks[i].cards.size() < 40)
		{
			printf("WARNING: Deck card count less than 40\n");
		}
		decks[i].shuffle();
		for (int j = 0; j < 5; j++)
		{
			/*Card* c = decks[i].draw();
			shields[i].addCard(c);*/
			Message msg("cardmove");
			msg.addValue("card", decks[i].cards.at(decks[i].cards.size() - 1 - j)->UniqueId);
			msg.addValue("from", ZONE_DECK);
			msg.addValue("to", ZONE_SHIELD);
			MsgMngr.sendMessage(msg);
		}
		for (int j = 0; j < 5; j++)
		{
			/*Card* c = decks[i].draw();
			hands[i].addCard(c);*/
			Message msg("cardmove");
			msg.addValue("card", decks[i].cards.at(decks[i].cards.size() - 6 - j)->UniqueId);
			msg.addValue("from", ZONE_DECK);
			msg.addValue("to", ZONE_HAND);
			MsgMngr.sendMessage(msg);
		}
	}
}

void Duel::nextTurn()
{
	Message msg("endturn");
	msg.addValue("player", turn);
	MsgMngr.sendMessage(msg);
}

void Duel::resetAttack()
{
	//cout << "attackreset" << endl;
	attackphase = PHASE_NONE;
	attacker = -1;
	defender = -1;
	breakcount = -1;
	shieldtargets.clear();
}

void Duel::resetCasting()
{
	//cout << "casting reset" << endl;
	castingcard = -1;
	castingciv = -1;
	castingcivtapped = false;
	castingcost = -1;
	castingevobait = -1;
}

void Duel::clearCards()
{
	for (int i = 0; i < 2; i++)
	{
		decks[i].cards.clear();
		graveyards[i].cards.clear();
		hands[i].cards.clear();
		manazones[i].cards.clear();
		shields[i].cards.clear();
		battlezones[i].cards.clear();

		shields[i].slotsUsed = 0;
	}
	mCardList.clear();
	nextUniqueId = 0;
}

void Duel::resetChoice()
{
	choiceCard = -1;
	choicePlayer = -1;
	isChoiceActive = false;
	//cout << "choice reset" << endl;
}

Zone* Duel::getZone(int player, int zone)
{
	if (zone == ZONE_BATTLE)
	{
		return &battlezones[player];
	}
	else if (zone == ZONE_MANA)
	{
		return &manazones[player];
	}
	else if (zone == ZONE_HAND)
	{
		return &hands[player];
	}
	else if (zone == ZONE_DECK)
	{
		return &decks[player];
	}
	else if (zone == ZONE_SHIELD)
	{
		return &shields[player];
	}
	else if (zone == ZONE_GRAVEYARD)
	{
		return &graveyards[player];
	}
	else if (zone == ZONE_EVOLVED)
	{
		return &battlezones[player];
	}
	return NULL;
}

void Duel::flipCardForPlayer(int cid, int p)
{
	//CardList.at(cid)->flipForPlayer(p);
}

void Duel::unflipCardForPlayer(int cid, int p)
{
	//CardList.at(cid)->unflipForPlayer(p);
}

void Duel::destroyCard(Card* c)
{
	//moveCard(c, ZONE_GRAVEYARD);
}

int getOpponent(int turn)
{
	return (turn + 1) % 2;
}