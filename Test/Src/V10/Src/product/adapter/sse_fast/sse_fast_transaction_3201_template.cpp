#include "sse_fast_transaction_3201_template.h"
#include "../common/rawdata_object.h"


wmdf::SSEFastTransaction3201Template::SSEFastTransaction3201Template()
:FastTemplate(item_count_)
{

}

wmdf::SSEFastTransaction3201Template::~SSEFastTransaction3201Template()
{

}

wmdf::WindFastMessage* wmdf::SSEFastTransaction3201Template::DecodeRaw(uint8_t* raw_data,uint32_t len )
{
	int data_status=0;
	int tid=0;
	fast_decoder_->ReSet(raw_data,len);
	int capacity=64;
	int size=0;
	uint8_t palce_str[20];
	Transaction* data_array = new Transaction[capacity];//���������ķ���	
	for(int32_t i=0;i!=capacity;++i)
	{
		data_array[i].buyOrderRecNo = WMDF_CONSTS_32BIT_NIL_VALUE;
		data_array[i].function_code = WMDF_CONSTS_8BIT_NIL_VALUE;
		data_array[i].order_kind = WMDF_CONSTS_8BIT_NIL_VALUE;
		data_array[i].price = WMDF_CONSTS_DOUBLE_NIL_VALUE;
		data_array[i].rec_no = WMDF_CONSTS_32BIT_NIL_VALUE;
		data_array[i].sellOrderRecNo = WMDF_CONSTS_32BIT_NIL_VALUE;
		data_array[i].set_no = WMDF_CONSTS_32BIT_NIL_VALUE;
		data_array[i].trade_money = WMDF_CONSTS_DOUBLE_NIL_VALUE;
		data_array[i].trade_qty = WMDF_CONSTS_32BIT_NIL_VALUE;
		data_array[i].trade_time = WMDF_CONSTS_32BIT_NIL_VALUE;
		memset(data_array[i].wind_code,0,sizeof(data_array->wind_code));
	}
	while(!fast_decoder_->Empty())
	{

		fast_decoder_->BeginNewMessage();
		tid = fast_decoder_->DecodeUInt32(0,DEFAULT);
		assert(tid==SSE_TRANSACTION_3201_TYPE);
		data_status=fast_decoder_->DecodeInt32(1,DEFAULT);
		if(data_status<=0)//������Ч
		{
			// constant ��������Ҫ
			if(size>=capacity)
			{
				Transaction* temp = new Transaction[capacity*2];
				memcpy(temp,data_array,sizeof(Transaction)*capacity);
				capacity=capacity*2;
				delete[] data_array;
				data_array = temp;
				for(int32_t i=size;i!=capacity;++i)
				{
					data_array[i].buyOrderRecNo = WMDF_CONSTS_32BIT_NIL_VALUE;
					data_array[i].function_code = WMDF_CONSTS_8BIT_NIL_VALUE;
					data_array[i].order_kind = WMDF_CONSTS_8BIT_NIL_VALUE;
					data_array[i].price = WMDF_CONSTS_DOUBLE_NIL_VALUE;
					data_array[i].rec_no = WMDF_CONSTS_32BIT_NIL_VALUE;
					data_array[i].sellOrderRecNo = WMDF_CONSTS_32BIT_NIL_VALUE;
					data_array[i].set_no = WMDF_CONSTS_32BIT_NIL_VALUE;
					data_array[i].trade_money = WMDF_CONSTS_DOUBLE_NIL_VALUE;
					data_array[i].trade_qty = WMDF_CONSTS_32BIT_NIL_VALUE;
					data_array[i].trade_time = WMDF_CONSTS_32BIT_NIL_VALUE;
					memset(data_array[i].wind_code,0,sizeof(data_array->wind_code));
				}
			}
			//��ȡ����
			Transaction& current_transcation=data_array[size++];

			//�������
			current_transcation.rec_no=fast_decoder_->DecodeInt32(2,INCREASE,PT_MANDATORY);
			current_transcation.set_no=fast_decoder_->DecodeInt32(3,COPY);//�Ͻ���trade_channel����set_no
			fast_decoder_->DecodeString(4,COPY,(uint8_t*)current_transcation.wind_code,sizeof(current_transcation.wind_code));
			
			current_transcation.trade_time = fast_decoder_->DecodeInt32(5,COPY);

			int32_t price = fast_decoder_->DecodeInt32(6,DEFAULT);
      current_transcation.price = Utils::Divide(price,WMDF_CONSTS_ONE_THOUSAND);

			int64_t trade_qty = fast_decoder_->DecodeInt64(7,DEFAULT);
				current_transcation.trade_qty = Utils::DivideEx2(trade_qty,WMDF_CONSTS_ONE_THOUSAND);

			int64_t trade_money = fast_decoder_->DecodeInt64(8,DEFAULT);
			current_transcation.trade_money = Utils::Divide(trade_money,WMDF_CONSTS_HUNDRED_THOUSAND);
		}else//������Ч
		{
			fast_decoder_->DecodeInt32(2,INCREASE);
			fast_decoder_->DecodeInt32(3,DEFAULT);
			fast_decoder_->DecodeString(4,DEFAULT,palce_str,sizeof(palce_str));
			fast_decoder_->DecodeInt32(5,DEFAULT);
			fast_decoder_->DecodeInt32(6,DEFAULT);
			fast_decoder_->DecodeInt64(7,DEFAULT);
			fast_decoder_->DecodeInt64(8,DEFAULT);
		}
	}

	WindFastMessage* msg = new WindFastMessage();
	msg->MsgType = SSE_TRANSACTION_3201_TYPE;
	msg->Size=size;
	msg->Data = data_array;
	return msg;
}
