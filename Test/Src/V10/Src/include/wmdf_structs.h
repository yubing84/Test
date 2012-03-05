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
  int8_t        major_version;          //���汾��
  int8_t        minor_version;          //���汾��
}SystemMessageHeader;

//������
typedef struct HeartBeat
{
  int8_t        place_holder;           //����ռλ
}HeartBeat;

// ���Ĳ�Ʒ����Ϣ
typedef struct ProductInfo
{
  int16_t       product_id;           //��ƷID
  int8_t        major_version;        //���汾��
  int8_t        minor_version;        //���汾��
  int8_t        codec;                //���������� UNKNOW = 0,FAST = 1,BINARY = 2, RAWDATA = 3, FEEDHANDLER=4
}ProductInfo;

//��¼������Ϣ���ɿͻ��˷����������
typedef struct LoginRequest
{
	uint8_t       user_name[32];         //�û����32�ֽ�
	uint8_t       password[16];          //�����16�ֽ�
  int16_t       product_count;         //���Ĳ�Ʒ����
  ProductInfo*  product;               //��Ʒ��������
}LoginRequest;

//��������Ϣ
typedef struct ServerInfo
{
  uint8_t       server_addr[15];       //IP��ַ
  uint32_t      server_port;           //����˿�
}ServerInfo;

//��Ϣ״̬��Ϣ
typedef struct MessageInfo
{
  int16_t       message_id;           //��ϢID
  int8_t        message_status;       //�����Ƿ�ɹ�  1�� valid; 2�� invalid;
}MessageInfo;

//��Ʒ����״̬��Ϣ
typedef struct ProductStatus
{
  int16_t      product_id;            //��ϢID
  int8_t       product_status;        //��Ʒ����״̬ 1 valid; 2 invalid;
  int8_t       major_version;         //���汾��
  int8_t       minor_version;         //���汾��
  int8_t       codec;                 //���������� UNKNOW = 0,FAST = 1,BINARY = 2, RAWDATA = 3, FEEDHANDLER=4
  int32_t      message_count;         //������Ϣ����
  MessageInfo* message_info;          //��Ϣ״̬
}ProductStatus;

// ��¼��Ӧ��Ϣ,�ɷ������Ӧ�ͻ���
typedef struct LoginResponse
{
	int8_t         ack_type;            //������Ӧ����  1 valid; 2 invalid;
  uint32_t       user_id;             //�û�ID
  int32_t        server_count;        //����������
  ServerInfo*    serverinfo;          //��������Ϣ
  int32_t        product_count;       //���Ĳ�Ʒ����
  ProductStatus* product_status;      //��Ʒ״̬��Ϣ
}LoginResponse;

// �ǳ�֪ͨ��Ϣ, ���ڿͻ��˵ǳ�WMDFϵͳ
typedef struct Logout
{
  int8_t      logout_type;            // define logout type. 1 is server notify to logout;
}Logout;

//�г�Ԥ���̺�����ʱ����
typedef struct MarketDateSignal
{
  int8_t      market_operation;        //1= ���� 2 = ����
  date_t      market_date;             //��������
  int16_t     product_id;              //��Ʒid
}MarketDateSignal;

/************************************************************************/
/*                         �����Ϣ                               */
/************************************************************************/
// �����Ϣͷ
typedef struct MonitorMessageHeader
{
  int8_t      place_holder;               //ռλ��
}MonitorMessageHeader;

//��������ͳ��
typedef struct TransferDataStat
{
  int16_t     product_id;                 //��ƷID
  uint8_t     source_ip[15];              //����ip
  int32_t     source_port;                //����˿�
  uint8_t     source_status;              //������״̬

  double      receive_data_flow;          //���յ����ֽ�����(KB/S)
  double      receive_pack_flow;          //���յ��İ�����
  uint32_t    receive_packet_count;       //���յ��İ���
  uint32_t    pre_receive_packet_count;   //�ϴ�ͳ��ʱreceive����
  uint64_t    receive_data_size;          //ԭʼ��С(KB)
  uint64_t    pre_receive_data_size;      //�ϴ�ͳ��ʱ������С(KB)

  double      send_data_flow;             //�����ֽ�����(KB/S)
  double      send_pack_flow;             //���Ͱ�����
  uint32_t    send_packet_count;          //�ѷ��Ͱ���
  uint32_t    pre_send_packet_count;      //�ϴ�ͳ��ʱ�ѷ��Ͱ���
  uint32_t    send_packet_delta;          //ǰ��ͳ�Ƶ����ڷ��͵İ���

  uint64_t    encoded_size;               //������С(KB)
  uint64_t    pre_encoded_size;           //�ϴ�ͳ��ʱ������С(KB)

  uint64_t    binary_struct_size;         //�����ƽṹ���С(KB)
  double      compression_ratio;          //ѹ����(%)
  uint32_t    total_msg_delay;            //ƽ���ӳ�(ms)
  uint32_t    pre_total_msg_delay;        //�ϴ���Ϣ���ӳ�
  uint32_t    msg_avg_delay;              //ƽ���ӳ�
  uint32_t    delayed_msg_delta;          //ǰ��ͳ���ӳٵ����ڷ������ӳٰ���
  uint32_t    delayed_msg_count;          //�ӳٰ�������
  uint32_t    pre_delayed_msg_count;      //�ϴ��ӳٰ�������
}TransferDataStat;

typedef struct ClientStatus
{
  int32_t        socket_id;               //socketid
  uint8_t        user_name[32];           //�û����32�ֽ�
	uint8_t        client_ip[15];           //�ͻ�IP
  time_stamp_t   duration;                //����ʱ��
	double         send_data_flow;          //��������(KB/S)
  int64_t        send_bytes;              //�ܵķ����ֽ���
  int64_t        pre_send_bytes;          //ǰһ�η����ֽ���
  int32_t        msg_in_queue;            //��������е����ݰ�����
	int32_t        product_count;           //���Ĳ�Ʒ����
	ProductInfo*   product_infos;           //���Ĳ�Ʒ��Ϣ
}ClientStatus;

typedef struct MonitorEvent
{
  int8_t        level;                    //�¼����� FATAL=0, ERROR=1,WARN=2,INFO=3,DEBUG=4
  date_time_t   date_time;                //�¼�������ʱ��
  uint8_t       at_where[60];             //��ص�
  int32_t       event_id;                 //�¼�ID
  uint8_t       what_happened[150];       //�¼����ݣ��� ��¼ ������ʧ�ܡ���
}MonitorEvent;


/************************************************************************/
/*                         ����������Ϣ                           */
/************************************************************************/

// ����������Ϣͷ
typedef struct MarketMessageHeader
{
	int8_t place_holder;
}MarketMessageHeader;

// ����L1�г�����
typedef struct L1MarketSnapshot
{
	char          wind_code[16];           //֤ȯ����
	time_stamp_t  data_time_stamp;         //ʱ���
	double        pre_close;               //ǰ�ռ�
	double        open_price;              //���տ��̼�
	double        high_price;              //������߼�
	double        low_price;               //������ͼ�
  double        new_price;               //���¼�
	int64_t       total_volume;            //�ɽ���
	double        total_amount;	           //�ɽ���
	double        bid_price1;              //��1��
	double        bid_price2;              //��2��
	double        bid_price3;              //��3��
	double        bid_price4;              //��4��
	double        bid_price5;              //��5��
	double        ask_price1;              //��1��
	double        ask_price2;              //��2��
	double        ask_price3;              //��3��
	double        ask_price4;              //��4��
	double        ask_price5;              //��5��
	int32_t       ask_size1;               //��1��
	int32_t       ask_size2;               //��2��
	int32_t       ask_size3;               //��3��
	int32_t       ask_size4;               //��4��
	int32_t       ask_size5;               //��5��
	int32_t       bid_size1;               //��1��
	int32_t       bid_size2;               //��2��
	int32_t       bid_size3;               //��3��
	int32_t       bid_size4;               //��4��
	int32_t       bid_size5;               //��5��
}L1MarketSnapshot;

// L2�г�����
typedef struct L2MarketSnapshot
{
	char          wind_code[16];
  time_stamp_t  data_time_stamp;            //����ʱ�䣬2
  double        pre_close;                  //ǰ�ռۣ�4
  double        open_price;                 //���̼ۣ�5
  double        high_price;                 //��߼ۣ�6
  double        low_price;                  //��ͼۣ�7
  double        new_price;                  //���¼ۣ�3
  int64_t       total_volume;               //�ܳɽ�����8
  double        total_amount;               //�ܳɽ��59
  double        bid_price1;                 //��1�ۣ�11
	double        bid_price2;                 //��2�ۣ�12
	double        bid_price3;                 //��3�ۣ�13
	double        bid_price4;                 //��4�ۣ�14
	double        bid_price5;                 //��5�ۣ�15
	double        bid_price6;                 //��6�ۣ�16
	double        bid_price7;                 //��7�ۣ�17
	double        bid_price8;                 //��8�ۣ�18
	double        bid_price9;                 //��9�ۣ�19
	double        bid_price10;                //��10�ۣ�20
	double        ask_price1;                 //��1�ۣ�21
	double        ask_price2;                 //��2�ۣ�22
	double        ask_price3;                 //��3�ۣ�23
	double        ask_price4;                 //��4�ۣ�24
	double        ask_price5;                 //��5�ۣ�25
	double        ask_price6;                 //��6�ۣ�26
	double        ask_price7;                 //��7�ۣ�27
	double        ask_price8;                 //��8�ۣ�28
	double        ask_price9;                 //��9�ۣ�29
	double        ask_price10;                //��10�ۣ�30
  int32_t       bid_size1;                  //��1����31
  int32_t       bid_size2;                  //��2����32
  int32_t       bid_size3;                  //��3����33
  int32_t       bid_size4;                  //��4����34
  int32_t       bid_size5;                  //��5����35
  int32_t       bid_size6;                  //��6����36
  int32_t       bid_size7;                  //��7����37
  int32_t       bid_size8;                  //��8����38
  int32_t       bid_size9;                  //��9����39
  int32_t       bid_size10;                 //��10����40
	int32_t       ask_size1;                  //��1����41
	int32_t       ask_size2;                  //��2����42
	int32_t       ask_size3;                  //��3����43
	int32_t       ask_size4;                  //��4����44
	int32_t       ask_size5;                  //��5����45
	int32_t       ask_size6;                  //��6����46
	int32_t       ask_size7;                  //��7����47
	int32_t       ask_size8;                  //��8����48
	int32_t       ask_size9;                  //��9����49
	int32_t       ask_size10;                 //��10����50
  int64_t       transactions_count;         //�����ܱ���, 71
  double        weighted_average_bid_price; //��Ȩƽ��ί��۸�86����L2
  double        weighted_average_ask_price; //��Ȩƽ��ί���۸�87����L2
  int64_t       total_bid_size;             //ί������������340����L2
  int64_t       total_ask_size;             //ί������������341����L2
  double        peratio1;                   // SZSE ��Ʊ���۸�/����ÿ������    v1.1
                                            // SZSE ծȯ��ÿ��ԪӦ����Ϣ
  double        peratio2;                   // SZSE     ��Ʊ���۸�/����ÿ������ v1.1
                                            // SZSE/SSE ծȯ������������
                                            // SZSE/SSE ����ÿ�ٷݵ�IOPV��ֵ
                                            // SZSE     Ȩ֤�������
  int8_t        trade_status;               // ����״̬ 1=�������� 2=ͣ��      v1.1
}L2MarketSnapshot;


// ��ʳɽ�
typedef struct L2Transaction
{
	char          wind_code[16];              //֤ȯ����
	time_stamp_t  trade_time;                 //����ʱ��
	int32_t       volume;                     //�ɽ�����
  double        price;                      //�ɽ��۸�
  double        amount;                     //�ɽ���� sse
  int32_t       set_no;                     //֤ȯ������ szse
  int32_t       rec_no;                     //�ɽ����
  int32_t       buyOrderRecNo;              //��ί������ szse
  int32_t       sellOrderRecNo;             //����ί������ szse
	int8_t        order_kind;                 //�ɽ���� szse
	int8_t        function_code;              //�ɽ����� szse
}L2Transaction;


// L2ί�ж��м�����
typedef struct L2OrderQueueItem
{
	int32_t       operator_type;            //ί�е�����0-Absent, 1-Add,2-Update,3-Delete
	int32_t       entry_id;                 //ί�е��ڶ����е�λ��Start from 0, No Meaning if
	int32_t       size;                     //ί����
}L2OrderQueueItem;

// L2ί�ж��м���
typedef struct L2OrderQueuePriceLevel
{
	int32_t           operator_type;            //�۸������0-Absent,1-Add,2-Update,3-Delete
	double            order_price;              //�۸�
	int32_t           total_number;             //��ǰ��λ����ί�б���
	int32_t           orders_number;            //�˴η����仯��ί�б���
	L2OrderQueueItem* order_items;              //order_items��Item������orders_number
}L2OrderQueuePriceLevel;

// L2ί�ж���
typedef struct L2OrderQueue
{
	char                    wind_code[16];        //֤ȯ����
	time_stamp_t            data_time_stamp;      //ʱ���
	uint8_t                 order_side;           //ί�з��� 1 = Bid Queue, 2 = Ask Queue, other: Invalid
	int32_t                 image_status;         //Ӱ������ 1 = FullImage, 2 = Update, other: Invalid
	int32_t                 price_level_count;    //�۸���� Number of PriceLevelItems, should = PriceLevel_items.size();
	L2OrderQueuePriceLevel* price_levels;         //ί�м۸��ϵĶ�����ϸ��Ϣ
}L2OrderQueue;


// ��L2���ί��
typedef struct SZSEL2Order
{
	char         wind_code[16];                 //֤ȯ����
  time_stamp_t order_time;                    //ί��ʱ��
	int32_t      set_no;                        //֤ȯ������
	int32_t      rec_no;                        //ί������
	int32_t      size;                          //ί������,  ��
  double       price;                         //�۸�
	char         order_kind;                    //ί�����,  1=ί��, 2=ί��, 3=����
	char         function_code;                 //�ɽ�����
}SZSEL2Order;

// �н���L2�г�����
typedef struct CFEL2MarketSnapshot
{
	char          wind_code[16];               // ��Լ����,��:IF1106
	date_t        trade_date;                  // ��������, yyyymmdd			1
	time_stamp_t  data_time_stamp;             // ����޸�ʱ��, hhMMss		2
	double        pre_close;                   // ������					4
	double        open_price;                  // ����					5
	double        high_price;                  // ����߼�					6
	double        low_price;                   // ����ͼ�					7
  double        new_price;                   // ���¼�					3
  int64_t       total_volume;                // �ܳɽ���					8
  double        total_amount;                // �ܳɽ����				59
	double        bid_price1;                  // �����һ				11
	double        bid_price2;                  // ����۶�				12
	double        bid_price3;                  // �������				13
	double        bid_price4;                  // �������				14
	double        bid_price5;                  // �������				15
	double        ask_price1;                  // ������һ				21
	double        ask_price2;                  // �����۶�				22
	double        ask_price3;                  // ��������				23
	double        ask_price4;                  // ��������				24
	double        ask_price5;                  // ��������				25
	int32_t       ask_size1;                   // ������һ				41
	int32_t       ask_size2;                   // ��������				42
  int32_t       ask_size3;                   // ��������				43
	int32_t       ask_size4;                   // ��������				34
	int32_t       ask_size5;                   // ��������				45
	int32_t       bid_size1;                   // ������һ				31
	int32_t       bid_size2;                   // ��������				32
	int32_t       bid_size3;                   // ��������				33
	int32_t       bid_size4;                   // ��������				44
	int32_t       bid_size5;                   // ��������				35
	double        pre_settle;                  // �����					75
	int64_t       position;                    // ���³ֲ���				76
	int64_t       pre_position;                // ��ֲ���					77
	double        high_limit;                  // ��ͣ���					211
	double        low_limit;                   // ��ͣ���					212
  double        settle;                      // �����
}CFEL2MarketSnapshot;

// �ڻ�L1�г�����
typedef struct FuturesMarketSnapshot
{
  char          wind_code[16];              //��Լ����
  date_t        trade_date;                 //������    1
  time_stamp_t  data_time_stamp;            //����޸�ʱ�� 2
  double        pre_close;                  //������  4
  double        open_price;                 //����  5
  double        high_price;                 //��߼�  6
  double        low_price;                  //��ͼ�  7
  double        new_price;                  //���¼�  3
  int64_t       total_volume;               //�ܳɽ���  8
  double        total_amount;               //�ܳɽ����  59    ֣������
  double        bid_price1;                 //�����һ  11
  double        ask_price1;                 //������һ  21
  int32_t       ask_size1;                  //������һ  41
  int32_t       bid_size1;                  //������һ  31
  double        pre_settle;                 //�����  75        �н�����֣������
  int64_t       pre_position;               //��ֲ���    77
  double        settle;                     //�����  74        ֣������
  int64_t       position;                   //���³ֲ���  76
  double        average_price;              //����  79          ֣������
  double        high_limit;                 //��ͣ��  211
  double        low_limit;                  //��ͣ��  212
}FuturesMarketSnapshot;

//��������������ָ������
typedef struct IndexSnapshot
{
  char					wind_code[16];
  time_stamp_t	data_time_stamp;							//����ʱ�䣬2
  double				pre_close;										//��������ָ����632
  double				open_price;										//���տ���ָ����5
  double				high_price;										//���ָ����6
  double				low_price;										//���ָ����7
  double				new_price;										//����ָ����3
  int64_t				total_volume;									//�ܳɽ���,8
  double				total_amount;									//��Ӧָ�����ܳɽ���59
}IndexSnapshot;

// ����г�����
typedef struct FXMarketSnapshot
{
	char wind_code[16];
	date_t trade_date;
	time_stamp_t data_time_stamp;
	double pre_close;
	double open_price;
	double high_price;
	double low_price;
	double new_price;
  double bid_price1;
	double ask_price1;
}FXMarketSnapshot;

#pragma pack(pop)



#endif
