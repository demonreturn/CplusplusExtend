#include "CCSInetAddress.h"
#include "CCSSocket.h"
#include "CCSOSMemory.h"

#include <string.h>

// 最大端口 65536
const WORD MAX_PORT_NUM = 0Xffff;
const DWORD MAX_IP_AND_PORT_LENGTH = 256;

CCCSInetAddress::CCCSInetAddress()
{
	Set( NULL, 0 );
}

CCCSInetAddress::CCCSInetAddress( const char* phostnameAndPort )
{
	Set( phostnameAndPort );
}

CCCSInetAddress::CCCSInetAddress( const char* phostname, WORD port )
{
	Set( phostname, port );
}

CCCSInetAddress::~CCCSInetAddress()
{
}

CCSResult CCCSInetAddress::Set( const char* phostname, WORD port )
{
	::memset( &m_sockAddr, 0, sizeof( m_sockAddr) );

	m_sockAddr.sin_family = AF_INET;
	if ( NULL == phostname )
	{
		return CCS_OK;
	}

	m_sockAddr.sin_port = ::htons( port );
	
	return SetIP( phostname );
}

CCSResult CCCSInetAddress::Set( const char* phostnameAndPort )
{
	if ( NULL == phostnameAndPort )
	{
		return CCS_ERROR_NULL_POINTER;
	}

	DWORD dwLength = CCS_OS::OSStrlen( phostnameAndPort, MAX_IP_AND_PORT_LENGTH );

	WORD wPort = 0;

	// 查找":", ":"之前都算是ip
	char* szFind = const_cast<char*>( ::strchr(phostnameAndPort, ':'));
	if ( NULL == szFind )
	{
		szFind = const_cast<char*>( phostnameAndPort ) + dwLength;
		wPort = 0;

		return CCS_ERROR_FAILURE;
	}
	else
	{
		// ":"之后的都算是端口
		if ( MAX_PORT_NUM > static_cast<WORD>( ::atoi(szFind+1))
			&& (0 < static_cast<WORD>( ::atoi(szFind+1) )) )
		{
			wPort = static_cast<WORD>(::atoi(szFind + 1));
		}
		else
		{
			return CCS_ERROR_FAILURE;
		}
	}

	char szBuf[MAX_IP_AND_PORT_LENGTH] = { 0 };
	int iAddrLen = szFind - phostnameAndPort;


	return 0;
}

CCSResult CCCSInetAddress::Set( DWORD dwIP )
{
	return 0;
}

CCSResult CCCSInetAddress::SetIP( const char* pszIP )
{
	DWORD dwIP = CCS_OS::IPStringToDigital( pszIP );

	if ( INADDR_NONE != dwIP )
	{
		return SetIP( dwIP, true );
	}

	return CCS_ERROR_FAILURE;
}

CCSResult CCCSInetAddress::SetIP( DWORD dwIP, bool bnetworkOrder /*= false */ )
{
	if ( false == bnetworkOrder )
	{
		m_sockAddr.sin_addr.s_addr = ::htonl( dwIP );
	}
	else
	{
		m_sockAddr.sin_addr.s_addr = dwIP;
	}

	return 0;
}

CCSResult CCCSInetAddress::SetPort( WORD port )
{
	m_sockAddr.sin_port = port;

	return 0;
}

WORD CCCSInetAddress::GetPort() const
{
	return ::ntohs( m_sockAddr.sin_port );
}

CCSString CCCSInetAddress::GetStrIP() const
{
	return CCS_OS::IPDigitalToString( m_sockAddr.sin_addr.s_addr );
}

DWORD CCCSInetAddress::GetSize() const
{
	return sizeof( CCSSOCKADDR );
}

const CCSSOCKADDR* CCCSInetAddress::GetRawAddress() const
{
	return &m_sockAddr;
}
