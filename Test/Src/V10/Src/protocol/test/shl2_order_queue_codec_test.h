#include <iostream>
#include <string>
#include <time.h> 
#include "../fast_codec_shl2_order_queue.h"
#include "../stop_bit_codec_szl2_order_queue.h"
#include "testUtils.h"

using std::string;

namespace wmdf{



void TestSHL2OrderQueueCodec()
	{	
    cout<<"------SSE L2 OrderQueue------"<<endl;
    char* windCode = new char[10];
    int ilength=1000;
    int times = 1;
    uint8_t* buffer=NULL;
    L2OrderQueue* orderQueues = new L2OrderQueue[ilength];		  
    L2OrderQueuePriceLevel* orderQueueLevel;	
    L2OrderQueueItem* order_queue_level_qty;
    
    clock_t start, end;
    
    for(int i=0;i<ilength;i++)
	  {  		  
      sprintf(windCode,"%06d.SH",i%10);        
      
	    memcpy(orderQueues[i].wind_code,windCode,10);
	    orderQueues[i].date_time_stamp=133001+i/60;
	    orderQueues[i].side = i%2;
		  orderQueues[i].image_status = i%2+1;
		  orderQueues[i].price_level_count=2;

      orderQueueLevel = new L2OrderQueuePriceLevel[2];      
      for(int j=0;j<2;j++)
      {        
        orderQueueLevel[j].price_level_operator=i%2;
        orderQueueLevel[j].price=15+(double)(i%10)/10;
        orderQueueLevel[j].orders_total=3;
        orderQueueLevel[j].orders_count=50;

        order_queue_level_qty = new L2OrderQueueItem[50];        
        for(int k=0;k<50;k++)
        {         
          order_queue_level_qty[k].order_queue_operator=i%2;
          order_queue_level_qty[k].order_queue_operator_entry_id=i%10000;
          order_queue_level_qty[k].order_qty=k*100000;          
        }
        orderQueueLevel[j].order_queue_items = order_queue_level_qty;
      }
      orderQueues[i].order_queue_levels = orderQueueLevel;
      //TestUtils::TolerateOrderQueue(&orderQueues[i]);
	  }

      
      
      StopBitCodecSZL2OrderQueue* codec = new StopBitCodecSZL2OrderQueue();		

      int count =0,bufferSize=0;
      start = clock();
      for(int i=0;i<times;i++)
      {         
        codec->EncodeData(orderQueues,ilength);  
      }

      end = clock();
      cout<<"�������ʱ: "<<(double)(end - start)/1000<<"S"<<endl;
      cout<<"ÿ�������: "<<(double)100*times/((end - start))<<"����"<<endl;

      bufferSize = codec->EncodeData(orderQueues,1000);
      cout<<"BufferSize:"<<bufferSize<<endl;
      if (bufferSize >0)
      { 
          buffer = (uint8_t*)malloc(bufferSize);
          codec->DequeueBuffer(buffer);
          start = clock();
          
          for(int p=0;p<times;p++)
          {       
            L2OrderQueue* items = (L2OrderQueue*)codec->DecodeData(buffer,bufferSize,count);
            std::cout<<p<<std::endl;     

            for(int i=0;i<count;i++)
            {
              if(!TestUtils::CompareOrderQueue(&orderQueues[i],&items[i]))
              {
                std::cout<<"FastCodecSHL2OrderQueue��["<<i<<"] error!"<<std::endl;
              }
		          /*else
		          {
			          std::cout<<"index ["<<i<<"] ok."<<std::endl;
		          }*/
            }
           
            TestUtils::DestroySSEL2OrderQueues(items,count);
            items=NULL;
          } 
          free(buffer);
          buffer=NULL;
          end = clock();
          cout<<"�����ʱ: "<<(double)(end - start)/1000<<"S"<<endl;
          cout<<"ÿ�������: "<<(double)times*100/(end - start)<<"����"<<endl;
      }   
      delete codec;
  }   
}