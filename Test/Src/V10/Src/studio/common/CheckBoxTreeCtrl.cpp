// TWTreeCtrl.cpp : implementation file
//

#include "../main_frame/StdAfx.h"
#include "CheckBoxTreeCtrl.h"
#include "../main_frame/Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CCheckBoxTreeCtrl

CCheckBoxTreeCtrl::CCheckBoxTreeCtrl()
{
	m_uFlags=0;
}

CCheckBoxTreeCtrl::~CCheckBoxTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CCheckBoxTreeCtrl, CExpandTreeCtrl)
	//{{AFX_MSG_MAP(CCheckBoxTreeCtrl)
	ON_WM_LBUTTONDOWN()
  ON_WM_RBUTTONDOWN()
	ON_NOTIFY_REFLECT(NM_CLICK, OnStateIconClick)
	ON_NOTIFY_REFLECT(TVN_KEYDOWN, OnKeydown)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCheckBoxTreeCtrl message handlers

void CCheckBoxTreeCtrl::OnStateIconClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(m_uFlags&TVHT_ONITEMSTATEICON) *pResult=1;
	else *pResult = 0;
}

void CCheckBoxTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	HTREEITEM hItem =HitTest(point, &m_uFlags);
	if ( (m_uFlags&TVHT_ONITEMSTATEICON ))
	{
    //nState: 0->��ѡ��ť 1->û��ѡ�� 2->����ѡ�� 3->ȫ��ѡ��
    UINT nState = GetItemState( hItem, TVIS_STATEIMAGEMASK ) >> 12;
    nState=(nState==3)?1:3;
    SetItemState( hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );

    // ͬʱ������������ѡ��
    SelectItem(hItem);

	}
	
	CExpandTreeCtrl::OnLButtonDown(nFlags, point);
}

void CCheckBoxTreeCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
 	//����ո��
 //if(nChar==0x20)
 //	{
 //		HTREEITEM hItem =GetSelectedItem();
 //		UINT nState = GetItemState( hItem, TVIS_STATEIMAGEMASK ) ;//>> 12;
 //		if(nState!=0)
 //		{
 //			//nState=(nState==3)?1:3;
 //			SetItemState( hItem, nState, TVIS_STATEIMAGEMASK );
 //		}
 //	}
	//else
	CExpandTreeCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCheckBoxTreeCtrl::OnKeydown(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;
	
	*pResult = 0;
}

BOOL CCheckBoxTreeCtrl::SetCheck(HTREEITEM hItem, BOOL fCheck)
{
  int nState;
  if(fCheck)
    nState = 3;
  else
    nState = 1;

  BOOL bReturn = CExpandTreeCtrl::SetItemState( hItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );

	//TravelChild(hItem, nState);
	//TravelSiblingAndParent(hItem, nState);
	return bReturn;
}

void CCheckBoxTreeCtrl::TravelChild(HTREEITEM hItem, int nState)
{
  HTREEITEM hChildItem,hBrotherItem;

  //�����ӽڵ㣬û�оͽ���
  hChildItem=GetChildItem(hItem);
  if(hChildItem!=NULL)
  {
    //�����ӽڵ��״̬�뵱ǰ�ڵ��״̬һ��
    CTreeCtrl::SetItemState( hChildItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
    //�ٵݹ鴦���ӽڵ���ӽڵ���ֵܽڵ�
    TravelChild(hChildItem, nState);

    //�����ӽڵ���ֵܽڵ�����ӽڵ�
    hBrotherItem=GetNextSiblingItem(hChildItem);
    while (hBrotherItem)
    {
      //�����ӽڵ���ֵܽڵ�״̬�뵱ǰ�ڵ��״̬һ��
      int nState1 = GetItemState( hBrotherItem, TVIS_STATEIMAGEMASK ) >> 12;
      if(nState1!=0)
      {
        CTreeCtrl::SetItemState( hBrotherItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
      }
      //�ٵݹ鴦���ӽڵ���ֵܽڵ���ӽڵ���ֵܽڵ�
      TravelChild(hBrotherItem, nState);
      hBrotherItem=GetNextSiblingItem(hBrotherItem);
    }
  }
  //else
  //{
  //  CExpandTreeCtrl::SetCheck( hItem, nState ); 
  //}
}

void CCheckBoxTreeCtrl::TravelSiblingAndParent(HTREEITEM hItem, int nState)
{
  HTREEITEM hNextSiblingItem,hPrevSiblingItem,hParentItem;

  //���Ҹ��ڵ㣬û�оͽ���
  hParentItem=GetParentItem(hItem);
  if(hParentItem!=NULL)
  {
    int nState1=nState;//���ʼֵ����ֹû���ֵܽڵ�ʱ����

    //���ҵ�ǰ�ڵ�������ֵܽڵ��״̬
    hNextSiblingItem=GetNextSiblingItem(hItem);
    while(hNextSiblingItem!=NULL)
    {
      nState1 = GetItemState( hNextSiblingItem, TVIS_STATEIMAGEMASK ) >> 12;
      if(nState1!=nState && nState1!=0)
        break;
      else 
        hNextSiblingItem=GetNextSiblingItem(hNextSiblingItem);
    }

    if(nState1==nState)
    {
      //���ҵ�ǰ�ڵ�������ֵܽڵ��״̬
      hPrevSiblingItem=GetPrevSiblingItem(hItem);
      while(hPrevSiblingItem!=NULL)
      {
        nState1 = GetItemState( hPrevSiblingItem, TVIS_STATEIMAGEMASK ) >> 12;
        if(nState1!=nState && nState1!=0)
          break;
        else
          hPrevSiblingItem=GetPrevSiblingItem(hPrevSiblingItem);
      }
    }

    if(nState1==nState || nState1==0)
    {
      nState1 = GetItemState( hParentItem, TVIS_STATEIMAGEMASK ) >> 12;
      if(nState1!=0)
      {
        //���״̬һ�£��򸸽ڵ��״̬�뵱ǰ�ڵ��״̬һ��
        CTreeCtrl::SetItemState( hParentItem, INDEXTOSTATEIMAGEMASK(nState), TVIS_STATEIMAGEMASK );
      }
      //�ٵݹ鴦���ڵ���ֵܽڵ���丸�ڵ�
      TravelSiblingAndParent(hParentItem,nState);
    }
    else
    {
      //״̬��һ�£���ǰ�ڵ�ĸ��ڵ㡢���ڵ�ĸ��ڵ㡭��״̬��Ϊ����̬
      hParentItem=GetParentItem(hItem);
      while(hParentItem!=NULL)
      {
        nState1 = GetItemState( hParentItem, TVIS_STATEIMAGEMASK ) >> 12;
        if(nState1!=0)
        {
          CTreeCtrl::SetItemState( hParentItem, INDEXTOSTATEIMAGEMASK(2), TVIS_STATEIMAGEMASK );
        }
        hParentItem=GetParentItem(hParentItem);
      }
    }
  }	
}

void CCheckBoxTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
 
}

BOOL CCheckBoxTreeCtrl::SetItemState(HTREEITEM hItem, UINT nState, UINT nStateMask, BOOL bSearch)
{
  BOOL bReturn=CTreeCtrl::SetItemState( hItem, nState, nStateMask );

  UINT iState = nState >> 12;
  if(iState!=0)
  {
    if(bSearch)
      TravelChild(hItem, iState);
    TravelSiblingAndParent(hItem,iState);
  }
  return bReturn;
}