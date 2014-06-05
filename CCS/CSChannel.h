
#ifndef _CCS_CHANNEL_H_
#define _CCS_CHANNEL_H_

#include "CCSBase.h"
#include "CSFormatter.h"

class CCSLogMessage;

class CCSChannel
{
public:
	virtual ~CCSChannel(){}

	virtual void Log( const CCSLogMessage& msg ) = 0;

	virtual const char* ChannelName() const = 0;

	virtual bool Open()
	{
		m_bOpen = true;

		return true;
	}

	virtual void Close()
	{
		m_bOpen = false;
	}

	CCSChannel()
		: m_formatter( NULL )
		, m_bOpen( false )
	{

	}

	void SetFormatter( TFormatterPtr pformatter )
	{
		m_formatter = pformatter;
	}

	bool IsOpend() const
	{
		return m_bOpen;
	}

private:
	CCSChannel( const CCSChannel& );
	CCSChannel& operator = ( const CCSChannel& );

	TFormatterPtr				m_formatter;
	bool						m_bOpen;
};

#endif	// _CCS_CHANNEL_H_