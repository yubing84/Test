#include "step_template_decoder.h"
#include "../common/rawdata_object.h"
#include "../../../environment/strutils.h"
#include "../../../monitor/logger.h"

using namespace std;

wmdf::StepTemplateDecoder::StepTemplateDecoder()
{
  step_packet_count_ = 0;    //step ���ĸ���
  max_packet_size_ = 0;      //���İ���С
  total_packet_size_ = 0;    //�ܵİ���С
}


wmdf::StepTemplateDecoder::~StepTemplateDecoder()
{

}

int32_t wmdf::StepTemplateDecoder::DecodeRawData(uint8_t* data,int32_t len)
{
  msg_items_.clear();
  head_ = data;
  tail_ = data+len;
  buff_len_ = len;
  int32_t offset = 0;

  while (offset+exchange_msg_min_len_ < buff_len_  )
  {
    uint8_t* temp=StrUtils::Str3Find(head_+offset,(uint8_t*)"8=S",tail_);//head start tag
    if (NULL == temp)
    {
      return offset;
    }
    temp+=exchange_msg_head_len_;//ָ��9=��֮��
    char* body_len_ptr;  //ָ��9=81 ���Ŀո�
    int32_t body_len = strtol((char*)temp,&body_len_ptr,10);

    //�ж�һ�������İ����Ƿ�С��ʣ�µ��ֽ���
    int32_t full_packet_len = ((uint8_t*)body_len_ptr-(head_+offset)+1)+ body_len+ exchange_mag_tail_len_;
    if(full_packet_len >buff_len_-offset)
      return offset;

    //�жϰ�������� 10=
    uint8_t* pack_end=StrUtils::Str3Find((uint8_t*)body_len_ptr+1+body_len,(uint8_t*)"10=",tail_);
    if (pack_end != (uint8_t*)body_len_ptr+1+body_len)
    {
      offset += 12; //������8=STEP.1.0.0��
      continue;
    }

    offset += full_packet_len;
    //��ȡmsgtype
    temp=(uint8_t*)body_len_ptr+4; //ָ�� 35=����3
    uint8_t* current_tid=temp;
    while(*temp!=1)temp++;//��ASCII ��1��תΪ0 Ϊ������ַ���������׼��
    *temp=0;


    //���� 49=VDE56=VDR34=052=20061213-09:21:35347=UTF-8
    for(int count=0;count<5;temp++)
    {
      if(*temp==1)
        count++;
    }
    DecodeMessage(current_tid,temp,head_+offset);

    step_packet_count_++; 
    max_packet_size_ = (max_packet_size_ > full_packet_len) ? max_packet_size_ : full_packet_len; 
    total_packet_size_ += full_packet_len;      
  }
  
  return offset;


}

void wmdf::StepTemplateDecoder::ResetContext()
{
  Logger::instance()->WriteFormatLog(LL_INFO,
    "decoder summary: step_packet_count: %I64d,  max_packet_size: %I64d, total_size: %I64d \n",
    step_packet_count_,max_packet_size_,total_packet_size_);  
  step_packet_count_ = 0;    //step ���ĸ���
  max_packet_size_ = 0;      //���İ���С
  total_packet_size_ = 0;    //�ܵİ���С
}
