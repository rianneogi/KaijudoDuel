#pragma once

#include "BattleZone.h"

class Choice
{
public:
	std::string mInfotext;
	int mButtonCount;
	int mValidRef;
	int mActionRef;

	bool mIsCopy;

	Choice();
	Choice(std::string info, int skip, int vr, int ar);
	~Choice();

	int callvalid(int cid, int sid);
	void callaction(int cid, int sid);
	void copyFrom(Choice* c);
};

