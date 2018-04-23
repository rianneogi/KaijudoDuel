#pragma once

#include "Graphics/ShaderProgram.h"

class Timer
{
public:
	Timer();
	~Timer();

	Uint32 getElaspedTime();
	void restart();

	Uint32 mStartTime;
};
