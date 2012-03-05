#pragma once

#include <string>
#include "../../include/wmdf_api.h"

// ��studio�г��ֵ�idת����ַ�
class CWordTranslation
{
public:
  CWordTranslation(void);
  ~CWordTranslation(void);

public:
  // ��product id ת���product name
  static std::string TranslationProductID(const int16_t product_id);

  // ��message id ת���message name
  static std::string TranslationMessageID(const int16_t product_id, const int16_t message_id);

  // ��ί�ж��е�sideת���name
  static std::string TranslationOrderQueueL2Side(const uint8_t side);

  // ��ί�ж��е�image_statusת���name
  static std::string TranslationOrderQueueL2ImageStatus(const int32_t image_status);

  // ��ί�ж��е�price_level_operatorת���name
  static std::string TranslationOrderQueueL2PriceLevelOperator(const int32_t price_level_operator);

  // ��ί�ж��е�order_queue_operatorת���name
  static std::string TranslationOrderQueueL2OrderQueueOperator(const int32_t order_queue_operator);

  // �����ί�е�order_kindת���name
  static std::string TranslationOrdersL2order_kind(const char order_kind);

  static std::string TranslateServerStatus(const int32_t server_stat);
};
