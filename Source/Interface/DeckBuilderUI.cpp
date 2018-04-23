#include "DeckBuilderUI.h"

void DeckData::addCard(int cid)
{
	int flag = 0;
	for(int i = 0;i<mCards.size();i++)
	{
		if(mCards[i]==cid && mCounts[i]<4)
		{
			mCounts[i]++;
			flag = 1;
		}
	}
	if(flag==0)
	{
		mCards.push_back(cid);
		mCounts.push_back(1);
	}
}

void DeckData::removeCard(int cid)
{
	for(int i = 0;i<mCards.size();i++)
	{
		if(mCards[i]==cid)
		{
			mCounts[i]--;
			
			if(mCounts[i]==0)
			{
				mCards.erase(mCards.begin() + i);
				mCounts.erase(mCounts.begin() + i);
			}
		}
	}
}

void DeckData::load(std::string path)
{
	mCards.empty();
	mCounts.empty();
	std::fstream file;
	file.open(path, std::ios::in | std::ios::out);
	std::string str;

	if (!file.is_open())
	{
		//cout << "ERROR opening deck: " << s << endl;
		printf("ERROR opening deck %s\n", path.c_str());
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
				if(name[name.size()-1]=='\r') //remove /r at eof
				{
					name = name.substr(0, name.size()-1);
				}
				
				mCards.push_back(getCardIdFromName(name));
				mCounts.push_back(count);
				printf("added %s\n", name.c_str());
				break;
			}
		}
	}

	file.close();

	mName = path;
}

void DeckData::save(std::string path)
{
	
}

DeckBuilderUI::DeckBuilderUI() : mActiveDeckId(0), mScrollPos(0)
{
}

DeckBuilderUI::~DeckBuilderUI()
{
	for(int i = 0;i<mCardModels.size();i++)
	{
		delete mCardModels[i];
	}
}

void DeckBuilderUI::init()
{
	for(int i = 0;i<DECKBUILDER_ROWS;i++)
	{
		for(int j = 0;j<DECKBUILDER_COLS;j++)
		{
			CardModel* c = new CardModel(0, DECKBUILDER_COLS*i + j);
			mCollectionModels.push_back(c);
			c->setPosition(glm::vec3(8.5f - (CONST_CARDSEPERATION_VERT/2)*j, 15.f, -2.f - i*CONST_CARDSEPERATION_HORI));
		}
	}
	
	mActiveDeckData.load("Decks/My Decks/7 - L Tappy Tappy.txt");
	int id = 0;
	for (int i = 0; i < mActiveDeckData.mCards.size(); i++)
	{
		for(int j = 0;j<mActiveDeckData.mCounts[i];j++)
		{
			CardModel* c = new CardModel(id, mActiveDeckData.mCards[i]);
			mCardModels.push_back(c);
			// c->setPosition(glm::vec3(2.f + CONST_CARDSEPERATION_VERT*mCardModels.size(), 0.1f, 2.f));
			id++;
		}
	}
	
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
}

void DeckBuilderUI::updateCard(CardModel* model, int pos, int size, int hovercard)
{
	Orientation o;
	o.pos = glm::vec3(-4, 15 + CONST_CARDTHICKNESS*pos, -3 + mScrollPos + (size-pos-1)*CONST_CARD_SCROLLER_SEPERATION);
	if (model->mUniqueId == hovercard)
	{
		o.pos.y += 1;
	}
	o.dir = glm::vec3(0, 0, 1);
	o.up = glm::vec3(0, 1, 0);
	o.calculateQuat();
	if (model->mUniqueId == hovercard)
	{
		model->setHoverMovement(o, 1000);
	}
	else
	{
		model->setMovement(o, 1000);
	}
}

void DeckBuilderUI::update(int deltaTime)
{
	Vector2i mousePos;
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	
	int hovercard = -1;
	
	if (mousePos.x >= 0 && mousePos.y >= 0)
	{
		glm::mat4 view, proj, projview;
		mCamera.render(view, proj);
		projview = proj*view;
		Vector2i screendim(SCREEN_WIDTH, SCREEN_HEIGHT);
		
		for (int i = mCardModels.size()-1; i>=0; i--)
		{
			if (mCardModels[i]->rayTrace(mousePos, projview, screendim))
			{
				hovercard = i;
				break;
			}
		}
	}
	
	for(int i = 0;i<mCardModels.size();i++)
	{
		updateCard(mCardModels[i], i, mCardModels.size(), hovercard);
		mCardModels[i]->update(deltaTime);
	}
}

void DeckBuilderUI::render()
{
	glm::mat4 view, projection;
	mCamera.render(view, projection);
	//glDisable(GL_CULL_FACE);
	//Vector2i mousePos;
	//SDL_GetMouseState(&mousePos.x, &mousePos.y);

	gActiveShader = SHADER_BASIC;
	gShaders[gActiveShader].bind();
	gShaders[gActiveShader].setUniformMat4f(0, mTableModel.mModelMatrix);
	gShaders[gActiveShader].setUniformMat4f(1, view);
	gShaders[gActiveShader].setUniformMat4f(2, projection);
	//gShaders[gActiveShader].setUniformVec3f(3, mCamera.mPosition);
	//gShaders[gActiveShader].setUniformInt(4, 1);
	//gShaders[gActiveShader].setUniformVec4f(4, glm::vec4(mCamera.mPosition, 1.0));
	//gShaders[gActiveShader].setUniformVec3f(5, glm::vec3(1,1,1));
	//gShaders[gActiveShader].setUniformInt(6, 75);
	
	mTableModel.render();

	
	for(int i = 0;i<mCardModels.size();i++)
	{
		mCardModels[i]->render(true);
	}
	for(int i = 0;i<mCollectionModels.size();i++)
	{
		mCollectionModels[i]->render(true);
	}
}

int DeckBuilderUI::handleEvent(const SDL_Event& event, int callback)
{
	if (event.type == SDL_MOUSEWHEEL)
	{
		mScrollPos += event.wheel.y;
	}
	
	return 0;
}
