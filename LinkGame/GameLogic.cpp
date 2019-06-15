#include "pch.h"
#include "GameLogic.h"

GameLogic::GameLogic()
{
	anTemp = new int[MAX_VERTEX_NUM];
}

GameLogic::~GameLogic()
{
	delete[] anTemp;
}

void GameLogic::InitMap(Graph& graph,int col,int row)
{
	MAX_COL = col;
	MAX_ROW = row;
	MAX_VERTEX_NUM = MAX_COL * MAX_ROW;
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		anTemp[i] = i% MAX_PIC_NUM;
	}
	srand((int)time(NULL));
	int index1, index2;
	int temp;
	for (int i = 0; i < 100; i++)
	{
		index1 = rand() % MAX_VERTEX_NUM;
		index2 = rand() % MAX_VERTEX_NUM;
		temp = anTemp[index1];
		anTemp[index1] = anTemp[index2];
		anTemp[index2] = temp;
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		graph.AddVex(anTemp[i]);
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
			UpdateArc(graph, i, j);

}

bool GameLogic::IsLink(Graph graph, Vertex v1, Vertex v2, stack<Vertex>& path)
{
	return graph.DFSTraverse(v1, v2, path);
}

void GameLogic::Clear(Graph& graph, Vertex v1, Vertex v2)
{
	graph.DelVex(v1);
	graph.DelVex(v2);
}

void GameLogic::ClearAll(Graph& graph)
{
	graph.ClearGraph();
}

bool GameLogic::IsBlank(Graph graph)
{
	return graph.GetBlanknum() == graph.GetVexnum();
}

bool GameLogic::SearchValidPath(Graph graph, stack<Vertex>& path)
{
	int vexnum = graph.GetVexnum();
	for (int i = 0; i < vexnum; i++)
	{
		if (graph.vexs[i] != -1)
		{
			for (int j = 0; j < vexnum; j++)
			{
				if (i == j)
					continue;
				if (graph.vexs[i] == graph.vexs[j])
				{
					Vertex t1, t2;
					t1.SetPoint(i / MAX_COL, i % MAX_COL);
					t1.info = graph.GetVexInfo(i);
					t2.SetPoint(j / MAX_COL, j % MAX_COL);
					t2.info = graph.GetVexInfo(j);
					if (graph.DFSTraverse(t1, t2, path))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

void GameLogic::ResetGraph(Graph& graph)
{

/*	srand((int)time(NULL));
	int index1, index2;
	int temp;
	for (int i = 0; i < 100; i++)
	{
		index1 = rand() % MAX_VERTEX_NUM;
		index2 = rand() % MAX_VERTEX_NUM;
		//graph.ExchangeVexs(index1, index2);
		temp = anTemp[index1];
		anTemp[index1] = anTemp[index2];
		anTemp[index2] = temp;
	}*/
	graph.ResetVexs();
	graph.ClearArcs();
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
			UpdateArc(graph, i, j);

}
bool GameLogic::sort(int& a, int& b)
{
	if (a > b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
	return false;
}

void GameLogic::UpdateArc(Graph& graph, int x, int y)
{
	int v1 = MAX_COL * x + y;
	int v2;
	if (y > 0)//еп╤овС
	{
		v2 = v1 - 1;
		if (graph.GetVexInfo(v1) == graph.GetVexInfo(v2) || graph.GetVexInfo(v1)== -1)
		{
			graph.AddArc(v1, v2);
		}
	}
	if (y < MAX_COL-1)//еп╤оср
	{
		v2 = v1 + 1;
		if (graph.GetVexInfo(v1) == graph.GetVexInfo(v2) || graph.GetVexInfo(v1) == -1)
		{
			graph.AddArc(v1, v2);
		}
	}
	if (x > 0)//еп╤оио
	{
		v2 = v1 - MAX_COL;
		if (graph.GetVexInfo(v1) == graph.GetVexInfo(v2) || graph.GetVexInfo(v1) == -1)
		{
			graph.AddArc(v1, v2);
		}
	}
	if (x < MAX_ROW-1)//еп╤ооб
	{
		v2 = v1 + MAX_COL;
		if (graph.GetVexInfo(v1) == graph.GetVexInfo(v2) || graph.GetVexInfo(v1) == -1)
		{
			graph.AddArc(v1, v2);
		}
	}
}

