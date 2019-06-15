// RemindGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "LinkGame.h"
#include "RemindGameDlg.h"
#include "afxdialogex.h"
#include "global.h"

// RemindGameDlg 对话框

IMPLEMENT_DYNAMIC(RemindGameDlg, CDialogEx)

RemindGameDlg::RemindGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REMIND, pParent)
{

}

RemindGameDlg::~RemindGameDlg()
{
}

RemindGameDlg::RemindGameDlg(int flag, CWnd* pParent ) : CDialogEx(IDD_REMIND, pParent)
{
	this->flag = flag;
	
}

void RemindGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void RemindGameDlg::ChangeMessage()
{
	CString str;
	if (flag == GAME_SUCCESS)
	{
		str = _T("游戏成功");

	}
	else
	{
		str = _T("游戏失败");
	}
	GetDlgItem(IDC_TATIC_REMIND)->SetWindowTextW(str);
}


BEGIN_MESSAGE_MAP(RemindGameDlg, CDialogEx)
END_MESSAGE_MAP()


// RemindGameDlg 消息处理程序


BOOL RemindGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ChangeMessage();
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
