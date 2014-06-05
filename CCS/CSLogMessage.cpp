#include "CSLogMessage.h"

#include "CCSOS.h"

const char* CCSLogMessage::LOG_LEVEL_NAME[LOG_LEVEL_SIZE] = 
{
	"",
	"Fatal",
	"Critical",
	"Error",
	"Warning",
	"Notice",
	"Info",
	"Debug",
	"Trace"
};

CCSLogMessage::CCSLogMessage( 
	const CCSString& src,
	const CCSString& text,
	ELogLevel level,
	const char* pfile,
	const char* fun,
	int line )
	: m_source( src )
	, m_text( text )
	, m_level( level )
	, m_pid( 0 )
	, m_threadID( 0 )
	, m_line( line )
	, m_file( pfile )
	, m_function( fun )
{
	m_pid = CCS_OS::GetProcessID();
	m_threadID = CCS_OS::GetSelfThreadID();
}

CCSLogMessage::CCSLogMessage( const CCSLogMessage& msg )
	: m_source( msg.m_source )
	, m_text( msg.m_text )
	, m_level( msg.m_level )
	, m_pid( msg.m_pid )
	, m_threadID( msg.m_threadID )
	, m_line( msg.m_line )
	, m_function( msg.m_function )
	, m_time( msg.m_time )
{

}

CCSLogMessage& CCSLogMessage::operator=( const CCSLogMessage& msg )
{
	if (&msg != this )
	{
		m_source = msg.m_source;
		m_text = msg.m_text;
		m_level = msg.m_level;
		m_time = msg.m_time;
		m_pid = msg.m_pid;
		m_threadID = msg.m_threadID;
		m_line = msg.m_line;
		m_function = msg.m_function;
	}

	return *this;
}

bool CCSLogMessage::operator==( const CCSLogMessage& msg )
{
	if ( NULL != m_file 
		&& m_file == msg.GetSourceFile())
	{
		return true;
	}

	return false;
}

const char* CCSLogMessage::GetLevelName() const
{
	return GetLevelName( m_level );
}

const char* CCSLogMessage::GetLevelName( int level )
{
	if ( level < sizeof( LOG_LEVEL_NAME) / sizeof( LOG_LEVEL_NAME[0])
		&& level > 0 )
	{
		return LOG_LEVEL_NAME[level];
	}

	return LOG_LEVEL_NAME[0];
}




