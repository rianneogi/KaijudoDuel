#include "Card.h"

std::vector<std::string> gCardNames;

Card::Card() : UniqueId(-1), CardId(0), Owner(0), mModel(CardId)
{
	isFlipped = false;
	isTapped = false;
	isVisible[0] = true;
	isVisible[1] = true;
	summoningSickness = 1;
}

Card::Card(int uid, int cid, int owner) : UniqueId(uid), CardId(cid), Owner(owner), mModel(cid)
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
	Name = lua_tostring(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_getfield(LuaCards, -1, "type");
	Type = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_getfield(LuaCards, -1, "shieldtrigger");
	isShieldTrigger = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	if (Type==TYPE_CREATURE)
	{
		lua_getfield(LuaCards, -1, "race");
		Race = lua_tostring(LuaCards, -1);
		lua_pop(LuaCards, 1);

		lua_getfield(LuaCards, -1, "power");
		Power = lua_tointeger(LuaCards, -1);
		//displayPower = Power;
		lua_pop(LuaCards, 1);

		lua_getfield(LuaCards, -1, "breaker");
		Breaker = lua_tointeger(LuaCards, -1);
		lua_pop(LuaCards, 1);

		lua_getfield(LuaCards, -1, "blocker");
		isBlocker = lua_tointeger(LuaCards, -1);
		lua_pop(LuaCards, 1);
	}
	else
	{
		Race = "";
		Power = 0;
		//displayPower = 0;
		Breaker = 0;
		isBlocker = 0;
	}

	lua_getfield(LuaCards, -1, "civilization");
	Civilization = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_getfield(LuaCards, -1, "cost");
	ManaCost = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_pop(LuaCards, 1);
	lua_pop(LuaCards, 1);

	isTapped = false;
	isFlipped = false;
	isVisible[0] = true;
	isVisible[1] = true;
	Zone = ZONE_DECK;
	summoningSickness = 1;

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

void Card::render(int myPlayer)
{
	mModel.render(isVisible[myPlayer]);
}

void Card::update(int deltaTime)
{
	mModel.update(deltaTime);
}

bool Card::rayTrace(Vector2i mousePos, const glm::mat4& projview, const Vector2i& screenDimensions)
{
	Vector2f mousepixel;
	mousepixel.x = mousePos.x / (screenDimensions.x / 2.f) - 1.f;
	mousepixel.y = -(mousePos.y / (screenDimensions.y / 2.f) - 1.f);
	glm::mat4 finalmat = projview*mModel.getHoverModelMatrix();

	std::vector<glm::vec4> newverts;
	newverts.push_back(finalmat*glm::vec4(-1.f, 0.f, -1.38f, 1));
	newverts.push_back(finalmat*glm::vec4(1.f, 0.f, -1.38f, 1));
	newverts.push_back(finalmat*glm::vec4(1.f, 0.f, 1.38f, 1));
	newverts.push_back(finalmat*glm::vec4(-1.f, 0.f, 1.38f, 1));

	for (int i = 0;i < 4;i++) //perspective divide
	{
		newverts[i].x /= newverts[i].w;
		newverts[i].y /= newverts[i].w;
		newverts[i].z /= newverts[i].w;
	}

	if (isPointInsidePolygon(newverts, mousepixel.x, mousepixel.y))
	{
		return true;
	}
	return false;
}

void Card::copyFrom(Card* c)
{
	UniqueId = c->UniqueId;
	CardId = c->CardId;

}

void Card::handleEvent(const SDL_Event& e)
{
}

int Card::handleMessage(Message& msg)
{
	lua_getglobal(LuaCards, "Cards");
	lua_getfield(LuaCards, -1, gCardNames.at(CardId).c_str());
	lua_getfield(LuaCards, -1, "HandleMessage");
	lua_pushinteger(LuaCards, UniqueId);
	lua_pcall(LuaCards, 1, 0, 0);
	//sendMessageToBuffs(msg);
	lua_pop(LuaCards, 1);
	lua_pop(LuaCards, 1);

	int cnt = 0;
	for (std::vector<Modifier*>::iterator i = modifiers.begin(); i != modifiers.end(); i++, cnt++)
	{
		(*i)->handleMessage(UniqueId, cnt, msg);
	}

	return 0;
}

void Card::callOnCast()
{
	lua_getglobal(LuaCards, "Cards");
	lua_getfield(LuaCards, -1, gCardNames.at(CardId).c_str());
	lua_getfield(LuaCards, -1, "OnCast");
	lua_pushinteger(LuaCards, UniqueId);
	lua_pcall(LuaCards, 1, 0, 0);
	lua_pop(LuaCards, 1);
	lua_pop(LuaCards, 1);
}

void Card::move(Orientation target, int time)
{
	mModel.setMovement(target, time);
}

void Card::hover(Orientation target, int time)
{
	mModel.setHoverMovement(target, time);
}

void Card::setPosition(glm::vec3 pos)
{
	mModel.setPosition(pos);
}

void Card::updatePower(int pow)
{
	//powertext.setString(std::to_string(pow));
}

void Card::flip()
{
	isFlipped = true;
	mModel.mOrientation.up = glm::vec3(0, -1, 0);
	//sprite.setTexture(Textures.at(TEXTURE_CARDBACK));
}

void Card::unflip()
{
	isFlipped = false;
	mModel.mOrientation.up = glm::vec3(0, 1, 0);
	//sprite.setTexture(CardTextures.at(CardId));
}

void Card::tap()
{
	isTapped = true;
	mModel.mOrientation.dir = glm::vec3(1, 0, 0);
	//sprite.setRotation(90);
}

void Card::untap()
{
	isTapped = false;
	mModel.mOrientation.dir = glm::vec3(0, 0, 1);
	//sprite.setRotation(0);
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

	name = "Resources\\Cards\\" + set + "\\" + name + ".png";
	gCardTextures.push_back(new Texture());
	if (!gCardTextures.at(gCardTextures.size() - 1)->loadFromFile(name))
	{
		//cout << "ERROR cant load texture " << CardNames.at(CardNames.size() - 1) << endl;
		printf("ERROR: cant load card texture %s\n", gCardNames.at(gCardNames.size() - 1).c_str());
	}
	//printf("Generated texture: %d\n", gCardTextures[gCardTextures.size() - 1]->mTextureID);
	//gCardTextures.at(gCardTextures.size() - 1).setSmooth(true);
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
	for (int i = 0;i < gCardTextures.size();i++)
	{
		delete gCardTextures[i];
	}
	lua_close(LuaCards);
}