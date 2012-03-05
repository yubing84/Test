#ifndef WIND_MDF_INTERNAL_API_H
#define WIND_MDF_INTERNAL_API_H

#include <math.h>
#include "wmdf_api.h"

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(push, 1)

typedef enum ConfigFileType
{
  CFT_SYSTEM = 0,                 //ϵͳ��Ϣ����
  CFT_PRODUCT = 1,                //��Ʒ��Ϣ����
  CFT_SOURCE = 2,                 //����Դ����
  CFT_USER = 3                    //�û���Ϣ����
}ConfigFileType;

typedef struct ConfigInfoRequset
{
  uint8_t         connection_id;
  ConfigFileType  config_type;            // 0=system.xml 1=product.xml 2=source.xml 3=user.xml
}ConfigInfoRequset;

typedef struct ConfigInfo
{
  uint8_t         connection_id;
  ConfigFileType  config_type;            // 0=system.xml 1=product.xml 2=source.xml 3=user.xml
  int32_t     length;
  int8_t      bytes[1];
}ConfigInfo;

typedef struct UpdateConfigResponse
{
  uint8_t         connection_id;
  ConfigFileType  config_type;            // 0=system.xml 1=product.xml 2=source.xml 3=user.xml
  eReturnValue    return_value;
}UpdateConfigResponse;

#pragma pack(pop)

////////////////////////////////////////////////////////////////
//  version 1.0 
////////////////////////////////////////////////////////////////

WMDF_API ConfigInfo* wmdf_request_configinfo(ConfigInfoRequset* args);
WMDF_API eReturnValue wmdf_set_configinfo(ConfigInfo* configinfo);

#ifdef __cplusplus
}
#endif

#endif
