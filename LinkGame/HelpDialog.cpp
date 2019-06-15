// HelpDialog.cpp: 实现文件
//

#include "pch.h"
#include "LinkGame.h"
#include "HelpDialog.h"
#include "afxdialogex.h"


// HelpDialog 对话框

IMPLEMENT_DYNAMIC(HelpDlg, CDialogEx)

HelpDlg::HelpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
{
	pos = 0;
}

HelpDlg::~HelpDlg()
{
}

void HelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_horiScrollbar);
}


BEGIN_MESSAGE_MAP(HelpDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// HelpDialog 消息处理程序


BOOL HelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CClientDC dc(this);
	HANDLE hBmpHelp = ::LoadImageW(NULL, TEXT("sources\\help.bmp"), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR | LR_CREATEDIBSECTION| LR_LOADFROMFILE);
	
	CRect dlgRect;
	GetWindowRect(dlgRect);
	m_rtHelp.left = 0;
	m_rtHelp.top = 0;
	m_rtHelp.bottom = dlgRect.Height() - 100;
	m_rtHelp.right = dlgRect.Width();

	m_dcHelp.CreateCompatibleDC(&dc);
	m_dcHelp.SelectObject(hBmpHelp);


	CRect rtClient;
	this->GetWindowRect(&rtClient);
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, rtClient.Width(), rtClient.Height());
	m_dcMem.SelectObject(&bmpMem);

	m_dcMem.BitBlt(0, 0, rtClient.Width(), rtClient.Height(), NULL, 0, 0, WHITENESS); 

	//this->GetDlgItem(IDC_STATIC_HELP)->GetWindowRect(&m_rtHelp);
	//this->ScreenToClient(&m_rtHelp);

	UpdateHelp(0);

	CBitmap bmpHelp;
	bmpHelp.Attach(hBmpHelp);
	BITMAP bmpInfo;
	bmpHelp.GetBitmap(&bmpInfo);

	((CScrollBar*)this->GetDlgItem(IDC_SCROLLBAR1))->SetScrollRange(0, bmpInfo.bmHeight);

	CBitmap bitmap;
	HGDIOBJ temp;
	bitmap.LoadBitmapW(IDB_BITMAP_HELP);
	//m_dcMem.CreateCompatibleDC(&m_dcMem);
	temp = m_dcMem.SelectObject(hBmpHelp);	// TODO:  在此添加额外的初始化


	/*BITMAP bgPicture;
	CRect rect;
	GetClientRect(&rect);
	m_rtHelp.SetRect(rect.left+10, rect.top+10, rect.right - 40, rect.bottom - 40);


	m_horiScrollbar.SetScrollRange(0, 100);
	m_horiScrollbar.SetScrollPos(0);
	//初始化背景
	CBitmap bitmap;
	HGDIOBJ temp;
	bitmap.LoadBitmapW(IDB_BITMAP_HELP);
	m_dcMem.CreateCompatibleDC(&m_dcMem);
	bitmap.GetBitmap(&bgPicture);
	temp = m_dcMem.SelectObject(bitmap);	// TODO:  在此添加额外的初始化

	UpdateHelp(0);*/
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void HelpDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(&rect);

	dc.BitBlt(0,0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcMem, 0, 0, SRCCOPY);
	//UpdateHelp(0);

}


void HelpDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int minpos = 0;
	int maxpos = 0;
	m_horiScrollbar.GetScrollRange(&minpos, &maxpos);
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nSBCode)
	{
	case SB_LINEUP:
		pos = pos - 1 >= 0 ? pos - 1 : pos;
		break;
	case SB_LINEDOWN:
		pos += 1;
		break;
	case SB_PAGEUP:
		pos -= 10;
		break;
	case SB_PAGEDOWN:
		pos += 10;
		break;
	case SB_TOP:
		pos = minpos;
		break;
	case SB_BOTTOM:
		pos = maxpos;
		break;
	case SB_THUMBPOSITION:
		pos = nPos;
		break;
	default:
		break;
	}
	m_horiScrollbar.SetScrollPos(pos, TRUE);
	UpdateHelp(pos);
	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);

}

void HelpDlg::UpdateHelp(int pos)
{
	m_dcMem.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), NULL, 0, 0, WHITENESS);
	m_dcMem.BitBlt(0, 0, m_rtHelp.Width(), m_rtHelp.Height(), &m_dcHelp, 0, pos, SRCCOPY);
	InvalidateRect(m_rtHelp, FALSE);

}


HBRUSH HelpDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	int a =pWnd->GetDlgCtrlID();
	if (a == IDC_STATIC_COPYRIGHT)
	{
		COLORREF clr = RGB(255, 255, 255);
		HBRUSH bkBrush = ::CreateSolidBrush(clr);
		return bkBrush;
	}
	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
