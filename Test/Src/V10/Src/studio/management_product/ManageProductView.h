#pragma once
#include "afxcmn.h"

/////////////////////////////////////////////////////////////////////////////
// CManageProductView form view

#pragma once
#include "afxwin.h"

#include "../../product/product_manager.h"
#include "ManageProductAddProductDescripterDialog.h"
#include "ManageProductAddVersionDescripterDialog.h"
#include "ManageProductAddMessageDescripterDialog.h"
#include "../common/ExpandTreeCtrl.h"

enum PRODUCT_INNER_TYPE;

class CManageProductView : public CFormView
{
  DECLARE_DYNCREATE(CManageProductView)

protected:
	CManageProductView();           // protected constructor used by dynamic creation
	virtual ~CManageProductView();

public:
	enum { IDD = IDD_MANAGE_PRODUCT };
#ifdef _DEBUG
  virtual void AssertValid() const;
#ifndef _WIN32_WCE
  virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

public:
  // ��Ʒ������
  wmdf::ProductManager m_product_manager;

  CExpandTreeCtrl m_conTreeProduct;

  // ��Ӹ��������ĶԻ���
  CManageProductAddProductDescripterDialog* m_pAddProductDescripterDialog;
  CManageProductAddVersionDescripterDialog* m_pAddVersionDescripterDialog;
  CManageProductAddMessageDescripterDialog* m_pAddMessageDescripterDialog;

public:
  // ����m_product_manager��ʼ��TreeProduct�ؼ�
  void InitTreeProduct();

  // �ӵ�ǰ��ѡ�񣬵õ����Ӧ��Descripter����
  void* GetDescripterFromSelect(PRODUCT_INNER_TYPE& type);

  bool AddProductDescripter(wmdf::ProductDescripter* pPD);
  bool ModifyProductDescripter(wmdf::ProductDescripter* pPD);
  bool AddVersionDescripter(wmdf::VersionDescripter* pVD);
  bool ModifyVersionDescripter(wmdf::VersionDescripter* pVD);
  bool AddMessageDescripter(wmdf::MessageDescripter* pMD);
  bool ModifyMessageDescripter(wmdf::MessageDescripter* pMD);

  // ������xml�ļ���
  void SaveToXmlFile(const std::string& file_path);

  // ��鵱ǰѡ��item������sibling�Ƿ���strText�ظ�
  bool SiblingRepeat(CString strText);

  // ˢ��static�ؼ�����ʾ����
  void RefreshContent();

public:
  virtual void OnInitialUpdate();
  afx_msg void OnDestroy();

public:

  afx_msg void OnBnClickedButtonAdd();
  afx_msg void OnBnClickedButtonModify();
  afx_msg void OnBnClickedButtonDelete();

  afx_msg LRESULT OnAddProductDescripter(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnAddVersionDescripter(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnAddMessageDescripter(WPARAM wParam, LPARAM lParam);

  afx_msg void OnTvnSelchangedTreeProduct(NMHDR *pNMHDR, LRESULT *pResult);
};
