#include "CCSTimeStamp.h"


CCCSTimeStamp::CCCSTimeStamp()
{
	Refresh();
}

CCCSTimeStamp::CCCSTimeStamp( TTimeValue tv )
	: m_ts( tv )
{

}

CCCSTimeStamp::CCCSTimeStamp( const CCCSTimeStamp& src )
{
	m_ts = src.m_ts;
}

CCCSTimeStamp::~CCCSTimeStamp()
{
}

void CCCSTimeStamp::Refresh()
{
#ifdef CCS_WIN32
	FILETIME ft;
	::GetSystemTimeAsFileTime( &ft );

	// (1970-01-01 00:00:00) expressed in Windows NT FILETIME
	ULARGE_INTEGER lg;
	lg.LowPart = 0xD53E8000;
	lg.HighPart = 0x019DB1DE;

	ULARGE_INTEGER ts;
	ts.LowPart = ft.dwLowDateTime;
	ts.HighPart = ft.dwHighDateTime;
	ts.QuadPart -= lg.QuadPart;

	m_ts = ts.QuadPart / 10;
#elif defined( CCS_LINUX)		// linux  й╣ож
	struct timeval tv;
	if ( !gettimeofday( &tv, NULL ))
	{
		m_ts = TTimeValue(tv.tv_sec) * resolution() + tv.tv_usec;
	}
	else
	{
		m_ts = 0;
	}
#endif
}

std::time_t CCCSTimeStamp::GetTime() const
{
	return std::time_t( m_ts / Resolution() );
}

CCCSTimeStamp::TTimeValue CCCSTimeStamp::GetUtcTime() const
{
	return m_ts * 10 + (TTimeDiff(0x01b21dd2) << 32) + 0x13814000;
}

CCCSTimeStamp::TTimeValue CCCSTimeStamp::GetMicroseconds() const
{
	return m_ts;
}

CCCSTimeStamp::TTimeDiff CCCSTimeStamp::GetElapsed() const
{
	CCCSTimeStamp now;
	return now - *this;
}

void CCCSTimeStamp::ToFileTime( UINT32& fileTimeLow, UINT32& fileTimeHigh ) const
{
	// (1970-01-01 00:00:00) expressed in Windows NT FILETIME
	ULARGE_INTEGER lg;
	lg.LowPart  = 0xD53E8000;
	lg.HighPart = 0x019DB1DE;

	ULARGE_INTEGER ts;
	ts.QuadPart = m_ts * 10;
	ts.QuadPart += lg.QuadPart;

	fileTimeLow = ts.LowPart;
	fileTimeHigh = ts.HighPart;
}

bool CCCSTimeStamp::IsTimeElapsed( TTimeDiff interval ) const
{
	CCCSTimeStamp now;
	TTimeDiff diff = now - *this;

	return diff >= interval;
}

CCCSTimeStamp CCCSTimeStamp::FromEpochTime( std::time_t t )
{
	return CCCSTimeStamp( TTimeValue(t) * Resolution() );
}

CCCSTimeStamp CCCSTimeStamp::FromEpochMillisecond( TTimeValue tv )
{
	return CCCSTimeStamp( tv * 1000 );
}

CCCSTimeStamp CCCSTimeStamp::FromUTCTime( TTimeValue tv )
{
	tv -= (TTimeDiff(0x01b21dd2) << 32) + 0x13814000;
	tv /= 10;

	return CCCSTimeStamp( tv );
}

CCCSTimeStamp CCCSTimeStamp::FromFileTime( UINT32 fileTimeLow, UINT32 fileTimeHigh )
{
	ULARGE_INTEGER lg; // UNIX epoch (1970-01-01 00:00:00) expressed in Windows NT FILETIME
	lg.LowPart  = 0xD53E8000;
	lg.HighPart = 0x019DB1DE;

	ULARGE_INTEGER ts;
	ts.LowPart  = fileTimeLow;
	ts.HighPart = fileTimeHigh;
	ts.QuadPart -= lg.QuadPart;

	return CCCSTimeStamp(ts.QuadPart/10);
}

CCCSTimeStamp::TTimeValue CCCSTimeStamp::Resolution()
{
	return 1000000;
}

bool CCCSTimeStamp::operator==( const CCCSTimeStamp& ts ) const
{
	return m_ts == ts.m_ts;
}

bool CCCSTimeStamp::operator!=( const CCCSTimeStamp& ts ) const
{
	return m_ts != ts.m_ts;
}

bool CCCSTimeStamp::operator>( const CCCSTimeStamp& ts ) const
{
	return m_ts > ts.m_ts;
}

bool CCCSTimeStamp::operator>=( const CCCSTimeStamp& ts ) const
{
	return m_ts >= ts.m_ts;
}

bool CCCSTimeStamp::operator<( const CCCSTimeStamp& ts ) const
{
	return m_ts < ts.m_ts;
}

bool CCCSTimeStamp::operator<=( const CCCSTimeStamp& ts ) const
{
	return m_ts <= ts.m_ts;
}

CCCSTimeStamp CCCSTimeStamp::operator+( TTimeDiff d ) const
{
	return CCCSTimeStamp( m_ts + d );
}

CCCSTimeStamp CCCSTimeStamp::operator-( TTimeDiff d ) const
{
	return CCCSTimeStamp( m_ts - d );
}

CCCSTimeStamp::TTimeDiff CCCSTimeStamp::operator-( const CCCSTimeStamp& ts ) const
{
	return m_ts - ts.m_ts;
}

CCCSTimeStamp& CCCSTimeStamp::operator+=( TTimeDiff d )
{
	m_ts += d;

	return *this;
}

CCCSTimeStamp& CCCSTimeStamp::operator-=( TTimeDiff d )
{
	m_ts -= d;

	return *this;
}

CCCSTimeStamp& CCCSTimeStamp::operator=( const CCCSTimeStamp& other )
{
	m_ts = other.m_ts;

	return *this;
}

CCCSTimeStamp& CCCSTimeStamp::operator=( TTimeValue tv )
{
	m_ts = tv;

	return *this;
}

