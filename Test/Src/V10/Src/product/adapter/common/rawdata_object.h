#ifndef	RAWDATA_OBJECT_H
#define RAWDATA_OBJECT_H


#include "../../../include/wmdf_api.h"
#ifdef __linux__
#include <cstring>
#endif


#define UNKNOWN_TEMPLATE_ID 0

#define	TEMPLATE_SZSE_ORDERS_201																"UA201"
#define TEMPLATE_SZSE_ORDERS_201_TYPE													201

#define  TEMPLATE_SZSE_TRANSACTION_202													"UA202"
#define  SZSE_TRANSACTION_202_TYPE										202

#define  SZSE_MARKETDATA_103													"UA103"
#define  SZSE_MARKETDATA_103_TYPE											103

#define  SZSE_INDEXDATA_104														"UA104"
#define  SZSE_INDEXDATA_104_TYPE											104

#define SZSE_ORDERQUEUE_TYPE													100			//�Լ����壬��ģ���ж���


#define SSE_MARKETOVERVIEW_1115												"UA1115"
#define SSE_MARKETOVERVIEW_1115_TYPE									1115

#define SSE_VIRTUALAUCTIONPRICE_1107									"UA1107"
#define SSE_VIRTUALAUCTIONPRICE_1107_TYPE							1107

#define SSE_ORDERQUEUE_1111														"UA1111"
#define SSE_ORDERQUEUE_1111_TYPE											1111

#define SSE_MARKETDATA_1102														"UA1102"
#define SSE_MARKETDATA_1102_TYPE											1102

#define SSE_TRANSACTION_1101													"UA1101"
#define SSE_TRANSACTION_1101_TYPE											1101

#define SSE_INDEXDATA_1113														"UA1113"
#define SSE_INDEXDATA_1113_TYPE												1113

#define SSE_ORDERRANKING_1103													"UA1103"
#define SSE_ORDERRANKING_1103_TYPE										1103

#define SSE_TRANSACTIONRANKINGBYINDUSTRY_1104					"UA1104"
#define SSE_TRANSACTIONRANKINGBYINDUSTRY_1104_TYPE		1104

#define SSE_MARKETOVERVIEW_3115												"UA3115"
#define SSE_MARKETOVERVIEW_3115_TYPE									3115

#define SSE_MARKETDATA_3102														"UA3102"
#define SSE_MARKETDATA_3102_TYPE											3102

#define SSE_ORDERQUEUE_3111														"UA3111"
#define SSE_ORDERQUEUE_3111_TYPE											3111

#define SSE_INDEXDATA_3113														"UA3113"
#define SSE_INDEXDATA_3113_TYPE												3113

#define SSE_VIRTUALAUCTIONPRICE_3107									"UA3107"
#define SSE_VIRTUALAUCTIONPRICE_3107_TYPE							3107

#define SSE_TRANSACTION_3101													"UA3101"
#define SSE_TRANSACTION_3101_TYPE											3101

#define SSE_TRANSACTION_3201													"UA3201"
#define SSE_TRANSACTION_3201_TYPE											3201

#define SSE_MARKETDATA_3202														"UA3202"
#define SSE_MARKETDATA_3202_TYPE											3202

#define SSE_FILTER_TYPE																9999


namespace wmdf{

	typedef enum StepType
	{
		ST_SSE,
		ST_SZSE
	}StepType;

	typedef struct WindStepMessage
	{
		int MsgType;
		void* Data;
	}WindStepMessage;

	typedef struct WindFastMessage
	{
		int32_t MsgType;
		int32_t Size;
		void* Data;
	}WindFastMessage;

	typedef struct CompareStruct
	{
		int32_t trade_time;
		double new_price;
		int64_t volume;
		double peratio1;
		double peratio2;
	}CompareStruct;

	typedef struct Transaction
	{
		char wind_code[16];         //֤ȯ����
		int32_t trade_time;    //����ʱ��
		int32_t set_no;             //֤ȯ������ szse
		int32_t rec_no;             //�ɽ����
		int32_t buyOrderRecNo;      //��ί������ szse
		int32_t sellOrderRecNo;     //����ί������ szse
		double price;               //�ɽ��۸�
		int32_t trade_qty;          //�ɽ�����
		int8_t order_kind;          //�ɽ���� szse
		int8_t function_code;       //�ɽ����� szse
		//int32_t trade_channel;        //X sse
		double trade_money;          //X sse
	}Transaction;

	typedef struct BidPriceLevel
	{
		uint64_t  BidSize; //����3λС��
		double  BidPx; //����3λС��
	}BidPriceLevel;

	typedef struct OfferPriceLevel
	{
		uint64_t  OfferSize; //����3λС��
		double  OfferPx; //����3λС��
	}OfferPriceLevel;

	typedef struct MarketData
	{
		char wind_code[16];
		int32_t trade_date;              //�������ڣ�1
		int32_t trade_time;        //����ʱ�䣬2

		double new_price;               //���¼ۣ�3
		double pre_close;              //ǰ�ռۣ�4
		double today_open;              //���̼ۣ�5
		double today_high;              //��߼ۣ�6
		double today_low;               //��ͼۣ�7

		int64_t volume;                 //�ܳɽ�����8
		double total_amount;            //�ܳɽ��59

		double bid_price[10];              //��1�ۣ�11
		double ask_price[10];              //��1�ۣ�21
		int32_t bid_size[10];           //��1����31
		int32_t ask_size[10];           //��1����41
		int64_t transactions_count;     //�����ܱ���, 71
		double weighted_average_best_bid;	//��Ȩƽ��ί��۸�86����L2
		double weighted_average_best_ask; //��Ȩƽ��ί���۸�87����L2
		double peratio1;
		double peratio2;                    //253 or 261
		int64_t l2_total_bid_qty;       //ί������������340����L2
		int64_t l2_total_offer_qty;     //ί������������341����L2
		int8_t trade_status;
	}MarketData;

	typedef struct IndexData
	{
		int32_t DataTimeStamp;
		int32_t DataStatus;
		char SecurityID[16];
		double PreClosePx; //����3λС��
		double OpenPx; //����3λС��
		double HighPx; //����3λС��
		double LowPx;  //����3λС��
		double LastPx; //����3λС��
		int64_t  volume;
		double total_amount;            //�ܳɽ��59
		int64_t transactions_count;
	}IndexData;


	typedef struct Orders
	{
		char         wind_code[16];                 //֤ȯ����
		time_stamp_t order_time;                    //ί��ʱ��
		int32_t      set_no;                        //֤ȯ������
		int32_t      rec_no;                        //ί������
		int32_t      size;                          //ί������,  ��
		double       price;                         //�۸�
		char         order_kind;                    //ί�����,  1=ί��, 2=ί��, 3=����
		char         function_code;                 //�ɽ�����
	}Orders;

	typedef struct OrderItem
	{
		int32_t order_queue_operator;           //0-Absent, 1-Add,2-Update,3-Delete
		int32_t order_queue_operator_entry_id;  //Start from 0, No Meaning if < 0
		int32_t order_qty;
	}OrderItem;


	typedef struct OrderQueuePriceLevel
	{
		int32_t price_level_operator;     //0-Absent,1-Add,2-Update,3-Delete
		double price;
		int32_t orders_total;             //��ǰ��λ����ί�б���
		int32_t orders_count;             //�˴η����仯��ί�б���
		OrderItem* order_queue_items;     // size = orders_count
	}OrderQueuePriceLevel;


	typedef struct OrderQueueImage
	{
		char wind_code[16];
		int32_t date_time_stamp;             // 163025
		uint8_t side[8];                             // 1 = Bid Queue, 2 = Ask Queue, other: Invalid
		int32_t image_status;                     // 1 = FullImage, 2 = Update, other: Invalid
		int32_t price_level_count;                // Number of PriceLevelItems, should = PriceLevel_items.size();
		OrderQueuePriceLevel* order_queue_levels;
	}OrderQueueImage;


  typedef struct PriceLevel_3202
  {
    int32_t price_level_operator;
    double price;
    int32_t order_qty;
    int32_t num_order;
    int32_t no_order;
    OrderItem* order_items;
  }PriceLevel_3202;

  typedef struct MarketData_3202
  {
    char windcode[16];
    int32_t date_time_stamp;
    int32_t image_status;
    double preclose_price;
    double open_price;
    double high_price;
    double low_price;
    double last_price;
    double close_price;
    int8_t instrument_status[8];
    int64_t num_trades;					//transaction_count
    int64_t total_volume_trade;	//volume
    double total_value_trade;		//total_amount
    int64_t total_bid_qty;
    double weighted_avg_bid_price;
    double alt_weighted_avg_bid_price;
    int64_t total_offer_qty;
    double weighted_avg_offer_price;
    double alt_weighted_avg_offer_price;
    double iopv;
    double yield_to_maturity;
    int64_t total_warrant_exec_qty;
    double warrant_lower_price;
    double warrant_upper_price;
    int32_t num_of_bid_level;
    PriceLevel_3202 *bidlevels;
    int32_t num_of_offer_level;
    PriceLevel_3202 *offerlevels;
  }MarketData_3202;

	typedef struct MarketOverView1115
	{
		char windcode[16];
		int32_t date_time_stamp;
		int32_t ashareindex;
		int32_t bshareindex;
		int32_t sseindex;
		int32_t origtime;
		int32_t origdate;
	}MarketOverView1115;

	typedef struct MarketOverView3115
	{
		char windcode[16];
		int32_t date_time_stamp;
		int32_t origtime;
		int32_t origdate;
	}MarketOverView3115;


	typedef struct VirtualAuctionPrice
	{
		char windcode[16];
		int32_t date_time_stamp;
		double price;
		int32_t virtualauctionqty;
		int32_t bidleaveqty;
		int32_t askleaveqty;
	}VirtualAuctionPrice;
}

#endif
