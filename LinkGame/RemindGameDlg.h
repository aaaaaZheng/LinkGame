#pragma once


// RemindGameDlg 对话框

class RemindGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RemindGameDlg)

public:
	RemindGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~RemindGameDlg();
	RemindGameDlg(int flag,CWnd* pParent = nullptr);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REMIND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	int flag;

	virtual BOOL OnInitDialog();
	void ChangeMessage();

};
