
// LinkGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "LinkGame.h"
#include "LinkGameDlg.h"
#include "afxdialogex.h"
#include "MainGameDlg.h"
#include"RankDlg.h"
#include "LevelGame.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLinkGameDlg 对话框



CLinkGameDlg::CLinkGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LINKGAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLinkGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLinkGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BASIC, &CLinkGameDlg::OnBnClickedButtonBasic)
	ON_BN_CLICKED(IDC_BUTTON_BASIC, &CLinkGameDlg::OnBnClickedButtonBasic)
	ON_BN_CLICKED(IDC_BUTTON_RELAX, &CLinkGameDlg::OnBnClickedButtonRelax)
	ON_BN_CLICKED(IDC_BUTTON_LEVEL, &CLinkGameDlg::OnBnClickedButtonLevel)
	ON_BN_CLICKED(IDC_BUTTON_RANK, &CLinkGameDlg::OnBnClickedButtonRank)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CLinkGameDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CLinkGameDlg::OnBnClickedButtonHelp)
END_MESSAGE_MAP()


// CLinkGameDlg 消息处理程序

BOOL CLinkGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitBackground();





	


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLinkGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLinkGameDlg::OnPaint()
{
	CPaintDC dc(this);
	 // 用于绘制的设备上下文
	CRect rect;
	GetClientRect(&rect);

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcMem, 0, 0, SRCCOPY);
	CFont font;
	dc.SetTextColor(RGB(0, 0, 255));
	dc.SetBkColor(RGB(255, 0, 0));
	font.CreatePointFont(200, _T("Courier New"));
	CFont* oldFont;
	oldFont = dc.SelectObject(&font);
	CString strWel = _T("Welcome to LinkGame");
	SIZE size;
	size=dc.GetTextExtent(strWel, strWel.GetLength());
	int x = (rect.Width() - size.cx) / 2;
	int y = (rect.Height() - size.cy) / 2;
	dc.TextOutW(x, y, strWel);
	dc.SelectObject(oldFont);



	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLinkGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CLinkGameDlg::InitBackground()
{
	BITMAP bgPicture;
	CRect rect;
	GetClientRect(&rect);

	//初始化背景
	CBitmap bitmap;
	HGDIOBJ temp;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	m_dcMem.CreateCompatibleDC(&m_dcMem);
	bitmap.GetBitmap(&bgPicture);
	temp = m_dcMem.SelectObject(bitmap);
	//dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcbg, 0, 0,bgPicture.bmWidth,bgPicture.bmHeight, SRCCOPY);

//	m_dcMem.SelectObject(temp);
}



void CLinkGameDlg::OnBnClickedButtonBasic()
{
	this->ShowWindow(SW_HIDE);

	//打开游戏界面
	MainGameDlg mainGameDlg;
	GameControl *aGameControl = new BasicGame;
	Flag aFlag;
	aFlag.Timer = true;
	aFlag.bProp = false;
	aFlag.Score = false;
	aFlag.szTitle = _T("基本模式");

	aGameControl->SetGameFlag(aFlag);
	mainGameDlg.SetGameModel(aGameControl);
	mainGameDlg.DoModal();

	this->ShowWindow(SW_SHOW);

}


void CLinkGameDlg::OnBnClickedButtonRelax()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);

	//打开游戏界面
	MainGameDlg mainGameDlg;
	GameControl* aGameControl = new EasyGame;
	Flag aFlag;
	aFlag.Timer = false;
	aFlag.bProp = true;
	aFlag.Score = true;
	aFlag.szTitle = _T("休闲模式");

	aGameControl->SetGameFlag(aFlag);
	mainGameDlg.SetGameModel(aGameControl);
	mainGameDlg.DoModal();


	//strCommond.Format(_T("play %s repeat"), strFileName);
	//mciSendString(strCommond, NULL, 0, NULL);

	this->ShowWindow(SW_SHOW);
}


void CLinkGameDlg::OnBnClickedButtonLevel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);

	//打开游戏界面
	MainGameDlg mainGameDlg;
	LevelGame* aGameControl = new LevelGame;
	Flag aFlag;
	aFlag.Timer = true;
	aFlag.bProp = true;
	aFlag.Score = true;
	aFlag.szTitle = _T("关卡模式");
	aGameControl->SetGameFlag(aFlag);
	mainGameDlg.SetGameModel(aGameControl);
	mainGameDlg.DoModal();

	//strCommond.Format(_T("play %s repeat"), strFileName);
	//mciSendString(strCommond, NULL, 0, NULL);

	this->ShowWindow(SW_SHOW);
	
}


void CLinkGameDlg::OnBnClickedButtonRank()
{
	// TODO: 在此添加控件通知处理程序代码
	RankDlg rankDlg;
	rankDlg.DoModal();
}


void CLinkGameDlg::OnBnClickedButtonSetting()
{
	SettingDlg settingDlg;
	settingDlg.DoModal();
	// TODO: 在此添加控件通知处理程序代码
}


void CLinkGameDlg::OnBnClickedButtonHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	HelpDlg helpDialog;
	helpDialog.DoModal();
}
