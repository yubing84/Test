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
    char InstrumentID[31];         // 合约代码,如:IF1106

    char TradingDay[9];            // 交易日, yyyymmdd			1
    char UpdateTime[13];           // 最后修改时间, hhMMss		2
    int UpdateMillisec;            // 最后修改毫秒, mmm			X

    double LastPrice;              // 最新价					3
    double OpenPrice;              // 今开盘					5
    double HighestPrice;           // 最高价					6
    double LowestPrice;            // 最低价					7
    double LastMatchQty;           // 最新成交量				X
    double Volume;                 // 总成交量					8
    double Turnover;               // 总成交金额				59
    double ClosePrice;             // 今收盘					3（重复）	X
    double AvgPrice;               // 当日均价					79			X

    double PreSettlementPrice;     // 昨结算					75
    double SettlementPrice;        // 今结算					74			X?
    double PreClosePrice;          // 昨收盘					4
    double PreOpenInterest;        // 昨持仓量					77
    double OpenInterest;           // 最新持仓量				76
    double InterestChange;         // 持仓量变化				78			X

    double      BidPrice1;             // 申买价一				11
    double      BidVolume1;            // 申买量一				31
    double      AskPrice1;             // 申卖价一				21
    double      AskVolume1;            // 申卖量一				41

    double      BidPrice2;             // 申买价二				12
    double      BidVolume2;            // 申买量二				32
    double      AskPrice2;             // 申卖价二				22
    double      AskVolume2;            // 申卖量二				42

    double      BidPrice3;             // 申买价三				13
    double      BidVolume3;            // 申买量三				33
    double      AskPrice3;             // 申卖价三				23
    double      AskVolume3;            // 申卖量三				43

    double      BidPrice4;             // 申买价四				14
    double      BidVolume4;            // 申买量四				34
    double      AskPrice4;             // 申卖价四				24
    double      AskVolume4;            // 申卖量四				44

    double      BidPrice5;             // 申买价五				15
    double      BidVolume5;            // 申买量五				35
    double      AskPrice5;             // 申卖价五				25
    double      AskVolume5;            // 申卖量五				45

    double UpperLimitPrice;            // 涨停板价					211
    double LowerLimitPrice;            // 跌停板价					212
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
