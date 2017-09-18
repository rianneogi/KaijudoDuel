#include "Card.h"

//std::vector<std::string> gCardNames;

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
	assert(cid < gCardDatabase.size());
	printf("id: %d %s\n", cid, gCardDatabase[cid].Name.c_str());

	mName = gCardDatabase[cid].Name;
	mType = gCardDatabase[cid].Type;
	mRace = gCardDatabase[cid].Race;
	mPower = gCardDatabase[cid].Power;
	mManaCost = gCardDatabase[cid].ManaCost;
	mCivilization = gCardDatabase[cid].Civilization;

	lua_getglobal(LuaCards, "Cards");
	//printf("name %s %d\n", gCardDatabase[cid].Name.c_str(), cid);
	lua_getfield(LuaCards, -1, gCardDatabase[cid].Name.c_str());

	/*lua_getfield(LuaCards, -1, "name");
	mName = lua_tostring(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_getfield(LuaCards, -1, "type");
	mType = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);*/

	lua_getfield(LuaCards, -1, "shieldtrigger");
	mIsShieldTrigger = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	if (mType==TYPE_CREATURE)
	{
		//lua_getfield(LuaCards, -1, "race");
		//mRace = lua_tostring(LuaCards, -1);
		//lua_pop(LuaCards, 1);

		//lua_getfield(LuaCards, -1, "power");
		//mPower = lua_tointeger(LuaCards, -1);
		////displayPower = Power;
		//lua_pop(LuaCards, 1);

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

	/*lua_getfield(LuaCards, -1, "civilization");
	mCivilization = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_getfield(LuaCards, -1, "cost");
	mManaCost = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);*/

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
	lua_getfield(LuaCards, -1, gCardDatabase[mCardId].Name.c_str());
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
	lua_getfield(LuaCards, -1, gCardDatabase[mCardId].Name.c_str());
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
	for (size_t i = 0; i < gCardDatabase.size(); i++)
	{
		if (gCardDatabase[i].Name == s)
		{
			return i;
		}
	}
	return -1;
}

//static int loadcard(lua_State* L)
//{
//	std::string name = lua_tostring(L, 1);
//	std::string set = lua_tostring(L, 2);
//
//	//std::cout << "Loading Card : " << name << "\n";
//	printf("Loading Card : %s %d\n", name.c_str(), gCardNames.size());
//
//	gCardNames.push_back(name);
//
//	lua_getglobal(LuaCards, "Cards");
//	lua_getfield(LuaCards, -1, name.c_str());
//
//	lua_getfield(LuaCards, -1, "type");
//	int type = lua_tointeger(LuaCards, -1);
//	lua_pop(LuaCards, 1);
//
//	std::string race = "";
//	int power = 0;
//
//	if (type == TYPE_CREATURE)
//	{
//		lua_getfield(LuaCards, -1, "race");
//		race = lua_tostring(LuaCards, -1);
//		lua_pop(LuaCards, 1);
//
//		lua_getfield(LuaCards, -1, "power");
//		power = lua_tointeger(LuaCards, -1);
//		lua_pop(LuaCards, 1);
//	}
//
//	lua_getfield(LuaCards, -1, "civilization");
//	int civ = lua_tointeger(LuaCards, -1);
//	lua_pop(LuaCards, 1);
//
//	lua_getfield(LuaCards, -1, "cost");
//	int cost = lua_tointeger(LuaCards, -1);
//	lua_pop(LuaCards, 1);
//
//	lua_pop(LuaCards, 1);
//	lua_pop(LuaCards, 1);
//
//	CardData cd(gCardDatabase.size(), name, set, race, civ, type, cost, power);
//	gCardDatabase.push_back(cd);
//
//	return 0;
//}

void loadSet(std::string path, std::string set_name)
{
	std::fstream file(path);
	if (!file.is_open())
	{
		printf("ERROR: Unable to load set %s\n", path.c_str());
	}

	boost::property_tree::ptree p;
	boost::property_tree::read_xml(file, p);
	auto cards = p.get_child(boost::property_tree::ptree::path_type("set.cards"));

	std::string name = "";
	std::string race = "";
	int civ = -1;
	int type = -1;
	int cost = -1;
	int power = -1;

	std::string tmp = "";

	for (auto it : cards)
	{
		//printf("tree: %s\n", it.first);
		//printf("name %s\n", it.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.name")).c_str());
		name = it.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.name"));
		for (auto it2 : it.second)
		{
			if (it2.first == "property")
			{
				if (it2.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.name")) == "Civilization")
				{
					//printf("civ %s\n", it2.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.value")).c_str());
					tmp = it2.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.value"));
					if (tmp == "Light") civ = CIV_LIGHT;
					else if (tmp == "Darkness") civ = CIV_DARKNESS;
					else if (tmp == "Fire") civ = CIV_FIRE;
					else if (tmp == "Water") civ = CIV_WATER;
					else if (tmp == "Nature") civ = CIV_NATURE;
					else printf("ERROR: Unknown civ for card %s\n", name.c_str());
				}
				if (it2.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.name")) == "Power")
				{
					//printf("power %s\n", it2.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.value")).c_str());
					tmp = it2.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.value"));
					if (tmp != "")
					{
						if (tmp[tmp.size() - 1] == '+' || tmp[tmp.size() - 1] == '-')
						{
							//printf("old %s\n", tmp.c_str());
							tmp = tmp.substr(0, tmp.size() - 1);
							//printf("new %s\n", tmp.c_str());
						}
						power = atoi(tmp.c_str());
					}
				}
				if (it2.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.name")) == "Race")
				{
					//printf("race %s\n", it2.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.value")).c_str());
					race = it2.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.value"));
				}
				if (it2.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.name")) == "Cost")
				{
					//printf("cost %s\n", it2.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.value")).c_str());
					cost = atoi(it2.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.value")).c_str());
				}
				if (it2.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.name")) == "Type")
				{
					//printf("type %s\n", it2.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.value")).c_str());
					tmp = it2.second.get<std::string>(boost::property_tree::ptree::path_type("<xmlattr>.value"));
					if (tmp == "Creature") type = TYPE_CREATURE;
					else if (tmp == "Evolution Creature") type = TYPE_CREATURE;
					else if (tmp == "Spell") type = TYPE_SPELL;
					else printf("ERROR: Unknown type for card %s\n", name.c_str());
				}
			}
		}
		CardData cd(gCardDatabase.size(), name, set_name, race, civ, type, cost, power);
		gCardDatabase.push_back(cd);
	}
}

bool initCards()
{
	//std::cout << "Loading Cards...\n";
	printf("Loading Cards...\n");
	LuaCards = luaL_newstate(); //create new lua state
	luaL_openlibs(LuaCards);

	//lua_register(LuaCards, "loadcard", loadcard); //register loadcard
	registerLua(LuaCards); //register functions

	if (luaL_loadfile(LuaCards, "Lua\\Cards.lua") || lua_pcall(LuaCards, 0, 0, 0))
	{
		printf("Error: failed to load Cards.lua\n");
		printf("%s\n", lua_tostring(LuaCards, -1));
		_getch();
		return false;
	}

	//lua_getglobal(LuaCards, "loadCards");
	//lua_pcall(LuaCards, 0, 0, 0); //execute once to load cards
	//lua_pop(LuaCards, 1);

	loadSet("Resources/Sets XML/DM-01 Base Set/set.xml", "DM-01 Base Set");
	loadSet("Resources/Sets XML/DM-02 Master of Evolution/set.xml", "DM-02 Master of Evolution");
	loadSet("Resources/Sets XML/DM-03 Master of Destruction/set.xml", "DM-03 Master of Destruction");
	loadSet("Resources/Sets XML/DM-04 Challenge of Black Shadow/set.xml", "DM-04 Challenge of Black Shadow");
	loadSet("Resources/Sets XML/DM-05 Return of the Survivor/set.xml", "DM-05 Return of the Survivor");
	loadSet("Resources/Sets XML/DM-06 Invincible Soul/set.xml", "DM-06 Invincible Soul");
	loadSet("Resources/Sets XML/DM-07 Invincible Charge/set.xml", "DM-07 Invincible Charge");
	loadSet("Resources/Sets XML/DM-08 Invincible Legend/set.xml", "DM-08 Invincible Legend");
	loadSet("Resources/Sets XML/DM-09 Invincible Blood/set.xml", "DM-09 Invincible Blood");
	loadSet("Resources/Sets XML/Promo and DMC Packs/set.xml", "Promo and DMC Packs");

	return true;
}

void cleanupCards()
{
	lua_close(LuaCards);
}