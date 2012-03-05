#pragma once

#include <string>
#include "../../include/wmdf_api.h"

class CValueTranslation
{
public:
  CValueTranslation(void);
  ~CValueTranslation(void);

public:
  // ��8 bit value ת���string. �ص���ת����Чֵ
  static std::string Translation8BitValue(int8_t value);

  // ��32 bit value ת���string. �ص���ת����Чֵ
  static std::string Translation32BitValue(int32_t value);

  // ��64 bit value ת���string. �ص���ת����Чֵ
  static std::string Translation64BitValue(int64_t value);

  // ��double value ת���string. �ص���ת����Чֵ
  static std::string TranslationDoubleValue(double value);

  // ��char* value ת���string. �ص���ת����Чֵ
  static std::string TranslationStringValue(std::string value);

private:
  static std::string m_not_available;
};