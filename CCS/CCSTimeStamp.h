
#ifndef _CCS_TIMESTAMP_H_
#define _CCS_TIMESTAMP_H_

#include "CCSBase.h"

#include <ctime>

class CCS_API CCCSTimeStamp
{
public:
	typedef long long TTimeValue;
	typedef long long TTimeDiff;

public:
	CCCSTimeStamp();

	CCCSTimeStamp( TTimeValue tv );

	CCCSTimeStamp( const CCCSTimeStamp& src );

	~CCCSTimeStamp();

public:
	// ���µ���ǰʱ��
	void Refresh();

	// ����ʱ�����time_t��ʽ�ı�ʾ��base time��1970��1��1��0��,������S
	std::time_t GetTime() const;

	// ����ʱ�����UTC��ʾ��ʽ��base time��1582��10��15��0��,������100ns
	TTimeValue GetUtcTime() const;

	// ����ʱ�����΢���ʾ��base time��1970��1��1��0ʱ
	TTimeValue GetMicroseconds() const;

	// ���ڵ�ʱ����ʱ�������ʾ��ʱ��Ĳ�ֵ
	TTimeDiff GetElapsed() const;

	void ToFileTime( UINT32& fileTimeLow, UINT32& fileTimeHigh ) const;

	// ʱ�������ʾ��ʱ���뵱ǰʱ��Ĳ�ֵ�Ƿ����interval��
	// ʱ�������ʾ��ʱ����������Ƿ��Ѿ���ȥ��interval
	bool IsTimeElapsed(TTimeDiff interval) const;

	static CCCSTimeStamp FromEpochTime( std::time_t t );

	static CCCSTimeStamp FromEpochMillisecond( TTimeValue tv );

	static CCCSTimeStamp FromUTCTime( TTimeValue tv );

	static CCCSTimeStamp FromFileTime( UINT32 fileTimeLow,
		UINT32 fileTimeHigh );

	static TTimeValue Resolution();

	//////////////////////////////////////////////////////////////////////////
	// ���������
	bool operator == (const CCCSTimeStamp& ts) const;
	bool operator != (const CCCSTimeStamp& ts) const;
	bool operator >  (const CCCSTimeStamp& ts) const;
	bool operator >= (const CCCSTimeStamp& ts) const;
	bool operator <  (const CCCSTimeStamp& ts) const;
	bool operator <= (const CCCSTimeStamp& ts) const;

	CCCSTimeStamp  operator +  (TTimeDiff d) const;
	CCCSTimeStamp  operator -  (TTimeDiff d) const;
	TTimeDiff     operator -  (const CCCSTimeStamp& ts) const;
	CCCSTimeStamp& operator += (TTimeDiff d);
	CCCSTimeStamp& operator -= (TTimeDiff d);

	CCCSTimeStamp& operator = (const CCCSTimeStamp& other);
	CCCSTimeStamp& operator = (TTimeValue tv);
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

private:
	// ʱ�����64λUTCʱ���ʾ,������΢��
	TTimeValue					m_ts;
};

#endif // _CCS_TIMESTAMP_H_

