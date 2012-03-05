#pragma once
#include "afxcmn.h"

/////////////////////////////////////////////////////////////////////////////
// CManageProductDialog form view

#pragma once
#include "afxwin.h"

#include "../../product/product_manager.h"
#include "ManageProductAddProductDescripterDialog.h"
#include "ManageProductAddVersionDescripterDialog.h"
#include "ManageProductAddMessageDescripterDialog.h"
#include "../common/ExpandTreeCtrl.h"
#include <vector>
#include "../common/BeautifulButton.h"

struct source_data;

class CManageProductDialog : public CDialog
{
  DECLARE_DYNCREATE(CManageProductDialog)

public:
	CManageProductDialog(UINT id = IDD, CWnd* pParent = NULL);           // protected constructor used by dynamic creation
	virtual ~CManageProductDialog();

public:
	enum { IDD = IDD_MANAGE_PRODUCT };

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

public:
  // ��Ʒ������
  // wmdf::ProductManager m_product_manager;

  wmdf::Persistable* m_pDataManager;

  CExpandTreeCtrl m_conTreeProduct;

public:
  // ����m_product_manager��ʼ��TreeProduct�ؼ�
  virtual void InitTreeProduct();

  // �ӵ�ǰ��ѡ�񣬵õ����Ӧ��Descripter����
  virtual void GetDescripterFromSelect(source_data*& pSourceData, std::vector<void*>& arrAncestor);

  bool AddProductDescripter(wmdf::ProductDescripter* pPD);
  bool AddVersionDescripter(wmdf::VersionDescripter* pVD);
  bool AddMessageDescripter(wmdf::MessageDescripter* pMD);
  bool ModifyProductDescripter(wmdf::ProductDescripter* pPD);
  bool ModifyVersionDescripter(wmdf::VersionDescripter* pVD);
  bool ModifyMessageDescripter(wmdf::MessageDescripter* pMD);

  // ��鵱ǰѡ��item������sibling�Ƿ���strText�ظ�
  bool SiblingRepeat(CString strText);

  // ˢ��static�ؼ�����ʾ����
  virtual void RefreshContent();

  void GetContentFromData(CString& strContent, wmdf::ProductDescripter* pData);
  void GetContentFromData(CString& strContent, wmdf::VersionDescripter* pData);
  void GetContentFromData(CString& strContent, wmdf::MessageDescripter* pData);

  // �麯��������pSourceData��ָ�����ͣ�������ͬ��CAddOrModifyDialog
  virtual void CreateAddModifyDialog(UINT type, CAddOrModifyDialog*& pDlg, bool bAdd = true);

  // �麯���������ݹ�������ɾ������
  virtual void DeleteData(source_data* pSourceData);
  virtual bool LoadDataManager();
  // ��������
  virtual void MementoData();

  virtual void ParseDataItem(void* pData, bool bAdd, ENUM_DIALOG_TYPE type);

public:

  virtual afx_msg void OnBnClickedButtonAdd();
  virtual afx_msg void OnBnClickedButtonModify();
  virtual afx_msg void OnBnClickedButtonDelete();

  afx_msg LRESULT OnAddDataItem(WPARAM wParam, LPARAM lParam);

  virtual afx_msg void OnTvnSelchangedTreeProduct(NMHDR *pNMHDR, LRESULT *pResult);
  virtual BOOL OnInitDialog();
  afx_msg void OnBnClickedOk();
  CButton m_conButton_add;
  CButton m_conButton_modify;
  CButton m_conButton_delete;
  CButton m_conButton_search;
  CButton m_conButton_ok;
  CButton m_conButton_cancel;
  CComboBox m_dest_server;
  bool m_flag;
  afx_msg void OnBnClickedGetConfigButton();
  afx_msg void OnBnClickedUpdateConfigButton();
  
};
