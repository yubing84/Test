#include "../main_frame/StdAfx.h"
#include "ValueTranslation.h"
#include <sstream>
#include <math.h>
#include <iomanip>

using namespace std;

const string NOT_AVAILABLE = "NA";

string CValueTranslation::m_not_available = NOT_AVAILABLE;

CValueTranslation:: CValueTranslation(void)
{
  
}

CValueTranslation::~CValueTranslation(void)
{
}

// ��8 bit value ת���string. �ص���ת����Чֵ
string CValueTranslation::Translation8BitValue(int8_t value)
{
   if(value == WMDF_CONSTS_8BIT_NIL_VALUE)
     return m_not_available;

  stringstream ss;
  ss << value;
  return ss.str();
}

// ��32 bit value ת���string. �ص���ת����Чֵ
string CValueTranslation::Translation32BitValue(int32_t value)
{
  if(value == WMDF_CONSTS_32BIT_NIL_VALUE)
    return m_not_available;

  stringstream ss;
  ss << value;
  return ss.str();
}

// ��64 bit value ת���string. �ص���ת����Чֵ
string CValueTranslation::Translation64BitValue(int64_t value)
{
  if(value == WMDF_CONSTS_64BIT_NIL_VALUE)
    return m_not_available;

  stringstream ss;
  ss << value;
  return ss.str();
}

// ��double value ת���string. �ص���ת����Чֵ
string CValueTranslation::TranslationDoubleValue(double value)
{
 /* if(value == WMDF_CONSTS_DOUBLE_NIL_VALUE)
      return m_not_available*/

  if(value != value)
    return m_not_available;

  stringstream ss;
  ss << setiosflags(ios::fixed) << setprecision(3) << value; // �����ÿ�ѧ������
  return ss.str();
}

// ��char* value ת���string. �ص���ת����Чֵ
string CValueTranslation::TranslationStringValue(string value)
{
  if(value == string(reinterpret_cast<char*>(WMDF_CONSTS_STRING_NIL_VALUE)))
    return m_not_available;

  stringstream ss;
  ss << value;
  return ss.str();
}