// RemindSaveDlg.cpp: 实现文件
//

#include "pch.h"
#include "LinkGame.h"
#include "RemindSaveDlg.h"
#include "afxdialogex.h"


// RemindSaveDlg 对话框

IMPLEMENT_DYNAMIC(RemindSaveDlg, CDialogEx)

RemindSaveDlg::RemindSaveDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REMIND_SAVE, pParent)
{

}

RemindSaveDlg::~RemindSaveDlg()
{
}

void RemindSaveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RemindSaveDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &RemindSaveDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &RemindSaveDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// RemindSaveDlg 消息处理程序


void RemindSaveDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码3
	ok = true;
	CDialogEx::OnOK();
}


void RemindSaveDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	ok = false;
	CDialogEx::OnCancel();
}
