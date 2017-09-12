#include "Card.h"

std::vector<std::string> gCardNames;

Card::Card() : mUniqueId(-1), mCardId(0), mOwner(0)
{
	mIsFlipped = false;
	mIsTapped = false;
	mIsVisible[0] = true;
	mIsVisible[1] = true;
	mSummoningSickness = 1;
}

Card::Card(int uid, int cid, int owner) : mUniqueId(uid), mCardId(cid), mOwner(owner)
{
	//if (uid == -1)
	//	cout << "ERROR unit id = -1" << endl;
	assert(uid >= 0);
	assert(cid >= 0);
	assert(cid < gCardNames.size());
	printf("id: %d %s\n", cid, gCardNames[cid].c_str());

	lua_getglobal(LuaCards, "Cards");
	lua_getfield(LuaCards, -1, gCardNames.at(cid).c_str());

	lua_getfield(LuaCards, -1, "name");
	mName = lua_tostring(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_getfield(LuaCards, -1, "type");
	mType = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_getfield(LuaCards, -1, "shieldtrigger");
	mIsShieldTrigger = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	if (mType==TYPE_CREATURE)
	{
		lua_getfield(LuaCards, -1, "race");
		mRace = lua_tostring(LuaCards, -1);
		lua_pop(LuaCards, 1);

		lua_getfield(LuaCards, -1, "power");
		mPower = lua_tointeger(LuaCards, -1);
		//displayPower = Power;
		lua_pop(LuaCards, 1);

		lua_getfield(LuaCards, -1, "breaker");
		mBreaker = lua_tointeger(LuaCards, -1);
		lua_pop(LuaCards, 1);

		lua_getfield(LuaCards, -1, "blocker");
		mIsBlocker = lua_tointeger(LuaCards, -1);
		lua_pop(LuaCards, 1);
	}
	else
	{
		mRace = "";
		mPower = 0;
		//displayPower = 0;
		mBreaker = 0;
		mIsBlocker = 0;
	}

	lua_getfield(LuaCards, -1, "civilization");
	mCivilization = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_getfield(LuaCards, -1, "cost");
	mManaCost = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_pop(LuaCards, 1);
	lua_pop(LuaCards, 1);

	mIsTapped = false;
	mIsFlipped = false;
	mIsVisible[0] = true;
	mIsVisible[1] = true;
	mZone = ZONE_DECK;
	mSummoningSickness = 1;

	/*sprite = sf::Sprite(CardTextures.at(CardId));
	sprite.setScale(CARD_SCALE, CARD_SCALE);
	sf::FloatRect v = sprite.getLocalBounds();
	sprite.setOrigin(v.width / 2, v.height / 2);
	powertext = sf::Text(std::to_string(Power), DefaultFont, 12);
	powertext.setStyle(sf::Text::Style::Bold);
	powertext.setColor(sf::Color::Black);*/
}

Card::~Card()
{
}

//void Card::render(int myPlayer)
//{
//	mModel.render(isVisible[myPlayer]);
//}
//
//void Card::update(int deltaTime)
//{
//	mModel.update(deltaTime);
//}

void Card::copyFrom(Card* c)
{
	mUniqueId = c->mUniqueId;
	mCardId = c->mCardId;

}

//void Card::handleEvent(const SDL_Event& e)
//{
//}

int Card::handleMessage(Message& msg)
{
	lua_getglobal(LuaCards, "Cards");
	lua_getfield(LuaCards, -1, gCardNames.at(mCardId).c_str());
	lua_getfield(LuaCards, -1, "HandleMessage");
	lua_pushinteger(LuaCards, mUniqueId);
	lua_pcall(LuaCards, 1, 0, 0);
	//sendMessageToBuffs(msg);
	lua_pop(LuaCards, 1);
	lua_pop(LuaCards, 1);

	int cnt = 0;
	for (std::vector<Modifier*>::iterator i = mModifiers.begin(); i != mModifiers.end(); i++, cnt++)
	{
		(*i)->handleMessage(mUniqueId, cnt, msg);
	}
	
	return 0;
}

void Card::callOnCast()
{
	lua_getglobal(LuaCards, "Cards");
	lua_getfield(LuaCards, -1, gCardNames.at(mCardId).c_str());
	lua_getfield(LuaCards, -1, "OnCast");
	lua_pushinteger(LuaCards, mUniqueId);
	lua_pcall(LuaCards, 1, 0, 0);
	lua_pop(LuaCards, 1);
	lua_pop(LuaCards, 1);
}

//void Card::move(Orientation target, int time)
//{
//	mModel.setMovement(target, time);
//}
//
//void Card::hover(Orientation target, int time)
//{
//	mModel.setHoverMovement(target, time);
//}
//
//void Card::setPosition(glm::vec3 pos)
//{
//	mModel.setPosition(pos);
//}

//void Card::updatePower(int pow)
//{
//	//powertext.setString(std::to_string(pow));
//}

void Card::flip()
{
	mIsFlipped = true;
	//mModel.mOrientation.up = glm::vec3(0, -1, 0);
	//sprite.setTexture(Textures.at(TEXTURE_CARDBACK));
}

void Card::unflip()
{
	mIsFlipped = false;
	//mModel.mOrientation.up = glm::vec3(0, 1, 0);
	//sprite.setTexture(CardTextures.at(CardId));
}

void Card::tap()
{
	mIsTapped = true;
	//mModel.mOrientation.dir = glm::vec3(1, 0, 0);
	//sprite.setRotation(90);
}

void Card::untap()
{
	mIsTapped = false;
	//mModel.mOrientation.dir = glm::vec3(0, 0, 1);
	//sprite.setRotation(0);
}

void Card::setVisibility(int player, int visibility)
{
	mIsVisible[player] = visibility;
}

//sf::FloatRect Card::getBounds()
//{
//	return sprite.getGlobalBounds();
//}


int getCardIdFromName(std::string s)
{
	for (int i = 0; i < gCardNames.size(); i++)
	{
		if (gCardNames.at(i) == s)
		{
			return i;
		}
	}
	return -1;
}

static int loadcard(lua_State* L)
{
	std::string name = lua_tostring(L, 1);
	std::string set = lua_tostring(L, 2);

	//std::cout << "Loading Card : " << name << "\n";
	printf("Loading Card : %s %d\n", name.c_str(), gCardNames.size());

	gCardNames.push_back(name);

	lua_getglobal(LuaCards, "Cards");
	lua_getfield(LuaCards, -1, name.c_str());

	lua_getfield(LuaCards, -1, "type");
	int type = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	std::string race = "";
	int power = 0;

	if (type == TYPE_CREATURE)
	{
		lua_getfield(LuaCards, -1, "race");
		race = lua_tostring(LuaCards, -1);
		lua_pop(LuaCards, 1);

		lua_getfield(LuaCards, -1, "power");
		power = lua_tointeger(LuaCards, -1);
		lua_pop(LuaCards, 1);
	}

	lua_getfield(LuaCards, -1, "civilization");
	int civ = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_getfield(LuaCards, -1, "cost");
	int cost = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_pop(LuaCards, 1);
	lua_pop(LuaCards, 1);

	CardData cd(CardDatabase.size(), name, set, race, civ, type, cost, power);
	CardDatabase.push_back(cd);

	return 0;
}

bool initCards()
{
	//std::cout << "Loading Cards...\n";
	printf("Loading Cards...\n");
	LuaCards = luaL_newstate(); //create new lua state
	luaL_openlibs(LuaCards);

	lua_register(LuaCards, "loadcard", loadcard); //register loadcard
	registerLua(LuaCards); //register functions

	if (luaL_loadfile(LuaCards, "Lua\\Cards.lua") || lua_pcall(LuaCards, 0, 0, 0))
	{
		printf("Error: failed to load Cards.lua\n");
		printf("%s\n", lua_tostring(LuaCards, -1));
		_getch();
		return false;
	}

	lua_getglobal(LuaCards, "loadCards");
	lua_pcall(LuaCards, 0, 0, 0); //execute once to load cards
	lua_pop(LuaCards, 1);

	return true;
}

void cleanupCards()
{
	lua_close(LuaCards);
}