#pragma once

#include "MessageManager.h"
#include "LuaInclude.h"

extern lua_State* LuaCards;

class Modifier
{
public:
	//vector<string> func;
	int funcref;

	Modifier();
	Modifier(int ref);
	~Modifier();

	void setfunc(int ref);
	int handleMessage(int cid, int mid, Message& msg);
};

void registerLua(lua_State* L);

