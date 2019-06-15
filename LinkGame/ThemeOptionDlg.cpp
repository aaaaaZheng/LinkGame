// ThemeOptionDlg.cpp: 实现文件
//

#include "pch.h"
#include "LinkGame.h"
#include "ThemeOptionDlg.h"
#include "afxdialogex.h"


// ThemeOptionDlg 对话框

IMPLEMENT_DYNAMIC(ThemeOptionDlg, CDialogEx)

ThemeOptionDlg::ThemeOptionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_THEME, pParent)
	, m_nThemeType(0)
	, m_strElemPath(_T(""))
	, m_strMaskPath(_T(""))
{

}

ThemeOptionDlg::~ThemeOptionDlg()
{
}

void ThemeOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_FRUIT, m_nThemeType);
	DDX_Text(pDX, IDC_ELEM_PATH, m_strElemPath);
	DDX_Text(pDX, IDC_MASK_PATH, m_strMaskPath);
	DDX_Control(pDX, IDC_ELEM_PATH, elemPath);
	DDX_Control(pDX, IDC_MASK_PATH, maskPath);
}


BEGIN_MESSAGE_MAP(ThemeOptionDlg, CDialogEx)

	ON_BN_CLICKED(IDC_BUTTON_BROWSE1, &ThemeOptionDlg::OnBnClickedButtonBrowse1)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE2, &ThemeOptionDlg::OnBnClickedButtonBrowse2)
	ON_BN_CLICKED(IDC_RADIO_FRUIT, &ThemeOptionDlg::OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_CARTOON, &ThemeOptionDlg::OnBnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO_CUSTOM, &ThemeOptionDlg::OnBnClickedRadio)
END_MESSAGE_MAP()


// ThemeOptionDlg 消息处理程序




void ThemeOptionDlg::OnBnClickedButtonBrowse1()
{
	CFileDialog dlg(TRUE/*这个参数为TRUE就是“打开”对话框，为FALSE就是“保存”对话框*/, NULL, NULL, OFN_HIDEREADONLY, _T("所有文件(*.*)|*.*||"), NULL, NULL, FALSE);
	if (dlg.DoModal() == IDOK)//如果用户在文件对话框中点击了“确定”按钮
	{
		CString strPathName = dlg.GetPathName();//获取文件路径到strPathName
		elemPath.SetWindowText(strPathName);//显示文件路径到编辑框
		m_strElemPath = strPathName;

	}
}


void ThemeOptionDlg::OnBnClickedButtonBrowse2()
{
	CFileDialog dlg(TRUE/*这个参数为TRUE就是“打开”对话框，为FALSE就是“保存”对话框*/, NULL, NULL, OFN_HIDEREADONLY, _T("所有文件(*.*)|*.*||"), NULL, NULL, FALSE);
	if (dlg.DoModal() == IDOK)//如果用户在文件对话框中点击了“确定”按钮
	{
		CString strPathName = dlg.GetPathName();//获取文件路径到strPathName
		maskPath.SetWindowText(strPathName);//显示文件路径到编辑框
		m_strMaskPath = strPathName;
	}
}


void ThemeOptionDlg::OnBnClickedRadio()
{
	UpdateData(TRUE);
	// TODO: 在此添加控件通知处理程序代码
	switch (m_nThemeType)
	{
	case 0:
		flag = 0;
		GetDlgItem(IDC_BUTTON_BROWSE1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_BROWSE2)->EnableWindow(FALSE);
		GetDlgItem(IDC_ELEM_PATH)->EnableWindow(FALSE);
		GetDlgItem(IDC_MASK_PATH)->EnableWindow(FALSE);
		break;
	case 1:
		flag = 1;
		GetDlgItem(IDC_BUTTON_BROWSE1)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_BROWSE2)->EnableWindow(FALSE);
		GetDlgItem(IDC_ELEM_PATH)->EnableWindow(FALSE);
		GetDlgItem(IDC_MASK_PATH)->EnableWindow(FALSE);
		break;
	case 2:
		flag = 2;
		GetDlgItem(IDC_BUTTON_BROWSE1)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_BROWSE2)->EnableWindow(TRUE);
		GetDlgItem(IDC_ELEM_PATH)->EnableWindow(TRUE);
		GetDlgItem(IDC_MASK_PATH)->EnableWindow(TRUE);
		break;
	default:
		break;
	}
}

void ThemeOptionDlg::Save()
{

	Config* con = Config::GetSingleInstance();
	if (flag == 0)
		con->Save(1);
	else if (flag == 1)
		con->Save(2);
	else
		con->Save(flag, m_strElemPath, m_strMaskPath);
}





BOOL ThemeOptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString elemPath = Config::GetSingleInstance()->GetElemPath();
	CString maskPath = Config::GetSingleInstance()->GetMaskPath();

	GetDlgItem(IDC_BUTTON_BROWSE1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BROWSE2)->EnableWindow(FALSE);
	GetDlgItem(IDC_ELEM_PATH)->EnableWindow(FALSE);
	GetDlgItem(IDC_MASK_PATH)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
