
#ifndef _CCS_LOGGER_H_
#define _CCS_LOGGER_H_

#include "CCSBase.h"

#include "CSShareVariantT.h"

class CCSChannel;
class CCSLogMessage;

class CCSLogger
{
public:
	class CAutoRegister
	{
	public:
		CAutoRegister( CCSChannel* pchannel )
		{
			CCSLogger::Instance()->Register( pchannel );
		}
	};

public:
	typedef std::vector<CCSString>		ChannelNameVec;

	static CCSLogger* Instance();

	void Init( const CCSString& strConfig );

	void Register( CCSChannel* pchannel );

	int GetLoggerLevel() const;

	bool SetLoggerLevel( int level );

	bool SetLoggerLevel( const CCSString& levelName );

	bool AttachChannel( const CCSString& channelName );

	void DetachChannel( const CCSString& channelName );

	CCSChannel* FindChannel( const CCSString& channelName ) const;

	void LogMsg( const CCSLogMessage& msg );

	CCSString GetLevelName() const;

	ChannelNameVec GetAllChannelNames() const;

	ChannelNameVec GetOpendChannelNames() const;

	~CCSLogger();

private:

	void Reset();

	static int GetLevelName( const CCSString& levelName );

	CCSLogger();

	CCSLogger( const CCSLogger& );

	typedef std::map<CCSString,CCSChannel*>	Name2ChannelMap;
	
	Name2ChannelMap				m_channels;

	typedef CCSShareVariantT<int>	LOG_LEVEL;
	LOG_LEVEL					m_logLevel;
};


#endif // _CCS_LOGGER_H_
