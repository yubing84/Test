#ifndef CFFE_ADAPTER_H_
#define CFFE_ADAPTER_H_

#include "product_adapter.h"


namespace wmdf
{
  class ProductSource;
  class Splitter;

#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */

  typedef struct Cffe_L2_Market_Struct
  {
    char InstrumentID[31];         // ��Լ����,��:IF1106

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

    double      BidPrice2;             // ����۶�				12
    double      BidVolume2;            // ��������				32
    double      AskPrice2;             // �����۶�				22
    double      AskVolume2;            // ��������				42

    double      BidPrice3;             // �������				13
    double      BidVolume3;            // ��������				33
    double      AskPrice3;             // ��������				23
    double      AskVolume3;            // ��������				43

    double      BidPrice4;             // �������				14
    double      BidVolume4;            // ��������				34
    double      AskPrice4;             // ��������				24
    double      AskVolume4;            // ��������				44

    double      BidPrice5;             // �������				15
    double      BidVolume5;            // ��������				35
    double      AskPrice5;             // ��������				25
    double      AskVolume5;            // ��������				45

    double UpperLimitPrice;            // ��ͣ���					211
    double LowerLimitPrice;            // ��ͣ���					212
  }Cffe_L2_Market_Struct;


#pragma pack(pop)

  class CffeL2Adapter : public ProductAdapter
  {
  public:
    CffeL2Adapter(ProductSource* product_source);
    virtual ~CffeL2Adapter();
  protected:
    virtual uint32_t ParseMessage(const uint32_t length);    
    void PublishMessages();
    void ClearRecords();
  private:
    Splitter* splitter_;
    std::vector<Cffe_L2_Market_Struct*> old_records_;
  };
}



#endif
