#pragma once
#include "GameControl.h"
class BasicGame :
	public GameControl
{
	void StartGame();
	bool IsWin();
	bool Help(stack<Vertex>& s);
	void Reset();
};

