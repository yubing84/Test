#include <vector>
#include "../../include/wmdf_api.h"

#pragma pack(push)
#pragma pack(1)


struct L2_OrderItem            // ����Level2, ���ί��
{
  int64_t	OrderNumber;   // ί�б�ţ���ֻ��Ʊ������
  int64_t	RecNo;         // ί������, TradeIndex
  double	OrderPrice;
  int64_t	OrderQty;      // ί������,  ��
  int64_t	OrderTime;     // ί��ʱ��,  HHMMSSXX
  int64_t	OrderType;    // ί�����,  1=ί��, 2=ί��, 3=����
};

/*

struct L2_Transaction_RevertDataItem
{
  unsigned int	RevertIndex;        // ���ȳɽ����
  unsigned int	MSTime;             // �ɽ�ʱ����뼶
  unsigned char	TradeSide;         // 1=������, 2=��������, 0=����δ֪
  unsigned int	TradePrice;         // ��ʳɽ��۸�
  unsigned int	TradeVolume;        // ��ʳɽ���������
  unsigned int	BidIndexRef;        // �˿̶�Ӧί����
  unsigned int	BidVol;             // �˿̶�Ӧ�򵥴�С������
  unsigned int	OfferIndexRef;      // �˿̶�Ӧί�����
  unsigned int	OfferVol;           // �˿̶�Ӧ������С������
  unsigned char	BuyTradeFlag;      // ����������ɽ���ʶ 0 = ��ʼ 1= ���� 2= �м䵥 3 = ����
  unsigned char	SellTradeFlag;     // �����������ɽ���ʶ 0 = ��ʼ 1= ���� 2= �м䵥 3 = ����
};

typedef std::vector<L2_Transaction_RevertDataItem> L2_Transaction_RevertData;
*/


struct L2_TransactionItem      // Level2��ʳɽ�
{
  int64_t	TradeNumber;   // �ɽ���ţ���0��ʼ�ۼ�
  int64_t	TradeIndex;    // �ɽ���ţ�����������
  int64_t	TradeTime;     // �ɽ�ʱ��, HHMMSSXX,   xx ��ȷΪ�ٷ�֮һ��
  double TradePrice;
  int64_t	TradeQty;      // �ɽ�����
  int64_t TradeMoney;
};

struct L2_OrderQueueItem
{
  unsigned char PriceLevelOperator;			//1-Add,2-Update,3-Delete
  unsigned int  OrderQueueOperatorEntryID;	// Start from 0, No Meaning if
  unsigned int  OrderQty;
};


struct L2_OrderQueue_PriceLevel
{
  unsigned char		PriceLevelOperator;	//1-Add,2-Update,3-Delete
  unsigned int		Price;
  unsigned int		NumOfOrders;		// ��ǰ��λ����ί�б���
  unsigned int		NoOrders;			// �˴η����仯��ί�б���
  L2_OrderQueueItem* Orders;				// size = NoOrders
};


struct L2_OrderQueue
{
  unsigned int  DateTimeStamp;  // 163025
  unsigned char Side;           // 1 = Bid Queue, 2 = Ask Queue, other: Invalid
  unsigned char ImageStatus;    // 1 = FullImage, 2 = Update, other: Invalid
  unsigned int  NoPriceLevel;   // Number of PriceLevelItems, should = PriceLevel_items.size();
  L2_OrderQueue_PriceLevel* PriceLevel;   //
};

typedef union _WnValue
{
  signed char    c;      // signed character
  unsigned char  b;      // unsigned character
  signed short   s;      // signed short
  unsigned short w;      // unsigned short
  signed long    l;      // signed long
  unsigned long  u;      // unsigned int
  long long		   i;	   // __int64
  float          f;      // float
  double         d;      // double
} WnValue;


typedef struct _Old_WnField
{
  unsigned short    nFieldId;      // field ID defined by WIND
  unsigned char    bValueType;    // value type(ref. Part I)
  WnValue Value;         // union to hold the actual value
} Old_WnField;



// ��������
typedef struct _WnItem
{
  unsigned char PriceLevelOperator;
  unsigned int  OrderQueueOperatorEntryID;   // Start from 0, No Meaning if
  unsigned int  OrderQty;
}WnItem;

typedef std::vector<WnItem> L2_OrderQueueItems;

typedef struct _WnPriceLevel
{
  unsigned char      PriceLevelOperator;
  double				Price;
  unsigned int       NumOfOrders;    // ��ǰ��λ����ί�б���
  unsigned int       NoOrders;       // �˴η����仯��ί�б���
  L2_OrderQueueItems Orders;         // size = NoOrders
}WnPriceLevel;

typedef struct _WnOrderQueue
{
  unsigned int  DateTimeStamp;		// 163025
  unsigned char Side;					// 1 = Bid Queue, 2 = Ask Queue, other: Invalid
  unsigned char ImageStatus;			// 1 = FullImage, 2 = Update, other: Invalid
  unsigned int  NoPriceLevel;			// Number of PriceLevelItems, should = PriceLevel_items.size();
  std::vector<WnPriceLevel> PriceLevel;	//
}WnOrderQueue;



#pragma pack(pop)
