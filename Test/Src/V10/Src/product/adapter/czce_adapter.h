#ifndef CZCE_ADAPTER_H_
#define CZCE_ADAPTER_H_

#include "product_adapter.h"



namespace wmdf
{

#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */

  typedef struct CZC_FuturesDataStruct_L2
  {
    char Length[3];						   //�ṹ�峤��

    char InstrumentId[20];       //��Լ����

    char PreClose[12];					//ǰ���̼۸�		4
    char PreSettle[12];					//ǰ����۸�		75
    char OpenPrice[12];					//���̼�			5

    char BidPrice[12];					//����۸�			11
    char BidLot[12];					  //��������			31
    char AskPrice[12];					//������			21
    char AskLot[12];					  //��������			41

    char LastPrice[12];					//���¼�			3
    char OpenInterest[12];		  //�ֲ���			76

    char HighPrice[12];					//��߼�			6
    char LowPrice[12];					//��ͼ�			7
    char ClosePrice[12];				//���̼�			3(�ظ�) X
    char SettlePrice[12];				//���ս�������	74
    char ClearPrice[12];				//�����			X

    char AveragePrice[12];			//����				79
    char LifeHigh[12];					//��ʷ��߳ɽ��۸�	X
    char LifeLow[12];					  //��ʷ��ͳɽ��۸�	X
    char HighLimit[12];					//��ͣ��			211
    char LowLimit[12];					//��ͣ��			212

    char TotalVolume[12];				//�ܳɽ���		8

  }STRUCT_CZC;

#pragma pack(pop)

  class CzceAdapter : public ProductAdapter
  {
  public:
    CzceAdapter(ProductSource* product_source);
    virtual ~CzceAdapter();
  protected:
    virtual uint32_t ParseMessage(const uint32_t length);    
    void PublishMessages();
    void ClearRecords();
  private:
    
    std::vector<STRUCT_CZC*> old_records_;
  };
}


#endif
