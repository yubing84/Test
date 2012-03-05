#pragma once
#include "SSEL2_StructDefine.h"

#define VALUE_ABSENT	-1000

enum E_SSE_ERROR_CODE
{
	E_SSE_OK						= 0,
	// �����ļ�������;
	E_SSE_CONFIGFILE_NOTEXIST		= -1,
	// �����ļ���ʧ��;
	E_SSE_CONFIGFILE_OPENFAILED		= -2,
	// ģ��·��Ϊ��;
	E_SSE_CONFIGFILE_NOXMLPATHITEM	= -3,
	// �����ļ����п�ֵ;
	E_SSE_CONFIGFILE_EMPTYVALUE		= -4,
	// ����XMLģ��ʧ��;
	E_SSE_PARSE_FAIL				= -5,
	// ��ʼ��δ���;
	E_SSE_INIT_UNCOMPLETE			= -6,
	// ����������д���������;
	E_SSE_EXIST_HEARTBEAT			= -7,
	// XML�ļ�������;
	E_SSE_XMLFILENOTEXIST			= -8
};

extern "C"
{
	/**
	*��ʼ������;
	*@param:  bIsFilterHB  ������true��ʱ���������������֮������;
	*@retval: ��ʼ����Ϣ;
	*/
	__declspec(dllexport) int SSEInit(bool bIsFilterHB);
	/**
	*����SSE_L2��������;
	*@param:  pucRawData  ��Ҫ����������;
	*@param:  unRawDataLength  ��Ҫ���������ݳ���;
	*@param:  ppVecFHData  ָ���Ž��������ݵ�vectorָ���ָ��;
	*@retval: 1. E_SSE_OK	�����ɹ� 2. E_SSE_INIT_UNCOMPLETE ��ʼ��δ���3. E_SSE_EXIST_HEARTBEAT  ����������;
	*/
	__declspec(dllexport) int SSEDecodeRawData(const unsigned char *pucRawData,unsigned int unRawDataLength,vecFeedHandlerData** ppVecFHData);
	/**
	*�ͷ���Դ;
	*@param:  ��Դָ��;
	*@retval: ��;
	*/
	__declspec(dllexport) void SSEReleaseBuffer(vecFeedHandlerData *ptrVecFHData);
	/**
	*ж�ؽ���ģ�麯��;
	*@param:  ��;
	*@retval: E_SSE_OK;
	*/
	__declspec(dllexport) int SSEUninit();
}