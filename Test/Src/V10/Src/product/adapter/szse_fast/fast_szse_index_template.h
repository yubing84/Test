#ifndef FAST_SZSE_INDEX_TEMPLATE
#define FAST_SZSE_INDEX_TEMPLATE

#include "../common/fast_template.h"
#include <map>


namespace wmdf
{
  class FastSzseIndexTemplate:public FastTemplate
  {
  public:
    FastSzseIndexTemplate(void);
    ~FastSzseIndexTemplate(void);
    virtual WindFastMessage* DecodeRaw(uint8_t* raw_data,uint32_t len);
  private:
    static const int item_count_ = 12;//ģ���һ���ӽڵ���������в�����constantԪ��
    std::map<std::string,int32_t> time_map_;
  };
}
#endif
