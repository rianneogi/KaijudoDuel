#include "DuelInterface.h"

float gZoomDistance = 25.f;
const float gCameraSpeed = 0.0001f;

DuelInterface::DuelInterface()
{
	printf("WARNING: Duel interface init through default constructor\n");
}

DuelInterface::DuelInterface(Duel* duel)
{
	mDuel = duel;

	for (size_t i = 0; i < mDuel->mCardList.size(); i++)
	{
		assert(i == mDuel->mCardList[i]->UniqueId);
		mCardModels.push_back(new CardModel(i, mDuel->mCardList[i]->CardId));
	}

	int Factor[2] = { -1, 1 };
	int Factor2[2] = { 1,0 };

	for (int i = 0; i < 2; i++)
	{
		mDeckRenderers[i] = new DeckRenderer();
		mGraveyardRenderers[i] = new GraveyardRenderer();
		mHandRenderers[i] = new HandRenderer(i);
		mManaZoneRenderers[i] = new ManaZoneRenderer();
		mShieldZoneRenderers[i] = new ShieldZoneRenderer();
		mBattleZoneRenderers[i] = new BattleZoneRenderer();


		mDeckRenderers[i]->mPos = glm::vec3(-2 * CONST_CARDSEPERATION, CONST_CARDELEVATION, Factor[i] * (1 * CONST_CARDSEPERATION + Factor2[i] * CONST_CARDSEPERATION));
		mGraveyardRenderers[i]->mPos = glm::vec3(-2 * CONST_CARDSEPERATION, CONST_CARDELEVATION, Factor[i] * (2 * CONST_CARDSEPERATION + Factor2[i] * CONST_CARDSEPERATION));
		mHandRenderers[i]->mPos = glm::vec3(-2 * CONST_CARDSEPERATION, CONST_CARDELEVATION, Factor[i] * (3 * CONST_CARDSEPERATION + Factor2[i] * CONST_CARDSEPERATION));
		mManaZoneRenderers[i]->mPos = glm::vec3(-2 * CONST_CARDSEPERATION, CONST_CARDELEVATION, Factor[i] * (2 * CONST_CARDSEPERATION + Factor2[i] * CONST_CARDSEPERATION));
		mShieldZoneRenderers[i]->mPos = glm::vec3(-2 * CONST_CARDSEPERATION, CONST_CARDELEVATION, Factor[i] * (1 * CONST_CARDSEPERATION + Factor2[i] * CONST_CARDSEPERATION));
		mBattleZoneRenderers[i]->mPos = glm::vec3(-2 * CONST_CARDSEPERATION, CONST_CARDELEVATION, Factor[i] * (0 * CONST_CARDSEPERATION + Factor2[i] * CONST_CARDSEPERATION));

		mDeckRenderers[i]->mHeight = CONST_CARDSEPERATION;
		mGraveyardRenderers[i]->mHeight = CONST_CARDSEPERATION;
		mHandRenderers[i]->mHeight = CONST_CARDSEPERATION;
		mManaZoneRenderers[i]->mHeight = CONST_CARDSEPERATION;
		mShieldZoneRenderers[i]->mHeight = CONST_CARDSEPERATION;
		mBattleZoneRenderers[i]->mHeight = CONST_CARDSEPERATION;

		mDeckRenderers[i]->mWidth = CONST_CARDSEPERATION;
		mGraveyardRenderers[i]->mWidth = CONST_CARDSEPERATION;
		mHandRenderers[i]->mWidth = CONST_CARDSEPERATION;
		mManaZoneRenderers[i]->mWidth = CONST_CARDSEPERATION * 5;
		mShieldZoneRenderers[i]->mWidth = CONST_CARDSEPERATION * 5;
		mBattleZoneRenderers[i]->mWidth = CONST_CARDSEPERATION * 5;
	}

	duelstate = DUELSTATE_MENU;
	dueltype = DUELTYPE_SINGLE;

	mHoverCardId = -1;
	mSelectedCardId = -1;

	setMyPlayer(0);

	mCamera.setPosition(glm::vec3(0, 0, 0));
	mCamera.setHorizontalAngle(0);
	mCamera.setVerticalAngle(-M_PI / 2);
	mCamera.update();
	mCamera.mPosition = -mCamera.mDirection * gZoomDistance;
	mCamera.update();

	mTableModel.setMesh(&gMeshs[MESH_TABLE]);
	mTableModel.setTexture(&gTableTexture);
	mTableModel.setPosition(glm::vec3(0, 0, 0));
	mTableModel.mModelMatrix = glm::scale(mTableModel.mModelMatrix, glm::vec3(5, 5, 5));

	mEndTurnModel.setMesh(&gMeshs[MESH_ENDTURN]);
	mEndTurnModel.setTexture(&gTableTexture);
	mEndTurnModel.mModelMatrix = glm::scale(mTableModel.mModelMatrix, glm::vec3(0.25f, 0.25f, 0.25f));
	mEndTurnModel.setPosition(glm::vec3(-8.f, 1.0, 0.0));
	mEndTurnModel.setModelMatrix(glm::rotate(mEndTurnModel.mModelMatrix, float(M_PI), glm::vec3(0, 1, 0)));

	mHandRenderers[0]->setCamera(&mCamera);
	mHandRenderers[1]->setCamera(&mCamera);
}

DuelInterface::~DuelInterface()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			delete getZoneRenderer(i, j);
		}
	}

	for (size_t i = 0; i < mCardModels.size(); i++)
	{
		delete mCardModels[i];
	}
}

void DuelInterface::render()
{
	glm::mat4 view, projection;
	mCamera.render(view, projection);

	Vector2i mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);

	gActiveShader = SHADER_BASIC;
	gShaders[gActiveShader].bind();
	gShaders[gActiveShader].setUniformMat4f(0, mTableModel.mModelMatrix);
	gShaders[gActiveShader].setUniformMat4f(1, view);
	gShaders[gActiveShader].setUniformMat4f(2, projection);
	mTableModel.render();
	gShaders[gActiveShader].setUniformMat4f(0, mEndTurnModel.mModelMatrix);
	mEndTurnModel.render();

	//render cards
	for (size_t i = 0; i < mCardModels.size(); i++)
	{
		mCardModels[i]->render(true);
	}

	/*for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			getZoneRenderer(i,j)->renderCards(myPlayer);
		}
	}*/
}

int DuelInterface::handleEvent(const SDL_Event& event, int callback)
{
	Vector2i mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (mSelectedCardId == -1)
			{
				if (mHoverCardId != -1)
				{
					if (mDuel->mCardList[mHoverCardId]->Zone == ZONE_HAND || mDuel->mCardList[mHoverCardId]->Zone == ZONE_BATTLE) //select card
					{
						assert(mHoverCardId < mDuel->mCardList.size());
						mSelectedCardId = mHoverCardId;
						//mDuel.CardList[mHoverCardId]->move(target, 0);
					}
					else if (mDuel->mCardList[mHoverCardId]->Zone == ZONE_MANA) //tap mana
					{
						Message msg("manatap");
						msg.addValue("card", mHoverCardId);
						mDuel->handleInterfaceInput(msg);
					}
				}

				glm::mat4 view, proj, projview;
				mCamera.render(view, proj);
				projview = proj*view;
				Vector2i screendim(SCREEN_WIDTH, SCREEN_HEIGHT);
				if (mEndTurnModel.rayTrace(mousePos, projview, screendim)) //end turn
				{
					Message msg("endturn");
					mDuel->handleInterfaceInput(msg);
					printf("end turn pressed\n");
				}
			}
			else
			{
				if (mDuel->mCardList[mSelectedCardId]->Zone == ZONE_HAND)
				{
					glm::mat4 view, proj, projview;
					mCamera.render(view, proj);
					projview = proj*view;
					Vector2i screendim(SCREEN_WIDTH, SCREEN_HEIGHT);
					if (mBattleZoneRenderers[mDuel->turn]->rayTrace(mousePos, projview, screendim)) //play card
					{
						Message msg("cardplay");
						msg.addValue("card", mSelectedCardId);
						msg.addValue("evobait", -1);
						mDuel->handleInterfaceInput(msg);
					}
					else if (mManaZoneRenderers[mDuel->turn]->rayTrace(mousePos, projview, screendim)) //put card in mana
					{
						Message msg("cardmana");
						msg.addValue("card", mSelectedCardId);
						mDuel->handleInterfaceInput(msg);
					}
					mSelectedCardId = -1;
				}
				else if (mDuel->mCardList[mSelectedCardId]->Zone == ZONE_BATTLE) 
				{
					glm::mat4 view, proj, projview;
					mCamera.render(view, proj);
					projview = proj*view;
					Vector2i screendim(SCREEN_WIDTH, SCREEN_HEIGHT);

					int has_attacked = 0;
					for (size_t i = 0; i < mDuel->battlezones[!mDuel->turn].cards.size(); i++) //attack creatures
					{
						if (mCardModels[mDuel->battlezones[!mDuel->turn].cards[i]->UniqueId]->rayTrace(mousePos, projview, screendim))
						{
							Message msg("creatureattack");
							msg.addValue("attacker", mSelectedCardId);
							msg.addValue("defender", mDuel->battlezones[!mDuel->turn].cards[i]->UniqueId);
							msg.addValue("defendertype", DEFENDER_CREATURE);
							mDuel->handleInterfaceInput(msg);
							has_attacked = 1;
							mSelectedCardId = -1;
						}
					}

					if (!has_attacked) //attack shields
					{
						for (size_t i = 0; i < mDuel->shields[!mDuel->turn].cards.size(); i++)
						{
							if (mCardModels[mDuel->shields[!mDuel->turn].cards[i]->UniqueId]->rayTrace(mousePos, projview, screendim))
							{
								Message msg("creatureattack");
								msg.addValue("attacker", mSelectedCardId);
								msg.addValue("defender", mDuel->shields[!mDuel->turn].cards[i]->UniqueId);
								msg.addValue("defendertype", DEFENDER_PLAYER);
								mDuel->handleInterfaceInput(msg);
								mSelectedCardId = -1;
							}
						}
					}
				}
			}
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
		{
			mSelectedCardId = -1;
		}
	}

	return 0;
}

//int DuelInterface::receivePacket(sf::Packet& packet, int callback)
//{
//	if (dueltype == DUELTYPE_MULTI)
//	{
//		sf::Uint32 ptype;
//		packet >> ptype;
//		if (ptype == PACKET_MSG)
//		{
//			Message msg;
//			packet >> msg;
//			cout << "received msg packet : " << msg.getType() << endl;
//			duel.handleInterfaceInput(msg);
//		}
//		else if (ptype == PACKET_SETDECK)
//		{
//			cout << "setdeck packet recieved" << endl;
//			sf::Uint32 size;
//			packet >> size;
//			cout << "size: " << endl;
//			duel.decks[deckschosen].cards.empty();
//			for (int i = 0; i < size; i++)
//			{
//				sf::Uint32 cid;
//				packet >> cid;
//				Card* c = new Card(duel.nextUniqueId, cid, deckschosen);
//				duel.CardList.push_back(c);
//				duel.decks[deckschosen].addCard(c);
//				duel.nextUniqueId++;
//				cout << "added card: " << cid << endl;
//			}
//			deckschosen++;
//			if (deckschosen >= 2)
//			{
//				duelstate = DUELSTATE_DUEL;
//				duel.startDuel();
//			}
//		}
//		else if (ptype == PACKET_SETSEED)
//		{
//			sf::Uint32 x;
//			packet >> x;
//			//std::srand(x);
//			duel.RandomGen.SetRandomSeed(x);
//			cout << "set seed packet received : " << x << endl;
//		}
//		else if (ptype == PACKET_CHOICESELECT)
//		{
//			sf::Uint32 x;
//			packet >> x;
//			duel.resetChoice();
//			cout << "choice select packet received : " << x << endl;
//			return x;
//		}
//		else if (ptype == PACKET_ADDARROW)
//		{
//			arrows.push_back(Arrow());
//			sf::Uint32 fx, fy, tx, ty;
//			packet >> fx >> fy >> tx >> ty;
//			arrows.at(arrows.size() - 1).setColor(ATTACKARROWCOLOR);
//			arrows.at(arrows.size() - 1).setFrom(fx,fy);
//			arrows.at(arrows.size() - 1).setTo(tx, ty);
//			cout << "add arrow packet received" << endl;
//		}
//		else if (ptype == PACKET_CLEARARROWS)
//		{
//			arrows.clear();
//			cout << "clear arrows packet received" << endl;
//			mousearrow = -1;
//		}
//	}
//	return RETURN_NOTHING;
//}

//void DuelInterface::parseMessages(unsigned int deltatime)
//{
//	mDuel->parseMessages(deltatime);
//}

void DuelInterface::update(int deltaTime)
{
	mDuel->dispatchAllMessages();

	for (int i = 0; i < 2; i++)
		mHandRenderers[i]->mTurn = mDuel->turn;

	int newhovercard = -1;
	Vector2i mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	if (mousePos.x >= 0 && mousePos.y >= 0)
	{
		glm::mat4 view, proj, projview;
		mCamera.render(view, proj);
		projview = proj*view;
		Vector2i screendim(SCREEN_WIDTH, SCREEN_HEIGHT);
		//float minDepth = 1;
		for (int i = mDuel->hands[mDuel->turn].cards.size() - 1;i >= 0;i--)
		{
			if (mCardModels[mDuel->hands[mDuel->turn].cards[i]->UniqueId]->rayTrace(mousePos, projview, screendim))
			{
				if (newhovercard != mDuel->hands[mDuel->turn].cards[i]->UniqueId)
				{
					newhovercard = mDuel->hands[mDuel->turn].cards[i]->UniqueId;
				}
				break;
			}
		}
		for (int i = 0; i < mCardModels.size(); i++)
		{
			if (mDuel->mCardList[i]->Zone == ZONE_BATTLE || mDuel->mCardList[i]->Zone == ZONE_MANA
				|| mDuel->mCardList[i]->Zone == ZONE_HAND)
			{
				if (mCardModels[i]->rayTrace(mousePos, projview, screendim))
				{
					newhovercard = i;
				}
			}
		}
		if (mSelectedCardId != -1 && mDuel->mCardList[mSelectedCardId]->Zone == ZONE_HAND)
		{
			assert(mSelectedCardId < mDuel->mCardList.size());

			Vector2f mousepixel;
			mousepixel.x = -(mousePos.x / (SCREEN_WIDTH / 2.f) - 1.f);
			mousepixel.y = -(mousePos.y / (SCREEN_HEIGHT / 2.f) - 1.f);

			Orientation o;
			o.pos = glm::vec3(8*mousepixel.x, (mCamera.mPosition + mCamera.mDirection*gHandStraightDistance).y, 8*mousepixel.y);
			o.dir = mCamera.mUp;
			o.up = -mCamera.mDirection;
			mCardModels[mSelectedCardId]->setOrientation(o);
		}
	}

	//Set hover card
	if (newhovercard != mHoverCardId && mSelectedCardId == -1)
	{
		mHoverCardId = newhovercard;
		printf("Hover: %d\n", mHoverCardId);
		//mHandRenderers[mDuel->turn]->mHoverCard = mHoverCardId;
		//mHandRenderers[0].update(mHoverCardId); //update hand
	}

	//Card Movement
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (size_t k = 0; k < mDuel->getZone(i, j)->cards.size(); k++)
			{
				Card* c = mDuel->getZone(i, j)->cards[k];
				if(c->UniqueId != mSelectedCardId)
					getZoneRenderer(i, j)->updateCard(mCardModels[c->UniqueId], k, mDuel->getZone(i, j)->cards.size(), 
						mHoverCardId, c->isTapped, c->isFlipped);
			}
		}
	}

	for (int i = 0;i < mCardModels.size();i++) //update cards
	{
		mCardModels[i]->update(deltaTime);
	}
}

void DuelInterface::undoSelection()
{
	selectedcard = -1;
	selectedcardzone = -1;
	iscardevo = -1;
	/*arrows.clear();
	mousearrow = -1;
	if (dueltype == DUELTYPE_MULTI)
	{
		sf::Packet p;
		sf::Uint32 ptype = PACKET_CLEARARROWS;
		p << ptype;
		Socket.send(p);
		cout << "clear arrows packet sent" << endl;
	}*/
}

ZoneRenderer* DuelInterface::getZoneRenderer(int player, int zone)
{
	if (zone == ZONE_BATTLE)
	{
		return mBattleZoneRenderers[player];
	}
	else if (zone == ZONE_MANA)
	{
		return mManaZoneRenderers[player];
	}
	else if (zone == ZONE_HAND)
	{
		return mHandRenderers[player];
	}
	else if (zone == ZONE_DECK)
	{
		return mDeckRenderers[player];
	}
	else if (zone == ZONE_SHIELD)
	{
		return mShieldZoneRenderers[player];
	}
	else if (zone == ZONE_GRAVEYARD)
	{
		return mGraveyardRenderers[player];
	}
	else if (zone == ZONE_EVOLVED)
	{
		return mBattleZoneRenderers[player];
	}
	printf("WARNING: getZoneRenderer called with unknown zone type: %d\n", zone);
	return NULL;
}

void DuelInterface::setDecklist()
{
	/*decklist.items.clear();
	fstream deckfile;
	deckfile.open("Decks\\My Decks\\decklist.txt", ios::out | ios::in);
	if (!deckfile.is_open())
	{
		cout << "ERROR cant open deckfile, please restart" << endl;
	}
	string s;
	while (!deckfile.eof())
	{
		getline(deckfile, s);
		decklist.items.push_back(s);
	}
	deckfile.close();*/
}

void DuelInterface::setMyPlayer(int p)
{
	myPlayer = p;
	mDuel->hands[0].mMyPlayer = p;
	mDuel->hands[1].mMyPlayer = p;
	//duel.hands[0].flipAllCards();
	//duel.hands[1].flipAllCards();
}

