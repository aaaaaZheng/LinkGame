#pragma once
#include "GameControl.h"
#include "ScoreLogic.h"
class LevelGame :
	public GameControl
{
protected:
	ScoreLogic scoreLogic;
public:
	void StartGame();
	bool IsWin();
	bool Help(stack<Vertex>& s);
	void Reset();
	bool Link(stack<Vertex>& path);
	bool PropLink();
	bool SaveScore();
};

