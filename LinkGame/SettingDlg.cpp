// SettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "LinkGame.h"
#include "SettingDlg.h"
#include "afxdialogex.h"


// SettingDlg 对话框

IMPLEMENT_DYNAMIC(SettingDlg, CDialogEx)

SettingDlg::SettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
{

}

SettingDlg::~SettingDlg()
{
}

void SettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_SETTING, m_tabSetting);
}


BEGIN_MESSAGE_MAP(SettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &SettingDlg::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_OK, &SettingDlg::OnBnClickedButtonOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SETTING, &SettingDlg::OnTcnSelchangeTabSetting)
END_MESSAGE_MAP()


// SettingDlg 消息处理程序


void SettingDlg::OnBnClickedButtonCancel()
{
	EndDialog(0);
}


void SettingDlg::OnBnClickedButtonOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_dlgTheme.Save();
	EndDialog(IDOK);
}


void SettingDlg::OnTcnSelchangeTabSetting(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int tab = m_tabSetting.GetCurSel();
	if (tab == 0)
	{
		m_dlgTheme.ShowWindow(SW_SHOW);
		m_dlgMusic.ShowWindow(SW_HIDE);
	}
	else if (tab == 1)
	{
		m_dlgMusic.ShowWindow(SW_SHOW);

		m_dlgTheme.ShowWindow(SW_HIDE);

	}

}


BOOL SettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_tabSetting.InsertItem(0, _T("主题设置"));
	m_tabSetting.InsertItem(1, _T("音效设置"));
	m_tabSetting.InsertItem(2, _T("地图大小"));


	m_dlgTheme.Create(IDD_DIALOG_THEME, GetDlgItem(IDD_DIALOG_THEME));
	m_dlgMusic.Create(IDD_DIALOG_MUSIC, GetDlgItem(IDD_DIALOG_MUSIC));
	//IDD_DIALOG_THEME
	CRect rc;
	m_tabSetting.GetClientRect(rc);
	rc.top += 20;
	m_dlgTheme.MoveWindow(&rc);
	m_dlgTheme.SetParent(&m_tabSetting);
	m_dlgMusic.MoveWindow(&rc);
	m_dlgMusic.SetParent(&m_tabSetting);
	m_dlgTheme.ShowWindow(SW_SHOW);
	m_dlgMusic.ShowWindow(SW_HIDE);

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
