#pragma once
#include"ThemeOptionDlg.h"
#include "MusicOptionDlg.h"
// SettingDlg 对话框

class SettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SettingDlg)

public:
	SettingDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~SettingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	ThemeOptionDlg m_dlgTheme;
	MusicOptionDlg m_dlgMusic;
	CTabCtrl m_tabSetting;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnTcnSelchangeTabSetting(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
};
