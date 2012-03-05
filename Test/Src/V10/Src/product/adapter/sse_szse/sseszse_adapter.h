#ifndef SSESZSE_ADAPTER_H
#define SSESZSE_ADAPTER_H

#include "../product_adapter.h"

namespace wmdf
{
  class DataDecoder;
  class SecurityContainerManager;

  class SSESZSEAdapter : public ProductAdapter
  {
  public:
    SSESZSEAdapter(ProductSource* product_source);
    virtual ~SSESZSEAdapter();
  protected:
    virtual uint32_t ParseMessage(const uint32_t length);    
    void PublishMessages();    
  protected:
    virtual void LaunchMarketSnapshotL2(SecurityContainerManager* scm)=0;
    virtual void LaunchL2Transactions(SecurityContainerManager* scm)=0;
    virtual void LaunchOrderQueueL2(SecurityContainerManager* scm)=0;
    virtual void LaunchSZSEL2Orders(SecurityContainerManager* scm)=0;

  private:
    DataDecoder* data_decoder_;
    uint8_t buf_unzip[1024*512];
  };
}

#endif
