#include "pch.h"
#include "GameControl.h"


bool GameControl::SaveScore()
{
	return false; 
}

Vertex GameControl::GetFirstVertex()
{
	return m_ptSelFirst;
}

Vertex GameControl::GetSelVertex()
{
	return m_ptSelSec;
}

int GameControl::GetPropNum()
{
	return propNum;
}

bool GameControl::PropLink()
{
	return true;
}

int GameControl::GetGrade()
{
	return m_nGrade;
}

void GameControl::StartGame()
{
	gameLogic.InitMap(graph);
}

int GameControl::GetElement(int x, int y)
{
	return graph.GetVexInfo(x, y);
}

void GameControl::SetFirstPoint(int x, int y)
{
	m_ptSelFirst.x = x;
	m_ptSelFirst.y = y;
	m_ptSelFirst.info = graph.GetVexInfo(x, y);
}

void GameControl::SetSecPoint(int x, int y)
{
	m_ptSelSec.x = x;
	m_ptSelSec.y = y;
	m_ptSelSec.info = graph.GetVexInfo(x, y);
}

bool GameControl::Link(Vertex v[2])
{
	if (m_ptSelFirst.x == m_ptSelSec.x && m_ptSelFirst.y == m_ptSelSec.y)
		return false;
	if (m_ptSelFirst.info != m_ptSelSec.info)
		return false;
	stack<Vertex> s;
	if (gameLogic.IsLink(graph, m_ptSelFirst, m_ptSelSec,s))
	{
		v[0].x = m_ptSelFirst.x;
		v[0].y = m_ptSelFirst.y;
		v[0].info= graph.GetVexInfo(m_ptSelFirst.x, m_ptSelFirst.y);
		v[1].x = m_ptSelSec.x;
		v[1].y = m_ptSelSec.y;
		v[1].info= graph.GetVexInfo(m_ptSelSec.x, m_ptSelSec.y);
		gameLogic.Clear(graph, m_ptSelFirst, m_ptSelSec);
		return true;
	}
	return false;
}

bool GameControl::Link(stack<Vertex> &path)
{
	if (m_ptSelFirst.x == m_ptSelSec.x && m_ptSelFirst.y == m_ptSelSec.y)
		return false;
	if (m_ptSelFirst.info != m_ptSelSec.info)
		return false;
	if (gameLogic.IsLink(graph, m_ptSelFirst, m_ptSelSec, path))
	{
		gameLogic.Clear(graph, m_ptSelFirst, m_ptSelSec);
		return true;
	}
	return false;
}

bool GameControl::IsWin()
{
	if (gameLogic.IsBlank(graph))
	{
		graph.ClearGraph();
		return true;
	}
	return false;
	
}

bool GameControl::Help(stack<Vertex>& s)
{
	return gameLogic.SearchValidPath(graph, s);
	
}

void GameControl::Reset()
{
	gameLogic.ResetGraph(graph);
}

void GameControl::SetGameFlag(Flag aflag)
{
	flag = aflag;
}

Flag GameControl::GetGameFlag()
{
	return flag;
}

void GameControl::ClearAll()
{
	gameLogic.ClearAll(graph);
}
