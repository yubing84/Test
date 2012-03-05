#include "fast_template_decoder.h"
#include "../../../monitor/logger.h"

wmdf::FastTemplateDecoder::FastTemplateDecoder()
{
  exchange_msg_min_len_ = 0;  //�г���С����С
  exchange_msg_head_len_ = 0;//��Ϣͷ��С
  exchange_mag_tail_len_ = 0;//��Ϣβ�ֽ���

  step_packet_count_ = 0;    //step ���ĸ���
  fast_content_count_ = 0;   //����fast���ĸ���
  max_packet_size_ = 0;      //���İ���С
  total_packet_size_ = 0;    //�ܵİ���С
}

wmdf::FastTemplateDecoder::~FastTemplateDecoder()
{

}


int32_t wmdf::FastTemplateDecoder::DecodeRawData( uint8_t* data,int32_t len )
{
  msg_items_.clear();
  head_ = data;
  tail_ = data+len;
  buff_len_ = len;
  int32_t offset_ = 0;

  while (offset_+exchange_msg_min_len_ < buff_len_  )
  {
    uint8_t* temp=StrUtils::Str3Find(head_+offset_,(uint8_t*)"8=S",tail_);//head start tag
    if (NULL == temp)
    {
      return offset_;
    }

    //����������ֹ�ҵ�96�ֶ��еġ�8=STEP��
    if(temp!=head_+offset_)
    {
      uint8_t* check_str=temp+strlen("8=STEP.1.0.0 "); 
      uint8_t* tmp_check_str=StrUtils::Str2Find(check_str,(uint8_t*)"9=",tail_);
      if(check_str==tmp_check_str)//��һ��ȷ��
      {
        while(*check_str!=1)check_str++;//����һkey��λ��
        check_str++;
        tmp_check_str=StrUtils::Str3Find(check_str,(uint8_t*)"35=",tail_);
        if(tmp_check_str!=check_str)
        {
          offset_ = temp - head_ + 12;
          continue;
        }
      }
      else
      {
        offset_ = temp - head_ + 12;
        continue;
      }
    }
    temp+=exchange_msg_head_len_;//ָ��9=��֮��
    char* body_len_ptr;  //ָ��9=81 ���Ŀո�
    int32_t body_len = strtol((char*)temp,&body_len_ptr,10);

    //�ж�һ�������İ����Ƿ�С��ʣ�µ��ֽ���
    int32_t full_packet_len = ((uint8_t*)body_len_ptr-(head_+offset_)+1)+ body_len+ exchange_mag_tail_len_;
    if(full_packet_len >buff_len_-offset_)
      return offset_;

    //�жϰ�������� 10=
    uint8_t* pack_end=StrUtils::Str3Find((uint8_t*)body_len_ptr+1+body_len,(uint8_t*)"10=",tail_);
    if (pack_end != (uint8_t*)body_len_ptr+1+body_len)
    {
      offset_ += 12; //������8=STEP.1.0.0��
      continue;
    }

    offset_ += full_packet_len;
    //��ȡmsgtype
    temp=(uint8_t*)body_len_ptr+4; //ָ�� 35=����3
    uint8_t* current_tid=temp;
    while(*temp!=1)temp++;//��ASCII ��1��תΪ0 Ϊ������ַ���������׼��
    *temp=0;
    Decode96Field(current_tid,temp,head_+offset_);

    //ͳ�ư���������С    
    step_packet_count_++; 
    max_packet_size_ = (max_packet_size_ > full_packet_len) ? max_packet_size_ : full_packet_len; 
    total_packet_size_ += full_packet_len;      
  }
  return offset_;	
}

void wmdf::FastTemplateDecoder::ResetContext()
{
  Logger::instance()->WriteFormatLog(LL_INFO,
    "decoder summary: step_packet_count: %I64d, 96_field_count: %I64d, max_packet_size: %I64d, total_size: %I64d \n",
    step_packet_count_,fast_content_count_,max_packet_size_,total_packet_size_);  
  step_packet_count_ = 0;    //step ���ĸ���
  fast_content_count_ = 0;   //����fast���ĸ���
  max_packet_size_ = 0;      //���İ���С
  total_packet_size_ = 0;    //�ܵİ���С
}
