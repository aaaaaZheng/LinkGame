#pragma once
#include"ScoreLogic.h"
#include "global.h"
#include<vector>
#include<iostream>
using namespace std;
// RankDlg 对话框

class RankDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RankDlg)

public:
	RankDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~RankDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RANK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	ScoreLogic scoreLogic;
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstRank;
	int m_nMode;
	afx_msg void OnBnClickedRadioEasy();
	virtual BOOL OnInitDialog();
	void DisplayRank();
};
