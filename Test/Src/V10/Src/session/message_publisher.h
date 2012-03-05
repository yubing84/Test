#ifndef MESSAGE_PUBLISHER_H
#define MESSAGE_PUBLISHER_H

#include "feed_server.h"
#include "subscriber_manager.h"

namespace wmdf
{

  //���ڷ����ṹ���mdf message
  class MessagePublisher
  {
  public:
    MessagePublisher();
    virtual ~MessagePublisher(void);

    //�������ݲ�Ʒ����Ϣ
    static void PublishOneMessage(SharedMdfMessage message);
    static void PublishOneMessage(SharedRelayMdfMessage message);

    //������ز�Ʒ����Ϣ
    static void PublishMonitorMessage(SharedMdfMessage message);

  };


}

#endif
