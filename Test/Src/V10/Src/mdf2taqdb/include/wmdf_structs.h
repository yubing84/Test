#ifndef WMDF_STRUCTS_H
#define WMDF_STRUCTS_H

#include "wmdf_api.h"

/************************************************************************/
/*                         ����������Ϣ                           */
/************************************************************************/
#pragma pack(push, 1)

// ����������Ϣͷ��

typedef struct SystemMessageHeader
{
  int8_t major_version;
  int8_t minor_version;
}SystemMessageHeader;

//
typedef struct HeartBeat
{
  int8_t place_holder;
}HeartBeat;

// ���Ĳ�Ʒ����Ϣ
typedef struct ProductInfo
{
  int16_t product_id;
  int8_t major_version;
  int8_t minor_version;
  int8_t codec;
}ProductInfo;

// ��¼������Ϣ���ɿͻ��˷����������
typedef struct LoginRequest
{
	// �û���������
	uint8_t user_name[32];         //�û����32�ֽ�
	uint8_t password[16];          //�����16�ֽ�
  int16_t product_count;
  ProductInfo* product;
}LoginRequest;

typedef struct ServerInfo
{
  uint8_t server_addr[15];
  uint32_t server_port;
}ServerInfo;

typedef struct MessageInfo
{
  int16_t message_id;
  int8_t message_status;  //1 valid; 2 invalid;
}MessageInfo;

typedef struct ProductStatus
{
  int16_t product_id;
  int8_t product_status;  //1 valid; 2 invalid;
  int8_t major_version;
  int8_t minor_version;
  int8_t codec;
  int32_t message_count;  
  MessageInfo* message_info;
}ProductStatus;

// ��¼��Ӧ��Ϣ���ɷ������Ӧ�ͻ���
typedef struct LoginResponse
{
	int8_t ack_type;
  uint32_t user_id;    //valid when ack_type = succeed;
  int32_t server_count;
  ServerInfo* serverinfo;
  int32_t product_count;
  ProductStatus* product_status;
}LoginResponse;

// �ǳ�֪ͨ��Ϣ�����ڿͻ��˵ǳ�WMDFϵͳ
typedef struct Logout
{
  int8_t logout_type;   // define logout type. 1 is server notify to logout;
}Logout;

//�г�Ԥ���̺�����ʱ����
typedef struct MarketDateSignal
{
  int8_t market_operation;  //1= ���� 2 = ����
  date_t market_date;
}MarketDateSignal;

/************************************************************************/
/*                         �����Ϣ                               */
/************************************************************************/
// �����Ϣͷ
typedef struct MonitorMessageHeader
{
  int8_t place_holder;
}MonitorMessageHeader;

//��������ͳ��
typedef struct TransferDataStat
{
  int16_t product_id;                 //��ƷID
  double  receive_data_flow;          //���յ����ֽ�����(KB/S)
  double  receive_pack_flow;          //���յ��İ�����
  uint32_t receive_packet_count;       //���յ��İ���
  uint32_t pre_receive_packet_count;   //�ϴ�ͳ��ʱreceive����
  uint64_t receive_data_size;          //ԭʼ��С(KB)
  uint64_t pre_receive_data_size;      //�ϴ�ͳ��ʱ������С(KB)

  double  send_data_flow;             //�����ֽ�����(KB/S)
  double  send_pack_flow;             //���Ͱ�����
  uint32_t send_packet_count;          //�ѷ��Ͱ���
  uint32_t pre_send_packet_count;      //�ϴ�ͳ��ʱ�ѷ��Ͱ���
  uint32_t send_packet_delta;          //ǰ��ͳ�Ƶ����ڷ��͵İ��� 

  uint64_t encoded_size;               //������С(KB)
  uint64_t pre_encoded_size;           //�ϴ�ͳ��ʱ������С(KB)  

  uint64_t binary_struct_size;         //�����ƽṹ���С(KB)  
  double compression_ratio;           //ѹ����(%)
  uint32_t total_msg_delay;            //ƽ���ӳ�(ms)
  uint32_t pre_total_msg_delay;        //�ϴ���Ϣ���ӳ�
  uint32_t msg_avg_delay;              //ƽ���ӳ�
  uint32_t delayed_msg_delta;          //ǰ��ͳ���ӳٵ����ڷ������ӳٰ���
  uint32_t delayed_msg_count;          //�ӳٰ�������
  uint32_t pre_delayed_msg_count;      //�ϴ��ӳٰ�������
}TransferDataStat;

typedef struct ClientStatus
{
  int32_t socket_id;
  uint8_t user_name[32];         //�û����32�ֽ�
	uint8_t client_ip[15];         //�ͻ�IP 
  time_stamp_t duration;         //����ʱ��
	double send_data_flow;         //��������(KB/S)
  int64_t send_bytes;            //�ܵķ����ֽ���
  int64_t pre_send_bytes;        //ǰһ�η����ֽ���
  int32_t msg_in_queue;          //��������е����ݰ�����
	int32_t product_count;
	ProductInfo* product_infos;
}ClientStatus;

/************************************************************************/
/*                         ����������Ϣ                           */
/************************************************************************/

// ����������Ϣͷ
typedef struct MarketMessageHeader
{
	int8_t place_holder;
}MarketMessageHeader;

// ����L1�г�����-----------------------Done
typedef struct L1MarketSnapshot
{
	char wind_code[16];
	date_t trade_date;
	time_stamp_t trade_time;

	double new_price;
	double prev_close;
	double today_open;
	double today_high;
	double today_low;

	int64_t volume;
	double total_amount;	
	//int64_t delta_volume;
	//double delta_amount;

	double bid_price1;
	double bid_price2;
	double bid_price3;
	double bid_price4;
	double bid_price5;
	double ask_price1;
	double ask_price2;
	double ask_price3;
	double ask_price4;
	double ask_price5;
	int32_t ask_volume1;
	int32_t ask_volume2;
	int32_t ask_volume3;
	int32_t ask_volume4;
	int32_t ask_volume5;
	int32_t bid_volume1;
	int32_t bid_volume2;
	int32_t bid_volume3;
	int32_t bid_volume4;
	int32_t bid_volume5;	
}L1MarketSnapshot;

// L2�г�����
typedef struct L2MarketSnapshot
{
	char wind_code[16];             
	date_t trade_date;              //�������ڣ�1
  time_stamp_t trade_time;        //����ʱ�䣬2  

  double new_price;               //���¼ۣ�3
  double prev_close;              //ǰ�ռۣ�4
  double today_open;              //���̼ۣ�5
  double today_high;              //��߼ۣ�6
  double today_low;               //��ͼۣ�7
  
  int64_t volume;                 //�ܳɽ�����8
  double total_amount;            //�ܳɽ��59

  double bid_price1;              //��1�ۣ�11
	double bid_price2;              //��2�ۣ�12            
	double bid_price3;              //��3�ۣ�13
	double bid_price4;              //��4�ۣ�14
	double bid_price5;              //��5�ۣ�15
	double bid_price6;              //��6�ۣ�16
	double bid_price7;              //��7�ۣ�17
	double bid_price8;              //��8�ۣ�18
	double bid_price9;              //��9�ۣ�19
	double bid_price10;             //��10�ۣ�20
	double ask_price1;              //��1�ۣ�21
	double ask_price2;              //��2�ۣ�22
	double ask_price3;              //��3�ۣ�23
	double ask_price4;              //��4�ۣ�24
	double ask_price5;              //��5�ۣ�25
	double ask_price6;              //��6�ۣ�26
	double ask_price7;              //��7�ۣ�27              
	double ask_price8;              //��8�ۣ�28
	double ask_price9;              //��9�ۣ�29
	double ask_price10;             //��10�ۣ�30
  int32_t bid_volume1;           //��1����31
  int32_t bid_volume2;           //��2����32
  int32_t bid_volume3;           //��3����33
  int32_t bid_volume4;           //��4����34
  int32_t bid_volume5;           //��5����35
  int32_t bid_volume6;           //��6����36
  int32_t bid_volume7;           //��7����37
  int32_t bid_volume8;           //��8����38
  int32_t bid_volume9;           //��9����39
  int32_t bid_volume10;          //��10����40
	int32_t ask_volume1;           //��1����41
	int32_t ask_volume2;           //��2����42
	int32_t ask_volume3;           //��3����43
	int32_t ask_volume4;           //��4����44
	int32_t ask_volume5;           //��5����45
	int32_t ask_volume6;           //��6����46
	int32_t ask_volume7;           //��7����47
	int32_t ask_volume8;           //��8����48
	int32_t ask_volume9;           //��9����49
	int32_t ask_volume10;          //��10����50

	
  int64_t transactions_count;     //�����ܱ���, 71
  double weighted_average_best_bid;	//��Ȩƽ��ί��۸�86����L2
  double weighted_average_best_ask; //��Ȩƽ��ί���۸�87����L2
  int64_t l2_total_bid_qty;       //ί������������340����L2
  int64_t l2_total_offer_qty;     //ί������������341����L2
}L2MarketSnapshot;


// ��ʳɽ�
typedef struct L2Transaction
{
	char wind_code[16];         //֤ȯ����
	time_stamp_t trade_time;    //����ʱ��
	int32_t set_no;             //֤ȯ������ szse  
	int32_t rec_no;             //�ɽ����
	int32_t buyOrderRecNo;      //��ί������ szse
	int32_t sellOrderRecNo;     //����ί������ szse
	double price;               //�ɽ��۸�
	int32_t trade_qty;          //�ɽ�����
	int8_t order_kind;          //�ɽ���� szse
	int8_t function_code;       //�ɽ����� szse
  int32_t trade_channel;        //X sse
  int64_t trade_money;          //X sse
}L2Transaction;


// L2ί�ж��м�����
typedef struct L2OrderQueueItem
{
	int32_t order_queue_operator;           //0-Absent, 1-Add,2-Update,3-Delete
	int32_t order_queue_operator_entry_id;  //Start from 0, No Meaning if
	int32_t order_qty;
}L2OrderQueueItem;

// L2ί�ж��м���
typedef struct L2OrderQueuePriceLevel
{
	int32_t price_level_operator;     //0-Absent,1-Add,2-Update,3-Delete
	double price;
	int32_t orders_total;             //��ǰ��λ����ί�б���
	int32_t orders_count;             //�˴η����仯��ί�б���
	L2OrderQueueItem* order_queue_items;     // size = orders_count
}L2OrderQueuePriceLevel;

// L2ί�ж���
typedef struct L2OrderQueue
{
	char wind_code[16];
	time_stamp_t date_time_stamp;             // 163025
	uint8_t side;                             // 1 = Bid Queue, 2 = Ask Queue, other: Invalid
	int32_t image_status;                     // 1 = FullImage, 2 = Update, other: Invalid
	int32_t price_level_count;                // Number of PriceLevelItems, should = PriceLevel_items.size();
	L2OrderQueuePriceLevel* order_queue_levels;
}L2OrderQueue;

//�Ͻ����г��ſ�
typedef struct MarketOverView
{
	char wind_code[16];								
	time_stamp_t date_time_stamp;							//163025
	int32_t origtime;													//����ʱ��
	int32_t origdate;													//��������
}MarketOverView;

//�Ͻ������⾺��
typedef struct VirtualAuctionPrice
{
	char wind_code[16];
	time_stamp_t date_time_stamp;							//163025
	double price;														//���⿪�̲ο��۸�
	int32_t virtual_auction_qty;							//����ƥ����
	int32_t leave_qty;												//����δƥ����
	uint8_t side;															//1 = bid, 2 = offer
}VirtualAuctionPrice;



// ��L2���ί��
typedef struct SZSEL2Order
{
	char wind_code[16];           //֤ȯ����
	int32_t set_no;               //X
	int32_t rec_no;               //ί������
	double order_price;           //�۸�
	int32_t order_qty;            //ί������,  ��
	time_stamp_t order_time;      //ί��ʱ��,  HHMMSSXX
	char order_kind;              //ί�����,  1=ί��, 2=ί��, 3=����
	char function_code;           //�ɽ�����
}SZSEL2Order;


// �н���L2�г�����
typedef struct CFEL2MarketSnapshot
{
	char wind_code[16];                 // ��Լ����,��:IF1106
	date_t trade_date;                  // ��������, yyyymmdd			1
	time_stamp_t trade_time;            // ����޸�ʱ��, hhMMss		2
  //int UpdateMillisec;                 // ����޸ĺ���, mmm			X
	double new_price;                   // ���¼�					3
	double prev_close;                  // ������					4
	double today_open;                  // ����					5
	double today_high;                  // ����߼�					6
	double today_low;                   // ����ͼ�					7
	
	double bid_price1;                  // �����һ				11
	double bid_price2;                  // ����۶�				12
	double bid_price3;                  // �������				13
	double bid_price4;                  // �������				14
	double bid_price5;                  // �������				15
	double ask_price1;                  // ������һ				21
	double ask_price2;                  // �����۶�				22
	double ask_price3;                  // ��������				23
	double ask_price4;                  // ��������				24
	double ask_price5;                  // ��������				25
	int32_t ask_volume1;                // ������һ				41
	int32_t ask_volume2;                // ��������				42
  int32_t ask_volume3;                // ��������				43
	int32_t ask_volume4;                // ��������				34
	int32_t ask_volume5;                // ��������				45
	int32_t bid_volume1;                // ������һ				31
	int32_t bid_volume2;                // ��������				32
	int32_t bid_volume3;                // ��������				33
	int32_t bid_volume4;                // ��������				44
	int32_t bid_volume5;                // ��������				35

  int64_t volume;                     // �ܳɽ���					8
	double total_amount;                    // �ܳɽ����				59
	double prev_settle;               // �����					75
	int64_t position;                 // ���³ֲ���				76
	int64_t prev_position;            // ��ֲ���					77
	double high_limit;                  // ��ͣ���					211	
	double low_limit;                   // ��ͣ���					212
}CFEL2MarketSnapshot;

// �ڻ�L1�г�����
typedef struct FuturesMarketSnapshot
{
  char wind_code[16];           //��Լ����
  date_t trade_date;            //������  yyyymmdd  1
  time_stamp_t trade_time;      //����޸�ʱ��,hhmmss 2

  double prev_close;            //������  4
  double today_open;            //����  5
  double today_high;            //��߼�  6
  double today_low;             //��ͼ�  7
  double new_price;             //���¼�  3

  int64_t volume;               //�ܳɽ���  8
  double amount;                //�ܳɽ����  59    ֣������

  double bid_price1;            //�����һ  11
  double ask_price1;            //������һ  21
  int32_t ask_volume1;          //������һ  41
  int32_t bid_volume1;          //������һ  31

 
  double settle;                //�����  74        ֣������
  double prev_settle;           //�����  75        �н�����֣������
  int64_t position;             //���³ֲ���  76    �н�����֣������
  int64_t prev_position;        //��ֲ���    77    �н�����
  double average_price;         //����  79          ֣������
  double high_limit;            //��ͣ��  211
  double low_limit;             //��ͣ��  212
}FuturesMarketSnapshot;

// �۹�L2�г�����
typedef struct HKEXL2MarketSnapshot
{
	char wind_code[16];
	date_t trade_date;
	time_stamp_t trade_time;
	double new_price;
	double prev_close;
	double today_open;
	double today_high;
	double today_low;
	int64_t volume;
	uint32_t delta_volume;
	double bid_price1;
	double bid_price2;
	double bid_price3;
	double bid_price4;
	double bid_price5;
	double ask_price1;
	double ask_price2;
	double ask_price3;
	double ask_price4;
	double ask_price5;
	int32_t ask_volume1;
	int32_t ask_volume2;
	int32_t ask_volume3;
	int32_t ask_volume4;
	int32_t ask_volume5;
	int32_t bid_volume1;
	int32_t bid_volume2;
	int32_t bid_volume3;
	int32_t bid_volume4;
	int32_t bid_volume5;
	double best_bid;
	double best_ask;
	int32_t bid_orders1;
	int32_t bid_orders2;
	int32_t bid_orders3;
	int32_t bid_orders4;
	int32_t bid_orders5;
	int32_t ask_orders1;
	int32_t ask_orders2;
	int32_t ask_orders3;
	int32_t ask_orders4;
	int32_t ask_orders5;
	int32_t transactions_count;
	double settle;
	double prev_settle;
	double high_limit;
	double low_limit;
}HKEXL2MarketSnapshot;




// ����г�����
typedef struct FXMarketSnapshot
{
	char wind_code[16];
	date_t trade_date;
	time_stamp_t trade_time;
	double new_price;
	double prev_close;
	double today_open;
	double today_high;
	double today_low;
	double bid_price1;
	double ask_price1;
}FXMarketSnapshot;

#pragma pack(pop)



#endif