#include "CSTimeSpan.h"

int CCSTimeSpan::Days() const
{
	return int( m_span / DAYS );
}

int CCSTimeSpan::Hours() const
{
	return int( (m_span / HOURS) % 24 );
}

int CCSTimeSpan::TotalHours() const
{
	return int( m_span / HOURS );
}

int CCSTimeSpan::Minutes() const
{
	return int(( m_span / MINUTES ) % 60 );
}

int CCSTimeSpan::TotalMinutes() const
{
	return int( m_span / MINUTES );
}

int CCSTimeSpan::Seconds() const
{
	return int(( m_span / SECONDS ) % 60 );
}

int CCSTimeSpan::TotalSeconds() const
{
	return int( m_span / SECONDS );
}

int CCSTimeSpan::MilliSeconds() const
{
	return int(( m_span / MILLISECONDS ) % 1000 );
}

CCSTimeSpan::TTimeDiff CCSTimeSpan::TotalMilliSeconds() const
{
	return int( m_span / MILLISECONDS );
}

int CCSTimeSpan::MicroSeconds() const
{
	return int( m_span % 1000 );
}

CCSTimeSpan::TTimeDiff CCSTimeSpan::TotalMicroSeconds() const
{
	return m_span;
}

int CCSTimeSpan::Useconds() const
{
	return int( m_span % 1000000 );
}

CCSTimeSpan::CCSTimeSpan()
	: m_span( 0 )
{

}

CCSTimeSpan::CCSTimeSpan( TTimeDiff microseconds )
	: m_span( microseconds )
{

}

CCSTimeSpan::CCSTimeSpan( long seconds, long microseconds )
	: m_span( TTimeDiff(seconds) * SECONDS + microseconds)
{

}

CCSTimeSpan::CCSTimeSpan( int days, int hours, int minutes, int seconds, int microseconds )
	: m_span( TTimeDiff(microseconds) + TTimeDiff(seconds) * SECONDS + TTimeDiff(minutes) * MINUTES + TTimeDiff(hours) * HOURS + TTimeDiff(days) * DAYS )
{

}

CCSTimeSpan::CCSTimeSpan( const CCSTimeSpan& timespan )
	: m_span( timespan.m_span )
{

}

CCSTimeSpan& CCSTimeSpan::operator=( const CCSTimeSpan& timespan )
{
	// no need to judge this == &timespan
	m_span = timespan.m_span;

	return *this;
}

CCSTimeSpan& CCSTimeSpan::operator=( TTimeDiff microseconds )
{
	m_span = microseconds;

	return *this;
}

CCSTimeSpan& CCSTimeSpan::Assign( int days, int hours, int minutes, int seconds, int microseconds )
{
	m_span = TTimeDiff(microseconds) + TTimeDiff(seconds) * SECONDS + TTimeDiff(minutes) * MINUTES + TTimeDiff(hours) * HOURS + TTimeDiff(days) * DAYS;

	return *this;
}

CCSTimeSpan& CCSTimeSpan::Assign( long seconds, long microseconds )
{
	m_span = TTimeDiff(seconds) * SECONDS + microseconds;

	return *this;
}

bool CCSTimeSpan::operator==( const CCSTimeSpan& ts ) const
{
	return m_span == ts.m_span;
}

bool CCSTimeSpan::operator==( TTimeDiff microseconds ) const
{
	return m_span == microseconds;
}

bool CCSTimeSpan::operator!=( const CCSTimeSpan& ts ) const
{
	return m_span != ts.m_span;
}

bool CCSTimeSpan::operator!=( TTimeDiff microseconds ) const
{
	return m_span != microseconds;
}

bool CCSTimeSpan::operator>( const CCSTimeSpan& ts ) const
{
	return m_span > ts.m_span;
}

bool CCSTimeSpan::operator>( TTimeDiff microseconds ) const
{
	return m_span > microseconds;
}

bool CCSTimeSpan::operator>=( const CCSTimeSpan& ts ) const
{
	return m_span >= ts.m_span;
}

bool CCSTimeSpan::operator>=( TTimeDiff microseconds ) const
{
	return m_span >= microseconds;
}

bool CCSTimeSpan::operator<( const CCSTimeSpan& ts ) const
{
	return m_span < ts.m_span;
}

bool CCSTimeSpan::operator<( TTimeDiff microseconds ) const
{
	return m_span < microseconds;
}

bool CCSTimeSpan::operator<=( const CCSTimeSpan& ts ) const
{
	return m_span <= ts.m_span;
}

bool CCSTimeSpan::operator<=( TTimeDiff microseconds ) const
{
	return m_span <= microseconds;
}

CCSTimeSpan CCSTimeSpan::operator+( const CCSTimeSpan& ts ) const
{
	return CCSTimeSpan( m_span + ts.m_span );
}

CCSTimeSpan CCSTimeSpan::operator+( TTimeDiff microseconds ) const
{
	return CCSTimeSpan( m_span + microseconds );
}

CCSTimeSpan CCSTimeSpan::operator-( const CCSTimeSpan& ts ) const
{
	return CCSTimeSpan( m_span - ts.m_span );
}

CCSTimeSpan& CCSTimeSpan::operator+=( const CCSTimeSpan& ts )
{
	m_span += ts.m_span;

	return *this;
}

CCSTimeSpan& CCSTimeSpan::operator+=( TTimeDiff microseconds )
{
	m_span += microseconds;

	return *this;
}

CCSTimeSpan& CCSTimeSpan::operator-=( const CCSTimeSpan& ts )
{
	m_span -= ts.m_span;

	return *this;
}

CCSTimeSpan CCSTimeSpan::operator-( TTimeDiff microseconds ) const
{
	return CCSTimeSpan( m_span - microseconds );
}

CCSTimeSpan& CCSTimeSpan::operator-=( TTimeDiff microseconds )
{
	m_span -= microseconds;

	return *this;
}


