#pragma once

#include "../../product/product_source_manager.h"
#include "../management_product/ManageProductDialog.h"

// CManageProductSourceDialog form view
struct source_data;

class CManageProductSourceDialog : public CManageProductDialog
{
	DECLARE_DYNCREATE(CManageProductSourceDialog)

public:
	CManageProductSourceDialog(UINT id = IDD, CWnd* pParent = NULL);           // protected constructor used by dynamic creation
	virtual ~CManageProductSourceDialog();

public:
	enum { IDD = IDD_MANAGE_PRODUCT_SOURCE };

protected:

private:

  // ����m_productSourceManager�ػ�m_conProductSourceTree
  virtual void InitTreeProduct();

  // ˢ��static�ؼ�����ʾ����
  virtual void RefreshContent();

  bool AddProductSource(wmdf::ProductSource* pItem);
  bool AddMarketTime(wmdf::MarketTime* pItem);
  bool AddBackupSource(wmdf::BackupSource* pItem);
  bool AddSubscribedProduct(wmdf::ProtocolDescription* pItem);
  bool ModifyProductSource(wmdf::ProductSource* pItem);
  bool ModifyMarketTime(wmdf::MarketTime* pItem);
  bool ModifyBackupSource(wmdf::BackupSource* pItem);
  bool ModifySubscribedProduct(wmdf::ProtocolDescription* pItem);

  // �������ݹ�����
  virtual bool LoadDataManager();

  void GetContentFromData(CString& strContent, wmdf::ProductSource* pData);
  void GetContentFromData(CString& strContent, wmdf::MarketTime* pData);
  void GetContentFromData(CString& strContent, wmdf::BackupSource* pData);
  void GetContentFromData(CString& strContent, wmdf::ProtocolDescription* pData);

  // �麯��������pSourceData��ָ�����ͣ�������ͬ��CAddOrModifyDialog
  virtual void CreateAddModifyDialog(UINT type, CAddOrModifyDialog*& pDlg, bool bAdd = true);

  // �麯���������ݹ�������ɾ������
  virtual void DeleteData(source_data* pSourceData);

  // ��������
  virtual void MementoData();

  virtual void ParseDataItem(void* pData, bool bAdd, ENUM_DIALOG_TYPE type);

	DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg void OnBnClickedGetConfigButton();
  afx_msg void OnBnClickedUpdateConfigButton();
};