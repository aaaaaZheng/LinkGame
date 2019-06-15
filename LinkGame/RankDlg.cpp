// RankDlg.cpp: 实现文件
//

#include "pch.h"
#include "LinkGame.h"
#include "RankDlg.h"
#include "afxdialogex.h"


// RankDlg 对话框

IMPLEMENT_DYNAMIC(RankDlg, CDialogEx)

RankDlg::RankDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RANK, pParent)
	, m_nMode(0)
{

}

RankDlg::~RankDlg()
{
}

void RankDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RANK, m_lstRank);
	DDX_Radio(pDX, IDC_RADIO_EASY, m_nMode);
}


BEGIN_MESSAGE_MAP(RankDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_EASY, &RankDlg::OnBnClickedRadioEasy)
	ON_BN_CLICKED(IDC_RADIO_GAME, &RankDlg::OnBnClickedRadioEasy)
END_MESSAGE_MAP()


// RankDlg 消息处理程序


void RankDlg::OnBnClickedRadioEasy()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	DisplayRank();
}


BOOL RankDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	m_lstRank.InsertColumn(0, _T("排名"), LVCFMT_CENTER, 50);
	m_lstRank.InsertColumn(1, _T("玩家姓名"), LVCFMT_CENTER, 300);
	m_lstRank.InsertColumn(2, _T("积分"), LVCFMT_CENTER, 75);
	DisplayRank();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void RankDlg::DisplayRank()
{
	m_lstRank.DeleteAllItems();
	vector<Score> ranks;
	scoreLogic.SearchRank(ranks, m_nMode + 1);
	CString num;
	CString aGrade;
	for (int i=0;i<ranks.size();i++)
	{
		num.Format(_T("%d"), i+1);
		m_lstRank.InsertItem(i, num);
		m_lstRank.SetItemText(i, 1, ranks[i].strName);
		aGrade.Format(_T("%d"), ranks[i].nGrade);
		m_lstRank.SetItemText(i, 2, aGrade);

	}

}
