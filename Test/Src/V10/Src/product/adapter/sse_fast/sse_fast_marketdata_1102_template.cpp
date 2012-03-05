#include "sse_fast_marketdata_1102_template.h"
#include "../common/rawdata_object.h"

wmdf::SSEFastMarketData1102Template::SSEFastMarketData1102Template()
:FastTemplate(item_count_)
{

}

wmdf::SSEFastMarketData1102Template::~SSEFastMarketData1102Template()
{

}

wmdf::WindFastMessage* wmdf::SSEFastMarketData1102Template::DecodeRaw(uint8_t* raw_data,uint32_t len )
{
	int data_status=0,data_time_stamp=0;
	int tid=0;
	fast_decoder_->ReSet(raw_data,len);
	int capacity=64;
	int size=0;
	uint8_t palce_str[20];
	uint64_t temp=0;
	MarketData* data_array = new MarketData[capacity];//���������ķ���	
	for(int32_t i=0;i!=capacity;++i)
	{
		for(int32_t j=0; j!=10; ++j)
		{
			data_array[i].ask_price[j] = 0;
			data_array[i].ask_size[j] = 0;
			data_array[i].bid_price[j] = 0;
			data_array[i].bid_size[j] = 0;
		}
		data_array[i].l2_total_bid_qty = WMDF_CONSTS_64BIT_NIL_VALUE;
		data_array[i].l2_total_offer_qty = WMDF_CONSTS_64BIT_NIL_VALUE;
		data_array[i].new_price = WMDF_CONSTS_DOUBLE_NIL_VALUE;
		data_array[i].pre_close = WMDF_CONSTS_DOUBLE_NIL_VALUE;
		data_array[i].today_high = WMDF_CONSTS_DOUBLE_NIL_VALUE;
		data_array[i].today_low = WMDF_CONSTS_DOUBLE_NIL_VALUE;
		data_array[i].today_open = WMDF_CONSTS_DOUBLE_NIL_VALUE;
		data_array[i].total_amount = WMDF_CONSTS_DOUBLE_NIL_VALUE;
		data_array[i].trade_date = WMDF_CONSTS_32BIT_NIL_VALUE;
		data_array[i].trade_time = WMDF_CONSTS_32BIT_NIL_VALUE;
		data_array[i].transactions_count = WMDF_CONSTS_64BIT_NIL_VALUE;
		data_array[i].volume = WMDF_CONSTS_64BIT_NIL_VALUE;
		data_array[i].weighted_average_best_ask = WMDF_CONSTS_DOUBLE_NIL_VALUE;
		data_array[i].weighted_average_best_bid = WMDF_CONSTS_DOUBLE_NIL_VALUE;
		data_array[i].peratio1 = WMDF_CONSTS_DOUBLE_NIL_VALUE;
		data_array[i].peratio2 = WMDF_CONSTS_DOUBLE_NIL_VALUE;
		data_array[i].trade_status = WMDF_CONSTS_8BIT_NIL_VALUE;
		memset(data_array[i].wind_code,0,sizeof(data_array->wind_code));
	}
	while(!fast_decoder_->Empty())
	{
		fast_decoder_->BeginNewMessage();
		tid = fast_decoder_->DecodeUInt32(0,DEFAULT);
		assert(tid==SSE_MARKETDATA_1102_TYPE);
		data_time_stamp = fast_decoder_->DecodeInt32(1,COPY,PT_MANDATORY);
		data_status=fast_decoder_->DecodeInt32(2,DEFAULT);
		if(data_status<=0)//������Ч
		{
			// constant ��������Ҫ
			if(size>=capacity)
			{
				MarketData* temp = new MarketData[capacity*2];
				memcpy(temp,data_array,sizeof(MarketData)*capacity);
				capacity=capacity*2;
				delete[] data_array;
				data_array = temp;
				for(int32_t i=size;i!=capacity;++i)
				{
					for(int32_t j=0; j!=10; ++j)
					{
						data_array[i].ask_price[j] = 0;
						data_array[i].ask_size[j] = 0;
						data_array[i].bid_price[j] = 0;
						data_array[i].bid_size[j] = 0;
					}
					data_array[i].l2_total_bid_qty = WMDF_CONSTS_64BIT_NIL_VALUE;
					data_array[i].l2_total_offer_qty = WMDF_CONSTS_64BIT_NIL_VALUE;
					data_array[i].new_price = WMDF_CONSTS_DOUBLE_NIL_VALUE;
					data_array[i].pre_close = WMDF_CONSTS_DOUBLE_NIL_VALUE;
					data_array[i].today_high = WMDF_CONSTS_DOUBLE_NIL_VALUE;
					data_array[i].today_low = WMDF_CONSTS_DOUBLE_NIL_VALUE;
					data_array[i].today_open = WMDF_CONSTS_DOUBLE_NIL_VALUE;
					data_array[i].total_amount = WMDF_CONSTS_DOUBLE_NIL_VALUE;
					data_array[i].trade_date = WMDF_CONSTS_32BIT_NIL_VALUE;
					data_array[i].trade_time = WMDF_CONSTS_32BIT_NIL_VALUE;
					data_array[i].transactions_count = WMDF_CONSTS_64BIT_NIL_VALUE;
					data_array[i].volume = WMDF_CONSTS_64BIT_NIL_VALUE;
					data_array[i].weighted_average_best_ask = WMDF_CONSTS_DOUBLE_NIL_VALUE;
					data_array[i].weighted_average_best_bid = WMDF_CONSTS_DOUBLE_NIL_VALUE;
					data_array[i].peratio1 = WMDF_CONSTS_DOUBLE_NIL_VALUE;
					data_array[i].peratio2 = WMDF_CONSTS_DOUBLE_NIL_VALUE;
					data_array[i].trade_status = WMDF_CONSTS_8BIT_NIL_VALUE;
					memset(data_array[i].wind_code,0,sizeof(data_array->wind_code));
				}
			}	
			//��ȡ����
			MarketData& curr_market_data = data_array[size++];
			//�������
			curr_market_data.trade_time= data_time_stamp*1000;
			fast_decoder_->DecodeString(3,NONE,(uint8_t*)curr_market_data.wind_code,sizeof(curr_market_data.wind_code));
      
			int32_t today_open = fast_decoder_->DecodeInt32(4,DEFAULT);
      curr_market_data.today_open = Utils::Divide(today_open,WMDF_CONSTS_ONE_THOUSAND);
			
			int32_t today_high = fast_decoder_->DecodeInt32(5,DEFAULT);
			curr_market_data.today_high = Utils::Divide(today_high,WMDF_CONSTS_ONE_THOUSAND);

			int32_t today_low = fast_decoder_->DecodeInt32(6,DEFAULT);
			curr_market_data.today_low = Utils::Divide(today_low,WMDF_CONSTS_ONE_THOUSAND);

			int32_t new_price = fast_decoder_->DecodeInt32(7,DEFAULT);
			curr_market_data.new_price = Utils::Divide(new_price,WMDF_CONSTS_ONE_THOUSAND);

			int32_t BidPriceLevelCount = fast_decoder_->DecodeInt32(8,NONE);

			if(BidPriceLevelCount>0)
			{
				for (int i=0;i<BidPriceLevelCount;i++)
				{
          curr_market_data.bid_size[i] = Utils::ConvertToInt32(fast_decoder_->DecodeInt64(8,NONE,PT_MANDATORY));
					curr_market_data.bid_price[i] = Utils::Divide(fast_decoder_->DecodeInt32(8,NONE,PT_MANDATORY),WMDF_CONSTS_ONE_THOUSAND);
				}
			}

			int32_t OfferPriceLevelsCount = fast_decoder_->DecodeInt32(8,NONE);

			if(OfferPriceLevelsCount>0)
			{
				for (int i=0;i<OfferPriceLevelsCount;i++)
				{
					curr_market_data.ask_size[i] = Utils::ConvertToInt32(fast_decoder_->DecodeInt64(8,NONE,PT_MANDATORY));
					curr_market_data.ask_price[i] = Utils::Divide(fast_decoder_->DecodeInt32(8,NONE,PT_MANDATORY),WMDF_CONSTS_ONE_THOUSAND);
				}
			}

			int32_t num_trades = fast_decoder_->DecodeInt32(10,DEFAULT);
      if(num_trades != WMDF_CONSTS_32BIT_NIL_VALUE)
        curr_market_data.transactions_count = num_trades;

			curr_market_data.volume = fast_decoder_->DecodeInt64(11,DEFAULT);

			int64_t total_amount = fast_decoder_->DecodeInt64(12,DEFAULT);
      curr_market_data.total_amount = Utils::Divide(total_amount,WMDF_CONSTS_ONE_THOUSAND);

			curr_market_data.l2_total_bid_qty = fast_decoder_->DecodeInt64(13,DEFAULT);

			int32_t weighted_average_best_bid = fast_decoder_->DecodeInt32(14,DEFAULT);
			curr_market_data.weighted_average_best_bid = Utils::Divide(weighted_average_best_bid,WMDF_CONSTS_ONE_THOUSAND);

			double AltWeightedAvgBidPx = Utils::Divide(fast_decoder_->DecodeInt32(15,DEFAULT),WMDF_CONSTS_TEN_THOUSAND);

			int64_t l2_total_offer_qty = fast_decoder_->DecodeInt64(16,DEFAULT);
			curr_market_data.l2_total_offer_qty = Utils::DivideEx(l2_total_offer_qty,WMDF_CONSTS_ONE_THOUSAND);

			int32_t weighted_average_best_ask = fast_decoder_->DecodeInt32(17,DEFAULT);
			curr_market_data.weighted_average_best_ask = Utils::Divide(weighted_average_best_ask,WMDF_CONSTS_ONE_THOUSAND);

			double AltWeightedAvgOfferPx=Utils::Divide(fast_decoder_->DecodeInt32(18,DEFAULT),WMDF_CONSTS_TEN_THOUSAND);

			
			int32_t iopv = fast_decoder_->DecodeInt32(19,DEFAULT);
      curr_market_data.peratio1 = Utils::Divide(iopv , WMDF_CONSTS_ONE_THOUSAND);

			int32_t ytm = fast_decoder_->DecodeInt32(20,DEFAULT);
      curr_market_data.peratio2 = Utils::Divide(ytm , WMDF_CONSTS_TEN_THOUSAND);
		}
		else//������Ч
		{
			fast_decoder_->DecodeString(3,NONE,palce_str,sizeof(palce_str));
			fast_decoder_->DecodeInt32(4,DEFAULT) ;
			fast_decoder_->DecodeInt32(5,DEFAULT) ;
			fast_decoder_->DecodeInt32(6,DEFAULT) ;
			fast_decoder_->DecodeInt32(7,DEFAULT) ;
			int count = fast_decoder_->DecodeInt32(8,NONE);			
			for (int i=1;i<count;i++)
			{
				fast_decoder_->DecodeInt64(8,NONE) ;
				fast_decoder_->DecodeInt32(8,NONE) ;
			}
			count = fast_decoder_->DecodeInt32(8,NONE);
			for (int i=1;i<count;i++)
			{
				fast_decoder_->DecodeInt64(8,NONE);
				fast_decoder_->DecodeInt32(8,NONE);
			}
			fast_decoder_->DecodeInt32(10,DEFAULT);
			fast_decoder_->DecodeInt64(11,DEFAULT);
			fast_decoder_->DecodeInt64(12,DEFAULT);
			fast_decoder_->DecodeInt64(13,DEFAULT);
			fast_decoder_->DecodeInt32(14,DEFAULT);
			fast_decoder_->DecodeInt32(15,DEFAULT);
			fast_decoder_->DecodeInt64(16,DEFAULT);
			fast_decoder_->DecodeInt32(17,DEFAULT);
			fast_decoder_->DecodeInt32(18,DEFAULT);
			fast_decoder_->DecodeInt32(19,DEFAULT);
			fast_decoder_->DecodeInt32(20,DEFAULT);
		}
	}

  if (size > 0)
  {
    WindFastMessage* msg = new WindFastMessage();
    msg->MsgType = SSE_MARKETDATA_1102_TYPE;
    msg->Size=size;
    msg->Data = data_array;

    return msg;
  }
  else
  {
    delete data_array;
  }
  return NULL;
}