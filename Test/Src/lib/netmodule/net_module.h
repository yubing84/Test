#ifndef NET_MODULE_
#define NET_MODULE_

#include <time.h>
#include "stdint.hpp"


#ifdef __cplusplus
extern "C" {
#endif

#ifndef NET_API
#define NET_API
#endif
// #if defined _WIN32
// #       pragma warning(disable:4091)
// #   if defined DLL_EXPORT
// #       define NET_API __declspec(dllexport)
// #   else
// #       define NET_API __declspec(dllimport)
// #   endif
// #else
// #   if defined __SUNPRO_C  || defined __SUNPRO_CC
// #       define NET_API __global
// #   elif (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER
// #       define NET_API __attribute__ ((visibility("default")))
// #   else
// #       define NET_API
// #   endif
// #endif



typedef enum EventState{MSG_DEBUG,MSG_INFO,MSG_ERROR}EventState;

typedef enum EventNo{
  E_OPEN,
  E_CONNECTED,
  E_DISCONNECTED,
  E_CLOSE,
  E_TIMEOUT,
  E_BUF_OVERFLOW,//���ݻ����������
  E_BUF_OVERFLOW_WARN,//���ݻ��������������,
  E_EOF,              //end of file ���ӵ���һ���Ͽ�������
  E_DECODE,
  E_UNKNOW
}EventNo;

typedef struct EventMsg
{
  int EventId;
  EventState State;
  time_t Time;
  char Context[80];
}EventMsg;

#pragma pack(push, 1)
typedef struct Message
{
  uint8_t STX;
  uint32_t msg_len;          //����Message�ĳ���
	uint32_t local_time;
  uint32_t packet_num;       //���ţ�ÿ����Ʒ��������
  uint16_t product_id;
  uint16_t message_id;
  uint8_t placeholder[2];
	uint8_t check_sum;
  uint8_t data[1];
}Message;
#pragma pack(pop)

struct EventCallbackArgs
{
  void* handle;//ע�⣺����handleΪclient ��server�ľ��(ָ��)
  int socket_id;
  EventMsg* event_msg;
  void* state;
};

struct MsgCallbackArgs
{
  void* handle;//ע�⣺����handleΪclient ��server�ľ��(ָ��)
  int socket_id;
  Message* msg;
  void* state;
};

//����connection��TCP���ò���
enum Option
{
  reuse_address,
  no_delay
};
#define MSG_HEADER_LEN (sizeof(Message)-sizeof(char))
#define RELAY_CLIENT 1
#define MDF_CLIENT 0
//////////////////////////////////////////////////////////////////////////
//Callback
//ע�⣺����handleΪclient ��server�ľ����ָ�룩 state
//��client����socket_idȫ��Ϊ0��û��ʵ�����壬ֻ��Ϊ������ͳһ
typedef void (*ConnectedCallback)(EventCallbackArgs& args);

//EventMsg ��Ҫ�ͷ��ֶ��ͷ��ڴ�
typedef void (*CloseCallback)(EventCallbackArgs& args);

typedef void (*RecvCallback)(MsgCallbackArgs& args);
//EventMsg ��Ҫ�ͷ��ֶ��ͷ��ڴ�
typedef void (*EventCallback)(EventCallbackArgs& args);


NET_API Message* CreateMessage(int size); //sizeΪdata�ĳ���
NET_API void ReleaseEventMsg(EventMsg* data);
NET_API void ReleaseMessage(Message* msg);
//client �ĳ�ʼ��
NET_API void* C_Client(int max_packet_size,int max_buf_msg);

NET_API int C_Connect(void* client, const char* ip_address,int port,size_t timeout);
NET_API void C_SendMsg(void* client,Message* msg);
NET_API Message* C_RecvMsg(void* client);
NET_API void C_Close(void* client);
NET_API void C_SetCloseCallback(void* client,CloseCallback callback);
NET_API void C_SetEventCallback(void* client,EventCallback callback);
NET_API void C_SetRecvCallback(void* client,RecvCallback callback);

NET_API void* S_Server(const char* ip_address,int port,int thread_num,int max_connection_count,int max_packet_size,int max_cache_msg_count);

NET_API int S_Start(void* server);
NET_API void S_Stop(void* server);
//NET_API ConnManager* GetConnManager();

NET_API void S_SendMsg(void* server,int socket_id,Message* msg);
NET_API void S_BroadcastMsg(void* server,int group_id,Message* msg);

NET_API void S_SetConnectedCallback(void* server,ConnectedCallback callback);
NET_API void S_SetCloseCallback(void* server,CloseCallback callback);
NET_API void S_SetRecvCallback(void* server,RecvCallback callback);
NET_API void S_SetEventCallback(void* server,EventCallback callback);

#ifdef __cplusplus
}
#endif




#endif
