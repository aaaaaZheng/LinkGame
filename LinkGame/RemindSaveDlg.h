#pragma once


// RemindSaveDlg 对话框

class RemindSaveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RemindSaveDlg)

public:
	RemindSaveDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~RemindSaveDlg();
	bool ok;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REMIND_SAVE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
