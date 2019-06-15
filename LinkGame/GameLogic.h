#pragma once
#include "global.h"
#include "Graph.h"
class GameLogic
{

protected:
	stack<Vertex> s;
	int* anTemp;
	//int anMap[4][4];
	//Vertex m_ptSelFirst;//选中的第一个点
//	Vertex m_ptSelSec;//选中的第二个点
public:
	GameLogic();
	~GameLogic();
	void InitMap(Graph& graph,int col=16, int row=10);
	bool IsLink(Graph graph, Vertex v1, Vertex v2, stack<Vertex>& path);
	void Clear(Graph& graph, Vertex v1, Vertex v2);
	void ClearAll(Graph& graph);
	bool IsBlank(Graph graph);
	bool SearchValidPath(Graph graph, stack<Vertex>& path);
	void ResetGraph(Graph& g);
private:
	bool sort(int& a, int& b);
	void UpdateArc(Graph& graph, int x, int y);

};

