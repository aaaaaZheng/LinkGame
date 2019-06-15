#pragma once
#include "global.h"
#include "GameLogic.h"
#include"GameControl.h"
#include "RemindGameDlg.h"
#include"HelpDialog.h"
#include"EasyGame.h"
#include"BasicGame.h"
#include"LinkGameDlg.h"
#include "RemindSaveDlg.h"
#include"SettingDlg.h"
#include "ConfigLogic.h"
// MainGameDlg 对话框

class MainGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MainGameDlg)

public:
	MainGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MainGameDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MainGame_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


protected:
	HICON m_hIcon;//对话框图标
	CDC m_dcMem;//位图内存DC
	CDC m_dcElement;//存放图标
	CDC m_dcMask;
	CDC m_dcPause;
	bool m_bFirstPoint;//是否是第一次选中的
//	Vertex m_ptSelFirst;//选中的第一个点
//	Vertex m_ptSelSec;//选中的第二个点
	Vertex m_ptGameTop;//游戏区起始点
	CSize m_sizeElem;//元素图片的大小
	CRect m_rtGameRect;//游戏区域的大小
	GameControl *gameControl;
	bool m_bPlaying;
	bool m_bPause;
	Flag m_flag;
	bool m_bProp;//是否使用道具消去
//	CProgressCtrl m_GameProgress;
	ConfigLogic configLogic;
	bool m_bMusic;
   //virtual BOOL OnInitDialog();//对话框初始化函数，设置对话框的标题栏
   //void OnPaint();//对话框WM_PAINT消息响应函数
   //初始化背景
	void InitBackground();
	void InitElement();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void SetGameModel(GameControl* aGameControl);
private:
	//int m_anMap[4][4];
	void UpdateMap();
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(Vertex m_ptSelFirst, Vertex m_ptSelSec);
	void DrawTipLine(stack<Vertex> path);
	void DrawGameTime();
	void DrawGameGrade();
	void ChangePropNum();
	void CalGameGrade();
	int JudgeWin();
	void UpdateTheme();
//	bool IsLink();
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonPrompt();
	afx_msg void OnBnClickedButtonReset();
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonRelax();
	afx_msg void OnBnClickedButtonHelp();
	afx_msg void OnBnClickedButtonProp();
	afx_msg void OnBnClickedButtonVic();
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnBnClickedButtonMusic();
};
