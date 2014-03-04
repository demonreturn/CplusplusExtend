#include "CCSInetAddress.h"


// ×î´ó¶Ë¿Ú 65536
const WORD MAX_PORT_NUM = 0Xffff;

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


}
