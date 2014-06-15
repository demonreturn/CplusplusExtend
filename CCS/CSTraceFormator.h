
#ifndef _CCS_TRACE_FORMATER_H_
#define _CCS_TRACE_FORMATER_H_

#include "CCSBase.h"

class CCCSInetAddress;

class CCSTraceFormator
{
public:
	/*
	 * д�����ݵı�����ʽ
	 *
	 * <HEX>, 16����
	 * <DECIMAL>, 10����
	*/
	typedef enum tag_Ordix
	{
		HEX     = 0,
		DECIMAL = 1
	} Ordix;

public:
	CCSTraceFormator( char* pbuffer, DWORD dwBufSize );

public:
	CCSTraceFormator& operator << ( char cValue );

	CCSTraceFormator& operator << ( BYTE cbValue );

	CCSTraceFormator& operator << ( short sValue );

	CCSTraceFormator& operator << ( WORD wValue );

	CCSTraceFormator& operator << ( int iValue );

	CCSTraceFormator& operator << ( UINT iValue );

	CCSTraceFormator& operator << ( long lValue );

	CCSTraceFormator& operator << ( LONGLONG llValue );

	CCSTraceFormator& operator << ( DWORD dwValue );

	CCSTraceFormator& operator << ( float fValue );

	CCSTraceFormator& operator << ( double dValue );

	CCSTraceFormator& operator << ( const char* pszValue );

	CCSTraceFormator& operator << ( void* lpValue );

	CCSTraceFormator& operator << ( const CCSString& strValue );

	CCSTraceFormator& operator << ( const CCCSInetAddress& address );

	CCSTraceFormator& operator << ( Ordix ordixValue );

	operator char* ();

private:
	void SetHexFlag( bool bHex );

	bool GetHexFlag() const;

	void AdvanceBuffer( const char* pBuffer );

private:
	bool						m_bHex;
	char*						m_pBuffer;
	DWORD						m_dwBufferSize;
	DWORD						m_dwPos;
};

#endif	// _CCS_TRACE_FORMATER_H_

