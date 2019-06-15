#pragma once
#include"Config.h"
// ThemeOptionDlg 对话框

class ThemeOptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ThemeOptionDlg)

public:
	ThemeOptionDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ThemeOptionDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_THEME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	int flag;
public:
	afx_msg void OnBnClickedButtonBrowse1();
	afx_msg void OnBnClickedButtonBrowse2();
	int m_nThemeType;
	afx_msg void OnBnClickedRadio();
	CString m_strElemPath;
	CString m_strMaskPath;
	void Save();
	virtual BOOL OnInitDialog();
	CEdit elemPath;
	CEdit maskPath;
};
