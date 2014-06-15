#include "CSTraceFormator.h"

#include "CCSOS.h"
#include "CCSInetAddress.h"
#include "CSTraceDefine.h"


CCSTraceFormator::CCSTraceFormator( char* pbuffer, DWORD dwBufSize )
	: m_pBuffer( pbuffer )
	, m_dwBufferSize( dwBufSize )
	, m_dwPos( 0 )
	, m_bHex( false )
{

}

void CCSTraceFormator::SetHexFlag( bool bHex )
{
	m_bHex = bHex;
}

bool CCSTraceFormator::GetHexFlag() const
{
	return m_bHex;
}

void CCSTraceFormator::AdvanceBuffer( const char* pBuffer )
{
	if ( NULL != pBuffer )
	{
		DWORD dwLength = CCS_OS::OSStrlen( pBuffer, m_dwBufferSize );

		if ( dwLength > ( m_dwBufferSize - m_dwPos - CCS_TRACE_RESERVE_DATA_LEN ))
		{
			dwLength = m_dwBufferSize - m_dwPos - CCS_TRACE_RESERVE_DATA_LEN;
		}

		if ( 0 < dwLength )
		{
			CCS_OS::OSMemcpy(
				m_pBuffer + m_dwPos * sizeof(char),
				m_dwBufferSize - m_dwPos * sizeof(char),
				(void*)pBuffer,
				dwLength * sizeof(char) );

			m_dwPos += dwLength;
		}
	}
}

CCSTraceFormator::operator char*()
{
	return m_pBuffer;
}

CCSTraceFormator& CCSTraceFormator::operator<<( char cValue )
{
	return (*this << (int)cValue );
}

CCSTraceFormator& CCSTraceFormator::operator<<( BYTE cbValue )
{
	return (*this << (int)cbValue );
}

CCSTraceFormator& CCSTraceFormator::operator<<( short sValue )
{
	return (*this << (int)sValue );
}

CCSTraceFormator& CCSTraceFormator::operator<<( WORD wValue )
{
	return (*this << (int)wValue );
}

CCSTraceFormator& CCSTraceFormator::operator<<( int iValue )
{
	char szValue[64] = { 0 };
	CCS_ZERO( szValue, 64 );

	CCS_OS::OSSprintf(szValue,
		64,
		GetHexFlag() ? "%d" : "%08x",
		iValue );

	AdvanceBuffer( szValue );

	SetHexFlag( false );

	return (*this);
}

CCSTraceFormator& CCSTraceFormator::operator<<( UINT iValue )
{
	char szValue[64] = { 0 };
	CCS_ZERO( szValue, 64 );

	CCS_OS::OSSprintf(szValue,
		64,
		GetHexFlag() ? "%u" : "%08x",
		iValue );

	AdvanceBuffer( szValue );

	SetHexFlag( false );

	return (*this);
}

CCSTraceFormator& CCSTraceFormator::operator<<( long lValue )
{
	char szValue[64] = { 0 };
	CCS_ZERO( szValue, 64 );

	CCS_OS::OSSprintf(szValue,
		64,
		GetHexFlag() ? "%ld" : "%08x",
		lValue );

	AdvanceBuffer( szValue );

	SetHexFlag( false );

	return (*this);
}

CCSTraceFormator& CCSTraceFormator::operator<<( LONGLONG llValue )
{
	char szValue[128] = { 0 };
	CCS_ZERO( szValue, 128 );

	CCS_OS::OSSprintf(szValue,
		128,
		GetHexFlag() ? "%lld" : "%08x",
		llValue );

	AdvanceBuffer( szValue );

	SetHexFlag( false );

	return (*this);
}

CCSTraceFormator& CCSTraceFormator::operator<<( DWORD dwValue )
{
	char szValue[64] = { 0 };
	CCS_ZERO( szValue, 64 );

	CCS_OS::OSSprintf(szValue,
		64,
		GetHexFlag() ? "%lu" : "%08x",
		dwValue );

	AdvanceBuffer( szValue );

	SetHexFlag( false );

	return (*this);
}

CCSTraceFormator& CCSTraceFormator::operator<<( float fValue )
{
	char szValue[64] = { 0 };
	CCS_ZERO( szValue, 64 );

	CCS_OS::OSSprintf(szValue,
		64,
		"%f",
		fValue );

	AdvanceBuffer( szValue );

	SetHexFlag( false );

	return (*this);
}

CCSTraceFormator& CCSTraceFormator::operator<<( double dValue )
{
	char szValue[64] = { 0 };
	CCS_ZERO( szValue, 64 );

	CCS_OS::OSSprintf(szValue,
		64,
		"%f",
		dValue );

	AdvanceBuffer( szValue );

	SetHexFlag( false );

	return (*this);
}

CCSTraceFormator& CCSTraceFormator::operator<<( const char* pszValue )
{
	AdvanceBuffer( pszValue );

	return (*this);
}

CCSTraceFormator& CCSTraceFormator::operator<<( void* lpValue )
{
	return (*this << "0x" << HEX << reinterpret_cast<DWORD>( lpValue) );
}

CCSTraceFormator& CCSTraceFormator::operator<<( const CCSString& strValue )
{
	return (*this << strValue.c_str() );
}

CCSTraceFormator& CCSTraceFormator::operator<<( const CCCSInetAddress& address )
{
	return (*this << const_cast<CCCSInetAddress&>(address).GetStrIP() << ":" << address.GetPort() );
}

CCSTraceFormator& CCSTraceFormator::operator<<( Ordix ordixValue )
{
	switch ( ordixValue )
	{
	case HEX:
		SetHexFlag( true );
		break;

	case DECIMAL:
		SetHexFlag( false );
		break;
	default:
		break;
	}

	return (*this);
}
