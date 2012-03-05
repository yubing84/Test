#ifndef FAST_SE_TRADE_TEMPLATE
#define FAST_SE_TRADE_TEMPLATE


#include "../common/fast_template.h"

namespace wmdf
{
  class FastSzseTradeTemplate:public FastTemplate
  {
  public:
    FastSzseTradeTemplate(void);
    ~FastSzseTradeTemplate(void);
    virtual WindFastMessage* DecodeRaw(uint8_t* raw_data,uint32_t len);
  private:
    static const int item_count_ = 11;//ģ���һ���ӽڵ���������в�����constantԪ��
  };
}

#endif
