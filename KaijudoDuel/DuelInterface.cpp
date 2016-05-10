#include "DuelInterface.h"

float gZoomDistance = 18.f;
const float gCameraSpeed = 0.0001f;

DuelInterface::DuelInterface()
{
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

	for (int i = 0;i < 2;i++)
	{
		mDuel.hands[i].setCamera(&mCamera);
	}
}

DuelInterface::~DuelInterface()
{
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

	//render zones
	for (int i = 0; i < 2; i++)
	{
		mDuel.decks[i].renderCards(myPlayer);
		mDuel.hands[i].renderCards(myPlayer);
		mDuel.manazones[i].renderCards(myPlayer);
		mDuel.graveyards[i].renderCards(myPlayer);
		mDuel.shields[i].renderCards(myPlayer);
		mDuel.battlezones[i].renderCards(myPlayer);
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
			if (mHoverCardId != -1)
			{
				assert(mHoverCardId < mDuel.CardList.size());
				mSelectedCardId = mHoverCardId;
				//mDuel.CardList[mHoverCardId]->move(target, 0);
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

void DuelInterface::parseMessages(unsigned int deltatime)
{
	mDuel.parseMessages(deltatime);
}

void DuelInterface::update(int deltaTime)
{
	int newhovercard = -1;
	Vector2i mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	if (mousePos.x >= 0 && mousePos.y >= 0)
	{
		glm::mat4 view, proj, projview;
		mCamera.render(view, proj);
		projview = proj*view;
		Vector2i screendim(SCREEN_WIDTH, SCREEN_HEIGHT);
		float minDepth = 1;
		for (int i = mDuel.hands[0].cards.size() - 1;i >= 0;i--)
		{
			if (mDuel.hands[0].cards[i]->rayTrace(mousePos, projview, screendim))
			{
				if (newhovercard != mDuel.hands[0].cards[i]->UniqueId)
				{
					newhovercard = mDuel.hands[0].cards[i]->UniqueId;
				}
				break;
			}
		}
		if (mSelectedCardId != -1)
		{
			assert(mSelectedCardId < mDuel.CardList.size());

			Vector2f mousepixel;
			mousepixel.x = -(mousePos.x / (SCREEN_WIDTH / 2.f) - 1.f);
			mousepixel.y = -(mousePos.y / (SCREEN_HEIGHT / 2.f) - 1.f);

			Orientation o;
			o.pos = glm::vec3(8*mousepixel.x, (mCamera.mPosition + mCamera.mDirection*gHandStraightDistance).y, 8*mousepixel.y);
			o.dir = mCamera.mUp;
			o.up = -mCamera.mDirection;
			mDuel.CardList[mSelectedCardId]->move(o, 1);
		}
	}
	if (newhovercard != mHoverCardId)
	{
		mHoverCardId = newhovercard;
		printf("Hover: %d\n", mHoverCardId);
		mDuel.hands[0].update(mHoverCardId); //update hand
	}

	for (int i = 0;i < mDuel.CardList.size();i++) //update cards
	{
		mDuel.CardList[i]->update(deltaTime);
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

//void DuelInterface::flipCardForPlayer(int cid, int p)
//{
//	if (myPlayer == p || dueltype == DUELTYPE_SINGLE)
//		duel.CardList.at(cid)->flip();
//}
//
//void DuelInterface::unflipCardForPlayer(int cid, int p)
//{
//	if (myPlayer == p || dueltype == DUELTYPE_SINGLE)
//		duel.CardList.at(cid)->unflip();
//}

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
	mDuel.hands[0].mMyPlayer = p;
	mDuel.hands[1].mMyPlayer = p;
	//duel.hands[0].flipAllCards();
	//duel.hands[1].flipAllCards();
}

