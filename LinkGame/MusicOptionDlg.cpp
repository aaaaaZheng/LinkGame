// MusicOptionDlg.cpp: 实现文件
//

#include "pch.h"
#include "LinkGame.h"
#include "MusicOptionDlg.h"
#include "afxdialogex.h"


// MusicOptionDlg 对话框

IMPLEMENT_DYNAMIC(MusicOptionDlg, CDialogEx)

MusicOptionDlg::MusicOptionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_MUSIC, pParent)
	, m_nThemeType(0)
	, musicPath(_T(""))
{

}

MusicOptionDlg::~MusicOptionDlg()
{
}

void MusicOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_FRUIT, m_nThemeType);
	DDX_Control(pDX, IDC_MUSIC_PATH, m_strMusicPath);
	DDX_Text(pDX, IDC_MUSIC_PATH, musicPath);
}


BEGIN_MESSAGE_MAP(MusicOptionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE1, &MusicOptionDlg::OnBnClickedButtonBrowse1)
	ON_BN_CLICKED(IDC_RADIO_FRUIT, &MusicOptionDlg::OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_CARTOON, &MusicOptionDlg::OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_CUSTOM, &MusicOptionDlg::OnBnClickedRadio)
END_MESSAGE_MAP()


// MusicOptionDlg 消息处理程序


void MusicOptionDlg::OnBnClickedButtonBrowse1()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL MusicOptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_BUTTON_BROWSE1)->EnableWindow(FALSE);
	GetDlgItem(IDC_MUSIC_PATH)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void MusicOptionDlg::OnBnClickedRadio()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	// TODO: 在此添加控件通知处理程序代码
	switch (m_nThemeType)
	{
	case 0:
		GetDlgItem(IDC_BUTTON_BROWSE1)->EnableWindow(FALSE);
		GetDlgItem(IDC_MUSIC_PATH)->EnableWindow(FALSE);
		break;
	case 1:
		GetDlgItem(IDC_BUTTON_BROWSE1)->EnableWindow(FALSE);
		GetDlgItem(IDC_MUSIC_PATH)->EnableWindow(FALSE);
		break;
	case 2:
		GetDlgItem(IDC_BUTTON_BROWSE1)->EnableWindow(TRUE);
		GetDlgItem(IDC_MUSIC_PATH)->EnableWindow(TRUE);
		break;
	default:
		break;
	}
}


