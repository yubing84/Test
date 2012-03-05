// MonitorUser.cpp : implementation file
//

#include "../main_frame/StdAfx.h"
#include "../main_frame/WMDF_Studio.h"
#include "ManageClientDialog.h"
#include "../common/UserSerachDlg.h"
#include "UserAddDlg.h"
#include "../main_frame/MainFrm.h"
#include <assert.h>
#include "../common/UIDateTime.h"
#include "../common/studio_utility.h"
#include "../../environment/file.h"
#include "../../environment/utils.h"
#include "../../include/date_time.h"
#include "../../environment/utils.h"
#include "../../environment/application_directory.h"
#include "../monitor/server_info.h"
#include "../monitor/server_manager.h"


using namespace std;
using namespace wmdf;

// CManageClientDialog

IMPLEMENT_DYNCREATE(CManageClientDialog, CDialog)

CManageClientDialog::CManageClientDialog(CWnd* pParent)
	: CDialog(CManageClientDialog::IDD, pParent)
{
  m_user_manager = new wmdf::UserManager();
  m_product_manager = NULL;
  m_bInitOK = false;
}

CManageClientDialog::~CManageClientDialog()
{
  delete m_user_manager;
}

void CManageClientDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LIST_USER, m_conListUser);
  DDX_Control(pDX, IDC_LIST_AUTHORIZE, m_conListAuthorize);
  DDX_Control(pDX, IDC_BUTTON_ADD, m_conButton_add);
  DDX_Control(pDX, IDC_BUTTON_MODIFY, m_conButton_modify);
  DDX_Control(pDX, IDC_BUTTON_DELETE, m_conButton_delete);
  DDX_Control(pDX, IDC_BUTTON_SEARCH, m_conButton_search);
  DDX_Control(pDX, IDOK, m_conButton_ok);
  DDX_Control(pDX, IDCANCEL, m_conButton_cancel);
  DDX_Control(pDX, DEST_SERVER_ID, m_dest_server);
}

BEGIN_MESSAGE_MAP(CManageClientDialog, CDialog)
  ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CManageClientDialog::OnBnClickedButtonSearch)
  ON_BN_CLICKED(IDC_BUTTON_ADD, &CManageClientDialog::OnBnClickedButtonAdd)
  ON_BN_CLICKED(IDC_BUTTON_DELETE, &CManageClientDialog::OnBnClickedButtonDelete)
  ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CManageClientDialog::OnBnClickedButtonModify)
  ON_WM_DESTROY()
  ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_USER, &CManageClientDialog::OnLvnItemchangedListUser)
  ON_MESSAGE(WM_ADD_CUSTOMER, OnAddUser)
  ON_BN_CLICKED(IDOK, &CManageClientDialog::OnBnClickedOk)
  ON_BN_CLICKED(IDCANCEL, &CManageClientDialog::OnBnClickedCancel)
  ON_BN_CLICKED(IDC_GET_CONFIG_BUTTON, &CManageClientDialog::OnBnClickedGetConfigButton)
  ON_BN_CLICKED(IDC_UPDATE_CONFIG_BUTTON, &CManageClientDialog::OnBnClickedUpdateConfigButton)
END_MESSAGE_MAP()

// CManageClientDialog message handlers

void CManageClientDialog::OnBnClickedButtonSearch()
{
  // TODO: Add your control notification handler code here
  CUserSerachDlg user_serach_dialog;
  if(IDOK == user_serach_dialog.DoModal())
  {

  }
  else
  {

  }
}

void CManageClientDialog::OnBnClickedButtonAdd()
{
   CUserAddDlg* pDlg = new CUserAddDlg(this);
   pDlg->SetProductManager(m_product_manager);
   pDlg->DoModal();
   delete pDlg;
   pDlg = NULL;
}

void CManageClientDialog::OnBnClickedButtonDelete()
{
  POSITION pos = m_conListUser.GetFirstSelectedItemPosition();
  int nItemIndex = m_conListUser.GetNextSelectedItem(pos);
  CString strUserId = m_conListUser.GetItemText(nItemIndex, 0);
  CString strContext = "ɾ��idΪ" + strUserId + "���û�?";
  if(IDOK == MessageBox(strContext, "ɾ��", MB_OKCANCEL))
  {
    int32_t user_id = atoi(strUserId.GetBuffer(0));
    strUserId.ReleaseBuffer();
    m_conListUser.DeleteUser(user_id);
    m_user_manager->delete_users(user_id);

    
  }
}

void CManageClientDialog::OnBnClickedButtonModify()
{
  // TODO: Add your control notification handler code here
  
  // ���Ȼ�ȡ��ǰѡ�е���
  POSITION pos = m_conListUser.GetFirstSelectedItemPosition();
  int nItem = m_conListUser.GetNextSelectedItem(pos);

  // ��ȡ���е�id
  CString str_id = m_conListUser.GetItemText(nItem, 0);
  int32_t user_id = atoi(str_id.GetBuffer(0));
  str_id.ReleaseBuffer();

  // �ҵ�id��Ӧ��user
  User* pUser = NULL;
  pUser = m_user_manager->FindUser(user_id);

  if(NULL == pUser)
  {
    MessageBox("��ѡ��Ҫ�޸ĵĶ���", "����", MB_ICONERROR);
    return;
  }

  // ����pUser���CUserModifyDlg
  CUserAddDlg user_modify_dialog(this, false);
  user_modify_dialog.m_pUser = pUser;
  user_modify_dialog.SetProductManager(m_product_manager);

  // create a modeless dialog
  // m_ptr_modify_dlg->ShowWindow(SW_SHOW);

  if(IDOK == user_modify_dialog.DoModal())
  {

  }
  else
  {

  }
}

void CManageClientDialog::OnDestroy()
{
  CDialog::OnDestroy();

  // TODO: Add your message handler code here
  ((CMainFrame*)AfxGetMainWnd())->m_pManageClient=NULL; // ��մ���ָ��
}

void CManageClientDialog::OnLvnItemchangedListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
  // TODO: Add your control notification handler code here
  if(!m_bInitOK)
    return;
  
  // �Ȼ�ȡ��ǰѡ���ж�Ӧ��user_id
  CString str_user_id = m_conListUser.GetItemText(pNMLV->iItem, 0);
  User* ptr_user = NULL;
  ptr_user = m_user_manager->FindUser(atoi(str_user_id.GetBuffer(0)));
  str_user_id.ReleaseBuffer();

  // assert(NULL != ptr_user);
  if(NULL == ptr_user) // �������޸�userʱ��������ʱɾ��ĳitem�������Ҳ���id��Ӧ��item�����
    return;


  // ���������Ȩ��Ʒ
  m_conListAuthorize.DeleteAllItems();

  int32_t item_index = 0;
  int32_t sub_item_index = 0;

  CString context;
  for(int32_t i = 0; i < ptr_user->authorized_products_count(); ++i)
  {
    int16_t product_id;
    product_id = ptr_user->authorized_products(i)->product_id();

    ProductDescripter* pPD = m_product_manager->FindProductDescripter(product_id);
    assert(NULL != pPD);
    for(int32_t j = 0; j < ptr_user->authorized_products(i)->message_count(); ++j)
    { 
      sub_item_index = 0;

      // �����Ȩ��Ʒid
      context.Format("%d", product_id);
      m_conListAuthorize.InsertItem(item_index, context);

      // �����Ȩ��Ʒ����
      context.Format("%s", pPD->description().c_str());
      m_conListAuthorize.SetItemText(item_index, ++sub_item_index, context);
      
      int16_t message_id;
      message_id = ptr_user->authorized_products(i)->message_id(j);

      // �����Ȩ��Ϣid
      context.Format("%d", message_id);
      m_conListAuthorize.SetItemText(item_index, ++sub_item_index, context);

      for(int32_t k = 0; k < pPD->support_versions_count(); ++k)
      {
        VersionDescripter* pVD = pPD->support_versions(k);

        MessageDescripter* pMD = pVD->FindMessageDescripter(message_id);
        if(NULL != pMD)
        {
          // �����Ȩ��Ϣ����
          context.Format("%s", pMD->message_description().c_str());
          m_conListAuthorize.SetItemText(item_index, ++sub_item_index, context); 
          break;
        }
      }

      ++item_index;
    }
  }

  m_conListAuthorize.Invalidate();

  *pResult = 0;
}

LRESULT CManageClientDialog::OnAddUser(WPARAM wParam, LPARAM lParam)
{
  User* pUser = reinterpret_cast<User*>(wParam);
  bool bAdd = *(reinterpret_cast<bool*>(lParam));

  if(bAdd)
    AddUser(*pUser);
  else
    ModifyUser(*pUser);
  return TRUE;
}

void CManageClientDialog::AddUser(const User& user)
{
  User* pUser = new User;
  *pUser = user;

  // �����û�ID
  pUser->set_user_id(m_user_manager->max_userid()+1);
  m_user_manager->add_users(pUser);

  m_conListUser.InsertUser(pUser);
}

void CManageClientDialog::ModifyUser(const User& user)
{
  User* pUser = new User;
  *pUser = user;

  // ��ɾ���������
  m_conListUser.DeleteUser(pUser->user_id());
  m_user_manager->delete_users(pUser->user_id());

  m_conListUser.InsertUser(pUser);
  m_user_manager->add_users(pUser);
}


BOOL CManageClientDialog::OnInitDialog()
{
  // TODO:  Add extra initialization here
  // initialize m_conListUser's header column
  m_conListUser.AddColumnHeader("�û�ID");
  m_conListUser.AddColumnHeader("�û�IP��ַ");
  m_conListUser.AddColumnHeader("�û���");
  m_conListUser.AddColumnHeader("�û�����");
  m_conListUser.AddColumnHeader("��˾��");
  m_conListUser.AddColumnHeader("��ϵ��");
  m_conListUser.AddColumnHeader("�绰");
  m_conListUser.AddColumnHeader("����");
  m_conListUser.AddColumnHeader("�û�����");
  m_conListUser.AddColumnHeader("��Ȩ��ֹʱ��");

  // initialize m_conListAuthorize's header column
  m_conListAuthorize.AddColumnHeader("��Ȩ��Ʒid");
  m_conListAuthorize.AddColumnHeader("��Ȩ��Ʒ����");
  m_conListAuthorize.AddColumnHeader("��Ȩģ��id");
  m_conListAuthorize.AddColumnHeader("��Ȩģ������");

  CDialog::OnInitDialog();

  // TODO: Add your specialized code here and/or call the base class
  SetWindowText("�ͻ�����");

  // set the style of listctrl
  m_conListUser.SetExtendedStyle(LVS_EX_FLATSB
    |LVS_EX_FULLROWSELECT
    |LVS_EX_HEADERDRAGDROP
    |LVS_EX_ONECLICKACTIVATE
    |LVS_EX_GRIDLINES);

  m_conListAuthorize.SetExtendedStyle(LVS_EX_FLATSB
    |LVS_EX_FULLROWSELECT
    |LVS_EX_HEADERDRAGDROP
    |LVS_EX_ONECLICKACTIVATE
    |LVS_EX_GRIDLINES);

  StudioUtility::InitServerList(m_dest_server);

  m_product_manager = wmdf::ProductManager::instance();
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CManageClientDialog::OnBnClickedOk()
{
  // �����������ļ�
  OnBnClickedUpdateConfigButton();
  OnOK();
}

void CManageClientDialog::OnBnClickedCancel()
{
  // TODO: Add your control notification handler code here
  __super::OnCancel();
}

void CManageClientDialog::OnBnClickedGetConfigButton()
{
  int server_index = m_dest_server.GetCurSel();
 
  if(StudioUtility::GetConfigInfo(server_index, CFT_USER,m_user_manager))
  {
    m_conListUser.DeleteAllItems();
    // �����û�
    for(int user_index = 0; user_index < m_user_manager->users_count(); ++user_index)
    {
      m_conListUser.InsertUser(m_user_manager->users(user_index));
    }

   if(StudioUtility::GetConfigInfo(server_index, CFT_PRODUCT,m_product_manager))
   {
     m_bInitOK = true;
   }
   else
   {
    MessageBox("��ȡ��Ʒ��Ϣʧ�ܣ����������Ƿ�����");
   }
  }
  else
    MessageBox("��ȡ�ͻ���Ϣʧ�ܣ����������Ƿ�����");
}

void CManageClientDialog::OnBnClickedUpdateConfigButton()
{
  if(m_bInitOK)
  {
    int index = m_dest_server.GetCurSel();
    if(!StudioUtility::SetConfigInfo(index,CFT_USER,m_user_manager))
    {
      MessageBox("�޸Ŀͻ���Ϣʧ�ܣ�");
    }
    else
    {
      MessageBox("�޸Ŀͻ���Ϣ�ɹ���");
    }
  }
  else
  {
    MessageBox("���Ȼ�ȡ������Ϣ���޸ģ�");
  }
}


