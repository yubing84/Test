
#ifndef lclientapi_h
#define lclientapi_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef GAVA_API
#ifdef _WIN32
#   
#   if defined DLL_EXPORT
#       define GAVA_API __declspec(dllexport)
#   else
#       define GAVA_API __declspec(dllimport)
#   endif
#else
#   if defined __SUNPRO_C  || defined __SUNPRO_CC
#       define GAVA_API __global
#   elif (defined __GNUC__ && __GNUC__ >= 4) || defined __INTEL_COMPILER
#       define GAVA_API __attribute__ ((visibility("default")))
#   else
#       define GAVA_API
#   endif
#endif
#else 
#define GAVA_API
#endif


#if ((defined _MSC_VER &&_MSC_VER>1500)||(defined __GNUC__ && __GNUC__ >= 4))
#include <stdint.h>
#include <stddef.h>
#else
#ifndef int8_t
  typedef char int8_t;
#endif
#ifndef int16_t
  typedef short int16_t;
#endif
#ifndef int32_t
  typedef int int32_t;
#endif
#ifndef int64_t
  typedef long long int64_t;
#endif
#ifndef uint8_t
  typedef unsigned char uint8_t;
#endif
#ifndef uint16_t
  typedef unsigned short uint16_t;
#endif
#ifndef uint32_t
  typedef unsigned int uint32_t;
#endif
#ifndef uint64_t
  typedef unsigned long long uint64_t;
#endif
#endif

typedef struct Value0
{
  int32_t type;       //���ڱ�ǵ�ǰ�ṹ��Ӧ��Gava����������
  void* owner;
  union{
    uint8_t u8;
    int32_t i32;
    int64_t i64;
    double  d;
    char* s;
    struct Value0* next;//���ڼ��ػ�
    struct
    {
      int32_t n;
      uint8_t data[1];
    };
  };
}*GValue;

#define gG(x)               ((x)->data)
#define gC(x)               gG(x)
#define gI(x)               ((int32_t*)gG(x))
#define gJ(x)               ((int64_t*)gG(x))
#define gE(x)               ((double*)gG(x))
#define gS(x)               ((char**)gG(x))
#define gL(x)               ((GValue*)gG(x))

#ifndef luai_NI
#define luai_NI              ((int)0x80000000)
#ifdef _WIN32
  #define luai_NL            ((long long)0x8000000000000000)
  #define luai_NN            (log(-1.0))
  extern double log(double);
#else 
  #define luai_NL            (0x8000000000000000LL)
  #define luai_NN            (0/0.0)
#endif

#define luai_NS             NULL
#define isNaI(n)            ((n) == luai_NI)
#define isNaL(n)            ((n) == luai_NL)
#define isNaN(n)            ((n) != (n))
#define isNaS(n)            ((n) == luai_NS)
#define isNaZ(n)            isNaN(n)
#define isNaD(n)            isNaI(n)
#define isNaT(n)            isNaI(n)
#define isNaU(n)            isNaI(n)
#define isNaV(n)            isNaI(n)
#define isNaM(n)            isNaI(n)

#endif //end of luai_NI

#ifndef LUA_TYPE
#define LUA_TYPE

#define LUA_TNONE		(-1)

#define LUA_TTYPEMASK	0xFFFF00FF

#define LUA_TNIL			0x0000
#define LUA_TLIGHTUSERDATA	0x0002

#define LUA_TBOOLEAN		0x0003
#define LUA_TBIT			  LUA_TBOOLEAN
#define LUA_TINT			  0x0004
#define LUA_TLONG			  0x0005
#define LUA_TNUMBER			0x0006
#define LUA_TSTRING			0x0007
#define LUA_TTABLE			0x0008
#define LUA_TVECTOR			0x0009
#define LUA_TGTABLE			0x000A
#define LUA_TBLOB       0x000B
#define LUA_TFUNCTION		0x000C
#define LUA_TUSERDATA		0x000D
#define LUA_TTHREAD			0x000E
#define LUA_NUMTAGS			0x000F
#define LUA_LIST        0x0010
#define LUA_TERROR      0x0011

#define LUA_TTYPE(subtype, basictype) ((subtype)|(basictype))
#define LUA_TDATETIME		LUA_TTYPE(0x0100, LUA_TNUMBER)
#define LUA_TDATE			  LUA_TTYPE(0x0100, LUA_TINT)
#define LUA_TMONTH			LUA_TTYPE(0x0200, LUA_TINT)
#define LUA_TMINUTE			LUA_TTYPE(0x0400, LUA_TINT)
#define LUA_TSECOND			LUA_TTYPE(0x0500, LUA_TINT)
#define LUA_TTIMESTAMP	LUA_TTYPE(0x0100, LUA_TLONG)
#define LUA_TTIME			  LUA_TTYPE(0x0300, LUA_TINT)
#define LUA_TTIMESPAN		LUA_TTYPE(0x0200, LUA_TLONG)

#endif //end of LUA_TYPE

/*
  * ˵���� ����Gava��������
  * ������
    * ipaddress ������IP��ַ��
    * port      �������˿ںš�
  * ���أ�
    * ����������ӳɹ����������Ӿ�������� ����-1��
*/
GAVA_API int32_t hopen(const char* ipaddress,int port);

/*
  * ˵���� �ر���Gava���������ӡ�
  * ������
    * sock_id ���Ӿ�����þ��������ͨ��hopen��������ʱ���صľ����
  * ���أ�
    * ʼ�շ��� 1.
*/
GAVA_API int32_t hclose(int32_t sock_id);

/*
  * ˵���� ��ͬ���ķ�ʽ������Gava������ִ�нű����
  * ������
    * sock_id ͨ��hopen��������ʱ���ص���Ч�����
    * script Gava�ű���
    * ... ���Ӳ�����������ݶ��������xΪ��һ�����������Ӳ���֮����������һ��NULL������
    * ���أ�
    * ����ű�Ϊ�������ã��򷵻غ������÷��صĽ����
  * ��ע��
    * �����߽���������
*/
GAVA_API GValue hexec(int32_t sock_id, const char* script, ...);

/*
* ���첽�ķ�ʽ����Gava������ִ�нű�����ʱ��ע��Ļص�������
*/
typedef void callback (GValue value);

/*
  * ˵���� ���첽�ķ�ʽ������Gava������ִ�нű����
  * ������
    * sock_id ͨ��hopen��������ʱ���ص���Ч�����
    * func ������ִ������첽����ʱ���ص��ú�����
    * script Gava�ű���
    * ... ���Ӳ�����������ݶ��������xΪ��һ�����������Ӳ���֮����������һ��NULL������
  * ���أ�
    * �������ʧ�ܣ�����-1�����򷵻�0��
*/
GAVA_API int32_t hasynccall(int32_t sock_id, callback func, const char* script, ...);

/*
  * ˵������int32_t����ת��Ϊ����Ϊint��GValue.
*/
GAVA_API GValue gint(int32_t);

/*
  * ˵������int32_t����ת��Ϊ����Ϊtime��GValue.
*/
GAVA_API GValue gttime(int32_t);

/*
  * ˵������int32_t����ת��Ϊ����Ϊminute��GValue.
*/
GAVA_API GValue gtminute(int32_t);

/*
  * ˵������int32_t����ת��Ϊ����Ϊsecond��GValue.
*/
GAVA_API GValue gtsecond(int32_t);

/*
  * ˵������int32_t����ת��Ϊ����Ϊmonth��GValue.
*/
GAVA_API GValue gtmonth(int32_t);

/*
  * ˵������int32_t����ת��Ϊ����Ϊdate��GValue.
*/
GAVA_API GValue gtdate(int32_t);

/*
  * ˵������double����ת��Ϊ����Ϊdatetime��GValue.
*/
GAVA_API GValue gtdatetime(double);

/*
  * ˵������blob����װ��GValue
*/
GAVA_API GValue gblob(const char*,size_t);

/*
  * ˵������0���������ַ�������ת��Ϊ����Ϊstring��GValue.
*/
GAVA_API GValue gstring(const char*);

/*
  * ˵������0���������ַ�������ת��Ϊ�ڲ����ַ���.
*/
GAVA_API char* ss(char*);

/*
  * ˵������int64_t����ת��Ϊ����Ϊlong��GValue.
*/
GAVA_API GValue glong(int64_t);

/*
  * ˵������double����ת��Ϊ����Ϊnumber��GValue.
*/
GAVA_API GValue gdouble(double);

/*
  * ˵������������Ϊtype��Ԫ�ظ���Ϊlength��������������Ϊvector��GValue.
  * ������
    * type ����ֵ��������ֵ��������Ч��LUA_TYPE
    * length ������Ԫ�صĸ���
  * ���أ�����Ϊvector��GValue.
*/
GAVA_API GValue gvector(int16_t type,int32_t length);

/*
  * ˵�������������Ϊlist��
  * ������
    * count ��Ҫ���Ϊlist��GValue����Ŀ
    * ... GValue
  * ���أ�
    * ����Ϊlist��GValue
*/
GAVA_API GValue glist(int32_t count,...);

/*
  * ˵�����ͷ��κβ���ʹ�õ�GValue���󡣰�����gint,glong���صģ�hexec���صģ��Լ��첽�ص���������ġ�
*/
GAVA_API void grelease(GValue value);

GAVA_API int gcount(GValue value);
GAVA_API int gencode(GValue value,char* data,int* len);

/*
  * ˵������ȡ�ڲ���ʾСʱ���ӵ�����ֵ
  * ������
    * hour Сʱ���֣���Чֵ����Ϊ[-99, +99]
    * minute ���Ӳ��֣���Чֵ����Ϊ[0, 59]
*/
GAVA_API int gminute(int hour,int minute);

/*
  * ˵������ȡ�ڲ���ʾСʱ�����������ֵ
  * ������
    * hour Сʱ���֣���Чֵ����Ϊ[-99, +99]
    * minute ���Ӳ��֣���Чֵ����Ϊ[0, 59]
    * second �벿�֣���Ч����Ϊ[0, 59]
*/
GAVA_API int gsecond(int hour,int minute,int second);

/*
  * ˵������ȡ�ڲ���ʾСʱ��������������ֵ
  * ������
    * hour Сʱ���֣���Чֵ����Ϊ[-99, +99]
    * minute ���Ӳ��֣���Чֵ����Ϊ[0, 59]
    * second �벿�֣���Ч����Ϊ[0, 59]
    * ms �벿�֣���Ч����Ϊ[0, 999]
*/
GAVA_API int gtime(int hour,int minute,int second,int ms);

/*
  * ˵������ȡ�ڲ���ʾ���µ�����ֵ
  * ������
    * year �겿�֣���Чֵ����Ϊ[1000, 9999]
    * month �²��֣���Чֵ����Ϊ[1, 12]
*/
GAVA_API int gmonth(int year,int month);

/*
  * ˵������ȡ�ڲ���ʾ���ڵ�����ֵ
  * ������
    * year ��lmonthͬ��
    * month ��lmonthͬ
    * day �ղ��֣���Чֵ����Ϊ[1, 31]����ע�⣬�Ͻ������������йأ�
*/
GAVA_API int gdate(int year,int month,int day);

/*
  * ˵������ȡ�ڲ���ʾ����ʱ��ĸ�����ֵ
  * ������
    * year ��ldateͬ��
    * month ��ldateͬ��
    * day ��ldateͬ��
    * hour ��ltimeͬ��
    * minute ��ltimeͬ��
    * second ��ltimeͬ��
    * ms ��ltimeͬ��
*/
GAVA_API double gdatetime(int year,int month,int day,int hour,int minute,int second,int ms);

/*
  * ˵�����������ڶ�Ӧ���ڼ���
  * ������
    * year ��ldateͬ��
    * month ��ldateͬ��
    * day ��ldateͬ��
*/
GAVA_API int gweek(int year,int month,int day);

/*
  * ˵���������ڲ���ʾ�ĵ�ǰ�·ݡ�
*/
GAVA_API int gcurrentmonth();

/*
  * ˵���������ڲ���ʾ�ĵ�ǰ���ڡ�
*/
GAVA_API int gcurrentdate();

/*
  * ˵���������ڲ���ʾ�ĵ�ǰСʱ���ӡ�
*/
GAVA_API int gcurrentminute();

/*
  * ˵���������ڲ���ʾ�ĵ�ǰСʱ�����롣
*/
GAVA_API int gcurrentsecond();

/*
  * ˵���������ڲ���ʾ�ĵ�ǰʱ��(Сʱ���������)��
*/
GAVA_API int gcurrenttime();

/*
  * ˵���������ڲ���ʾ�ĵ�ǰ����ʱ�䡣
*/
GAVA_API double gcurrentdatetime();

/*
  * ˵���������ڲ���ʾ�ĵ�ǰ�·ݡ�
*/
GAVA_API long long gtimestamp();

/*
  * ˵��: �������ڲ���ʾת��Ϊ�ꡢ�¡��յ�����
  * ������
    * d ���ڲ���ʾ������
    * year �������ڵ���
    * month �������ڵ���
    * day �������ڵ��գ��·ݵĵڼ��죩
  * ���أ����ʧ�ܷ���0�����򷵻�1
*/
GAVA_API int gdate2ymd(int d, int *year, int *month, int *day);

/*
  * ˵��: �����µ��ڲ���ʾת��Ϊ�ꡢ�µ�����
  * ������
    * m ���ڲ���ʾ������
    * year �������µ����
    * month �������µ��·�
  * ���أ����ת��ʧ�ܷ���0�����򷵻�1
*/
GAVA_API int gmonth2ym(int m, int *year, int *month);

/*
  * ˵��: ��ʱ�����͵��ڲ���ʾת��ΪСʱ���ͷ���������
  * ������
    * m ���ڲ���ʾ�ķ���
    * hour ����ʱ���е�Сʱ��
    * minute ����ʱ���еķ�����
  * ���أ����ת��ʧ�ܷ���0�����򷵻�1
*/
GAVA_API int gminute2hm(int m, int *hour, int *minute);

/*
  * ˵��: ��ʱ�������͵��ڲ���ʾת��Ϊʱ���֡��������
  * ������
    * m ���ڲ���ʾ�ķ���
    * hour ����ʱ�����е�Сʱ��
    * minute ����ʱ�����еķ�����
    * second ����ʱ�����е�����
  * ���أ����ת��ʧ�ܷ���0�����򷵻�1
*/
GAVA_API int gsecond2hms(int s, int *hour, int *minute, int *second);

/*
  * ˵��: ��ʱ�����͵��ڲ���ʾת��Ϊʱ���֡��롢���������
  * ������
    * m ���ڲ���ʾ�ķ���
    * hour ����ʱ���е�Сʱ��
    * minute ����ʱ���еķ�����
    * second ����ʱ���е�����
    * msecond ����ʱ���еĺ�����
  * ���أ����ת��ʧ�ܷ���0�����򷵻�1
*/
GAVA_API int gtime2hmsm(int t, int *hour, int *minute, int *second, int *msecond);

/*
  * ˵��: ������ʱ�����͵��ڲ���ʾת��Ϊ�ꡢ�¡��ա�ʱ���֡��롢���������
  * ������
    * m ���ڲ���ʾ�ķ���
    * year ��������ʱ���е����
    * month ��������ʱ���е��·�
    * day ��������ʱ���е��գ��·ݵĵڼ��죩
    * hour ��������ʱ���е�Сʱ��
    * minute ��������ʱ���еķ�����
    * second ��������ʱ���е�����
    * msecond ��������ʱ���еĺ�����
  * ���أ����ת��ʧ�ܷ���0�����򷵻�1
*/
GAVA_API int gdatetime2ymdhmsm(double dt,  int *year, int *month, int *day, 
  int *hour, int *minute, int *second, int *msecond);

#ifdef __cplusplus
}
#endif
#endif