#include "CSLogger.h"

#include "CSChannel.h"
#include "CSLogMessage.h"
#include "CCSOS.h"

#include <assert.h>

CCSLogger* CCSLogger::Instance()
{
	static CCSLogger s_logger;

	return &s_logger;
}

CCSString GetLoggerToken()
{
	char buffer[256] = { 0 };

	CCS_OS::OSSprintf( buffer, 256, "log_%s_%d", CCS_OS::GetProcessName(), CCS_OS::GetProcessID() );

	return CCSString( buffer );
}

CCSLogger::CCSLogger()
	: m_logLevel( GetLoggerToken().c_str(), CCSLogMessage::LOG_WARNING )
{

}

void CCSLogger::Init( const CCSString& strConfig )
{
	Reset();

	CCSString::size_type pos = strConfig.find( ';' );

	if ( pos >= strConfig.size() )
	{
		return;
	}

	CCSString level = strConfig.substr( 0, pos );
	SetLoggerLevel( level );

	CCSString::size_type old = pos + 1;
	while ( ( pos = strConfig.find( ';', old)) < strConfig.size())
	{
		AttachChannel( strConfig.substr( old, pos - old));

		old = ++pos;
	}

	if ( old < strConfig.size() )
	{
		AttachChannel( strConfig.substr(old) );
	}
}

void CCSLogger::Register( CCSChannel* pchannel )
{
	//assert( m_channels.find( pchannel->ChannelName()) == m_channels.end()) ;

	//m_channels.insert( Name2ChannelMap::value_type( pchannel->ChannelName(), pchannel));
}

int CCSLogger::GetLoggerLevel() const
{
	return m_logLevel;
}

bool CCSLogger::SetLoggerLevel( int level )
{
	if ( CCSLogMessage::LOG_LEVEL_SIZE <= level ||
		CCSLogMessage::LOG_FATAL > level )
	{
		return false;
	}

	m_logLevel = level;

	return true;
}

bool CCSLogger::SetLoggerLevel( const CCSString& levelName )
{
	int level = GetLevelName( levelName );

	if ( 0 == level )
	{
		return false;
	}

	m_logLevel = level;

	return true;
}

bool CCSLogger::AttachChannel( const CCSString & channelName )
{
	//Name2ChannelMap::iterator itor = m_channels.find( channelName );
// 	if ( m_channels.end() != itor )
// 	{
// 		if ( channelName == itor->second->ChannelName())
// 		{
// 			return itor->second->Open();
// 		}
// 	}

	return false;
}

void CCSLogger::DetachChannel( const CCSString& channelName )
{
	//Name2ChannelMap::iterator itor = m_channels.find( channelName );
// 	if ( m_channels.end() != itor )
// 	{
// 		if ( itor->second->ChannelName() == channelName )
// 		{
// 			itor->second->Close();
// 		}
// 	}
}

CCSChannel* CCSLogger::FindChannel( const CCSString& channelName ) const
{
// 	Name2ChannelMap::const_iterator itor = m_channels.find( channelName );
// 	if ( m_channels.end() != itor )
// 	{
// 		return itor->second;
// 	}

	return NULL;
}

int CCSLogger::GetLevelName( const CCSString& levelName )
{
// 	for (int index = 0; index < CCSLogMessage::LOG_LEVEL_SIZE; ++index)
// 	{
// 		if ( levelName == CCSLogMessage::GetLevelName( index ))
// 		{
// 			return index;
// 		}
// 	}

	return 0;
}

// CCSString CCSLogger::GetLevelName() const
// {
// 	return CCSLogger::GetLevelName( m_logLevel );
// }

