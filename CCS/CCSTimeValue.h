#ifndef _CCS_TIME_VALUE_H_
#define _CCS_TIME_VALUE_H_


#include "CCSBase.h"

typedef struct tag_TIMEVALUE
{
	long second;

	long usecond;
} TIMEVALUE;

class CCCSTimeValue
{

public:
	static CCCSTimeValue GetCurTimeOfDay();

	CCCSTimeValue();

	CCCSTimeValue( long long second, long usecond = 0 );

	CCCSTimeValue( const timeval& tv );

#ifdef WIN32
	CCCSTimeValue( const FILETIME& ft );
#endif

	void Set( long long second, long usecond );

	void Set( const timeval& tv );

	void Set( long long llsecond );

#ifdef WIN32
	void Set( const FILETIME& ft );
#endif

	DWORD GetMSecond() const;

	DWORD GetSecond() const;

	void SetSecond( long long second );

	long GetUSecond() const;

	void SetUSecond( long usecond );

// operation override
	CCCSTimeValue& operator += ( const CCCSTimeValue& tv );

	CCCSTimeValue& operator += ( long long tv );

	CCCSTimeValue& operator = ( const CCCSTimeValue& tv );

	CCCSTimeValue& operator = ( long long tv );

	CCCSTimeValue& operator -=( const CCCSTimeValue& tv );

	CCCSTimeValue& operator -=( long long tv );

	// 全局操作符重载
	friend CCCSTimeValue operator + ( const CCCSTimeValue& tv1,
		const CCCSTimeValue& tv2 );

	friend CCCSTimeValue operator - ( const CCCSTimeValue& tv1,
		const CCCSTimeValue& tv2 );

	friend BOOL operator < ( const CCCSTimeValue& tv1,
		const CCCSTimeValue& tv2 );

	friend BOOL operator > ( const CCCSTimeValue& tv1,
		const CCCSTimeValue& tv2 );

	friend BOOL operator <= ( const CCCSTimeValue& tv1,
		const CCCSTimeValue& tv2 );

	friend BOOL operator >= ( const CCCSTimeValue& tv1,
		const CCCSTimeValue& tv2 );

	friend BOOL operator == ( const CCCSTimeValue& tv1,
		const CCCSTimeValue& tv2 );

private:
	void BounderCheck();

	enum
	{
		// 一秒等1000毫秒
		ONE_SECOND_IN_MECS	= 1000,

		// 一秒等1000 * 1000微秒
		ONE_SECOND_IN_USECS = 1000 * 1000,

		// 一秒等1000 * 1000 * 1000纳秒
		ONE_SECOND_IN_NSECS = 1000 * 1000 * 1000,
	};

	TIMEVALUE					m_tv;
};

#endif // _CCS_TIME_VALUE_H_

