#pragma once


// MusicOptionDlg 对话框

class MusicOptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MusicOptionDlg)

public:
	MusicOptionDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MusicOptionDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MUSIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nThemeType;
	CEdit m_strMusicPath;
	CString musicPath;
	afx_msg void OnBnClickedButtonBrowse1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio();
};
