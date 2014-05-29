

#ifndef _CCS_INET_ADDRESS_H_
#define _CCS_INET_ADDRESS_H_

#include "CCSBase.h"

class CCS_API CCCSInetAddress
{
public:
	CCCSInetAddress();

	CCCSInetAddress( const char* phostnameAndPort );

	CCCSInetAddress( 
		const char* phostname,
		WORD port );

	~CCCSInetAddress();

public:
	CCSResult Set( const char* phostname, WORD port );

	// 127.0.0.1:1224
	CCSResult Set( const char* phostnameAndPort );

	CCSResult Set( DWORD dwIP );

	CCSResult SetPort( WORD port );

	WORD GetPort() const;

	CCSString GetStrIP() const;

	DWORD GetSize() const;

	const CCSSOCKADDR* GetRawAddress() const;

public:
	bool operator == ( const CCCSInetAddress& other ) const;

	bool operator <  ( const CCCSInetAddress& other ) const;

private:
	CCSResult SetIP( const char* pszIP );

	CCSResult SetIP( DWORD dwIP, bool bnetworkOrder = false );

private:
	CCSSOCKADDR					m_sockAddr;
};


#endif // _CCS_INET_ADDRESS_H_
