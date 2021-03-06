#include "MonitorOverviewDialog.h"
#include "../../environment/strutils.h"
#include "../common/WordTranslation.h"
#include "monitor_environment.h"
#include "AddServerDialog.h"
IMPLEMENT_DYNAMIC(CMonitorOverviewDialog, CDialog)

CMonitorOverviewDialog::CMonitorOverviewDialog( CWnd* pParent /*= NULL*/ )
: CDialog(CMonitorOverviewDialog::IDD, pParent)
{
   invoker_ = new WmdfInvoke();
   monitor_client_dlg_ = NULL;
   monitor_transfer_dlg_ = NULL;
}

CMonitorOverviewDialog::~CMonitorOverviewDialog()
{
  if(invoker_!=NULL)
  {
    invoker_->Disconnect();
    delete invoker_;
    invoker_ = NULL;
  }  
  delete MonitorEnvironment::Instance();
}

void CMonitorOverviewDialog::DoDataExchange( CDataExchange* pDX )
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_Server_LIST, m_server_list);
}

BEGIN_MESSAGE_MAP(CMonitorOverviewDialog, CDialog)
 ON_BN_CLICKED(IDOK, &CMonitorOverviewDialog::OnBnClickedOk)
 ON_NOTIFY(NM_RCLICK, IDC_Server_LIST, &CMonitorOverviewDialog::OnNMRClickServerList)
 ON_COMMAND(ID_Transfer_Monitor, &CMonitorOverviewDialog::OnTransferMonitor)
 ON_COMMAND(ID_Client_Monitor, &CMonitorOverviewDialog::OnClientMonitor)
 ON_BN_CLICKED(ID_BUTTON_CONNECT_ALL, &CMonitorOverviewDialog::OnConnectAll)
 ON_BN_CLICKED(ID_BUTTON_ADD_SERVER, &CMonitorOverviewDialog::OnAddServer)
 ON_BN_CLICKED(ID_BUTTON_DELETE_SERVER, &CMonitorOverviewDialog::OnDeleteSelectedServer)
 ON_WM_PAINT()
 ON_WM_SIZE()
 ON_WM_SIZING()
 ON_BN_CLICKED(IDC_BUTTON1, &CMonitorOverviewDialog::OnBnClickedButton1)
END_MESSAGE_MAP()

BEGIN_EASYSIZE_MAP(CMonitorOverviewDialog)
  EASYSIZE(IDC_Server_LIST,ES_BORDER,ES_KEEPSIZE,ES_BORDER,ES_BORDER,0)
END_EASYSIZE_MAP

void CMonitorOverviewDialog::OnBnClickedOk()
{
  // TODO: Add your control notification handler code here
  OnOK();
}


BOOL CMonitorOverviewDialog::OnInitDialog()
{
  CDialog::OnInitDialog();
  MonitorEnvironment::Instance()->Initialize();

  m_server_list.InsertColumn(0,"ip地址");
  m_server_list.InsertColumn(1,"端口");
  m_server_list.InsertColumn(2,"连接ID");
  m_server_list.InsertColumn(3,"连接状态");
  m_server_list.SetColumnWidth( 0 , LVSCW_AUTOSIZE_USEHEADER);
  m_server_list.SetColumnWidth( 1 , LVSCW_AUTOSIZE_USEHEADER); 
  m_server_list.SetColumnWidth( 2 , LVSCW_AUTOSIZE_USEHEADER); 
  m_server_list.SetColumnWidth( 3 , LVSCW_AUTOSIZE_USEHEADER);

  m_server_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

  ReloadServerList();

  m_toolBarImageList.Create(16, 16, TRUE | ILC_COLOR8, 4, 0);
  HICON hIcon = NULL;

  hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
    MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);
  m_toolBarImageList.Add(hIcon);

  hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
    MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 16, 16, 0);
  m_toolBarImageList.Add(hIcon);

  hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
    MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 16, 16, 0);
  m_toolBarImageList.Add(hIcon);

  hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
    MAKEINTRESOURCE(IDI_ICON4), IMAGE_ICON, 16, 16, 0);
  m_toolBarImageList.Add(hIcon);

 
  
  //   创建工具条并调入资源   
  if(!m_wndToolBar.Create(this)   ||   !m_wndToolBar.LoadToolBar(IDR_TOOLBAR_SERVER_MONITOR))   
  {   
    TRACE0("Failed   to   Create   Dialog   Toolbar/n");   
    EndDialog(IDCANCEL);   
  } 

  m_wndToolBar.GetToolBarCtrl().SetImageList(&m_toolBarImageList);

  CRect rcClientOld;   //   旧客户区RECT   
  CRect rcClientNew;   //   加入TOOLBAR后的CLIENT   RECT   
  GetClientRect(rcClientOld);   //     
  //   Called   to   reposition   and   resize   control   bars   in   the   client   area   of   a   window   
  //   The   reposQuery   FLAG   does   not   really   traw   the   Toolbar.     It   only   does   the   calculations.   
  //   And   puts   the   new   ClientRect   values   in   rcClientNew   so   we   can   do   the   rest   of   the   Math.   
  //重新计算RECT大小   
  RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0,reposQuery,rcClientNew);   

  //   All   of   the   Child   Windows   (Controls)   now   need   to   be   moved   so   the   Tollbar   does   not   cover   them   up.   
  //所有的子窗口将被移动，以免被TOOLBAR覆盖   
  //   Offest   to   move   all   child   controls   after   adding   Tollbar   
  //计算移动的距离   
  CPoint   ptOffset(rcClientNew.left-rcClientOld.left,   
    rcClientNew.top-rcClientOld.top);   

  CRect rcChild;   
  CWnd* pwndChild   =   GetWindow(GW_CHILD);     //得到子窗口   
  while(pwndChild)   //   处理所有子窗口   
  {//移动所有子窗口   
    pwndChild->GetWindowRect(rcChild);   
    ScreenToClient(rcChild);     
    rcChild.OffsetRect(ptOffset);     
    pwndChild->MoveWindow(rcChild,FALSE);     
    pwndChild   =   pwndChild->GetNextWindow();   
  }   

  CRect rcWindow;   
  GetWindowRect(rcWindow);   //   得到对话框RECT   
  rcWindow.right   +=   rcClientOld.Width()   -   rcClientNew.Width();   //   修改对话框尺寸   
  rcWindow.bottom   +=   rcClientOld.Height()   -   rcClientNew.Height();     
  MoveWindow(rcWindow,FALSE);   //   Redraw   Window   

  RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);  
  
  INIT_EASYSIZE;
  return TRUE;
}


void CMonitorOverviewDialog::OnNMRClickServerList(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
  // TODO: 在此添加控件通知处理程序代码
  POINT pt;

  GetCursorPos(&pt);

  CMenu menu;
  VERIFY(menu.LoadMenu(IDR_LIST_POPUPMENU));

  CMenu* pPopup = menu.GetSubMenu(0); // 这个就是菜单在菜单资源条中的位置
  ASSERT(pPopup != NULL);

  // 控制菜单状态，单击空白处使菜单项变灰无效，当然也可以不显示菜单，看你的需要了
  if(pNMItemActivate->iItem != -1)
  {
    pPopup->EnableMenuItem(ID_Transfer_Monitor, MF_ENABLED);
    pPopup->EnableMenuItem(ID_Client_Monitor, MF_ENABLED);
    pPopup->EnableMenuItem(ID_Connect, MF_ENABLED);
    pPopup->EnableMenuItem(ID_Disconnect, MF_ENABLED);
    pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,pt.x,pt.y,this);
  }    

  *pResult = 0;
}

void CMonitorOverviewDialog::OnTransferMonitor()
{
  // TODO: Add your command handler code here
  monitor_transfer_dlg_ = new CMonitorTransferCtrl();
  monitor_transfer_dlg_->Create(IDD_Monitor_Transfer,this);
  monitor_transfer_dlg_->ShowWindow(SW_SHOW);
}

void CMonitorOverviewDialog::OnClientMonitor()
{
  // TODO: Add your command handler code here3
  monitor_client_dlg_ = new CMonitorClientCtrl();
  monitor_client_dlg_->Create(IDD_Monitor_Client,this);
  monitor_client_dlg_->ShowWindow(SW_SHOW);
}

void CMonitorOverviewDialog::OnConnectAll()
{
  invoker_->Connect();
  ReloadServerList();
}

void CMonitorOverviewDialog::OnAddServer()
{
  AddServerDialog dlg;
  dlg.DoModal();
  ReloadServerList();
}

void CMonitorOverviewDialog::OnDeleteSelectedServer()
{
  if( IDOK != MessageBox("确认从监控列表中删除该服务?", "删除", MB_OKCANCEL) )
    return;

  POSITION pos = m_server_list.GetFirstSelectedItemPosition();
  if (pos != NULL)
  {
    while (pos)
    {
      int nItem = m_server_list.GetNextSelectedItem(pos);
      string s (m_server_list.GetItemText(nItem,2));
      int conn_id = atoi(s.c_str());
      MonitorEnvironment::Instance()->server_manager()->delete_server_by_cid(conn_id);
      m_server_list.DeleteItem(nItem);
    }
  }
  //ReloadServerList();
}

void CMonitorOverviewDialog::ReloadServerList()
{
  m_server_list.DeleteAllItems();
  ConnectInfo* server_info = NULL;
  for(int i =0;i<MonitorEnvironment::Instance()->server_manager()->server_info_count();i++)
  {
    server_info = MonitorEnvironment::Instance()->server_manager()->server_infos(i);
    m_server_list.InsertItem(i,server_info->ip().c_str());      
    m_server_list.SetItemText(i,1 ,StrUtils::formatstring(5,"%d",server_info->port()).c_str());
    m_server_list.SetItemText(i,2 ,StrUtils::formatstring(5,"%d",server_info->connect_id()).c_str());
    m_server_list.SetItemText(i,3 ,CWordTranslation::TranslateServerStatus(server_info->status()).c_str());
  }
  m_server_list.SetColumnWidth( 0 , LVSCW_AUTOSIZE);
  m_server_list.SetColumnWidth( 1 , LVSCW_AUTOSIZE); 
}



void CMonitorOverviewDialog::OnPaint()
{
  if (IsIconic())
  {
    CPaintDC dc(this); // device context for painting
  }
  else
  {
    CDialog::OnPaint();
  }
}

void CMonitorOverviewDialog::OnSize(UINT nType, int cx, int cy)
{
  CDialog::OnSize(nType, cx, cy);

  UPDATE_EASYSIZE;
}

void CMonitorOverviewDialog::OnSizing(UINT fwSide, LPRECT pRect)
{
  CDialog::OnSizing(fwSide, pRect);

  EASYSIZE_MINSIZE(280,250,fwSide,pRect);
}

void CMonitorOverviewDialog::OnBnClickedButton1()
{
  // TODO: Add your control notification handler code here
}
