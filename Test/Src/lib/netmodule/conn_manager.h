#ifndef WIND_NET_GROUP_CONN_MANAGER_
#define WIND_NET_GROUP_CONN_MANAGER_

#include "net_module.h"

namespace wmdf{

class Connection;

//ʵ�ֵ���ģʽ
NET_API class ConnManager
{
  friend class Server;
public:
  //���ڴ˶����ڳ���������ڼ䲻�����������Բ��ÿ����ڴ��ͷŵĲ���
  NET_API static ConnManager* GetInstance(int max_connection)
  {
    if(instance_==NULL)
      instance_ = new ConnManager(max_connection);
    return instance_;
  }

  NET_API ~ConnManager(void);
  //�̲߳���ȫ��
  NET_API int AddConnectionGroup();
  //�̲߳���ȫ��
  NET_API void AddConnection(int group_id,int socket_id);
  NET_API void RemoveConnection(int group_id,int socket_id);
	NET_API int GetConnectionCount(int group_id);
  NET_API void RemoveConnection(int socket_id);
  //����ֵΪconnection��socket_id
  int AddConnection(Connection* connection);
	void CloseConnection(int socket_id);
  NET_API void Close();
  //������ҪƵ��������Ϊ���Ч��ֱ������ʵ��
  NET_API Connection* GetConnection(int pos)
  {
    return connections_[pos];
  }

private:
  //ֻ��server���Է���
  void SendMsg(int socket_id,Message* msg);
  void BroadcastMsg(int group_id,Message* msg);
private:
  ConnManager(int max_connection);
  class ConnGroupManagerImpl;
  ConnGroupManagerImpl* impl_;
  Connection** connections_;
  static ConnManager* instance_;
};

}//end namespace
#endif

