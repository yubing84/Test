#ifndef WIND_NET_VERSION_
#define WIND_NET_VERSION_
#include "net_config.h"
#include <vector>
namespace wmdf{

struct Version 
{
  uint8_t VersionTag[4];//"wind"
  uint8_t Placeholder;//0
  uint8_t IsBigEditen;//0: litter editen 1 :big editen
  uint8_t FrameMajorVersion;//���Э��汾��(���汾��)
  uint8_t FrameMinorVersion;//���Э��汾�ţ��Ӱ汾�ţ�
  uint8_t DataMajorVersion;//����Э�����汾��
  uint8_t DataMinorVersion; //����Э���Ӱ汾��
};

class VersionManager:private boost::noncopyable
{
  typedef boost::shared_ptr<Version> VersionPtr;
  typedef std::vector<VersionPtr> VersionList;
public:
  VersionManager():support_versions_()
  {
  }
  ~VersionManager()
  {
    support_versions_.clear();
  }

  VersionPtr& CreateVersion(uint8_t frame_major_version,uint8_t frame_minor_version,uint8_t data_major_version,uint8_t data_minor_version)
  {
    current_version_=AddSupportVersion(frame_major_version,frame_minor_version,data_major_version,data_minor_version);
    return current_version_;
  }

  VersionPtr GetCurrentVersion()
  {
    return current_version_;
  }

  VersionPtr AddSupportVersion(uint8_t frame_major_version,uint8_t frame_minor_version,uint8_t data_major_version,uint8_t data_minor_version)
  {
    VersionPtr version_ptr = VersionPtr(new Version());
    memcpy(version_ptr->VersionTag,"WIND",4);
    version_ptr->IsBigEditen=0;//��Ҫ���ݻ�����ȡ����ǰ��û��ʹ��
    version_ptr->FrameMajorVersion=frame_major_version;
    version_ptr->FrameMinorVersion=frame_minor_version;
    version_ptr->DataMajorVersion=data_major_version;
    version_ptr->DataMinorVersion=data_minor_version;
    support_versions_.push_back(version_ptr);
    return version_ptr;
  }

  bool CheckVersion(Version* version)
  {
    VersionList::const_iterator iter = support_versions_.begin();
    for (;iter!=support_versions_.end();iter++)
    {
      if((*iter)->FrameMajorVersion==version->FrameMinorVersion&&
             (*iter)->FrameMinorVersion==version->FrameMinorVersion&&
                 (*iter)->DataMajorVersion==version->DataMajorVersion&&
                     (*iter)->DataMinorVersion==version->DataMinorVersion)
                     return true;
    }
    return false;
  }

  bool Empty()
  {
    return support_versions_.empty();
  }

private:
  VersionList support_versions_;
  VersionPtr current_version_;
 
};

}//end namespace
#endif