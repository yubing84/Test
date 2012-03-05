#ifndef SHFE_ADAPTER_H_
#define SHFE_ADAPTER_H_

#include "product_adapter.h"

namespace wmdf
{
  class Splitter;


#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */

  typedef struct SHFE_FuturesDataStruct_L2
  {
    char InstrumentID[31];         // ��Լ����

    char TradingDay[9];            // ������, yyyymmdd			1
    char UpdateTime[13];           // ����޸�ʱ��, hhMMss		2
    int UpdateMillisec;            // ����޸ĺ���, mmm			X

    double LastPrice;              // ���¼�					3
    double OpenPrice;              // ����					5
    double HighestPrice;           // ��߼�					6
    double LowestPrice;            // ��ͼ�					7
    double LastMatchQty;           // ���³ɽ���				X
    double Volume;                 // �ܳɽ���					8
    double Turnover;               // �ܳɽ����				59
    double ClosePrice;             // ������					3���ظ���	X
    double AvgPrice;               // ���վ���					79			X

    double PreSettlementPrice;     // �����					75
    double SettlementPrice;        // �����					74			X?
    double PreClosePrice;          // ������					4
    double PreOpenInterest;        // ��ֲ���					77
    double OpenInterest;           // ���³ֲ���				76
    double InterestChange;         // �ֲ����仯				78			X

    double      BidPrice1;             // �����һ				11
    double      BidVolume1;            // ������һ				31
    double      AskPrice1;             // ������һ				21
    double      AskVolume1;            // ������һ				41


    double UpperLimitPrice;        // ��ͣ���					211	
    double LowerLimitPrice;        // ��ͣ���					212
  }STRUCT_SHFE;

#pragma pack(pop)


  class ShfeAdapter : public ProductAdapter
  {
  public:
    ShfeAdapter(ProductSource* product_source);
    virtual ~ShfeAdapter();
  protected:
    virtual uint32_t ParseMessage(const uint32_t length);    
    void PublishMessages();
    void ClearRecords();
    bool IsShfeCode(int32_t n);
  private:
    Splitter* splitter_;
    std::vector<STRUCT_SHFE*> old_records_;
  };
}


#endif
