#include "DuelInterface.h"

float gZoomDistance = 25.f;
const float gCameraSpeed = 0.0001f;
const int HOVER_CARD_TIME = 500;

DuelInterface::DuelInterface()
{
	printf("WARNING: Duel interface init through default constructor\n");
}

DuelInterface::DuelInterface(Duel* duel)
{
	mDuel = duel;

	for (size_t i = 0; i < mDuel->mCardList.size(); i++)
	{
		assert(i == mDuel->mCardList[i]->mUniqueId);
		mCardModels.push_back(new CardModel(i, mDuel->mCardList[i]->mCardId));
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

		mDeckRenderers[i]->mPos = glm::vec3(-3 * CONST_CARDSEPERATION_HORI, CONST_CARDELEVATION, Factor[i] * (1 * CONST_CARDSEPERATION_VERT + Factor2[i] * CONST_CARDSEPERATION_VERT));
		mGraveyardRenderers[i]->mPos = glm::vec3(-4 * CONST_CARDSEPERATION_HORI, CONST_CARDELEVATION, Factor[i] * (1 * CONST_CARDSEPERATION_VERT + Factor2[i] * CONST_CARDSEPERATION_VERT));
		mHandRenderers[i]->mPos = glm::vec3(-2 * CONST_CARDSEPERATION_HORI, CONST_CARDELEVATION, Factor[i] * (3 * CONST_CARDSEPERATION_VERT + Factor2[i] * CONST_CARDSEPERATION_VERT));
		mManaZoneRenderers[i]->mPos = glm::vec3(-2 * CONST_CARDSEPERATION_HORI, CONST_CARDELEVATION, Factor[i] * (2 * CONST_CARDSEPERATION_VERT + Factor2[i] * CONST_CARDSEPERATION_VERT));
		mShieldZoneRenderers[i]->mPos = glm::vec3(-2 * CONST_CARDSEPERATION_HORI, CONST_CARDELEVATION, Factor[i] * (1 * CONST_CARDSEPERATION_VERT + Factor2[i] * CONST_CARDSEPERATION_VERT));
		mBattleZoneRenderers[i]->mPos = glm::vec3(-2 * CONST_CARDSEPERATION_HORI, CONST_CARDELEVATION, Factor[i] * (0 * CONST_CARDSEPERATION_VERT + Factor2[i] * CONST_CARDSEPERATION_VERT));

		mDeckRenderers[i]->mHeight = CONST_CARDSEPERATION_VERT;
		mGraveyardRenderers[i]->mHeight = CONST_CARDSEPERATION_VERT;
		mHandRenderers[i]->mHeight = CONST_CARDSEPERATION_VERT;
		mManaZoneRenderers[i]->mHeight = CONST_CARDSEPERATION_VERT;
		mShieldZoneRenderers[i]->mHeight = CONST_CARDSEPERATION_VERT;
		mBattleZoneRenderers[i]->mHeight = CONST_CARDSEPERATION_VERT;

		mDeckRenderers[i]->mWidth = CONST_CARDSEPERATION_HORI;
		mGraveyardRenderers[i]->mWidth = CONST_CARDSEPERATION_HORI;
		mHandRenderers[i]->mWidth = CONST_CARDSEPERATION_HORI;
		mManaZoneRenderers[i]->mWidth = CONST_CARDSEPERATION_HORI * 5;
		mShieldZoneRenderers[i]->mWidth = CONST_CARDSEPERATION_HORI * 5;
		mBattleZoneRenderers[i]->mWidth = CONST_CARDSEPERATION_HORI * 5;
	}

	duelstate = DUELSTATE_MENU;
	dueltype = DUELTYPE_SINGLE;

	mHoverCardId = -1;
	mSelectedCardId = -1;
	mHoverException = -1;
	mHighlightCardId = -1;

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
	mTableModel.mModelMatrix = glm::scale(mTableModel.mModelMatrix, glm::vec3(8, 8, 8));

	mEndTurnModel.setMesh(&gMeshs[MESH_ENDTURN]);
	mEndTurnModel.setTexture(&gTableTexture);
	mEndTurnModel.mModelMatrix = glm::scale(mTableModel.mModelMatrix, glm::vec3(0.25f, 0.25f, 0.25f));
	mEndTurnModel.setPosition(glm::vec3(-8.f, 1.0, 0.0));
	mEndTurnModel.setModelMatrix(glm::rotate(mEndTurnModel.mModelMatrix, float(M_PI), glm::vec3(0, 1, 0)));

	mButton2Model.setMesh(&gMeshs[MESH_ENDTURN]);
	mButton2Model.setTexture(&gTableTexture);
	mButton2Model.mModelMatrix = glm::scale(mTableModel.mModelMatrix, glm::vec3(0.25f, 0.25f, 0.25f));
	mButton2Model.setPosition(glm::vec3(-8.f, 1.0, -3.0));
	mButton2Model.setModelMatrix(glm::rotate(mButton2Model.mModelMatrix, float(M_PI), glm::vec3(0, 1, 0)));

	mHandRenderers[0]->setCamera(&mCamera);
	mHandRenderers[1]->setCamera(&mCamera);

	mTextRenderer.load("Resources/OxygenMono.ttf", glm::vec4(1, 1, 1, 1), 18);
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
	//glDisable(GL_CULL_FACE);
	//Vector2i mousePos;
	//SDL_GetMouseState(&mousePos.x, &mousePos.y);

	gActiveShader = SHADER_PHONG;
	gShaders[gActiveShader].bind();
	gShaders[gActiveShader].setUniformMat4f(0, mTableModel.mModelMatrix);
	gShaders[gActiveShader].setUniformMat4f(1, view);
	gShaders[gActiveShader].setUniformMat4f(2, projection);
	gShaders[gActiveShader].setUniformVec3f(3, mCamera.mPosition);
	//gShaders[gActiveShader].setUniformInt(4, 1);
	gShaders[gActiveShader].setUniformVec4f(4, glm::vec4(mCamera.mPosition, 1.0));
	gShaders[gActiveShader].setUniformVec3f(5, glm::vec3(1,1,1));
	gShaders[gActiveShader].setUniformInt(6, 75);
	mTableModel.render();
	gShaders[gActiveShader].setUniformMat4f(0, mEndTurnModel.mModelMatrix);
	mEndTurnModel.render();
	gShaders[gActiveShader].setUniformMat4f(0, mButton2Model.mModelMatrix);
	mButton2Model.render();

	//render cards
	for (size_t i = 0; i < mCardModels.size(); i++)
	{
		mCardModels[i]->render(true);
	}

	mTextRenderer.renderTextMVP("End Turn", 0.0, 0.0, 20.0 / SCREEN_WIDTH, 20.0 / SCREEN_HEIGHT, mEndTurnModel.mModelMatrix, view, projection);

	if (mDuel->mIsChoiceActive)
	{
		assert(mDuel->mChoice != NULL);
		mTextRenderer.renderText(mDuel->mCardList[mDuel->mChoiceCard]->mName + ": " + mDuel->mChoice->mInfotext, 0.5, 0.5, 2.0 / SCREEN_WIDTH, 2.0 / SCREEN_HEIGHT);
	}
	else if (mDuel->mAttackphase == PHASE_BLOCK)
	{
		mTextRenderer.renderText("Choose Blockers...", 0.5, 0.5, 2.0 / SCREEN_WIDTH, 2.0 / SCREEN_HEIGHT);
	}
	else if (mDuel->mAttackphase == PHASE_TARGET)
	{
		mTextRenderer.renderText("Choose Targets...", 0.5, 0.5, 2.0 / SCREEN_WIDTH, 2.0 / SCREEN_HEIGHT);
	}
	else if (mDuel->mAttackphase == PHASE_TRIGGER)
	{
		mTextRenderer.renderText("Choose Shield Triggers...", 0.5, 0.5, 2.0 / SCREEN_WIDTH, 2.0 / SCREEN_HEIGHT);
	}
	else if (mDuel->mCastingCard != -1)
	{
		mTextRenderer.renderText("Tap "+std::to_string(mDuel->mCastingCost)+" mana...", 0.5, 0.5, 2.0 / SCREEN_WIDTH, 2.0 / SCREEN_HEIGHT);
	}
}

int DuelInterface::handleEvent(const SDL_Event& event, int callback)
{
	Vector2i mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			if (mDuel->mIsChoiceActive) //select card for choice
			{
				assert(mSelectedCardId == -1);
				if (mHoverCardId != -1)
				{
					Message m("choiceselect");
					m.addValue("selection", mHoverCardId);
					mDuel->handleInterfaceInput(m);
				}

				glm::mat4 view, proj, projview;
				mCamera.render(view, proj);
				projview = proj*view;
				Vector2i screendim(SCREEN_WIDTH, SCREEN_HEIGHT);
				if (mEndTurnModel.rayTrace(mousePos, projview, screendim)) //end turn
				{
					endturn();
				}
				if (mButton2Model.rayTrace(mousePos, projview, screendim))
				{
					button2();
				}
			}
			else if (mSelectedCardId == -1)
			{
				if (mHoverCardId != -1)
				{
					if ((mDuel->mCardList[mHoverCardId]->mZone == ZONE_HAND || mDuel->mCardList[mHoverCardId]->mZone == ZONE_BATTLE) //select card
						&& mDuel->mCardList[mHoverCardId]->mOwner == mDuel->mTurn && mDuel->mAttackphase == PHASE_NONE 
						&& !mDuel->mIsChoiceActive) 
					{
						assert(mHoverCardId < mDuel->mCardList.size());
						mSelectedCardId = mHoverCardId;
						printf("Select: %d\n", mSelectedCardId);
						//mDuel.CardList[mHoverCardId]->move(target, 0);
					}
					else if (mDuel->mCardList[mHoverCardId]->mZone == ZONE_MANA) //tap mana
					{
						Message msg("manatap");
						msg.addValue("card", mHoverCardId);
						mDuel->handleInterfaceInput(msg);

						mHoverException = mHoverCardId;
					}
					else if (mDuel->mAttackphase == PHASE_BLOCK)
					{
						//for (size_t i = 0; i < mDuel->battlezones[!mDuel->turn].cards.size(); i++) //choose blocker
						//{
						//	if (mCardModels[mDuel->battlezones[!mDuel->turn].cards[i]->UniqueId]->rayTrace(mousePos, projview, screendim))
						//	{
						//		Message msg("creatureblock");
						//		msg.addValue("blocker", mDuel->battlezones[!mDuel->turn].cards[i]->UniqueId);
						//		mDuel->handleInterfaceInput(msg);
						//		break;
						//	}
						//}

						if (mDuel->mCardList[mHoverCardId]->mZone == ZONE_BATTLE && mDuel->mCardList[mHoverCardId]->mOwner == !mDuel->mTurn)
						{
							Message msg("creatureblock");
							msg.addValue("blocker", mHoverCardId);
							mDuel->handleInterfaceInput(msg);

							mHoverException = mHoverCardId;
						}
					}
					else if (mDuel->mAttackphase == PHASE_TARGET)
					{
						//for (size_t i = 0; i < mDuel->shields[!mDuel->turn].cards.size(); i++) //choose shields
						//{
						//	if (mCardModels[mDuel->shields[!mDuel->turn].cards[i]->UniqueId]->rayTrace(mousePos, projview, screendim))
						//	{
						//		Message msg("targetshield");
						//		msg.addValue("shield", mDuel->shields[!mDuel->turn].cards[i]->UniqueId);
						//		mDuel->handleInterfaceInput(msg);
						//		break;
						//	}
						//}

						if (mDuel->mCardList[mHoverCardId]->mZone == ZONE_SHIELD && mDuel->mCardList[mHoverCardId]->mOwner == !mDuel->mTurn)
						{
							Message msg("targetshield");
							msg.addValue("shield", mHoverCardId);
							mDuel->handleInterfaceInput(msg);

							mHoverException = mHoverCardId;
						}
					}
					else if (mDuel->mAttackphase == PHASE_TRIGGER)
					{
						//for (size_t i = 0; i < mDuel->hands[!mDuel->turn].cards.size(); i++) //use shield trigger
						//{
						//	if (mCardModels[mDuel->hands[!mDuel->turn].cards[i]->UniqueId]->rayTrace(mousePos, projview, screendim))
						//	{
						//		Message msg("triggeruse");
						//		msg.addValue("trigger", mDuel->shields[!mDuel->turn].cards[i]->UniqueId);
						//		mDuel->handleInterfaceInput(msg);
						//	}
						//}

						if (mDuel->mCardList[mHoverCardId]->mZone == ZONE_HAND && mDuel->mCardList[mHoverCardId]->mOwner == !mDuel->mTurn)
						{
							Message msg("targetshield");
							msg.addValue("shield", mHoverCardId);
							mDuel->handleInterfaceInput(msg);

							mHoverException = mHoverCardId;
						}
					}
				}

				glm::mat4 view, proj, projview;
				mCamera.render(view, proj);
				projview = proj*view;
				Vector2i screendim(SCREEN_WIDTH, SCREEN_HEIGHT);
				if (mEndTurnModel.rayTrace(mousePos, projview, screendim)) //end turn
				{
					endturn();
				}
				/*if (mButton2Model.rayTrace(mousePos, projview, screendim))
				{
					button2();
				}*/
				
				for (int i = 0; i < 2; i++)
				{
					if (mGraveyardRenderers[i]->rayTrace(mousePos, projview, screendim))
					{
						if (mGraveyardRenderers[i]->mIsOpen)
						{
							mGraveyardRenderers[i]->mIsOpen = 0;
						}
						else
						{
							for (int j = 0; j < 2; j++)
							{
								mGraveyardRenderers[j]->mIsOpen = 0;
								mDeckRenderers[j]->mIsOpen = 0;
							}
							mGraveyardRenderers[i]->mIsOpen = 1;
							mGraveyardRenderers[i]->mScrollPos = 0;
						}
					}
					if (mDeckRenderers[i]->rayTrace(mousePos, projview, screendim))
					{
						if (mDeckRenderers[i]->mIsOpen)
						{
							mDeckRenderers[i]->mIsOpen = 0;
						}
						else
						{
							for (int j = 0; j < 2; j++)
							{
								mGraveyardRenderers[j]->mIsOpen = 0;
								mDeckRenderers[j]->mIsOpen = 0;
							}
							mDeckRenderers[i]->mIsOpen = 1;
							mDeckRenderers[i]->mScrollPos = 0;
						}
					}
				}
			}
			else
			{
				if (mDuel->mCardList[mSelectedCardId]->mZone == ZONE_HAND)
				{
					glm::mat4 view, proj, projview;
					mCamera.render(view, proj);
					projview = proj*view;
					Vector2i screendim(SCREEN_WIDTH, SCREEN_HEIGHT);

					int is_evo = mDuel->getIsEvolution(mSelectedCardId);
					if (mManaZoneRenderers[mDuel->mTurn]->rayTrace(mousePos, projview, screendim)) //put card in mana
					{
						Message msg("cardmana");
						msg.addValue("card", mSelectedCardId);
						mDuel->handleInterfaceInput(msg);

						mHoverException = mSelectedCardId;
					}
					else if (!is_evo && mBattleZoneRenderers[mDuel->mTurn]->rayTrace(mousePos, projview, screendim)) //play card
					{
						Message msg("cardplay");
						msg.addValue("card", mSelectedCardId);
						msg.addValue("evobait", -1);
						mDuel->handleInterfaceInput(msg);

						mHoverException = mSelectedCardId;
					}
					else if (is_evo)
					{
						for (int i = 0; i < mDuel->mBattlezones[mDuel->mTurn].mCards.size(); i++)
						{
							if (mHoverCardId == mDuel->mBattlezones[mDuel->mTurn].mCards[i]->mUniqueId)
							{
								Message msg("cardplay");
								msg.addValue("card", mSelectedCardId);
								msg.addValue("evobait", mHoverCardId);
								mDuel->handleInterfaceInput(msg);

								mHoverException = mSelectedCardId;
								break;
							}
						}
					}
					mSelectedCardId = -1;
				}
				else if (mDuel->mCardList[mSelectedCardId]->mZone == ZONE_BATTLE) 
				{
					if (mHoverCardId != -1)
					{
						if (mDuel->mCardList[mHoverCardId]->mOwner != mDuel->mTurn)
						{
							if (mDuel->mCardList[mHoverCardId]->mZone == ZONE_BATTLE)
							{
								Message msg("creatureattack");
								msg.addValue("attacker", mSelectedCardId);
								msg.addValue("defender", mHoverCardId);
								msg.addValue("defendertype", DEFENDER_CREATURE);
								mDuel->handleInterfaceInput(msg);
								mSelectedCardId = -1;
							}
							else if (mDuel->mCardList[mHoverCardId]->mZone == ZONE_SHIELD)
							{
								Message msg("creatureattack");
								msg.addValue("attacker", mSelectedCardId);
								msg.addValue("defender", !mDuel->mTurn);
								msg.addValue("defendertype", DEFENDER_PLAYER);
								mDuel->handleInterfaceInput(msg);
								mSelectedCardId = -1;
							}
						}
					}
					//glm::mat4 view, proj, projview;
					//mCamera.render(view, proj);
					//projview = proj*view;
					//Vector2i screendim(SCREEN_WIDTH, SCREEN_HEIGHT);

					//int has_attacked = 0;
					//for (size_t i = 0; i < mDuel->battlezones[!mDuel->turn].cards.size(); i++) //attack creatures
					//{
					//	if (mCardModels[mDuel->battlezones[!mDuel->turn].cards[i]->UniqueId]->rayTrace(mousePos, projview, screendim))
					//	{
					//		Message msg("creatureattack");
					//		msg.addValue("attacker", mSelectedCardId);
					//		msg.addValue("defender", mDuel->battlezones[!mDuel->turn].cards[i]->UniqueId);
					//		msg.addValue("defendertype", DEFENDER_CREATURE);
					//		mDuel->handleInterfaceInput(msg);
					//		has_attacked = 1;
					//		mSelectedCardId = -1;
					//		break;
					//	}
					//}

					//if (!has_attacked) //attack shields
					//{
					//	for (size_t i = 0; i < mDuel->shields[!mDuel->turn].cards.size(); i++)
					//	{
					//		if (mCardModels[mDuel->shields[!mDuel->turn].cards[i]->UniqueId]->rayTrace(mousePos, projview, screendim))
					//		{
					//			Message msg("creatureattack");
					//			msg.addValue("attacker", mSelectedCardId);
					//			msg.addValue("defender", mDuel->shields[!mDuel->turn].cards[i]->UniqueId);
					//			msg.addValue("defendertype", DEFENDER_PLAYER);
					//			mDuel->handleInterfaceInput(msg);
					//			mSelectedCardId = -1;
					//			break;
					//		}
					//	}
					//}
				}
			}
		}
		else if (event.button.button == SDL_BUTTON_RIGHT)
		{
			mSelectedCardId = -1;
			for (int i = 0; i < 2; i++)
			{
				mGraveyardRenderers[i]->mIsOpen = 0;
				mDeckRenderers[i]->mIsOpen = 0;
			}
		}
	}
	else if (event.type == SDL_MOUSEWHEEL)
	{
		for (int i = 0; i < 2; i++)
		{
			if (mGraveyardRenderers[i]->mIsOpen)
			{
				mGraveyardRenderers[i]->mScrollPos += event.wheel.y;
			}
			if (mDeckRenderers[i]->mIsOpen)
			{
				mDeckRenderers[i]->mScrollPos += event.wheel.y;
			}
		}
	}
	else if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_SPACE)
		{
			endturn();
		}
	}

	return 0;
}

void DuelInterface::endturn()
{
	printf("endturn called\n");
	if (mDuel->mIsChoiceActive && mDuel->mChoice->mButtonCount >= 1)
	{
		printf("choiceselect sent\n");
		Message m("choiceselect");
		m.addValue("selection", -1);
		mDuel->handleInterfaceInput(m);
	}
	else if (mDuel->mAttackphase == PHASE_BLOCK)
	{
		Message msg("blockskip");
		mDuel->handleInterfaceInput(msg);
	}
	else if (mDuel->mAttackphase == PHASE_TRIGGER)
	{
		Message msg("triggerskip");
		mDuel->handleInterfaceInput(msg);
	}
	else
	{
		Message msg("endturn");
		mDuel->handleInterfaceInput(msg);
		printf("end turn pressed\n");
	}
}

void DuelInterface::button2()
{
	if (mDuel->mIsChoiceActive && mDuel->mChoice->mButtonCount >= 2)
	{
		Message m("choiceselect");
		m.addValue("selection", -2);
		mDuel->handleInterfaceInput(m);
	}
}

void DuelInterface::update(int deltaTime)
{
	//mDuel->dispatchAllMessages();

	Vector2i mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);

	/*for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			glm::mat4 view, proj, projview;
			mCamera.render(view, proj);
			projview = proj*view;
			Vector2i screendim(SCREEN_WIDTH, SCREEN_HEIGHT);
			if (getZoneRenderer(i, j)->rayTrace(mousePos, projview, screendim))
			{
				printf("raytrace %d %d\n", i, j);
			}
		}
	}*/

	for (int i = 0; i < 2; i++)
	{
		mHandRenderers[i]->mTurn = mDuel->mTurn;
		mHandRenderers[i]->mCastingCard = mDuel->mCastingCard;
	}

	int newhovercard = -1;
	
	if (mousePos.x >= 0 && mousePos.y >= 0)
	{
		glm::mat4 view, proj, projview;
		mCamera.render(view, proj);
		projview = proj*view;
		Vector2i screendim(SCREEN_WIDTH, SCREEN_HEIGHT);
		int flag = 0;

		for (int i = 0; i < 2; i++)
		{
			if (flag == 0 && mGraveyardRenderers[i]->mIsOpen)
			{
				for (int j = mDuel->mGraveyards[i].mCards.size()-1; j >= 0; j--)
				{
					if (mCardModels[mDuel->mGraveyards[i].mCards[j]->mUniqueId]->rayTrace(mousePos, projview, screendim))
					{
						if (newhovercard != mDuel->mGraveyards[i].mCards[j]->mUniqueId)
						{
							newhovercard = mDuel->mGraveyards[i].mCards[j]->mUniqueId;
							flag = 1;
						}
						break;
					}
				}
			}

			if (flag == 0 && mDeckRenderers[i]->mIsOpen)
			{
				for (int j = 0; j < mDuel->mDecks[i].mCards.size(); j++)
				{
					if (mCardModels[mDuel->mDecks[i].mCards[j]->mUniqueId]->rayTrace(mousePos, projview, screendim))
					{
						if (newhovercard != mDuel->mDecks[i].mCards[j]->mUniqueId)
						{
							newhovercard = mDuel->mDecks[i].mCards[j]->mUniqueId;
							flag = 1;
						}
						break;
					}
				}
			}
		}

		if (flag == 0)
		{
			for (int i = mDuel->mHands[mDuel->mTurn].mCards.size() - 1; i >= 0; i--)
			{
				if (mDuel->mHands[mDuel->mTurn].mCards[i]->mUniqueId !=mSelectedCardId 
					&& mCardModels[mDuel->mHands[mDuel->mTurn].mCards[i]->mUniqueId]->rayTrace(mousePos, projview, screendim))
				{
					if (newhovercard != mDuel->mHands[mDuel->mTurn].mCards[i]->mUniqueId)
					{
						newhovercard = mDuel->mHands[mDuel->mTurn].mCards[i]->mUniqueId;
						flag = 1;
					}
					break;
				}
			}
		}

		if (flag == 0)
		{
			for (int i = 0; i < mCardModels.size(); i++)
			{
				if ((mDuel->mCardList[i]->mZone == ZONE_BATTLE || mDuel->mCardList[i]->mZone == ZONE_MANA
					|| mDuel->mCardList[i]->mZone == ZONE_HAND || mDuel->mCardList[i]->mZone == ZONE_SHIELD)
					&& (i != mSelectedCardId || mDuel->mCardList[mSelectedCardId]->mZone != ZONE_HAND))
				{
					if (mCardModels[i]->rayTrace(mousePos, projview, screendim))
					{
						newhovercard = i;
						break;
					}
				}
			}
		}

		if (mSelectedCardId != -1 && mDuel->mCardList[mSelectedCardId]->mZone == ZONE_HAND)
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

	if (newhovercard == mHoverException && mHoverException != -1)
	{
		mHoverCardId = -1;
	}
	else if (newhovercard != mHoverCardId
		&& (newhovercard != mHoverException || mHoverException == -1))
	{
		mHoverCardId = newhovercard;
		printf("Hover: %d\n", mHoverCardId);
		mHoverTimer.restart();
		//mHandRenderers[mDuel->turn]->mHoverCard = mHoverCardId;
		//mHandRenderers[0].update(mHoverCardId); //update hand
	}
	if (newhovercard != mHoverException)
	{
		mHoverException = -1;
	}

	if (mHoverCardId == -1)
	{
		mHighlightCardId = -1;
	}
	else if (mHoverTimer.getElaspedTime() >= HOVER_CARD_TIME || mDuel->mCardList[mHoverCardId]->mZone == ZONE_HAND
		|| mDuel->mCardList[mHoverCardId]->mZone == ZONE_GRAVEYARD || mDuel->mCardList[mHoverCardId]->mZone == ZONE_DECK)
	{
		mHighlightCardId = mHoverCardId;
	}

	//Card Movement
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (size_t k = 0; k < mDuel->getZone(i, j)->mCards.size(); k++)
			{
				Card* c = mDuel->getZone(i, j)->mCards[k];
				if (c->mUniqueId != mSelectedCardId)
				{
					getZoneRenderer(i, j)->updateCard(mCardModels[c->mUniqueId], c, k, mDuel->getZone(i, j)->mCards.size(), mHighlightCardId);
					for (size_t m = 0; m < c->mEvoStack.size(); m++)
					{
						getZoneRenderer(i, j)->updateCard(mCardModels[c->mEvoStack[m]->mUniqueId], c, k, 
							mDuel->getZone(i, j)->mCards.size(), mHighlightCardId);
					}
				}
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
	mDuel->mHands[0].mMyPlayer = p;
	mDuel->mHands[1].mMyPlayer = p;
	//duel.hands[0].flipAllCards();
	//duel.hands[1].flipAllCards();
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