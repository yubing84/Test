#pragma once

//����Ի���������ֵı��
#define LEFTBAR      1    //��߿�
#define LEFTTITLE    2    //�����
#define RIGHTTITLE   4    //�ұ���
#define MIDTITLE     8    //�м����
#define RIGHTBAR     16   //�ұ߿�
#define BOTTOMBAR    32   //�ױ߿�
#define MINBUTTON    64   //��С����ť
#define MAXBUTTON    128  //��󻯰�ť
#define CLOSEBUTTON  256  //�رհ�ť
#define ALL          511  //���б�ʶ


//���尴ť״̬���
enum ButtonState{BS_NONE, BS_MIN, BS_MAX, BS_RES, BS_CLOSE};

class CBeautifulDialog : public CDialog
{
  DECLARE_DYNAMIC(CBeautifulDialog)

public:
  void SetTextColor(COLORREF color) {m_clText = color;}
  void SetTitleTextColor(COLORREF color) {m_clTitle = color;}
  void SetBkgnColor(COLORREF color) {m_crBK = color;}

  void SetEnableMaxsize(bool bEnableMaxsize) {m_bEnableMaxsize = bEnableMaxsize;}

protected:
  virtual void AutoAdjustLayout();    // �Զ������Ի���ؼ�����

//�����Ա����
private:
	int m_nTitleBarCX;	        // ���������
	int m_nTitleBarCY;	        // �������߶�
	int m_nFrameLeft;	          // �Ի�����߿���
	int m_nFrameRight;	        // �Ի����ұ߿���
	int m_nBorderCX;	          // �Ի���߿���
	int m_nBorderCY;	          // �Ի���߿�߶�
	int m_nTitleBtnCX;	        // ��������ť���
	int m_nTitleBtnCY;	        // ��������ť�߶�
	int m_nRightTitleCX;        // ��¼�ұ��������ֵĿ��

	CPoint m_MinPT;		          // ��С����ť����(�߼�����)
	CPoint m_MaxPT;		          // ��󻯰�ť����(�߼�����)
	CPoint m_ClosePT;	          // �رհ�ť����(�߼�����)

	COLORREF m_crBK;	          // �Ի��򱳾���ɫ
	COLORREF m_clText;	        // �Ի����ı���ɫ
  COLORREF m_clTitle;         // �Ի�������ı���ɫ
	CRect m_MinRC;		          // ���»���ť��ʾ����
	CRect m_MaxRC;		          // ��󻯰�ť��ʾ����
	CRect m_CloseRC;	          // �رհ�ť��ʾ����

	CRect m_TitleBarRC;	        // ��¼�ұ���������
	BOOL  m_bFirstDraw;	        // �״λ���
	ButtonState m_BtnState;
	BOOL m_bMaxed;		          // �Ƿ�Ϊ���״̬	
	
	CString m_csText;	          // �������ı�

private:
  bool m_bEnableMaxsize;
  bool m_bInitOK;

protected:
  CBrush m_brBkgnd;
  CBrush m_brControlBkgnd1;
  CBrush m_brControlBkgnd2;

// Construction
public:
	void DrawDialog(int nFlag = ALL);
	void DrawTitlebarText();
	void SetWindowText(CString csText);
	CBeautifulDialog(UINT ID = IDD, CWnd* pParent = NULL);	// standard constructor

	enum { IDD = 0 };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;
	
	virtual BOOL OnInitDialog();
  afx_msg void OnPaint();
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnNcLButtonDblClk(UINT nHitTest, CPoint point);
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp);
	DECLARE_MESSAGE_MAP()
};
