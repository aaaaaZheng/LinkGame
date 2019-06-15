#include "pch.h"
#include "BasicGame.h"

void BasicGame::StartGame()
{
	gameLogic.InitMap(graph);

}

bool BasicGame::IsWin()
{
	if (gameLogic.IsBlank(graph))
	{
		graph.ClearGraph();
		return true;
	}
	return false;
}

bool BasicGame::Help(stack<Vertex>& s)
{
	return gameLogic.SearchValidPath(graph, s);
}

void BasicGame::Reset()
{
	gameLogic.ResetGraph(graph);
}
