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

DeckBuilderUI::DeckBuilderUI() : mActiveDeckId(0)
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
	mActiveDeckData.load("Decks/My Decks/7 - L Tappy Tappy.txt");
	int id = 0;
	for (int i = 0; i < mActiveDeckData.mCards.size(); i++)
	{
		for(int j = 0;j<mActiveDeckData.mCounts[i];j++)
		{
			CardModel* c = new CardModel(id, mActiveDeckData.mCards[i]);
			mCardModels.push_back(c);
			c->setPosition(glm::vec3(2.f + CONST_CARDSEPERATION_VERT*mCardModels.size(), 0.1f, 2.f));
			id++;
		}
	}
}

void DeckBuilderUI::update(int deltaTime)
{
	for(int i = 0;i<mCardModels.size();i++)
	{
		mCardModels[i]->update(deltaTime);
	}
}

void DeckBuilderUI::render()
{
	for(int i = 0;i<mCardModels.size();i++)
	{
		mCardModels[i]->render(true);
	}
}

int DeckBuilderUI::handleEvent(const SDL_Event& event, int callback)
{
	return 0;
}
