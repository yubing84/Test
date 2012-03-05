#ifndef FAST_SZSE_ORDERS_TEMPLATE
#define FAST_SZSE_ORDERS_TEMPLATE

#include "../common/fast_template.h"

namespace wmdf
{
  class FastSzseOrdersTemplate:public FastTemplate
  {
  public:
    FastSzseOrdersTemplate(void);
    ~FastSzseOrdersTemplate(void);
    virtual WindFastMessage* DecodeRaw(uint8_t* raw_data,uint32_t len);
  private:
    static const int item_count_ = 9;//ģ���һ���ӽڵ���������в�����constantԪ��
  };
}

#endif
