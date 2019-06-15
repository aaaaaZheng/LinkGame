// MainGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "LinkGame.h"
#include "MainGameDlg.h"
#include "afxdialogex.h"
#include "Mmsystem.h"
#pragma comment(lib,"winmm.lib") 
// MainGameDlg 对话框

IMPLEMENT_DYNAMIC(MainGameDlg, CDialogEx)

MainGameDlg::MainGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MainGame_DIALOG, pParent)
{
}

MainGameDlg::~MainGameDlg()
{
	delete gameControl;
}

void MainGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}

void MainGameDlg::InitBackground()
{
	BITMAP bgPicture;


	//初始化背景
	CBitmap bitmap;
	HGDIOBJ temp;
	bitmap.LoadBitmapW(IDB_BITMAP1);
	m_dcMem.CreateCompatibleDC(&m_dcMem);
	bitmap.GetBitmap(&bgPicture);
	temp = m_dcMem.SelectObject(bitmap);
}

void MainGameDlg::InitElement()
{

	CString elemPath = configLogic.GetElemPath();
	CString maskPath = configLogic.GetMaskPath();


	//获得当前对话框的视频内存
	CClientDC dc(this);
	//加载BMP图片资源
	HANDLE hBmp1 = ::LoadImageW(NULL, elemPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存相兼容的内存pc
	m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(hBmp1);

	HANDLE hBmp2 = ::LoadImageW(NULL, maskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hBmp2);

	BITMAP stopPicture;


	//初始化背景
	CBitmap bitmap;
	HGDIOBJ temp;
	bitmap.LoadBitmapW(IDB_BITMAP_STOP);
	m_dcPause.CreateCompatibleDC(&m_dcPause);
	bitmap.GetBitmap(&stopPicture);
	temp = m_dcPause.SelectObject(bitmap);
	m_bPause = false;
}


BEGIN_MESSAGE_MAP(MainGameDlg, CDialogEx)
	ON_WM_PAINT()
	//ON_BN_CLICKED(IDC_BUTTON_BASIC, &MainGameDlg::OnBnClickedButtonBasic)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_START, &MainGameDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_PROMPT, &MainGameDlg::OnBnClickedButtonPrompt)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &MainGameDlg::OnBnClickedButtonReset)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_RELAX, &MainGameDlg::OnBnClickedButtonRelax)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &MainGameDlg::OnBnClickedButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_PROP, &MainGameDlg::OnBnClickedButtonProp)
	ON_BN_CLICKED(IDC_BUTTON_VIC, &MainGameDlg::OnBnClickedButtonVic)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &MainGameDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_MUSIC, &MainGameDlg::OnBnClickedButtonMusic)
END_MESSAGE_MAP()


// MainGameDlg 消息处理程序


BOOL MainGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_flag = gameControl->GetGameFlag();
	if (m_flag.Timer == true)
	{
		GetDlgItem(IDC_GAME_TIME)->EnableWindow(TRUE);

	}
	else
	{
		GetDlgItem(IDC_GAME_TIME)->EnableWindow(FALSE);
	}
	if (m_flag.bProp == true)
	{
		GetDlgItem(IDC_BUTTON_PROP)->ShowWindow(SW_SHOW);
		ChangePropNum();
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PROP)->ShowWindow(SW_HIDE);
	}
	if (m_flag.Score == true)
	{
		GetDlgItem(IDC_STATIC_SCORE)->ShowWindow(SW_SHOW);
		DrawGameGrade();
		GetDlgItem(IDC_STATIC_SCRORE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PROP)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_SCRORE)->ShowWindow(SW_HIDE);
	}
	//设置标题
	this->SetWindowTextW(m_flag.szTitle);


	InitBackground();
	InitElement();
	m_bPlaying = false;
	m_sizeElem.SetSize(PIC_WIDTH, PIC_HEIGHT);

	m_ptGameTop.SetPoint(MAP_LEFT, MAP_TOP);

	m_bFirstPoint = true;
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_ptGameTop.x + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_ptGameTop.y + MAX_ROW * m_sizeElem.cy;
	m_bMusic = false;

	GetDlgItem(IDC_BUTTON_RELAX)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void MainGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetClientRect(&rect);			   // 不为绘图消息调用 CDialogEx::OnPaint()
	//初始化背景
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcMem, 0, 0, SRCCOPY);
}

void MainGameDlg::SetGameModel(GameControl* aGameControl)
{
	gameControl = aGameControl;
}


void MainGameDlg::UpdateMap()
{
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;

	CClientDC dc(this);
	CBitmap bmpMap;
	HGDIOBJ p_Old;

	bmpMap.LoadBitmapW(IDB_BITMAP1);
	CDC dcMap;
	dcMap.CreateCompatibleDC(&dc);
	p_Old = dcMap.SelectObject(&bmpMap);
	m_dcMem.BitBlt(nLeft, nTop, MAX_COL * nElemW, MAX_ROW * nElemH, &dcMap, nLeft, nTop, SRCCOPY);

	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
		{
			if (gameControl->GetElement(i, j) != -1)
				//if (m_anMap[i][j] != -1)
			{
				m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemW, &m_dcMask, 0, gameControl->GetElement(i, j) * nElemH, SRCPAINT);
				m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemW, &m_dcElement, 0, gameControl->GetElement(i, j) * nElemH, SRCAND);
			}
		}
	dcMap.SelectObject(&p_Old);
}

void MainGameDlg::DrawTipFrame(int x, int y)
{
	CClientDC dc(this);

	HGDIOBJ p_OldPen;
	CPen p_NewPen(PS_SOLID, 1, RGB(255, 0, 0));
	CBrush br;
	br.CreateStockObject(NULL_BRUSH);
	p_OldPen = dc.SelectObject(p_NewPen);
	dc.SelectObject(br);
	dc.Rectangle(m_rtGameRect.left + y * m_sizeElem.cy, m_rtGameRect.top + x * m_sizeElem.cx, m_rtGameRect.left + m_sizeElem.cy + y * m_sizeElem.cy, m_rtGameRect.top + m_sizeElem.cx + x * m_sizeElem.cx);
	//m_dcMem.Rectangle(50 + nCol * 40, 50 + nRow * 40, 90 + nCol * 40, 90 + nRow * 40);

	m_dcMem.SelectObject(p_OldPen);
}

void MainGameDlg::DrawTipLine(Vertex m_ptSelFirst, Vertex m_ptSelSec)
{
	CClientDC dc(this);
	CPen p_NewPen(PS_SOLID, 10, RGB(0, 255, 0));
	HGDIOBJ p_OldPen;
	p_OldPen = dc.SelectObject(p_NewPen);
	CPoint first(m_ptGameTop.x + m_ptSelFirst.y * m_sizeElem.cy + m_sizeElem.cy / 2, m_ptGameTop.y + m_ptSelFirst.x * m_sizeElem.cx + m_sizeElem.cx / 2);//选中的第二个点
	CPoint sec(m_ptGameTop.x + m_ptSelSec.y * m_sizeElem.cy + m_sizeElem.cy / 2, m_ptGameTop.y + m_ptSelSec.x * m_sizeElem.cx + m_sizeElem.cx / 2);//游戏区起始点
	dc.MoveTo(first);
	dc.LineTo(sec);
	dc.SelectObject(p_OldPen);
	//Invalidate(0);
}

void MainGameDlg::DrawTipLine(stack<Vertex> path)
{
	CClientDC dc(this);
	CPen p_NewPen(PS_SOLID, 10, RGB(0, 255, 0));
	HGDIOBJ p_OldPen;
	p_OldPen = dc.SelectObject(p_NewPen);
	Vertex m_ptSelFirst;
	Vertex m_ptSelSec;
	int num = (int)path.size() - 1;
	for (int i = 0; i < num; i++)
	{
		m_ptSelFirst = path.top();
		path.pop();
		m_ptSelSec = path.top();

		CPoint first(m_ptGameTop.x + m_ptSelFirst.y * m_sizeElem.cy + m_sizeElem.cy / 2, m_ptGameTop.y + m_ptSelFirst.x * m_sizeElem.cx + m_sizeElem.cx / 2);//选中的第二个点
		CPoint sec(m_ptGameTop.x + m_ptSelSec.y * m_sizeElem.cy + m_sizeElem.cy / 2, m_ptGameTop.y + m_ptSelSec.x * m_sizeElem.cx + m_sizeElem.cx / 2);//游戏区起始点
		dc.MoveTo(first);
		dc.LineTo(sec);
	}

	dc.SelectObject(p_OldPen);
}
void MainGameDlg::DrawGameTime()
{
	CRect rect;
	GetClientRect(&rect);
	CClientDC dc(this);
	//CClientDC dc(this);
	CFont new_font;
	HGDIOBJ p_OldFont;
	new_font.CreateFontW(40, 20, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("宋体"));
	//new_font.CreatePointFont(1, _T("宋体"),&dc);
	p_OldFont = dc.SelectObject(new_font);
	dc.SetTextColor(RGB(0, 255, 0));
	int pos = m_GameProgress.GetPos();
	char time[10];
	_itoa_s(pos, time, 10, 10);
	//TCHAR time(pos);
	CString strWel = _T("Welcome to LinkGame");
	SIZE size;
	size = dc.GetTextExtent(strWel, 100);
	int x = 665;
	int y = 523;
	CString strWel1(time);
	dc.TextOut(x, y, strWel1);
	//dc.TextOutW(x, y, strWel1);
	//dc.SelectObject(p_OldFont);

}
void MainGameDlg::DrawGameGrade()
{
	int nGrade = gameControl->GetGrade();
	CClientDC dc(this);
	CFont new_font;
	HGDIOBJ p_OldFont;
	new_font.CreateFontW(30, 15, 0, 0, FW_NORMAL, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("宋体"));
	//new_font.CreatePointFont(1, _T("宋体"),&dc);
	p_OldFont = dc.SelectObject(new_font);
	dc.SetTextColor(RGB(0, 255, 0));
	char grade[10];
	_itoa_s(nGrade, grade, 10, 10);
	CString strWel1(grade);
	//	CRect rect;
	//	GetDlgItem(IDC_STATIC_SCRORE)->GetWindowRect(&rect);
	GetDlgItem(IDC_STATIC_SCORE)->SetFont(&new_font);
	GetDlgItem(IDC_STATIC_SCORE)->SetWindowText(strWel1);

	//dc.TextOut(705, 405, strWel1);
	//dc.SelectObject(p_OldFont);



}
void MainGameDlg::ChangePropNum()
{

	char grade[10];
	_itoa_s(gameControl->GetPropNum(), grade, 10, 10);
	CString strWell1("道具×");
	CString strWell2(grade);
	strWell1.Append(strWell2);
	GetDlgItem(IDC_BUTTON_PROP)->SetWindowText(strWell1);


}
void MainGameDlg::CalGameGrade()
{
	if (m_flag.Score == true)
	{
		int aGrade = gameControl->GetGrade();
		GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PROP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PROP)->SetWindowTextW(_T("道具"));

		if (aGrade >= 20)
		{
			GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(TRUE);
		}
		if (aGrade >= 50)
		{
			GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(TRUE);
		}
		if (gameControl->GetPropNum() != 0)
		{
			GetDlgItem(IDC_BUTTON_PROP)->EnableWindow(TRUE);
		}
	}


}
int MainGameDlg::JudgeWin()
{
	bool flag = gameControl->IsWin();
	if (gameControl->IsWin())
	{
		KillTimer(PLAY_TIME_ID);
		m_bPlaying = false;
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_RELAX)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);

		RemindGameDlg remindGameDlg(GAME_SUCCESS);
		remindGameDlg.DoModal();

		if (m_flag.Score == TRUE)
		{
			RemindSaveDlg saveDlg;
			if (saveDlg.DoModal())
				gameControl->SaveScore();
		}
		return GAME_SUCCESS;
	}
	int time = m_GameProgress.GetPos();
	if (time == 0 && m_flag.Timer == true)
	{
		m_bPlaying = false;

		GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_RELAX)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
		//提示失败
		RemindGameDlg remindGameDlg(GAME_LOSE);
		//remindGameDlg.flag = GAME_LOSE;
		remindGameDlg.DoModal();
		if (m_flag.Score == TRUE)
		{
			RemindSaveDlg saveDlg;
			if (saveDlg.DoModal())
				gameControl->SaveScore();
		}
		return  GAME_LOSE;
	}
	return GAME_PLAY;
}
void MainGameDlg::UpdateTheme()
{
	CString elemPath = configLogic.GetElemPath();
	CString maskPath = configLogic.GetMaskPath();
	//获得当前对话框的视频内存
	CClientDC dc(this);
	//加载BMP图片资源
	HANDLE hBmp1 = ::LoadImageW(NULL, elemPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存相兼容的内存pc
	//m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(hBmp1);

	HANDLE hBmp2 = ::LoadImageW(NULL, maskPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hBmp2);
	if (m_bPlaying == true)
		UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE);
}
void MainGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonUp(nFlags, point);

	if (point.y < m_ptGameTop.y || point.x < m_ptGameTop.x)
		return 	CDialogEx::OnLButtonUp(nFlags, point);

	//int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	//int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	//x为row y为col
	int y = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	int x = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	if (y > MAX_COL - 1 || x > MAX_ROW - 1)
		return 	CDialogEx::OnLButtonUp(nFlags, point);
	if (gameControl->GetElement(x, y) == -1)
		return;

	if (m_bFirstPoint == true)
	{
		DrawTipFrame(x, y);
		gameControl->SetFirstPoint(x, y);
		//	m_ptSelFirst.x = x;
		//	m_ptSelFirst.y = y;
		m_bFirstPoint = false;
	}
	else
	{
		m_bFirstPoint = true;
		DrawTipFrame(x, y);
		gameControl->SetSecPoint(x, y);
		stack<Vertex> path;
		if (m_bProp)
		{
			path.push(gameControl->GetFirstVertex());
			path.push(gameControl->GetFirstVertex());
			m_bProp = gameControl->PropLink();
			DrawTipLine(path);
			UpdateMap();
			m_bProp = false;
		}
		else
		{
			if (gameControl->Link(path))
			{
				if (m_flag.Score == TRUE)
				{
					CalGameGrade();
					DrawGameGrade();
				}
				DrawTipLine(path);
				UpdateMap();
			}
		}
		CalGameGrade();
		ChangePropNum();
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
		if (JudgeWin() != 1)
		{

		}
		//GetDlgItem(IDC_BUTTON_SETTING)->EnableWindow(TRUE);
	}

}


void MainGameDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码

	if (m_flag.Timer == true && m_flag.Score == false)//基本模式
	{
		m_GameProgress.SetRange(0, 300);
		m_GameProgress.SetPos(300);
		m_GameProgress.SetStep(-1);
		m_GameProgress.StepIt();

		SetTimer(PLAY_TIME_ID, 1000, NULL);
		GetDlgItem(IDC_GAME_TIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(TRUE);
	}
	else if (m_flag.Score == true && m_flag.Timer == false)//娱乐模式
	{
		GetDlgItem(IDC_STATIC_SCORE)->ShowWindow(SW_SHOW);
		DrawGameGrade();
		GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PROP)->EnableWindow(FALSE);
	}
	else if (m_flag.Timer == true && m_flag.Score == true)//关卡模式
	{
		m_GameProgress.SetRange(0, 300);
		m_GameProgress.SetPos(300);
		m_GameProgress.SetStep(-1);
		m_GameProgress.StepIt();
		SetTimer(PLAY_TIME_ID, 1000, NULL);
		GetDlgItem(IDC_GAME_TIME)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PROP)->EnableWindow(FALSE);
	}
	//GetDlgItem(IDC_BUTTON_SETTING)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RELAX)->EnableWindow(TRUE);
	m_bPlaying = true;
	gameControl->StartGame();

	UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE);
	//Invalidate(0);//使窗口无效，重绘窗口
}


void MainGameDlg::OnBnClickedButtonPrompt()
{
	// TODO: 在此添加控件通知处理程序代码

	stack<Vertex> s;
	gameControl->Help(s);
	DrawTipLine(s);
	UpdateMap();
	Sleep(200);

	if (m_flag.Score == TRUE)
	{
		CalGameGrade();
		DrawGameGrade();
	}
	InvalidateRect(m_rtGameRect, FALSE);

	//Invalidate(0);//使窗口无效，重绘窗口

	//InvalidateRect(m_rtGameRect, FALSE);
	/*if (gameControl.IsWin())
	{
		m_bPlaying = false;
		GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_RELAX)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
	}*/
}


void MainGameDlg::OnBnClickedButtonReset()
{
	gameControl->Reset();
	UpdateMap();

	if (m_flag.Score == TRUE)
	{
		CalGameGrade();
		DrawGameGrade();
	}
	InvalidateRect(m_rtGameRect, FALSE);

}


void MainGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == PLAY_TIME_ID && m_bPlaying && m_bPause == false)
	{
		DrawGameTime();
		//Invalidate(0);//使窗口无效，重绘窗口

		m_GameProgress.StepIt();
		JudgeWin();

	}
	CDialogEx::OnTimer(nIDEvent);
}


void MainGameDlg::OnBnClickedButtonRelax()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bPlaying == false)
		return;
	if (m_bPause == false)
	{
		int nTop = m_ptGameTop.y;
		int nLeft = m_ptGameTop.x;
		int nElemW = m_sizeElem.cx;
		int nElemH = m_sizeElem.cy;
		GetDlgItem(IDC_BUTTON_RELAX)->SetWindowTextW(_T("继续游戏"));
		GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
		m_bPause = true;
		m_dcMem.BitBlt(nLeft, nTop, MAX_COL * nElemW, MAX_ROW * nElemH, &m_dcPause, nLeft, nTop, SRCCOPY);
		//m_dcPause.BitBlt(0, 0, 600, 500, &m_dcPause, 0, 0, SRCCOPY);
		InvalidateRect(m_rtGameRect, FALSE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_RELAX)->SetWindowTextW(_T("暂停游戏"));
		if (m_flag.Timer == false && gameControl->GetGrade() == 0)//娱乐模式
		{
			GetDlgItem(IDC_STATIC_SCORE)->ShowWindow(SW_SHOW);
			DrawGameGrade();
			GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_PROP)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(TRUE);
			GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(TRUE);
		}
		UpdateMap();
		InvalidateRect(m_rtGameRect, FALSE);
		m_bPause = false;
	}
}


void MainGameDlg::OnBnClickedButtonHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	HelpDlg helpDialog;
	helpDialog.DoModal();
}


void MainGameDlg::OnBnClickedButtonProp()
{
	m_bProp = true;
	if (m_flag.Score == TRUE)
	{
		CalGameGrade();
		DrawGameGrade();
	}
}


void MainGameDlg::OnBnClickedButtonVic()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(PLAY_TIME_ID);
	m_bPlaying = false;
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_RELAX)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_PROMPT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RESET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SETTING)->EnableWindow(TRUE);

	//RemindGameDlg remindGameDlg(GAME_SUCCESS);
	//remindGameDlg.DoModal();
	MessageBox(_T("游戏结束"));
	if (m_flag.Score == TRUE)
	{
		RemindSaveDlg saveDlg;
		saveDlg.DoModal();
		if (saveDlg.ok == true)
		{
			gameControl->SaveScore();
		}
	}
	gameControl->ClearAll();
	UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE);
}


void MainGameDlg::OnBnClickedButtonSetting()
{
	SettingDlg settingDlg;
	if (settingDlg.DoModal() == IDOK)
	{
		UpdateTheme();
	}
	// TODO: 在此添加控件通知处理程序代码
}




void MainGameDlg::OnBnClickedButtonMusic()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_bMusic == false)
	{
		GetDlgItem(IDC_BUTTON_MUSIC)->SetWindowTextW(_T("音乐关"));

		m_bMusic = true;
		CString strFileName = configLogic.GetMusicPath();
		CString strCommond;
		strCommond.Format(_T("open %s alias bgm"), strFileName);
		mciSendString(strCommond, NULL, 0, NULL);
		mciSendString(L"play bgm repeat", NULL, 0, NULL);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_MUSIC)->SetWindowTextW(_T("音乐开"));
		m_bMusic = false;
		mciSendString(_T("close bgm"), NULL, 0, m_hWnd);
	}

}
