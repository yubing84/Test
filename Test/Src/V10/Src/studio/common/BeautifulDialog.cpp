// DesignDlgDlg.cpp : implementation file
//

#include "../main_frame/StdAfx.h"
#include "BeautifulDialog.h"
#include "../main_frame/Resource.h"

const COLORREF TEXT_COLOR = RGB(13, 125, 188);
const COLORREF BK_COLOR = RGB(208, 212, 221);
const COLORREF TITLE_COLOR = RGB(191, 217, 227);

// CBeautifulDialog dialog

IMPLEMENT_DYNAMIC(CBeautifulDialog, CDialog)

CBeautifulDialog::CBeautifulDialog(UINT ID, CWnd* pParent /* = NULL */)
	: CDialog(ID, pParent)
{
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_crBK = BK_COLOR;
	m_clText = TEXT_COLOR;
  m_clTitle = TITLE_COLOR;

	m_nTitleBtnCX = 0;
	m_nTitleBtnCY = 0;
	m_MinPT.x = 30;
	m_MinPT.y = 1;
	m_MaxPT.x = 55;
	m_MaxPT.y = 1;
	m_ClosePT.x = 80;
	m_ClosePT.y = 1;
	m_bFirstDraw = FALSE;
	
	CBitmap Bmp;
	Bmp.LoadBitmap(IDB_RIGHTTITLE);
	BITMAP bmpInfo;
	Bmp.GetObject(sizeof(BITMAP), &bmpInfo);
	m_nRightTitleCX = bmpInfo.bmWidth;
	Bmp.DeleteObject();
	//�����������ť�Ŀ�Ⱥ͸߶�
	BOOL bLoad = Bmp.LoadBitmap(IDB_CLOSEBTN);
	if (bLoad)
	{
		BITMAP bmpInfo;
		Bmp.GetBitmap(&bmpInfo);
		m_nTitleBtnCX = bmpInfo.bmWidth;
		m_nTitleBtnCY = bmpInfo.bmHeight;
		
		Bmp.DeleteObject();
	}	
	m_BtnState = BS_NONE;
	m_bMaxed = TRUE;

  m_brBkgnd.CreateSolidBrush(m_crBK);
  m_brControlBkgnd1.CreateSolidBrush(RGB(18,222,193));
  m_brControlBkgnd2.CreateSolidBrush(RGB(244,222,43));

  m_bEnableMaxsize = false;
  m_bInitOK = false;
}

void CBeautifulDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBeautifulDialog, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCACTIVATE()
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_NCMOUSEMOVE()
	ON_WM_MOUSEMOVE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCLBUTTONDBLCLK()
	ON_WM_NCCALCSIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBeautifulDialog message handlers

BOOL CBeautifulDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here
  //GetWindowText(m_csText);
  //CDialog::SetWindowText("");
  //SetWindowText(m_csText);

  LONG style = GetWindowLong(GetSafeHwnd(), GWL_STYLE);
  m_bEnableMaxsize = static_cast<bool>(style & WS_MAXIMIZEBOX);

  m_bInitOK = true;
//  SendMessage(WM_SIZE);

  return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBeautifulDialog::OnPaint() 
{
  if (IsIconic())
  {
    CPaintDC dc(this); // device context for painting

    SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;

    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  }
  else
  {
    CDialog::OnPaint();
  }

  DrawDialog();
  m_bFirstDraw = TRUE;
}

//���öԻ������
void CBeautifulDialog::SetWindowText(CString csText)
{
	m_csText = csText;
	//���Ʊ������ı�
	DrawTitlebarText();
}

//���Ʊ������ı�
void CBeautifulDialog::DrawTitlebarText()
{
	if (!m_csText.IsEmpty())
	{
		CDC* pDC = GetWindowDC();
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(m_clTitle);
		pDC->SetTextAlign(TA_CENTER);
		CRect rect;
		GetClientRect(rect);
		//��ȡ�ı��߶�
		CSize szText = pDC->GetTextExtent(m_csText);

		pDC->TextOut(rect.Width() / 2, (m_nTitleBarCY - szText.cy) / 2, m_csText);	
		ReleaseDC(pDC);
	}
}

//���ƶԻ���
void CBeautifulDialog::DrawDialog(int nFlag)
{
	int nFrameCY = GetSystemMetrics(SM_CYFIXEDFRAME);
	int nFrameCX = GetSystemMetrics(SM_CXFIXEDFRAME);
	//��ȡ�Ի����Ƿ��б߿�
	if (GetStyle() & WS_BORDER) 
	{
		m_nBorderCY = GetSystemMetrics(SM_CYBORDER) + nFrameCY;
		m_nBorderCX = GetSystemMetrics(SM_CXBORDER)	+ nFrameCX;		
	}
	else
	{
		m_nBorderCY =  nFrameCY;
		m_nBorderCX =  nFrameCX;			
	}
	//����������߶�
	m_nTitleBarCY = GetSystemMetrics(SM_CYCAPTION) + m_nBorderCY;

	CRect ClientRC;
	GetClientRect(ClientRC);
	CRect WinRC, FactRC;
	GetWindowRect(WinRC);
	FactRC.CopyRect(CRect(0, 0, WinRC.Width(), WinRC.Height()));
	//��ȡ�����豸������
	CWindowDC WindowDC(this);

	CBitmap Bmp;
	BITMAPINFO bmpInfo;
	
	CDC memDC;
	memDC.CreateCompatibleDC(&WindowDC);
	
	//���ƶԻ�����߿�λͼ
	if (nFlag & LEFTBAR)
	{
		Bmp.LoadBitmap(IDB_LEFTBAND);
		memDC.SelectObject(&Bmp);
		Bmp.GetObject(sizeof(BITMAPINFO), &bmpInfo);
		int nBmpCX = bmpInfo.bmiHeader.biWidth;
		int nBmpCY = bmpInfo.bmiHeader.biHeight;

		WindowDC.StretchBlt(0, m_nTitleBarCY, m_nBorderCX, FactRC.Height() - m_nTitleBarCY, 
			&memDC, 0, 0, nBmpCX, nBmpCY, SRCCOPY);
		Bmp.DeleteObject();
	}

	//��¼����������ұ�����λͼ�Ŀ��
	int nLeftBmpCX = 0;
	int nRightBmpCX = 0;
	//���������������
	if (nFlag & LEFTTITLE)
	{
		Bmp.LoadBitmap(IDB_LEFTTITLE);
		memDC.SelectObject(&Bmp);
		Bmp.GetObject(sizeof(BITMAPINFO), &bmpInfo);
		int nBmpCX = bmpInfo.bmiHeader.biWidth;
		int nBmpCY = bmpInfo.bmiHeader.biHeight;
		nLeftBmpCX = nBmpCX;
		WindowDC.StretchBlt(0, 0, nBmpCX, m_nTitleBarCY, 
			&memDC, 0, 0, nBmpCX, nBmpCY, SRCCOPY);
		Bmp.DeleteObject();
	}
	//�����ұ���������
	if (nFlag & RIGHTTITLE)
	{
		Bmp.LoadBitmap(IDB_RIGHTTITLE);
		memDC.SelectObject(&Bmp);
		Bmp.GetObject(sizeof(BITMAPINFO), &bmpInfo);
		int nBmpCX = bmpInfo.bmiHeader.biWidth;
		int nBmpCY = bmpInfo.bmiHeader.biHeight;
		nRightBmpCX = nBmpCX;
		m_nRightTitleCX = nRightBmpCX;
		int nOrgX = FactRC.Width() - nBmpCX;

		m_TitleBarRC.CopyRect(CRect(FactRC.Width() - nBmpCX, 0, FactRC.right, m_nTitleBarCY)  );
		WindowDC.StretchBlt(nOrgX, 0, nBmpCX, m_nTitleBarCY, 
							&memDC, 0, 0, nBmpCX, nBmpCY, SRCCOPY);
		Bmp.DeleteObject();		
	}
	//�����м����������
	if (nFlag & MIDTITLE)
	{
		Bmp.LoadBitmap(IDB_MIDTITLE);
		memDC.SelectObject(&Bmp);
		Bmp.GetObject(sizeof(BITMAPINFO), &bmpInfo);
		int nBmpCX = bmpInfo.bmiHeader.biWidth;
		int nBmpCY = bmpInfo.bmiHeader.biHeight;

		int nMidStreatch = FactRC.Width()-nLeftBmpCX-nRightBmpCX;

		WindowDC.StretchBlt(nLeftBmpCX, 0, nMidStreatch, m_nTitleBarCY, 
							&memDC, 0, 0, nBmpCX, nBmpCY, SRCCOPY);
		Bmp.DeleteObject();			
	}
	//���ƶԻ����ұ߿�
	if (nFlag & RIGHTBAR)
	{
		Bmp.LoadBitmap(IDB_RIGHTBAND);
		memDC.SelectObject(&Bmp);
		Bmp.GetObject(sizeof(BITMAPINFO), &bmpInfo);
		int nBmpCX = bmpInfo.bmiHeader.biWidth;
		int nBmpCY = bmpInfo.bmiHeader.biHeight;
		nLeftBmpCX = nBmpCX;
		WindowDC.StretchBlt(FactRC.Width()-m_nBorderCX, m_nTitleBarCY, m_nBorderCX, 
							FactRC.Height()-m_nTitleBarCY, &memDC, 0, 0, nBmpCX, nBmpCY, SRCCOPY);
		Bmp.DeleteObject();
	}
	//���ƶԻ���ױ߿�
	if (nFlag & BOTTOMBAR)
	{	
		Bmp.LoadBitmap(IDB_BOTTOMBAND);
		memDC.SelectObject(&Bmp);
		Bmp.GetObject(sizeof(BITMAPINFO), &bmpInfo);
		int nBmpCX = bmpInfo.bmiHeader.biWidth;
		int nBmpCY = bmpInfo.bmiHeader.biHeight;
		nLeftBmpCX = nBmpCX;
		WindowDC.StretchBlt(m_nBorderCX, FactRC.Height()-m_nBorderCY, FactRC.Width()-2*m_nBorderCX,
							m_nBorderCY, &memDC, 0, 0, nBmpCX, nBmpCY, SRCCOPY);
		Bmp.DeleteObject();
	}
	//������С����ť
	if (nFlag & MINBUTTON)
	{
		Bmp.LoadBitmap(IDB_MINBTN);
		memDC.SelectObject(&Bmp);
		Bmp.GetObject(sizeof(BITMAPINFO), &bmpInfo);
		int nBmpCX = bmpInfo.bmiHeader.biWidth;
		int nBmpCY = bmpInfo.bmiHeader.biHeight;
		WindowDC.StretchBlt(m_MinRC.left, m_MinRC.top, m_MinRC.Width(), 
							m_MinRC.Height(), &memDC, 0, 0, nBmpCX, nBmpCY, SRCCOPY);
		Bmp.DeleteObject();		
	}
	//������󻯰�ť
	if (nFlag & MAXBUTTON)
	{
		Bmp.LoadBitmap(IDB_MAXBTN);
		memDC.SelectObject(&Bmp);
		Bmp.GetObject(sizeof(BITMAPINFO), &bmpInfo);
		int nBmpCX = bmpInfo.bmiHeader.biWidth;
		int nBmpCY = bmpInfo.bmiHeader.biHeight;
		WindowDC.StretchBlt(m_MaxRC.left, m_MaxRC.top, m_MaxRC.Width(), 
							m_MaxRC.Height(), &memDC, 0, 0, nBmpCX, nBmpCY, SRCCOPY);
		Bmp.DeleteObject();	
	}
	//���ƹرհ�ť
	if (nFlag & CLOSEBUTTON)
	{
		Bmp.LoadBitmap(IDB_CLOSEBTN);
		memDC.SelectObject(&Bmp);
		Bmp.GetObject(sizeof(BITMAPINFO), &bmpInfo);
		int nBmpCX = bmpInfo.bmiHeader.biWidth;
		int nBmpCY = bmpInfo.bmiHeader.biHeight;
		WindowDC.StretchBlt(m_CloseRC.left, m_CloseRC.top, m_CloseRC.Width(), 
							m_CloseRC.Height(), &memDC, 0, 0, nBmpCX, nBmpCY, SRCCOPY);
		Bmp.DeleteObject();	
	}
	//����������ı�
	DrawTitlebarText();
}

BOOL CBeautifulDialog::OnNcActivate(BOOL bActive) 
{
	OnPaint();		
	return TRUE; //CDialog::OnNcActivate(bActive);
}

void CBeautifulDialog::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	int nFrameCY = GetSystemMetrics(SM_CYFIXEDFRAME);
	int nFrameCX = GetSystemMetrics(SM_CXFIXEDFRAME);
	//��ȡ�Ի����Ƿ��б߿�
	if (GetStyle() & WS_BORDER) 
	{
		m_nBorderCY = GetSystemMetrics(SM_CYBORDER) + nFrameCY;
		m_nBorderCX = GetSystemMetrics(SM_CXBORDER)	+ nFrameCX;		
	}
	else
	{
		m_nBorderCY =  nFrameCY;
		m_nBorderCX =  nFrameCX;			
	}
	//������������
	m_nTitleBarCY = GetSystemMetrics(SM_CYCAPTION) + m_nBorderCY;

	CRect ClientRC;
	GetClientRect(ClientRC);	//��ȡ�ͻ�����

	CRect WinRC;
	GetWindowRect(WinRC);

	m_MinRC.left = m_MinPT.x + WinRC.Width() - m_nRightTitleCX;
	m_MinRC.right = m_nTitleBtnCX + m_MinRC.left;
	m_MinRC.top = (m_nTitleBarCY - m_nTitleBtnCY) / 2 + m_MinPT.y;
	m_MinRC.bottom = m_MinRC.top + m_nTitleBtnCY;

	m_MaxRC.left = m_MaxPT.x + WinRC.Width() - m_nRightTitleCX;
	m_MaxRC.right = m_nTitleBtnCX + m_MaxRC.left;
	m_MaxRC.top = (m_nTitleBarCY - m_nTitleBtnCY) / 2 + m_MaxPT.y;
	m_MaxRC.bottom = m_MaxRC.top + m_nTitleBtnCY;	

	m_CloseRC.left = m_ClosePT.x + WinRC.Width() - m_nRightTitleCX;
	m_CloseRC.right = m_nTitleBtnCX + m_CloseRC.left;
	m_CloseRC.top = (m_nTitleBarCY - m_nTitleBtnCY) / 2 + m_ClosePT.y;
	m_CloseRC.bottom = m_CloseRC.top + m_nTitleBtnCY;	

  // �����ڲ��ؼ�����
  if(m_bInitOK)
    AutoAdjustLayout();
	
	Invalidate();	//������������	
}

HBRUSH CBeautifulDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	//HBRUSH hbr;
	//if (nCtlColor==CTLCOLOR_DLG)
	//{
	//	//����һ��λͼ��ˢ
	//	CBrush m_Brush(m_crBK);
	//	CRect rect;
	//	GetClientRect(rect);
	//	//ѡ�л�ˢ
	//	pDC->SelectObject(&m_Brush);
	//	//���ͻ�����
	//	pDC->FillRect(rect, &m_Brush);
	//	return m_Brush;
	//}
	//else
	//	hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	//return hbr;

  HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
  pDC->SetTextColor(m_clText);
  pDC->SetBkMode(TRANSPARENT);
  return hbr;

#if 0
  TCHAR szClassName[64];

  ::GetClassName(pWnd->GetSafeHwnd(),szClassName,64);
  if(lstrcmpi(szClassName,_T("Static")) == 0)   // Static�ؼ���������
  {
    pDC->SetTextColor(m_clText);
    pDC->SetBkMode(TRANSPARENT);
    // return (HBRUSH)m_brBkgnd;
          return hbr;

    //DWORD dwStyle = pWnd->GetStyle();
    //if((dwStyle & ES_MULTILINE)  == ES_MULTILINE) //����edit�ؼ�
    //{
    //  pDC->SetTextColor(m_clText);
    //  return hbr;
    //}
    //else
    //{
    //  pDC->SetTextColor(m_clText);
    //  pDC->SetBkMode(TRANSPARENT);

    //  return hbr;
    //  return (HBRUSH)m_brBkgnd;
    //}
  }
  else //���Ǳ༭�ؼ�
  {
    //if(pWnd->GetDlgCtrlID() == IDC_STC_REDTEXT)
    //{
    //  pDC->SetTextColor(RGB(255,0,0));
    //  pDC->SetBkMode(TRANSPARENT);
    //  return (HBRUSH)m_brBkgnd;
    //}
    //else if(pWnd->GetDlgCtrlID() == IDC_STC_BLUETEXT)
    //{
    //  pDC->SetTextColor(RGB(0,0,255));
    //  pDC->SetBkMode(TRANSPARENT);
    //  return (HBRUSH)m_brBkgnd;
    //}
    //else if(pWnd->GetDlgCtrlID() == IDC_STC_BLUETEXTWHITEBACK)
    //{
    //  pDC->SetTextColor(RGB(0,0,255));
    //  pDC->SetBkMode(TRANSPARENT);
    //  return (HBRUSH)m_brControlBkgnd1;
    //}
    //else if(pWnd->GetDlgCtrlID() == IDC_CHK_GREEN)
    //{
    //  pDC->SetTextColor(RGB(0,255,0));
    //  pDC->SetBkMode(TRANSPARENT);
    //  return (HBRUSH)m_brBkgnd;
    //}
    //else if(pWnd->GetDlgCtrlID() == IDC_RAD_BLUE)
    //{
    //  pDC->SetTextColor(RGB(0,0,255));
    //  pDC->SetBkMode(TRANSPARENT);
    //  return (HBRUSH)m_brBkgnd;
    //}
    //else if(pWnd->GetDlgCtrlID() == IDC_CHK_GREEN2)
    //{
    //  pDC->SetTextColor(RGB(0,255,0));
    //  pDC->SetBkMode(TRANSPARENT);
    //  return (HBRUSH)m_brControlBkgnd2;
    //}
    //else if(pWnd->GetDlgCtrlID() == IDC_RADIO2)
    //{
    //  pDC->SetTextColor(RGB(0,0,255));
    //  pDC->SetBkMode(TRANSPARENT);
    //  return (HBRUSH)m_brControlBkgnd2;
    //}
    //else
    {
      pDC->SetTextColor(m_clText);
      pDC->SetBkMode(TRANSPARENT);
      return hbr;
    }
  }
#endif
}

//����ڷǿͻ������ƶ�
void CBeautifulDialog::OnNcMouseMove(UINT nHitTest, CPoint point) 
{
	CRect MinRC, MaxRC, CloseRC, ClientRC;
	CWindowDC WindowDC (this);
	CDC memDC;
	memDC.CreateCompatibleDC(&WindowDC);

	BITMAPINFO bmpInfo;
	CBitmap Bmp;
	int nBmpCX, nBmpCY;
	GetWindowRect(ClientRC);

	MinRC.CopyRect(CRect(m_MinRC.left + ClientRC.left, ClientRC.top + m_MinRC.top, 
					m_MinRC.right + ClientRC.left,
					m_MinRC.bottom + m_MinRC.top + ClientRC.top));
	MaxRC.CopyRect(CRect(m_MaxRC.left + ClientRC.left, ClientRC.top + m_MaxRC.top,
					m_MaxRC.right + ClientRC.left,
					m_MaxRC.bottom + m_MaxRC.top + ClientRC.top));
	CloseRC.CopyRect(CRect(m_CloseRC.left + ClientRC.left, ClientRC.top + m_CloseRC.top, 
					m_CloseRC.right + ClientRC.left,
					m_CloseRC.bottom + m_CloseRC.top + ClientRC.top));

	if(MinRC.PtInRect(point)) //�������С����ť���ƶ�ʱ,���İ�ť��ʾ��λͼ
	{
		if (m_BtnState!= BS_MIN)
		{
			Bmp.LoadBitmap(IDB_MINHOTBTN);
			Bmp.GetObject(sizeof(bmpInfo), &bmpInfo);
			
			nBmpCX = bmpInfo.bmiHeader.biWidth;
			nBmpCY = bmpInfo.bmiHeader.biHeight;
			memDC.SelectObject(&Bmp);
			WindowDC.StretchBlt(m_MinRC.left, m_MinRC.top, m_MinRC.Width(), 
				m_MinRC.Height(), &memDC, 0, 0, nBmpCX, nBmpCY, SRCCOPY);
			m_bFirstDraw = FALSE;
			m_BtnState = BS_MIN;
			Bmp.DeleteObject();
		}
	}
	else
  if (MaxRC.PtInRect(point))
	{
    if(m_bEnableMaxsize)
    {
      if (m_BtnState != BS_MAX && m_BtnState != BS_RES)
      {
        Bmp.LoadBitmap(IDB_MAXHOTBTN);
        Bmp.GetObject(sizeof(bmpInfo),&bmpInfo);

        nBmpCX = bmpInfo.bmiHeader.biWidth;
        nBmpCY = bmpInfo.bmiHeader.biHeight;
        memDC.SelectObject(&Bmp);
        WindowDC.StretchBlt(m_MaxRC.left, m_MaxRC.top, m_MaxRC.Width(), 
          m_MaxRC.Height(), &memDC, 0, 0, nBmpCX, nBmpCY, SRCCOPY);
        m_bFirstDraw = FALSE;
        if (m_bMaxed)
        {
          m_BtnState = BS_MAX;
        }
        else
        {
          m_BtnState = BS_RES;
        }
        Bmp.DeleteObject();	
      }
    }
	}
	else
  if (CloseRC.PtInRect(point))
	{
		if (m_BtnState != BS_CLOSE)
		{
			Bmp.LoadBitmap(IDB_CLOSEHOTBTN);
			Bmp.GetObject(sizeof(bmpInfo),&bmpInfo);
			
			nBmpCX = bmpInfo.bmiHeader.biWidth;
			nBmpCY = bmpInfo.bmiHeader.biHeight;
			memDC.SelectObject(&Bmp);
			WindowDC.StretchBlt(m_CloseRC.left, m_CloseRC.top, m_CloseRC.Width(), 
								m_CloseRC.Height(), &memDC, 0, 0, nBmpCX, nBmpCY, SRCCOPY);
			m_bFirstDraw = FALSE;
			m_BtnState = BS_CLOSE;
			Bmp.DeleteObject();	
		}
	}
	else
	{		
		if (m_bFirstDraw == FALSE)
		{
			if (m_BtnState == BS_MIN)
			{
				DrawDialog(MINBUTTON);
			}
			else if (m_BtnState == BS_CLOSE)
			{
				DrawDialog(CLOSEBUTTON);
			}
			else if (m_BtnState==BS_MAX || m_BtnState==BS_RES)
			{
				DrawDialog(MAXBUTTON);
			}
		}
		m_BtnState = BS_NONE;
	}
	ReleaseDC(&memDC);	
	CDialog::OnNcMouseMove(nHitTest, point);
}

void CBeautifulDialog::OnMouseMove(UINT nFlags, CPoint point) 
{	
	if (m_BtnState != BS_NONE)
	{
		if (m_BtnState == BS_MIN)
		{
			DrawDialog(MINBUTTON);
		}
		else if (m_BtnState==BS_CLOSE)
		{
			DrawDialog(CLOSEBUTTON);
		}
		else if (m_BtnState==BS_MAX || m_BtnState==BS_RES)
		{
			DrawDialog(MAXBUTTON);
		}
		m_BtnState = BS_NONE;
	}
}

void CBeautifulDialog::OnNcLButtonDown(UINT nHitTest, CPoint point) 
{
	switch (m_BtnState)
	{
	case BS_CLOSE: //�رմ���
		{
			OnCancel();
		}
		break;
	case BS_MIN: 
		{
			ShowWindow(SW_SHOWMINIMIZED);
		}
		break;
	case BS_MAX:
		{
      if(m_bEnableMaxsize)
      {
        m_BtnState = BS_MAX;
        ShowWindow(SW_SHOWMAXIMIZED);
        m_bMaxed = FALSE;
      }
		}
		break;
	case BS_RES:
		{			
			ShowWindow(SW_RESTORE);
			m_bMaxed = TRUE;
		}
		break;
	}	
	CDialog::OnNcLButtonDown(nHitTest, point);
}

void CBeautifulDialog::OnNcLButtonUp(UINT nHitTest, CPoint point) 
{
	CDialog::OnNcLButtonUp(nHitTest, point);
}

//˫����������󻯻�ԭ��ʾ����
void CBeautifulDialog::OnNcLButtonDblClk(UINT nHitTest, CPoint point) 
{
  if(m_bEnableMaxsize)
  {
    //���㴰�ڱ���������
    CRect WinRC;
    GetWindowRect(WinRC);
    CRect TitleRC;
    //��ȡ��������ʾ����
    TitleRC.CopyRect(CRect(WinRC.left, WinRC.top, WinRC.right, WinRC.top + m_nTitleBarCY));
    if (TitleRC.PtInRect(point))			//�ж��û��Ƿ�˫������������
    {
      if ( m_bMaxed)
      {
        m_BtnState = BS_MAX;
        ShowWindow(SW_SHOWMAXIMIZED);
        m_bMaxed = FALSE;		
      }
      else
      {
        m_BtnState = BS_RES;
        ShowWindow(SW_RESTORE);
        m_bMaxed = TRUE;	
      }
    }
  }

	CDialog::OnNcLButtonDblClk(nHitTest, point);
}

void CBeautifulDialog::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	CDialog::OnNcCalcSize(bCalcValidRects, lpncsp);
}

void CBeautifulDialog::AutoAdjustLayout()
{

}