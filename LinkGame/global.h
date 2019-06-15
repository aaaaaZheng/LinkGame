#pragma once
#define BLANK -1
//#define MAX_COL				16 //游戏地图列数
//#define MAX_ROW				10 //游戏地图行数
//#define MAX_VERTEX_NUM		160 //顶点数
//#define MAX_PIC_NUM			16 //图片花色
#define REPEAR_NUM			10 //没种花色图片个数
#define MAP_TOP				50 //游戏地图左上角纵坐标
#define MAP_LEFT			20 //游戏地图左上角横坐标
#define PIC_WIDTH			40 //游戏图片宽度
#define PIC_HEIGHT			40 //游戏图片高度
#define PLAY_TIME_ID		1
#define GAME_LOSE			-1//游戏失败
#define GAME_SUCCESS		0//游戏胜利
#define GAME_PLAY			1//游戏中
#include <stack>
#include "afxdialogex.h"
#include <iostream>
using namespace std;
static int MAX_COL = 16;//游戏地图列数
static int MAX_ROW = 10; //游戏地图行数
static int MAX_PIC_NUM = MAX_COL; //图片花色
static int MAX_VERTEX_NUM = MAX_COL * MAX_ROW;//顶点数
struct  Vertex
{
	int x;
	int y;
	int info;
	void SetPoint(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
};

struct Flag
{
	bool Timer;//计时进度条
	bool bProp;//道具
	bool Score;//积分
	CString szTitle;//对话框标题栏文字
};

struct Score
{
	int nMode;
	int nGrade;
	int nLevel;
	CString strName;
};
