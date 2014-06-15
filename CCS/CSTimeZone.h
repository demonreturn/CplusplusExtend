
#ifndef _CCS_TIME_ZONE_H_
#define _CCS_TIME_ZONE_H_

#include "CCSBase.h"
#include "CCSTimeStamp.h"

class CCSTimeZone
{
public:
	/************************************
		����: ���ر���ʱ����UTCʱ���ʱ���λ�롣
		����ʱ�� = UTCʱ�� + UtcOffset + Dst
	
		����ֵ:int   ʱ����ֵ
	
		�����б�:
	************************************/
	static int UtcOffset();

	/************************************
		����: ���ϵͳʹ��������ʱ����������ʱ��ʱ���λ��
	
		����ֵ:int
	
		�����б�:
	************************************/
	static int Dst();

	/************************************
		����: ���ظ���ʱ����Ƿ�������ʱ��ʹ����C����ʱ���localtime
	
		����ֵ:bool
	
		�����б�:
		const CVxTimeStamp & timestamp
	************************************/
	static bool IsDst(const CCCSTimeStamp& timestamp);

	/************************************
		����: ���ص�ǰʱ����UTC֮��Ĳ�ֵ����λ�롣utcOffset + dst
	
		����ֵ:int
	
		�����б�:
	************************************/
	static int Tzd();
};

#endif	// _CCS_TIME_ZONE_H_

