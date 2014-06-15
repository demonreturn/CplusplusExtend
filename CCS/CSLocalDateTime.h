
#ifndef _CCS_LOCAL_TIME_H_
#define _CCS_LOCAL_TIME_H_

#include "CCSBase.h"
#include "CSDateTime.h"

class CCSLocalDateTime
{
public:
	// ����һ����ǰ��������ʱ��
	CCSLocalDateTime();

	/************************************
		����: ����һ��ָ�������ա������ı�������ʱ��
	
		����ֵ:
	
		�����б�:
		int year             0 to 9999.
		int month            1 to 12.
		int day              1 to 31
		int hour             0 to 23.
		int minute           0 to 59.
		int second           0 to 59.
		int millisecond      0 to 999.
		int microsecond      0 to 999.
	************************************/
	CCSLocalDateTime( int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microsecond = 0 );

	CCSLocalDateTime( const CCCSTimeStamp& timestamp );

	/************************************
		����: ����UTC ��datetime����һ����������ʱ��
		�ڲ������ʱ������ת��
	
		����ֵ:
	
		�����б�:
		const CVxDateTime & dateTime    UTC����ʱ��
	************************************/
	CCSLocalDateTime( const CCSDateTime& datetime );

	/************************************
		����: ���ݸ�����������������һ����������ʱ��
	
		����ֵ:
	
		�����б�:
		double julianDay               ����������
	************************************/
	CCSLocalDateTime( double julianDay );

	CCSLocalDateTime( const CCSLocalDateTime& dateTime );

	CCSLocalDateTime& operator = ( const CCSLocalDateTime& dateTime );

	CCSLocalDateTime& operator = ( double julianDay );

	/************************************
		����: ��ֵ����
	
		����ֵ:CVxLocalDateTime&
	
		�����б�:
		int year             0 to 9999.
		int month            1 to 12.
		int day              1 to 31
		int hour             0 to 23.
		int minute           0 to 59.
		int second           0 to 59.
		int millisecond      0 to 999.
		int microsecond      0 to 999.
	************************************/
	CCSLocalDateTime& Assign(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int microseconds = 0);

	int Year() const;

	int Month() const;

	// ����ʱ�������е����ڣ���2012-7-13 12:00:00:000 ���ص���13��
	int Day() const;

	// ���ص�ǰʱ������һ�����ǵڼ��ܡ� firstDayOfWeekӦ����SUNDAY (0) or MONDAY (1)
	// ����ֵ������0��53.
	int Week( int firstDayOfWeek = CCSDateTime::MONDAY ) const;

	// һ���е����ڣ�0��6 0 = Sunday, 1 = Monday, ..., 6 = Saturday
	int DayOfWeek() const;

	// ����һ���е����ڣ���1��1��ʱ����1��2��1��ʱ����32�ȵȡ�
	int DayOfYear() const;

	int Hour() const;

	int HourAMPM() const;

	bool IsAM() const;

	bool IsPM() const;

	int Minute() const;

	int Second() const;

	int Millisecond() const;

	int Microsecond() const;

	double JulianDay() const;

	int Tzd() const;

	CCSDateTime UTC() const;

	CCCSTimeStamp TimeStamp() const;

	CCCSTimeStamp::TTimeValue UTCTime() const;

	CCSString ToString() const;

// operator
	bool operator == ( const CCSLocalDateTime& dateTime ) const;
	bool operator != ( const CCSLocalDateTime& dateTime ) const;
	bool operator <  ( const CCSLocalDateTime& dateTime ) const;
	bool operator <= ( const CCSLocalDateTime& dateTime ) const;
	bool operator >  ( const CCSLocalDateTime& dateTime ) const;
	bool operator >= ( const CCSLocalDateTime& dateTime ) const;

	CCSLocalDateTime  operator +  ( const CCSTimeSpan& span ) const;
	CCSLocalDateTime  operator -  ( const CCSTimeSpan& span ) const;
	CCSTimeSpan		  operator -  ( const CCSLocalDateTime& dateTime ) const;
	CCSLocalDateTime& operator += ( const CCSTimeSpan& span );
	CCSLocalDateTime& operator -= ( const CCSTimeSpan& span );

protected:
	CCSLocalDateTime( CCCSTimeStamp::TTimeValue utcTime, CCCSTimeStamp::TTimeDiff diff, int tzd );

	void DetermineTzd(bool adjust = false);

	void AdjustForTzd();

	std::time_t DstOffset(int& dstOffset) const;

private:
	CCSDateTime					m_dateTime;
	int							m_tzd;
};

#endif	// _CCS_LOCAL_TIME_H_

