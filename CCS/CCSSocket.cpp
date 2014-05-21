#include "CCSSocket.h"
#include "CCSInetAddress.h"

CCS_OS::CCSSocketErrorAutoSave::CCSSocketErrorAutoSave()
	: m_iLastError( errno )
{

}

CCS_OS::CCSSocketErrorAutoSave::~CCSSocketErrorAutoSave()
{
	errno = m_iLastError;
}

int CCS_OS::CCSSocketErrorAutoSave::GetLastError()
{
	return m_iLastError;
}

extern CCS_API CCSString CCS_OS::IPDigitalToString( DWORD dwIP )
{
#ifdef CCS_WIN32
	struct in_addr addrIn;
	addrIn.s_addr = dwIP;

	const char* pAddr = ::inet_ntoa( addrIn );
#elif defined( CCS_LINUX)		// linux  实现
	char szbuff[INET_ADDRSTRLEN];
	const char* pAddr = ::inet_ntop(
		AF_INET,
		&dwIP,
		szbuff,
		sizeof(szbuff) );
#endif

	return CCSString(pAddr);
}

extern CCS_API DWORD CCS_OS::IPStringToDigital( const char* pstrIP )
{
	if ( NULL == pstrIP )
	{
		return INADDR_NONE;
	}

	DWORD dwIP = INADDR_ANY;
#ifdef CCS_WIN32
	dwIP = ::inet_addr( pstrIP );
#elif defined( CCS_LINUX)		// linux  实现
	::inet_pton(
		AF_INET,
		pstrIP,
		&dwIP );
#endif

	return dwIP;
}

extern CCS_API int CCS_OS::SetIOCtrl( CSSOCKET handle, int flag, void* pparam )
{
#ifdef CCS_WIN32
	return ::ioctlsocket(
		handle,
		flag,
		reinterpret_cast<DWORD*>(pparam) );
#elif defined( CCS_LINUX)		// linux  实现
	return ::ioctl(
		handle,
		flag,
		pparam );
#endif
}

extern CCS_API int CCS_OS::GetLocalAddress( 
	CSSOCKET handle,
	CCCSInetAddress& localAddress )
{
	int iSize = (int)localAddress.GetSize();

#ifdef CCS_WIN32
	int iRet = ::getsockname(
		handle,
		reinterpret_cast<sockaddr*>(
		const_cast<CCSSOCKADDR*>(localAddress.GetRawAddress()) ),
		&iSize );
#elif defined( CCS_LINUX)		// linux  实现
	int iRet = ::getsockname(
		handle,
		reinterpret_cast<sockaddr*>(
		const_cast<CCSSOCKADDR*>(localAddress.GetRawAddress()) ),
		reinterpret_cast<socklen_t*>( &iSize ) );
#endif

	if ( SOCKET_ERROR == iRet )
	{
#ifdef CCS_WIN32
		errno = ::WSAGetLastError();
#endif
	}

	return iRet;
	
}

extern CCS_API int CCS_OS::GetRemoteAddress( 
	CSSOCKET handle, 
	CCCSInetAddress& remoteAddress )
{
	int iSize = (int)remoteAddress.GetSize();

#ifdef CCS_WIN32
	int iRet = ::getpeername(
		handle,
		reinterpret_cast<sockaddr*>( const_cast<CCSSOCKADDR*>(remoteAddress.GetRawAddress())),
		&iSize );
#elif defined( CCS_LINUX)		// linux  实现
	int iRet = ::getpeername(
		handle,
		reinterpret_cast<sockaddr*>( const_cast<CCSSOCKADDR*>(remoteAddress.GetRawAddress())),
		reinterpret_cast<socklen_t*>(&iSize) );
#endif

	if ( SOCKET_ERROR == iRet )
	{
#ifdef CCS_WIN32
		errno = ::WSAGetLastError();
#endif
	}

	return iRet;
}

extern CCS_API int CCS_OS::SetSocketOption( 
	CSSOCKET handle,
	int iLevel,
	int iOption,
	const void* pOption,
	int iOptionLen )
{
#ifdef CCS_WIN32
	int iRet = ::setsockopt(
		handle,
		iLevel,
		iOption,
		static_cast<const char*>(pOption),
		iOptionLen );
#elif defined( CCS_LINUX)		// linux  实现
	int iRet = ::setsockopt(
		handle,
		iLevel,
		iOption,
		pOption,
		iOptionLen );
#endif
	
	if ( SOCKET_ERROR == iRet )
	{
#ifdef CCS_WIN32
		errno = ::WSAGetLastError();
#endif
	}

	return iRet;
}

extern CCS_API int CCS_OS::GetSocketOption( 
	CSSOCKET handle,
	int iLevel,
	int iOption,
	void* pOptionValue,
	int* pOptionLen )
{
#ifdef CCS_WIN32
	int iRet = ::getsockopt(
		handle,
		iLevel,
		iOption,
		static_cast<char*>(pOptionValue),
		pOptionLen );
#elif defined( CCS_LINUX)		// linux  实现
	int iRet = ::getsockopt(
		handle,
		iLevel,
		iOption,
		pOptionValue,
		reinterpret_cast<socklen_t*>(pOptionLen) );
#endif

	if ( SOCKET_ERROR == iRet )
	{
#ifdef CCS_WIN32
		errno = ::WSAGetLastError();
#endif
	}

	return iRet;
}

extern CCS_API int CCS_OS::CloseSocket( CSSOCKET handle )
{
	int iRet = 0;
#ifdef CCS_WIN32
	iRet = ::closesocket( handle );
#elif defined( CCS_LINUX)		// linux  实现
	iRet = ::close( handle );
#endif

	if ( SOCKET_ERROR == iRet )
	{
#ifdef CCS_WIN32
		errno = ::WSAGetLastError();
#endif
	}

	return iRet;
}

extern CCS_API int CCS_OS::Send( 
	HANDLE handle,
	const char* pData,
	DWORD dwLength,
	int iFlag /*= 0 */ )
{
	int iRet = ::send(
		(CSSOCKET)handle,
		pData,
		dwLength,
		iFlag );
#ifdef CCS_WIN32
	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
#elif defined( CCS_LINUX)		// linux  实现
	if ( SOCKET_ERROR == iRet &&
		errno == EAGAIN )
	{
		errno = EWOULDBLOCK;
	}
#endif

	return iRet;
}
