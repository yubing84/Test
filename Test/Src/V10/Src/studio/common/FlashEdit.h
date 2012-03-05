#pragma once


// CFlashEdit

class CFlashEdit : public CEdit
{
	DECLARE_DYNAMIC(CFlashEdit)

public:
	CFlashEdit();
	virtual ~CFlashEdit();

protected:
	DECLARE_MESSAGE_MAP()

public:
	void SetWindowText(LPCTSTR lpszString);
	afx_msg void OnPaint();

protected:
	// ��ɫ��ˢ
	CBrush m_brushRed;

	// ��ɫ��ˢ
	CBrush m_brushWhite;

	// ʹ�õĻ�ˢ
	CBrush* m_pBrush;

	// �ؼ���Client Rect
	CRect m_rect;

	//edit ��ʾ���ַ���
	CString m_str;

	// �����Ƿ��ػ��ַ���
	bool m_bDrawText;

	// ����
	CFont m_font;	

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


