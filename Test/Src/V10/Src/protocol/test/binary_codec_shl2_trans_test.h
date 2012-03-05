#include <iostream>
#include <string>
//#include <windows.h>

#include "../binary_codec_shl2_trans.h"
using std::string;
namespace wmdf{

	void TestSSEL2TransBinaryCodec()
	{
    cout<<"------SSE L2 Transaction BinaryCodec------"<<endl;
    clock_t start, end;
    int times = 1,ilength=1000,bufferSize=0;



    L2Transaction* trans = new L2Transaction[ilength];
    for(int i=0;i<ilength;i++)
    {
      string windCode = "000001.SH";
      memcpy(trans[i].wind_code,windCode.c_str(),10);
      trans[i].trade_channel = 10;
      trans[i].rec_no=i;
      trans[i].trade_money = 119*100000;
      trans[i].price=119;
      trans[i].trade_qty=100000;
      trans[i].trade_time = 103001+i%100;
    }

    BinaryCodecSHL2Trans* codec= new BinaryCodecSHL2Trans();

    start = clock();
    for(int j=0;j<times;j++)
    {
      bufferSize = codec->EncodeData(trans,ilength);
    }
    end = clock();
    cout<<"�������ʱ: "<<(double)(end - start)/1000<<"S"<<endl;
    cout<<"ÿ�������: "<<(double)times*1000/((end - start))<<"����)"<<endl;

		codec = new BinaryCodecSHL2Trans();

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
        L2Transaction* items = (L2Transaction*)codec->DecodeData(buffer,bufferSize,count);

        for(int i = 0;i<count;i++)
        {
          if(!TestUtils::CompareTransaction(trans[i],items[i]))
          {
            std::cout<<"BinaryCodecSHL2Trans ["<<i<<"] error!"<<std::endl;
          }
          /* else
          {
            std::cout<<"index ["<<i<<"] ok!"<<std::endl;
          }*/
        }
        delete[] items;
        items=NULL;
      }
      end = clock();
      cout<<"�������ʱ: "<<(double)(end - start)/1000<<"S"<<endl;
      cout<<"ÿ�������: "<<(double)times*1000/((end - start))<<"����)"<<endl;

    }
    delete codec;
	}
}
