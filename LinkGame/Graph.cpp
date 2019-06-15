#include "pch.h"
#include "Graph.h"

Graph::Graph(int col, int row)
{
	MAX_ROW = row;
	MAX_COL = col;
	MAX_PIC_NUM = MAX_COL;
	MAX_VERTEX_NUM = MAX_COL * MAX_ROW;
	vexs = new int[MAX_VERTEX_NUM];
	arcs = new int*[MAX_VERTEX_NUM];
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		arcs[i] = new int[MAX_VERTEX_NUM];
	}
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		vexs[i] = -1;//-1为没有图片
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			arcs[i][j] = 0;//0位没有边
		}
	}
	blanknum = 0;
	vexnum = 0, arcnum = 0;
}

Graph::~Graph()
{

}

void Graph::AddVex(int info)
{
	vexs[vexnum++] = info;
}

void Graph::AddArc(int v1, int v2)//0-15
{
	arcs[v1][v2] = 1;
	arcs[v2][v1] = 1;
	++arcnum;
}

void Graph::UpdateVex(int index, int info)
{
	vexs[index] = info;
	if (info == -1)
		blanknum++;
}

void Graph::ExchangeVexs(int index1, int index2)
{
	int t;
	t = vexs[index1];
	vexs[index1] = vexs[index2];
	vexs[index2] = t;
}

void Graph::DelVex(Vertex v)
{
	int x = v.x;
	int y = v.y;
	int index = MAX_COL * x + y;
	UpdateVex(index, -1);
	int v1 = MAX_COL * x + y;
	int v2;
	if (y > 0)//判断左
	{
		v2 = v1 - 1;
		AddArc(v1, v2);
	}
	if (y < MAX_COL -1)//判断右
	{
		v2 = v1 + 1;
		AddArc(v1, v2);
	}
	if (x > 0)//判断上
	{
		v2 = v1 - MAX_COL;
		AddArc(v1, v2);
	}
	if (x < MAX_ROW -1)//判断下
	{
		v2 = v1 + MAX_COL;
		AddArc(v1, v2);
	}
}

void Graph::ClearGraph()
{
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		vexs[i] = -1;//-1为没有图片
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			arcs[i][j] = 0;//0位没有边
		}
	}
	blanknum = 0;
	vexnum=0, arcnum=0;
}

void Graph::ClearArcs()
{
	arcnum = 0;
	/*for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			arcs[i][j] = 0;//0位没有边
		}
	}*/
}

int Graph::GetVexInfo(int index)
{
	return vexs[index];
}

int Graph::GetVexInfo(int x, int y)
{
	return vexs[MAX_COL * x + y];
}

int Graph::GetVexInfo(Vertex v)
{
	return vexs[MAX_COL * v.x + v.y];
}

bool Graph::IsAdjacent(int index1, int index2)
{
	return arcs[index1][index2];
}

int Graph::GetVexnum()
{
	return vexnum;
}

int Graph::GetAecnum()
{
	return arcnum;
}

int Graph::GetBlanknum()
{
	return blanknum;
}

int Graph::GetVex(int vexs[])
{
	for (int i = 0; i < vexnum; i++)
		vexs[i] = this->vexs[i];
	return vexnum;
}
int Graph::GetArcs(int **arcs)
{
	for (int i = 0; i < vexnum; i++)
		for (int j = 0; j < vexnum; j++)
			arcs[i][j] = this->arcs[i][j];
	return arcnum;
}
void Graph::ResetVexs()
{
	srand((int)time(NULL));
	int index1, index2;
	int temp;
	for (int i = 0; i < 100; i++)
	{
		index1 = rand() % MAX_VERTEX_NUM;
		index2 = rand() % MAX_VERTEX_NUM;
		//graph.ExchangeVexs(index1, index2);
		temp = vexs[index1];
		vexs[index1] = vexs[index2];
		vexs[index2] = temp;
	}
}
bool Graph::DFSTraverse(Vertex v1, Vertex v2, stack<Vertex>& path)
{
	int* visited = new int[vexnum];
	int cnt = 0;//拐点数
	for (int i = 0; i < vexnum; i++)
		visited[i] = 0;
	int index1 = v1.x * MAX_COL + v1.y;
	int index2 = v2.x * MAX_COL + v2.y;
	if (arcs[index1][index2] == 1)
	{
		path.push(v1);
		path.push(v2);
		return true;
	}
	bool flag = false;
	DFS(index1, index2, path, visited, flag, cnt);
	delete[]visited;
	if (flag == false)
		path.pop();
	return flag;
}

bool Graph::DFS(int v1, int v2, stack<Vertex>& path, int visited[], bool& flag, int& cnt)
{
	Vertex temp;
	temp.SetPoint(v1 / MAX_COL, v1 % MAX_COL);
	temp.info = GetVexInfo(v1);
	path.push(temp);
	if (IsCornor(path))
		cnt++;
	visited[v1] = 1;
	if (flag == true)
		return true;
	if (cnt > 2)
		return false;
	for (int i = 0; i < vexnum; i++)
	{
		if (visited[i] == 0 && arcs[v1][i] == 1 && i == v2 && cnt <= 2)
		{
			Vertex temp;
			temp.SetPoint(i / MAX_COL, i % MAX_COL);
			temp.info = GetVexInfo(i);
			path.push(temp);
			if (IsCornor(path) && cnt == 2)
			{
				path.pop();
				return false;
			}
			visited[i] = 1;
			flag = true;
			return true;
		}
		if (visited[i] == 0 && arcs[v1][i] == 1 && vexs[i] == -1 && flag == false)//
		{
			DFS(i, v2, path, visited, flag, cnt);
			if (flag == false)
			{
				if (IsCornor(path))
					cnt--;
				visited[i] = 0;
				path.pop();
			}
		}
	}
	return false;
}

bool Graph::IsCornor(stack<Vertex> s)
{
	if (s.size() < 3)
		return false;
	Vertex a[3];
	int index[3];
	for (int i = 0; i < 3; i++)
	{
		a[i] = s.top();
		index[i] = a[i].x * MAX_COL + a[i].y;
		s.pop();
	}
	if (abs(index[1] - index[0]) == abs(index[2] - index[1]))
		return false;
	return true;
}
