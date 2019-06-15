#pragma once
#define BLANK -1
//#define MAX_COL				16 //��Ϸ��ͼ����
//#define MAX_ROW				10 //��Ϸ��ͼ����
//#define MAX_VERTEX_NUM		160 //������
//#define MAX_PIC_NUM			16 //ͼƬ��ɫ
#define REPEAR_NUM			10 //û�ֻ�ɫͼƬ����
#define MAP_TOP				50 //��Ϸ��ͼ���Ͻ�������
#define MAP_LEFT			20 //��Ϸ��ͼ���ϽǺ�����
#define PIC_WIDTH			40 //��ϷͼƬ���
#define PIC_HEIGHT			40 //��ϷͼƬ�߶�
#define PLAY_TIME_ID		1
#define GAME_LOSE			-1//��Ϸʧ��
#define GAME_SUCCESS		0//��Ϸʤ��
#define GAME_PLAY			1//��Ϸ��
#include <stack>
#include "afxdialogex.h"
#include <iostream>
using namespace std;
static int MAX_COL = 16;//��Ϸ��ͼ����
static int MAX_ROW = 10; //��Ϸ��ͼ����
static int MAX_PIC_NUM = MAX_COL; //ͼƬ��ɫ
static int MAX_VERTEX_NUM = MAX_COL * MAX_ROW;//������
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
	bool Timer;//��ʱ������
	bool bProp;//����
	bool Score;//����
	CString szTitle;//�Ի������������
};

struct Score
{
	int nMode;
	int nGrade;
	int nLevel;
	CString strName;
};
