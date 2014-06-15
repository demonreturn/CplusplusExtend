#include "CSLocalDateTime.h"
#include "CSTimeSpan.h"
#include "CSTimeZone.h"


CCSLocalDateTime::CCSLocalDateTime()
{
	DetermineTzd( true );
}

CCSLocalDateTime::CCSLocalDateTime( int year, int month, int day, int hour /*= 0*/, int minute /*= 0*/, int second /*= 0*/, int millisecond /*= 0*/, int microsecond /*= 0 */ )
	:m_dateTime(year, month, day, hour, minute, second, millisecond, microsecond)
{
	DetermineTzd();
}

CCSLocalDateTime::CCSLocalDateTime( const CCCSTimeStamp& timestamp )
	:m_dateTime(timestamp)
{
	DetermineTzd( true );
}

CCSLocalDateTime::CCSLocalDateTime( const CCSDateTime& datetime )
	: m_dateTime( datetime )
{
	DetermineTzd( true );
}

CCSLocalDateTime::CCSLocalDateTime( double julianDay )
	: m_dateTime( julianDay )
{
	DetermineTzd( true );
}

CCSLocalDateTime::CCSLocalDateTime( const CCSLocalDateTime& dateTime )
	: m_dateTime( dateTime.m_dateTime )
	, m_tzd( dateTime.m_tzd )
{
	
}

CCSLocalDateTime::CCSLocalDateTime( CCCSTimeStamp::TTimeValue utcTime, CCCSTimeStamp::TTimeDiff diff, int tzd )
{

}

CCSLocalDateTime& CCSLocalDateTime::operator=( const CCSLocalDateTime& dateTime )
{
	if ( &dateTime != this )
	{
		m_dateTime = dateTime.m_dateTime;
		m_tzd = dateTime.m_tzd;
	}

	return *this;
}

CCSLocalDateTime& CCSLocalDateTime::operator=( double julianDay )
{
	m_dateTime = julianDay;
	DetermineTzd(true);

	return *this;
}

CCSLocalDateTime& CCSLocalDateTime::Assign( int year, int month, int day, int hour /*= 0*/, int minute /*= 0*/, int second /*= 0*/, int millisecond /*= 0*/, int microseconds /*= 0*/ )
{
	m_dateTime.Assign(year, month, day, hour, minute, second, millisecond, microseconds);
	DetermineTzd(false);
	return *this;
}

int CCSLocalDateTime::Year() const
{
	return m_dateTime.Year();
}

int CCSLocalDateTime::Month() const
{
	return m_dateTime.Month();
}

int CCSLocalDateTime::Day() const
{
	return m_dateTime.Day();
}

int CCSLocalDateTime::Week( int firstDayOfWeek /*= CCSDateTime::MONDAY */ ) const
{
	return m_dateTime.Week( firstDayOfWeek );
}

int CCSLocalDateTime::DayOfWeek() const
{
	return m_dateTime.DayOfWeek();
}

int CCSLocalDateTime::DayOfYear() const
{
	return m_dateTime.DayOfYear();
}

int CCSLocalDateTime::Hour() const
{
	return m_dateTime.Hour();
}

int CCSLocalDateTime::HourAMPM() const
{
	return m_dateTime.HourAMPM();
}

bool CCSLocalDateTime::IsAM() const
{
	return m_dateTime.IsAM();
}

bool CCSLocalDateTime::IsPM() const
{
	return m_dateTime.IsPM();
}

int CCSLocalDateTime::Minute() const
{
	return m_dateTime.Minute();
}

int CCSLocalDateTime::Second() const
{
	return m_dateTime.Second();
}

int CCSLocalDateTime::Millisecond() const
{
	return m_dateTime.Millisecond();
}

int CCSLocalDateTime::Microsecond() const
{
	return m_dateTime.Microsecond();
}

double CCSLocalDateTime::JulianDay() const
{
	return m_dateTime.JulianDay();
}

int CCSLocalDateTime::Tzd() const
{
	return m_tzd;
}

CCSDateTime CCSLocalDateTime::UTC() const
{
	return CCSDateTime( m_dateTime.UtcTime(), -((CCCSTimeStamp::TTimeDiff)m_tzd) * CCSTimeSpan::SECONDS );
}

CCCSTimeStamp CCSLocalDateTime::TimeStamp() const
{
	return CCCSTimeStamp::FromUTCTime( m_dateTime.UtcTime() );
}

CCCSTimeStamp::TTimeValue CCSLocalDateTime::UTCTime() const
{
	return m_dateTime.UtcTime() - ((CCCSTimeStamp::TTimeDiff)m_tzd) * CCSTimeSpan::SECONDS;
}

CCSString CCSLocalDateTime::ToString() const
{
	return m_dateTime.ToString();
}

bool CCSLocalDateTime::operator==( const CCSLocalDateTime& dateTime ) const
{
	return UTCTime() == dateTime.UTCTime();
}

bool CCSLocalDateTime::operator!=( const CCSLocalDateTime& dateTime ) const
{
	return UTCTime() != dateTime.UTCTime();
}

bool CCSLocalDateTime::operator<( const CCSLocalDateTime& dateTime ) const
{
	return UTCTime() < dateTime.UTCTime();
}

bool CCSLocalDateTime::operator<=( const CCSLocalDateTime& dateTime ) const
{
	UTCTime() <= dateTime.UTCTime();
}

bool CCSLocalDateTime::operator>( const CCSLocalDateTime& dateTime ) const
{
	return UTCTime() > dateTime.UTCTime();
}

bool CCSLocalDateTime::operator>=( const CCSLocalDateTime& dateTime ) const
{
	return UTCTime() >= dateTime.UTCTime();
}

CCSLocalDateTime CCSLocalDateTime::operator+( const CCSTimeSpan& span ) const
{
	CCSDateTime tmp( UTCTime(), span.TotalMicroSeconds() );

	return CCSLocalDateTime(tmp);
}

CCSLocalDateTime CCSLocalDateTime::operator-( const CCSTimeSpan& span ) const
{
	CCSDateTime tmp( UTCTime(), -span.TotalMicroSeconds() );

	return CCSLocalDateTime(tmp);
}

CCSTimeSpan CCSLocalDateTime::operator-( const CCSLocalDateTime& dateTime ) const
{
	return CCSTimeSpan( (UTCTime() - dateTime.UTCTime()) /10 );
}

CCSLocalDateTime& CCSLocalDateTime::operator+=( const CCSTimeSpan& span )
{
	*this = CCSDateTime( UTCTime(), span.TotalMicroSeconds() );

	return *this;
}

CCSLocalDateTime& CCSLocalDateTime::operator-=( const CCSTimeSpan& span )
{
	*this = CCSDateTime( UTCTime(), -span.TotalMicroSeconds() );

	return *this;
}

void CCSLocalDateTime::DetermineTzd( bool adjust /*= false*/ )
{
	if ( adjust )
	{
		std::time_t epochTime = m_dateTime.TimeStamp().GetTime();
#ifdef CCS_WIN32
		std::tm broken;
		errno_t eno = localtime_s( &broken, &epochTime );
		if ( 0 != eno )
		{
			return;
		}

		m_tzd = (CCSTimeZone::UtcOffset() + ((broken.tm_isdst == 1) ? 3600 : 0));
#elif defined( CCS_LINUX)		// linux  й╣ож
		std::tm broken;

		if ( localtime_r(&epochTime, &broken))
		{
			m_tzd = (Timezone::UtcOffset() + ((broken.tm_isdst == 1) ? 3600 : 0));
		}
#endif

		AdjustForTzd();
	}
	else
	{
		int dst;
		DstOffset(dst);
		m_tzd = (CCSTimeZone::UtcOffset() + dst);
	}
}

void CCSLocalDateTime::AdjustForTzd()
{
	m_dateTime += CCSTimeSpan(((CCCSTimeStamp::TTimeDiff) m_tzd)*CCSTimeSpan::SECONDS);
}

std::time_t CCSLocalDateTime::DstOffset( int& dstOffset ) const
{
	std::time_t local;
	std::tm     broken;

	broken.tm_year  = (m_dateTime.Year() - 1900);
	broken.tm_mon   = (m_dateTime.Month() - 1);
	broken.tm_mday  = m_dateTime.Day();
	broken.tm_hour  = m_dateTime.Hour();
	broken.tm_min   = m_dateTime.Minute();
	broken.tm_sec   = m_dateTime.Second();
	broken.tm_isdst = -1;

	local = std::mktime(&broken);

	dstOffset = (broken.tm_isdst == 1) ? 3600 : 0;
	return local;
}


