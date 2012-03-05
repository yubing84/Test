#ifndef WIND_NET_CLIENT_
#define WIND_NET_CLIENT_

#include "net_module.h"
#include "service.h"
#include "message_factory.h"

namespace wmdf{

NET_API class Client
{
public:
  //max_packet_size  �������ȣ����������ݰ����ȴ�����ʱ����Ϊ�˰��ǷǷ����ݰ�ֱ�Ӻ���
  //max_buf_msg ��������Ϣ�����������ۼƵ���Ϣ����������max_buf_msgʱ���������е�ȫ����Ϣ�������
  //has_active_heart �Ƿ�������Ӧ����������clientһֱ���ⷢ����������
  //reconnect �Ͽ����Ƿ�����
  //thread_num �ͷ���ӵ�е��߳���
  NET_API Client(int max_packet_size,int max_buf_msg, int thread_num=1);
  NET_API ~Client();
	NET_API void Init(int client_type=0);
  NET_API int Connect(const char* ip_address,int port,size_t timeout=0);
  NET_API void SendMsg(Message* msg);
  NET_API Message* RecvMsg();
  NET_API void Close();

  NET_API void SetCloseCallback(CloseCallback callback);
  NET_API void SetEventCallback(EventCallback callback);
	NET_API void SetRecvCallback(RecvCallback callback);
  NET_API void SetState(void* state);

private:
  class ClientImpl;
  ClientImpl* impl_;

};
}//end namespace
#endif

