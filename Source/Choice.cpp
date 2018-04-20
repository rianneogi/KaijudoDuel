#include "Choice.h"

Choice::Choice() : mInfotext(""), mButtonCount(0)
{
}

Choice::Choice(std::string info, int bcount, int vr, int ar) : mInfotext(info), mButtonCount(bcount), mValidRef(vr), mActionRef(ar), mIsCopy(false)
{
}

Choice::~Choice()
{
	if (!mIsCopy)
	{
		luaL_unref(LuaCards, LUA_REGISTRYINDEX, mValidRef);
		luaL_unref(LuaCards, LUA_REGISTRYINDEX, mActionRef);
		//cout << "unref " << validref << " " << actionref << endl;
	}
}

int Choice::callvalid(int cid, int sid)
{
	int r = -1;
	lua_rawgeti(LuaCards, LUA_REGISTRYINDEX, mValidRef);
	lua_pushinteger(LuaCards, cid);
	lua_pushinteger(LuaCards, sid);
	lua_pcall(LuaCards, 2, 1, 0);
	r = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);
	if (r == -1)
	{
		//cout << "ERROR callvalid returning -1" << endl;
	}
	return r;
}

void Choice::callaction(int cid, int sid)
{
	lua_rawgeti(LuaCards, LUA_REGISTRYINDEX, mActionRef);
	lua_pushinteger(LuaCards, cid);
	lua_pushinteger(LuaCards, sid);
	lua_pcall(LuaCards, 2, 0, 0);
}

void Choice::copyFrom(Choice* c)
{
	mInfotext = c->mInfotext;
	mButtonCount = c->mButtonCount;
	mValidRef = c->mValidRef;
	mActionRef = c->mActionRef;
	mIsCopy = true;
}

