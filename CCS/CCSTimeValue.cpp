#include "CCSTimeValue.h"


CCCSTimeValue CCCSTimeValue::GetCurTimeOfDay()
{
#ifdef CCS_WIN32
	FILETIME ftime;
	::GetSystemTimeAsFileTime( &ftime );

	return CCCSTimeValue( ftime );

#elif defined( CCS_LINUX)		// linux  实现
	timeval tvcur;
	::gettimeofday( &tvcur, NULL );

	return CCCSTimeValue( tvcur );
#endif
}

CCCSTimeValue::CCCSTimeValue()
{
	this->Set( 0, 0 );
}

CCCSTimeValue::CCCSTimeValue( long long second, long usecond /*= 0 */ )
{
	this->Set( second, usecond );
}

CCCSTimeValue::CCCSTimeValue( const timeval& tv )
{
	this->Set( tv );
}

#ifdef WIN32
CCCSTimeValue::CCCSTimeValue( const FILETIME& ft )
{
	this->Set( ft );
}
#endif

void CCCSTimeValue::Set( long long second, long usecond )
{
	long ltemp = (long) second;
	m_tv.second = ltemp;
	m_tv.usecond = (long)((second - (LONGLONG)ltemp) * ONE_SECOND_IN_USECS);
	m_tv.usecond += usecond;

	this->BounderCheck();
}

void CCCSTimeValue::Set( const timeval& tv )
{
	m_tv.second = tv.tv_sec;
	m_tv.usecond = tv.tv_usec;

	this->BounderCheck();
}

void CCCSTimeValue::Set( long long llsecond )
{
	long ltemp = (long)llsecond;
	m_tv.second = ltemp;
	m_tv.usecond = (long)((llsecond - (long long)ltemp) * ONE_SECOND_IN_USECS );
}

void CCCSTimeValue::Set( const FILETIME& ft )
{
	ULARGE_INTEGER _100ns;
	_100ns.LowPart = ft.dwLowDateTime;
	_100ns.HighPart = ft.dwHighDateTime;

	_100ns.QuadPart -= (unsigned __int64)0x19db1ded53e8000;

	// Convert 100ns units to seconds;
	this->m_tv.second = (LONG) (_100ns.QuadPart / (10000 * 1000));
	// Convert remainder to microseconds;
	this->m_tv.usecond = (LONG) ((_100ns.QuadPart % (10000 * 1000)) / 10);

	this->BounderCheck();
}

DWORD CCCSTimeValue::GetMSecond() const
{
	return m_tv.second * ONE_SECOND_IN_MECS + 
		m_tv.usecond / (ONE_SECOND_IN_USECS/ONE_SECOND_IN_MECS);
}

DWORD CCCSTimeValue::GetSecond() const
{
	return m_tv.second;
}

void CCCSTimeValue::SetSecond( long long second )
{
	Set( second );
}

long CCCSTimeValue::GetUSecond() const
{
	return m_tv.usecond;
}

void CCCSTimeValue::SetUSecond( long usecond )
{
	m_tv.usecond = usecond;

	BounderCheck();
}

CCCSTimeValue& CCCSTimeValue::operator+=( const CCCSTimeValue& tv )
{
	SetSecond( GetSecond() + tv.GetSecond() );
	SetUSecond( GetUSecond() + tv.GetUSecond() );

	return *this;
}

CCCSTimeValue& CCCSTimeValue::operator+=( long long tv )
{
	SetSecond( GetSecond() + tv );

	return *this;
}

CCCSTimeValue& CCCSTimeValue::operator=( const CCCSTimeValue& tv )
{
	Set( tv.GetSecond(), tv.GetUSecond() );

	return *this;
}

CCCSTimeValue& CCCSTimeValue::operator=( long long tv )
{
	SetSecond( tv );

	return *this;
}

CCCSTimeValue& CCCSTimeValue::operator-=( const CCCSTimeValue& tv )
{
	SetSecond( GetSecond() - tv.GetSecond() );
	SetUSecond( GetUSecond() - tv.GetUSecond() );

	BounderCheck();

	return *this;
}

CCCSTimeValue& CCCSTimeValue::operator-=( long long tv )
{
	SetSecond( GetSecond() - tv );

	BounderCheck();

	return *this;
}

void CCCSTimeValue::BounderCheck()
{
	//如果 usecond 大于边界，则提升
	if ( ONE_SECOND_IN_USECS <= m_tv.usecond )
	{
		m_tv.second += m_tv.usecond / ONE_SECOND_IN_USECS;
		m_tv.usecond = m_tv.usecond % ONE_SECOND_IN_USECS;
	}
	// 如果 m_tv.usecond 小于 负的边界值，即小于1微秒
	else if ( -ONE_SECOND_IN_USECS >= m_tv.usecond )
	{
		do 
		{
			m_tv.second--;

			m_tv.usecond += ONE_SECOND_IN_USECS;
		} while ( -ONE_SECOND_IN_USECS >= m_tv.usecond );
	}

	if ( 1 <= m_tv.second && 0 >= m_tv.usecond )
	{
		m_tv.second--;
		m_tv.usecond += ONE_SECOND_IN_USECS;
	}
	else if ( 0 >= m_tv.second && 0 < m_tv.usecond )
	{
		m_tv.second++;
		m_tv.usecond -= ONE_SECOND_IN_USECS;
	}
}

CCCSTimeValue operator + (
	const CCCSTimeValue &tv1,
	const CCCSTimeValue &tv2 )
{
	CCCSTimeValue sum( tv1 );
	sum += tv2;

	return sum;
}

CCCSTimeValue operator - (
	const CCCSTimeValue &tv1,
	const CCCSTimeValue &tv2 )
{
	CCCSTimeValue delta( tv1 );
	delta -= tv2;

	return delta;
}

BOOL operator < (
	const CCCSTimeValue &tv1,
	const CCCSTimeValue &tv2 )
{
	return tv1 < tv2;
}

BOOL operator > (
	const CCCSTimeValue &tv1,
	const CCCSTimeValue &tv2 )
{
	return tv1 > tv2;
}

BOOL operator <= (
	const CCCSTimeValue &tv1,
	const CCCSTimeValue &tv2 )
{
	return tv1 <= tv2;
}

BOOL operator >= (
	const CCCSTimeValue &tv1,
	const CCCSTimeValue &tv2 )
{
	return tv1 >= tv2;
}

BOOL operator == (
	const CCCSTimeValue &tv1,
	const CCCSTimeValue &tv2 )
{
	return tv1 == tv2;
}