#include <iostream>
#include <string>
#include <time.h>
#include "../fast_codec_szl2_orders.h"
#include "../stop_bit_codec_szl2_orders.h"
#include "testUtils.h"
using std::string;
namespace wmdf{


void TestSZL2OrdersCodec()
{	
  cout<<"------SZSE L2 Orders------"<<endl;
  clock_t start, end;
  int times = 1,ilength=1000,bufferSize=0;

  SZSEL2Order* trans = new SZSEL2Order[ilength];
  for(int i=0;i<ilength;i++)
  {
	  string windCode = "000001.SH";
	  memcpy(trans[i].wind_code,windCode.c_str(),10);
		trans[i].rec_no = 10;
		trans[i].rec_no=i;
		trans[i].order_kind = 'c';
    trans[i].function_code = 'a';
		trans[i].order_price=119;
		trans[i].order_qty=100000;
	  trans[i].order_time = 103001+i%100;			
  }
  
  StopBitCodecSZL2Orders* codec = new StopBitCodecSZL2Orders();

  start = clock();
  for(int j=0;j<times;j++)		
  {
	  bufferSize = codec->EncodeData(trans,ilength);
  }      
  end = clock();
  cout<<"�������ʱ: "<<(double)(end - start)/1000<<"S"<<endl;
  cout<<"ÿ�������: "<<(double)times*100/((end - start))<<"����)"<<endl;

  bufferSize = codec->EncodeData(trans,ilength);
  std::cout<<"BufferSize:"<<bufferSize<<std::endl;  				
  if(bufferSize>0)
  {
	  uint8_t* buffer = (uint8_t*)malloc(bufferSize);
	  codec->DequeueBuffer(buffer);
	  int count=0;
	  start = clock();
	  for(int p=0;p<times;p++)
	  {  				
		  SZSEL2Order* items = (SZSEL2Order*)codec->DecodeData(buffer,bufferSize,count);
		  
		  //std::cout<<p<<std::endl;
		  for(int i = 0;i<count;i++)
		  {
		    if(!TestUtils::CompareOrders(&trans[i],&items[i]))
		    {
		      std::cout<<"FastCodecSZL2Orders ["<<i<<"] error!"<<std::endl;
		    }
        /*else
        {
          std::cout<<"index ["<<i<<"] ok!"<<std::endl;
        }*/
		  }
      delete[] items;
      items=NULL;
	  }
        
	  end = clock();
	  cout<<"�������ʱ: "<<(double)(end - start)/1000<<"S"<<endl;
	  cout<<"ÿ�������: "<<(double)times*100/((end - start))<<"����)"<<endl;
	  }
  delete codec;
  }
}