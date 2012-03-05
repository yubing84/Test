#ifndef STEP_TEMPLATE_DECODER_H
#define STEP_TEMPLATE_DECODER_H

#include <vector>
#include "../../../include/wmdf_api.h"

namespace wmdf{

  struct WindStepMessage;

	class StepTemplateDecoder
	{
	public:
		StepTemplateDecoder();
		virtual ~StepTemplateDecoder();
    void ResetContext();
    int32_t DecodeRawData(uint8_t* data,int32_t len);
    std::vector<WindStepMessage*>& msg_items(){return msg_items_;}
	protected:
    virtual void DecodeMessage(uint8_t* tid,uint8_t* message_start,uint8_t* message_end)=0;
  protected:
    uint8_t* head_;
    uint8_t* tail_;
    int32_t buff_len_;
    std::vector<WindStepMessage*> msg_items_;
    int32_t exchange_msg_min_len_;  //�г���С����С
    int32_t exchange_msg_head_len_;//��Ϣͷ��С
    int32_t exchange_mag_tail_len_;//��Ϣβ�ֽ���

    int64_t step_packet_count_;    //step ���ĸ���
    int64_t max_packet_size_;      //���İ���С
    int64_t total_packet_size_;    //�ܵİ���С
	};
}
#endif
