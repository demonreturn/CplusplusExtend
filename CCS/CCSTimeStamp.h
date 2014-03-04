
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
	// 更新到当前时间
	void Refresh();

	// 返回时间戳的time_t方式的表示，base time是1970年1月1日0点,精度是S
	std::time_t GetTime() const;

	// 返回时间戳的UTC表示方式，base time是1582年10月15日0点,精度是100ns
	TTimeValue GetUtcTime() const;

	// 返回时间戳的微秒表示，base time是1970年1月1日0时
	TTimeValue GetMicroseconds() const;

	// 现在的时间与时间戳所表示的时间的差值
	TTimeDiff GetElapsed() const;

	void ToFileTime( UINT32& fileTimeLow, UINT32& fileTimeHigh ) const;

	// 时间戳所表示的时间与当前时间的差值是否大于interval。
	// 时间戳所表示的时间距离现在是否已经逝去了interval
	bool IsTimeElapsed(TTimeDiff interval) const;

	static CCCSTimeStamp FromEpochTime( std::time_t t );

	static CCCSTimeStamp FromEpochMillisecond( TTimeValue tv );

	static CCCSTimeStamp FromUTCTime( TTimeValue tv );

	static CCCSTimeStamp FromFileTime( UINT32 fileTimeLow,
		UINT32 fileTimeHigh );

	static TTimeValue Resolution();

	//////////////////////////////////////////////////////////////////////////
	// 运算符重载
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
	// 时间戳的64位UTC时间表示,精度是微秒
	TTimeValue					m_ts;
};

#endif // _CCS_TIMESTAMP_H_

