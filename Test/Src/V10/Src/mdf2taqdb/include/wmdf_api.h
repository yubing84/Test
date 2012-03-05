#ifndef WIND_MDF_API_H
#define WIND_MDF_API_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) || defined(_WIN32_WCE) || defined(__WIN32__)
#  ifndef WIN32
#    define WIN32
#  endif
#endif

#ifdef WIN32
#       pragma warning(disable:4091) 
#   if defined DLL_EXPORT
#       define WMDF_API __declspec(dllexport)
#   else
#       define WMDF_API __declspec(dllimport)
#   endif
#else
#   if defined __SUNPRO_C  || defined __SUNPRO_CC
#       define WMDF_API __global
#   elif (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER
#       define WMDF_API __attribute__ ((visibility("default")))
#   else
#       define WMDF_API
#   endif
#endif

  ////////////////////////////////////////////////////////////////
  //  Platform independent data types                           //
  ////////////////////////////////////////////////////////////////

#if (defined _MSC_VER &&_MSC_VER<=1500)
#ifndef int8_t
  typedef __int8 int8_t;
#endif
#ifndef int16_t
  typedef __int16 int16_t;
#endif
#ifndef int32_t
  typedef __int32 int32_t;
#endif
#ifndef int64_t
  typedef __int64 int64_t;
#endif
#ifndef uint8_t
  typedef unsigned __int8 uint8_t;
#endif
#ifndef uint16_t
  typedef unsigned __int16 uint16_t;
#endif
#ifndef uint32_t
  typedef unsigned __int32 uint32_t;
#endif
#ifndef uint64_t
  typedef unsigned __int64 uint64_t;
#endif
#else
#include <stdint.h>
#endif

#ifndef date_t
  typedef int32_t date_t;
#endif
#ifndef time_stamp_t
  typedef int32_t time_stamp_t;
#endif

#ifndef date_time_t
  typedef double date_time_t;
#endif
  

////////////////////////////////////////////////////////////////
//  NIL value of types                                        //
////////////////////////////////////////////////////////////////
#define WMDF_CONSTS_8BIT_NIL_VALUE ((int8_t)0x80)
#define WMDF_CONSTS_32BIT_NIL_VALUE ((int)0x80000000)
#define WMDF_CONSTS_64BIT_NIL_VALUE ((int64_t)0x8000000000000000)
#define WMDF_CONSTS_DOUBLE_NIL_VALUE ((double)log(-1.0))
#define WMDF_CONSTS_STRING_NIL_VALUE (uint8_t*)""

  /************************************************************************/
  /*                         WMDF��ƷID                                  */
  /************************************************************************/
  const int16_t PRODUCT_INVALID_ID   = 0;   //��Ч��ƷID
  const int16_t PRODEUCT_SYSTEM_ID   = 1;  //ϵͳ��Ϣ
  const int16_t PRODEUCT_MONITOR_ID    = 2;  //��ز�Ʒ
  const int16_t PRODUCT_SSE_LEVEL1_ID  = 10;  //�Ͻ���Level1
  const int16_t PRODUCT_SZSE_LEVEL1_ID = 11;  //���Level1
  const int16_t PRODUCT_SSE_LEVEL2_ID  = 12;  //�Ͻ���Level2
  const int16_t PRODUCT_SZSE_LEVEL2_ID = 13;  //���Level2

  const int16_t PRODUCT_CFFE_LEVEL1_ID = 20;  //�н���Level1
  const int16_t PRODUCT_CFFE_LEVEL2_ID = 21;  //�н���Level2
  const int16_t PRODUCT_SHFE_LEVEL1_ID = 22;  //������Level1
  const int16_t PRODUCT_DCE_LEVEL1_ID  = 23;  //������Level1
  const int16_t PRODUCT_CZCE_LEVEL1_ID = 24;  //֣����Level1

  const int16_t PRODUCT_FX_ID          = 25;   //���


  const int16_t PRODUCT_SIMULATOR_ID   = 2010; //��Ʒģ����������������Դʱ�ĵ���
  const int16_t PRODUCT_RELAY_BEGIN_ID   = 2011; //Feed Server Relay, ����FeedServer�ļ���,�Լ��ͻ���API
  const int16_t PRODUCT_RELAY_END_ID     = 2019; 

  /************************************************************************/
  /*                         WMDF��Ʒ��Ϣ����                        */
  /************************************************************************/
  const int16_t MESSAGE_INVALID_ID   = 00;   //��Ч��ϢID

  const int16_t SYSTEM_HEARTBEAT_ID         = 1; //������Ϣ
  const int16_t SYSTEM_LOGIN_REQUEST_ID     = 2; //��¼������Ϣ
  const int16_t SYSTEM_LOGIN_RESPONSE_ID    = 3; //��¼��Ӧ��Ϣ
  const int16_t SYSTEM_LOGOUT_ID            = 4; //�ǳ�֪ͨ��Ϣ
  const int16_t SYSTEM_MARKET_DATE_SIGNAL_ID = 5;//�г���ʼǰ�ͽ������ͽ��������ź�ID

  const int16_t MONITOR_TRANSFER_STATUS_ID    = 1;  // ���紫��״̬��Ϣ
  const int16_t MONITOR_CLIENT_STATUS_ID      = 2;  // ��ؿͻ���״̬��Ϣ
  const int16_t MONITOR_SURVIVAL_STATUS_ID    = 3;  // ��ظ����������ӵĴ��״̬

  const int16_t SSEL1_MARKETDATA_ID   = 1;     //�Ͻ���Level1����

  const int16_t SZSEL1_MARKETDATA_ID   = 1;     //���Level1����

  const int16_t SSEL2_MARKETDATA_ID   = 1;  //�Ͻ���Level2����
  const int16_t SSEL2_TRANSACTION_ID  = 2;  //�Ͻ���Level2��ʳɽ�
  const int16_t SSEL2_ORDERQUEUE_ID   = 3;  //�Ͻ���Level2ί�ж���
  const int16_t SSEL2_MARKETOVERVIEW_ID	= 4;			//�Ͻ���Level2�г��ſ�
  const int16_t SSEL2_VIRTUALAUCTIONPRICE_ID =5;	//�Ͻ���Level2���⾺��

  const int16_t SZSEL2_MARKETDATA_ID   = 1;  //���Level2����
  const int16_t SZSEL2_TRANSACTION_ID  = 2;  //���Level2��ʳɽ�
  const int16_t SZSEL2_ORDERQUEUE_ID   = 3;  //���Level2ί�ж���
  const int16_t SZSEL2_SINGLEORDER_ID  = 4;  //���Level2���ί������

  const int16_t CFFEL1_MARKETDATA_ID   = 1;  //�н���Level1����
  
  const int16_t CFFEL2_MARKETDATA_ID   = 1;  //�н���Level2����

  const int16_t SHFEL1_MARKETDATA_ID   = 1;  //������Level1����

  const int16_t DCEL1_MARKETDATA_ID   = 1;  //������Level1����
  
  const int16_t CZCEL1_MARKETDATA_ID   = 1;  //֣����Level1����
  
  const int16_t FX_MARKETDATA_ID      = 1;    //������




  /************************************************************************/
  /*                         WMDF��Ʒ�汾����                        */
  /************************************************************************/
  const int8_t VERSION_INVALID_ID         = 0x7F;  // ��Ч�汾ID

  const int8_t MAJOR_VERSION_SYSTEM_ID    = 0x01;  //���������Ʒ
  const int8_t MINOR_VERSION_SYSTEM_ID    = 0x00;

  const int8_t MAJOR_VERSION_MONITOR_ID     = 0x01;  //��ز�Ʒ
  const int8_t MINOR_VERSION_MONITOR_ID     = 0x00;


  const int8_t MAJOR_VERSION_SSE_LEVEL1_ID  = 0x01;  //�Ͻ���Level1
  const int8_t MINOR_VERSION_SSE_LEVEL1_ID  = 0x00;

  const int8_t MAJOR_VERSION_SZSE_LEVEL1_ID = 0x01;  //���Level1
  const int8_t MINOR_VERSION_SZSE_LEVEL1_ID = 0x00;

  const int8_t MAJOR_VERSION_SSE_LEVEL2_ID  = 0x01;  //�Ͻ���Level2
  const int8_t MINOR_VERSION_SSE_LEVEL2_ID  = 0x00;

  const int8_t MAJOR_VERSION_SZSE_LEVEL2_ID = 0x01;  //���Level2
  const int8_t MINOR_VERSION_SZSE_LEVEL2_ID = 0x00;

  const int8_t MAJOR_VERSION_CFFE_LEVEL1_ID = 0x01;  //�н���Level1
  const int8_t MINOR_VERSION_CFFE_LEVEL1_ID = 0x00;

  const int8_t MAJOR_VERSION_CFFE_LEVEL2_ID = 0x01;  //�н���Level2
  const int8_t MINOR_VERSION_CFFE_LEVEL2_ID = 0x00;

  const int8_t MAJOR_VERSION_SHFE_LEVEL1_ID = 0x01;  //������Level1
  const int8_t MINOR_VERSION_SHFE_LEVEL1_ID = 0x00;

  const int8_t MAJOR_VERSION_DCE_LEVEL1_ID  = 0x01;  //������Level1
  const int8_t MINOR_VERSION_DCE_LEVEL1_ID  = 0x00;

  const int8_t MAJOR_VERSION_CZCE_LEVEL1_ID = 0x01;  //֣����Level1
  const int8_t MINOR_VERSION_CZCE_LEVEL1_ID = 0x00;

  const int8_t MAJOR_VERSION_FX_ID          = 0x01;   //���
  const int8_t MINOR_VERSION_FX_ID          =0x00;

  /************************************************************************/
  /*                       WMDF Protocol Processor Unique ID              */
  /************************************************************************/

#define ID_SHIFT_CODEC		  0
#define ID_SHIFT_MIN_VER    32
#define ID_SHIFT_MAJ_VER    40
#define ID_SHIFT_PID		    48

#define MAKE_UNIQUE_ID(pId,majVer,minVer,codec)								                        \
  ((((int64_t)pId) << ID_SHIFT_PID)		| (((int64_t)majVer)   << ID_SHIFT_MAJ_VER) |	  \
  (((int64_t)minVer)  << ID_SHIFT_MIN_VER) | (((int64_t)codec) << ID_SHIFT_CODEC))

#define SYSTEM_1_0_BINARY (int64_t)MAKE_UNIQUE_ID( PRODEUCT_SYSTEM_ID, MAJOR_VERSION_SYSTEM_ID,  MINOR_VERSION_SYSTEM_ID,  CT_BINARY)
#define MONITOR_1_0_BINARY (int64_t)MAKE_UNIQUE_ID( PRODEUCT_MONITOR_ID, MAJOR_VERSION_MONITOR_ID,  MINOR_VERSION_MONITOR_ID,  CT_BINARY)

#define SSEL1_1_0_FAST		(int64_t)MAKE_UNIQUE_ID( PRODUCT_SSE_LEVEL1_ID, MAJOR_VERSION_SSE_LEVEL1_ID,  MINOR_VERSION_SSE_LEVEL1_ID,  CT_FAST)
#define SSEL1_1_0_BINARY	(int64_t)MAKE_UNIQUE_ID( PRODUCT_SSE_LEVEL1_ID, MAJOR_VERSION_SSE_LEVEL1_ID,  MINOR_VERSION_SSE_LEVEL1_ID,  CT_BINARY)

#define	SSEL2_1_0_FAST		(int64_t)MAKE_UNIQUE_ID( PRODUCT_SSE_LEVEL2_ID, MAJOR_VERSION_SSE_LEVEL2_ID,  MINOR_VERSION_SSE_LEVEL2_ID,  CT_FAST)
#define SSEL2_1_0_BINARY	(int64_t)MAKE_UNIQUE_ID( PRODUCT_SSE_LEVEL2_ID, MAJOR_VERSION_SSE_LEVEL2_ID,  MINOR_VERSION_SSE_LEVEL2_ID,  CT_BINARY)

#define SZSEL1_1_0_FAST		(int64_t)MAKE_UNIQUE_ID(PRODUCT_SZSE_LEVEL1_ID, MAJOR_VERSION_SZSE_LEVEL1_ID, MINOR_VERSION_SZSE_LEVEL1_ID, CT_FAST)
#define SZSEL1_1_0_BINARY	(int64_t)MAKE_UNIQUE_ID(PRODUCT_SZSE_LEVEL1_ID, MAJOR_VERSION_SZSE_LEVEL1_ID, MINOR_VERSION_SZSE_LEVEL1_ID, CT_BINARY)
#define SZSEL2_1_0_FAST		(int64_t)MAKE_UNIQUE_ID(PRODUCT_SZSE_LEVEL2_ID, MAJOR_VERSION_SZSE_LEVEL2_ID, MINOR_VERSION_SZSE_LEVEL2_ID, CT_FAST)
#define SZSEL2_1_0_BINARY	(int64_t)MAKE_UNIQUE_ID(PRODUCT_SZSE_LEVEL2_ID, MAJOR_VERSION_SZSE_LEVEL2_ID, MINOR_VERSION_SZSE_LEVEL2_ID, CT_BINARY)	

#define CFFEL1_1_0_FAST		(int64_t)MAKE_UNIQUE_ID(PRODUCT_CFFE_LEVEL1_ID, MAJOR_VERSION_CFFE_LEVEL1_ID, MINOR_VERSION_CFFE_LEVEL1_ID, CT_FAST)
#define CFFEL1_1_0_BINARY	(int64_t)MAKE_UNIQUE_ID(PRODUCT_CFFE_LEVEL1_ID, MAJOR_VERSION_CFFE_LEVEL1_ID, MINOR_VERSION_CFFE_LEVEL1_ID, CT_BINARY)
#define CFFEL2_1_0_FAST		(int64_t)MAKE_UNIQUE_ID(PRODUCT_CFFE_LEVEL2_ID, MAJOR_VERSION_CFFE_LEVEL2_ID, MINOR_VERSION_CFFE_LEVEL2_ID, CT_FAST)
#define CFFEL2_1_0_BINARY	(int64_t)MAKE_UNIQUE_ID(PRODUCT_CFFE_LEVEL2_ID, MAJOR_VERSION_CFFE_LEVEL2_ID, MINOR_VERSION_CFFE_LEVEL2_ID, CT_BINARY)	

#define SHFEL1_1_0_FAST		(int64_t)MAKE_UNIQUE_ID(PRODUCT_SHFE_LEVEL1_ID, MAJOR_VERSION_SHFE_LEVEL1_ID, MINOR_VERSION_SHFE_LEVEL1_ID, CT_FAST)
#define SHFEL1_1_0_BINARY	(int64_t)MAKE_UNIQUE_ID(PRODUCT_SHFE_LEVEL1_ID, MAJOR_VERSION_SHFE_LEVEL1_ID, MINOR_VERSION_SHFE_LEVEL1_ID, CT_BINARY)

#define DCEL1_1_0_FAST		(int64_t)MAKE_UNIQUE_ID(PRODUCT_DCE_LEVEL1_ID,	MAJOR_VERSION_DCE_LEVEL1_ID,  MINOR_VERSION_DCE_LEVEL1_ID,  CT_FAST)
#define DCEL1_1_0_BINARY	(int64_t)MAKE_UNIQUE_ID(PRODUCT_DCE_LEVEL1_ID,	MAJOR_VERSION_DCE_LEVEL1_ID,  MINOR_VERSION_DCE_LEVEL1_ID,  CT_BINARY)

#define CZCEL1_1_0_FAST		(int64_t)MAKE_UNIQUE_ID(PRODUCT_CZCE_LEVEL1_ID, MAJOR_VERSION_CZCE_LEVEL1_ID, MINOR_VERSION_CZCE_LEVEL1_ID, CT_FAST)
#define CZCEL1_1_0_BINARY	(int64_t)MAKE_UNIQUE_ID(PRODUCT_CZCE_LEVEL1_ID, MAJOR_VERSION_CZCE_LEVEL1_ID, MINOR_VERSION_CZCE_LEVEL1_ID, CT_BINARY)



/////////////////////////////////////////////////////////////////////////
// Return Values for DLL functions:  All API functions having a return
//   will return one of these codes
//////////////////////////////////////////////////////////////////////////
//to do define all return value
typedef enum eReturnValue
{
  INVALID_VALUE          =	 -1,	//For cases where a number is returned instead of enum type
  SUCCESS                = 0,              //Successfull Opperation

  AUTHORITY_VALID        = 1,		           //Ȩ����Ч
  AUTHORITY_INVALID      = 2, 		         //Ȩ����Ч
  SEND_DATA_FAILD        =  3,             //��������ʧ��
  USER_NOT_EXIST         = 4,              //�û���������
  PASSWORD_INCORRECT     = 5,              //�������
  IP_UNAUTHORIZED        = 6,              //IPδ��Ȩ
  LOAD_API_FAILED        = 7,              //����APIʧ��
  UNLOAD_API_FAILED      = 8,              //ж��APIʧ��
  LOGOUT_FAILED          = 9,              //�ǳ�ʧ��
  NORMAL_DISCONNECT      = 10,             //�����Ͽ�
  ABNORMAL_DISCONNECT    = 11,             //�쳣�Ͽ�
  CONNECTION_ID_INVALID  = 12,            //��Ч������ID(0-7)
  CONNECTION_OVERLOAD    = 13,            //���������������������8��
  CONNECTION_FAILED      =14,              //����ʧ��   
  IDEXPIRED              =15               //�˺Ź���

} eReturnValue;


//����������
typedef enum CodecType
{
  CT_UNKNOW = 0,
  CT_FAST = 1,      //fast����
  CT_BINARY = 2,    //�����Ʊ���
  CT_RAWDATA = 3,   //������ԭʼ����
  CT_FEEDHANDLER=4  //feedhandler��ʽ
} CodecType;

typedef enum MarketOperation
{
  MO_OPEN = 1,
  MO_CLOSE = 2
};

typedef enum LogoutType
{
  LT_SERVERNOTIFY   //�������֪ͨ�ͻ��˶Ͽ�����
} LogoutType;

////////////////////////////////////////////////////////////////
//  All API structures
////////////////////////////////////////////////////////////////

//��ʼ��APIʱ�������
typedef struct OpenArgs
{
  uint8_t connection_id;         //0-31(���֧��32������)
  uint8_t user_name[32];         //�û����32�ֽ�
  uint8_t password[16];          //�����16�ֽ�
  uint8_t server_addr[15];       //��������ַ
  uint32_t server_port;          //�������˿�
  CodecType codec_type;          //Э�����������
  int32_t marktet_open_time;     //����ʱ��
  int32_t markt_close_time;      //����ʱ��
} OpenArgs;

typedef struct CloseArgs
{
  uint8_t connection_id;         //0-31(���֧��32������)
} CloseArgs;

typedef struct APIVersionArgs
{
  uint32_t major;
  uint32_t minor;
  uint32_t patch;
} APIVersionArgs;

typedef struct FilterArgs
{
  uint8_t connection_id;
  uint8_t* filter_masks;              //windcode�����ַ���,�Զ��ŷָ�����600000.SH,600001.SH
}FilterArgs;

typedef struct MdfRecord
{
  time_stamp_t local_time;// local time;n
	uint32_t packet_num;    // packet num 
  int16_t product_id;     // product id;
  int16_t message_id;     // message id;
  int8_t major_version;   // major version 
  int8_t minor_version;   // minor version
  void* header;           // product header;
  int32_t record_count;   // product record count;
  void* body;             // product record;
} MdfRecord;

typedef struct RecordArgs
{
  uint8_t connection_id;         //0-31(���֧��32������)
  MdfRecord* record;             //���ݼ�¼ 
  void* state;                   //�ص�������
} RecordArgs;


typedef struct EventArgs
{
  uint8_t connection_id;         //0-31(���֧��32������)
  int32_t EventId;
  time_stamp_t Time;
  uint8_t Context[256];
  void* state;
} EventArgs;

typedef void (*RecordCallback)(RecordArgs* record);

typedef void (*FeedEventCallback)(EventArgs* args);

typedef struct CallbackArgs
{
  uint8_t connection_id;         //0-31(���֧��32������)
  RecordCallback record_callback;
  FeedEventCallback event_callback;
  void* state;
}CallbackArgs;


////////////////////////////////////////////////////////////////
//  API function prototypes
////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
//  version 1.0 
////////////////////////////////////////////////////////////////
WMDF_API eReturnValue wmdf_initialize();
WMDF_API eReturnValue wmdf_finalize();
WMDF_API eReturnValue wmdf_open_connection(OpenArgs* args);
WMDF_API eReturnValue wmdf_close_connection(CloseArgs* args);
WMDF_API eReturnValue wmdf_set_filter_mask(FilterArgs* args);
WMDF_API eReturnValue wmdf_get_api_version(APIVersionArgs* args);
WMDF_API eReturnValue wmdf_get_server_info();
WMDF_API eReturnValue wmdf_set_callback(CallbackArgs* args);
WMDF_API eReturnValue wmdf_get_record(RecordArgs* args);
WMDF_API eReturnValue wmdf_release_record(RecordArgs* args);

//#define release(recode) {wmdf_release_product_message(record);record=NULL;}


#ifdef __cplusplus
}
#endif

#endif
