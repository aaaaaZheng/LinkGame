#include "pch.h"
#include "LevelGame.h"

void LevelGame::StartGame()
{

	gameLogic.InitMap(graph);

}

bool LevelGame::IsWin()
{
	if (gameLogic.IsBlank(graph))
	{
		graph.ClearGraph();
		return true;
	}
	return false;

}

bool LevelGame::Help(stack<Vertex>& s)
{
	if (gameLogic.SearchValidPath(graph, s))
	{
		m_nGrade -= 20;
		return true;
	}
	return false;
}

void LevelGame::Reset()
{
	gameLogic.ResetGraph(graph);
	m_nGrade -= 50;
}

bool LevelGame::Link(stack<Vertex>& path)
{
	if (m_ptSelFirst.x == m_ptSelSec.x && m_ptSelFirst.y == m_ptSelSec.y)
		return false;
	if (m_ptSelFirst.info != m_ptSelSec.info)
		return false;
	if (gameLogic.IsLink(graph, m_ptSelFirst, m_ptSelSec, path))
	{
		m_nGrade += 10;
		if (m_nGrade % 100 == 0)
			++propNum;
		gameLogic.Clear(graph, m_ptSelFirst, m_ptSelSec);
		return true;
	}
	return false;
}

bool LevelGame::PropLink()
{
	if (m_ptSelFirst.info == m_ptSelSec.info && m_ptSelSec.info != BLANK && m_ptSelFirst.info != BLANK)
	{
		propNum--;

		gameLogic.Clear(graph, m_ptSelFirst, m_ptSelSec);
		m_nGrade += 10;
		return true;
	}
	return false;
}

bool LevelGame::SaveScore()
{
	CString str; //获取系统时间 　　

	CTime tm = CTime::GetCurrentTime();

	str = tm.Format("%Y%m%d%H%M%S");
	Score score;
	score.strName = str;
	score.nGrade = m_nGrade;
	score.nMode = 1;
	if (m_nGrade < 500)
		score.nLevel = 1;
	else if (m_nGrade < 1000)
		score.nLevel = 2;
	else
		score.nLevel = 3;
	return scoreLogic.SaveScore(score);
}
