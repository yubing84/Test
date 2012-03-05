#ifndef _FeedHandler_Protocol_Define_Header_20110429_
#define _FeedHandler_Protocol_Define_Header_20110429_

#ifdef _WINDOWS

#else	//Linux
typedef int __int32;
typedef long long __int64;
#endif

#pragma once

#include <vector>

#pragma pack(push)  // push current alignment to stack
#pragma pack(1)		// force compiler to use byte alligned structures

// ָ�����Ͷ���(Part I)
#define WN_VAL_TYPE_NULL              0     // undefined type
#define WN_VAL_TYPE_STRUCT			  1		// structure data block
#define WN_VAL_TYPE_UINT32			  2		// unsigned int32
#define WN_VAL_TYPE_INT32			  3		// int32
#define WN_VAL_TYPE_UINT64			  4		// unsigned int64
#define WN_VAL_TYPE_INT64			  5		// int64
#define WN_VAL_TYPE_DOUBLE			  6		// double
#define WN_VAL_TYPE_STRING			  7		// string


// �ṹ�����Ͷ���(Part II)
enum SequenceTypeFlag
{
	SEQUENCE_VALUE_NULL = 0,
	// ����Ϊ�Ͻ���L2�ṹ������
	SEQUENCE_BidPriceLevel_3102,
	SEQUENCE_OfferPriceLevel_3102,
	SEQUENCE_Rankings_3103,
	SEQUENCE_Rankings_3104,
	SEQUENCE_Rankings_3105,
	SEQUENCE_Rankings_3106,
	SEQUENCE_PriceLevel_3111,
	SEQUENCE_BidLevels_3112,
	SEQUENCE_OfferLevels_3112,
	SEQUENCE_BidPriceLevel_5102,
	SEQUENCE_OfferPriceLevel_5102,
	SEQUENCE_BidOfferLevels_3202,
	// ����Ϊ���L2�ṹ������
	SEQUENCE_SecurityAltIDs_101,
	SEQUENCE_MiscFees_101,
	SEQUENCE_IndicesParticipated_101,
	SEQUENCE_BidOfferPriceLevel_103
};

typedef struct tagPacketHeader
{
	unsigned int unPacketSize;		//���ݰ���С
	unsigned char ucWindCode[16];	//Wind Code
	unsigned int unIndexNum;		//ָ������
}PacketHeader,*ptrPacketHeader;

/*
// ����ָ�꣨�ṹ�壩������ͷ
typedef struct _WnStructHead
{
	unsigned int	unDataLen;		//�������ݳ��ȣ��������ṹ�������ȣ�
	unsigned char	ucStructType;	//�ṹ����(ref. Part II)
	unsigned short	usElementNum;	//Ԫ�ظ���
}WnStHead,*ptrWnStHead;

typedef struct _WnStruct
{
	ptrWnStHead		ptrStHead;		//����ָ������ͷ
	unsigned char *	pBinary;		//����ָ��������
}WnStruct,*ptrWnStruct;
*/

typedef struct _WnStruct
{
	unsigned char	ucStructType;	//�ṹ����(ref. Part II)
	void*  pStructData;
}WnStruct,*ptrWnStruct;

typedef struct _WnString
{
	unsigned int	unStringLen;
	unsigned char * pString;		//����ָ��������
}WnString,*ptrWnString;

// union to hold a value of several data type
typedef union _WnValue
{
	unsigned __int32	ui32;			// unsigned int32
	unsigned __int64	ui64;			// unsigned int64
	__int64				i64;			// __int64
	__int32				i32;			// __int32
	double				d;				// double

	ptrWnStruct	ptrStruct;			// ����ָ��������
	ptrWnString ptrString;			// �ַ���

} WnValue,*ptrWnValue;

//���ָ��Ľṹ��
typedef struct _WnField
{
	unsigned short	usFieldId;		// field ID defined by FeedHandler Group
	unsigned char   ucValueType;	// value type(ref. Part I)
	ptrWnValue		ptrValue;		// union to hold the actual value
} WnField,*ptrWnField;

typedef struct _SecurityData
{
	char szWindCode[16];			//Wind Code
	std::vector<ptrWnField> vecField;	//����ָ��
}WnSecurityData,*ptrWnSecurityData;

typedef std::vector<ptrWnSecurityData> vecFeedHandlerData;

typedef struct tagFeedHandlerHeader
{
	//�̶�����
	unsigned char	ucPrefix[2];	//��ʼ����0x5555
	unsigned char	ucVersion;		//�汾��Ϣ ���λ��ʾ�Ƿ�ѹ��(0-δѹ����1-ѹ��)

	//��汾��ز���
	unsigned int	unLocalTime;	//����ʱ�䣨HHMMSSXXX����ȷ��ms��
	unsigned int	unDataTimeStamp;//���ݰ�ʱ�����HHMMSSXXX����ȷ��ms��
	unsigned int	unPacketNo;		//���ݰ����[1..M]
	unsigned char	ucMachineNo;	//����Դ���ڵĻ������
	unsigned char	ucChannel;		//����Դͨ�����[1..N]
	unsigned int	unCodeTotal;	//Wind֤ȯ��������

	unsigned char	ucCheckSum;		//У��λ
	unsigned int	unDataLen;		//���ݲ��ֳ��ȣ������岿�֣�
}FH_HEADER;

typedef struct tagFeedHandlerTail
{
	unsigned char	ucSuffix[2];		//��������0x1616
}FH_TAIL;

enum ENUM_COMMAND
{
	E_WN_SET_COMPRESS_FLAG = 1, //����ѹ����־
};

typedef struct tagFHCommand
{
	int nCommand;   
	int nContent;
}FH_COMMAND;



//����Ӷ�����ڸ���ǰ��!!!
#pragma pack(pop)

#endif
