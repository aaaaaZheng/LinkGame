#pragma once
#include "GameLogic.h"
#include"Graph.h"
class GameControl
{
protected:
	Graph graph;
	Vertex m_ptSelFirst;//选中的第一个点
	Vertex m_ptSelSec;//选中的第二个点
	GameLogic gameLogic;
	Flag flag;
	int m_nGrade=0;
	int propNum=0;
public:
	virtual bool SaveScore();
	Vertex GetFirstVertex();
	Vertex GetSelVertex();
	int GetPropNum();
	virtual bool PropLink();
	virtual int GetGrade();
	virtual void StartGame() = 0;
	int GetElement(int x, int y);
	void SetFirstPoint(int x, int y);
	void SetSecPoint(int x, int y);
	bool Link(Vertex v[2]);
	virtual bool Link(stack<Vertex> &path);
	virtual  bool IsWin()=0;
	virtual bool Help(stack<Vertex> &s)=0;
	virtual void Reset() = 0;
	void SetGameFlag(Flag aflag);
	Flag GetGameFlag();
	void ClearAll();
};

