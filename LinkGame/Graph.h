#pragma once
#include "global.h"
class Graph
{
public:
	Graph(int col=16, int row=10);
	~Graph();
	void AddVex(int info);
	void AddArc(int v1, int v2);
	void UpdateVex(int index, int info);
	void ExchangeVexs(int index1, int index2);
	void DelVex(Vertex v);
	void ClearGraph();
	void ClearArcs();
	int GetVexInfo(int index);
	int GetVexInfo(int x,int y);
	int GetVexInfo(Vertex v);
	bool IsAdjacent(int index1, int index2);
	int GetVexnum();
	int GetAecnum();
	int GetBlanknum();
	int GetVex(int vexs[]);
	int GetArcs(int **arcs);
	void ResetVexs();
	bool DFSTraverse(Vertex v1, Vertex v2, stack<Vertex> &path);
	int *vexs;//顶点信息
	int **arcs;//邻接矩阵
protected:
	int vexnum, arcnum;
	int blanknum;
	bool DFS(int v1, int v2,stack<Vertex> &path,int visited[], bool &flag, int &cnt);
	bool IsCornor(stack<Vertex> s);
};
