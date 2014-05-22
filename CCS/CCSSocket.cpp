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

extern CCS_API int CCS_OS::SendV( 
	HANDLE handle,
	const iovec pszIov[],
	DWORD dwCount )
{
	int iRet = 0;
#ifdef CCS_WIN32
	DWORD dwBytesSend = 0;
	iRet = ::WSASend(
		(CSSOCKET)handle,
		(WSABUF*)pszIov,
		dwCount,
		&dwBytesSend,
		0,
		NULL,
		NULL );

	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
	else
	{
		iRet = (int)dwBytesSend;
	}

#elif defined( CCS_LINUX)		// linux  实现
	iRet = ::writev(
		handle,
		pszIov,
		dwCount );
#endif
}

extern CCS_API int CCS_OS::Recv( 
	HANDLE handle,
	char* pBuffer,
	DWORD dwLength,
	int iFlag /*= 0 */ )
{
	if ( NULL == pBuffer )
	{
		return SOCKET_ERROR;
	}

	int iRet = ::recv(
		(CSSOCKET)handle,
		pBuffer,
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

extern CCS_API int CCS_OS::RecvV( 
	HANDLE handle,
	iovec szIov[],
	DWORD dwCount )
{
	if ( NULL == szIov )
	{
		return SOCKET_ERROR;
	}

	int iRet = 0;
#ifdef CCS_WIN32
	DWORD dwBytesRecv = 0;
	DWORD dwFlag = 0;

	iRet = ::WSARecv(
		(CSSOCKET)handle,
		(WSABUF*) szIov,
		dwCount,
		&dwBytesRecv,
		&dwFlag,
		NULL,
		NULL );

	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
	else
	{
		iRet = (int)dwBytesRecv;
	}
#elif defined( CCS_LINUX)		// linux  实现
	iRet = ::readv(
		handle,
		szIov,
		dwCount );
#endif

	return iRet;
}

extern CCS_API int CCS_OS::Bind( 
	HANDLE handle,
	const CCCSInetAddress& localAddreess )
{
#ifdef CCS_WIN32
	int iRet = ::bind(
		(CSSOCKET)handle,
		reinterpret_cast<const sockaddr*>(localAddreess.GetRawAddress()),
		localAddreess.GetSize() );
#elif defined( CCS_LINUX)		// linux  实现
	int iRet = ::bind(
		(CSSOCKET)handle,
		reinterpret_cast<const sockaddr*>(localAddreess.GetRawAddress()),
		static_cast<socklen_t>(localAddreess.GetSize() ));
#endif

	return iRet;
}

extern CCS_API int CCS_OS::ShutDown( HANDLE handle, int iFlag )
{
	int iRet = ::shutdown(
		(CSSOCKET)handle,
		iFlag );

#ifdef CCS_WIN32
	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
#endif

	return iRet;
}

extern CCS_API int CCS_OS::SendUdp( 
	HANDLE handle,
	const char* pData,
	DWORD dwLength,
	const CCCSInetAddress& peerAddress,
	int iFlag /*= 0 */ )
{
#ifdef CCS_WIN32
	int iRet = ::sendto(
		(CSSOCKET)handle,
		pData,
		dwLength,
		iFlag,
		reinterpret_cast<const sockaddr*>( peerAddress.GetRawAddress()),
		peerAddress.GetSize() );

	if ( SOCKET_ERROR == iRet )
	{
		errno == ::WSAGetLastError();
	}
#elif defined( CCS_LINUX)		// linux  实现
	int iRet = ::sendto(
		(CSSOCKET)handle,
		pData,
		dwLength,
		iFlag,
		reinterpret_cast<const sockaddr*>( peerAddress.GetRawAddress()),
		static_cast<socklen_t>(peerAddress.GetSize()) );
#endif

	return iRet;
}

extern CCS_API int CCS_OS::SendUdpV( 
	HANDLE handle,
	const iovec pszIov[],
	DWORD dwCount,
	const CCCSInetAddress& peerAddress )
{
	int iRet = 0;
#ifdef CCS_WIN32
	DWORD dwBytesSend = 0;
	iRet = ::WSASendTo(
		(CSSOCKET)handle,
		(WSABUF*)pszIov,
		dwCount,
		&dwBytesSend,
		0,
		reinterpret_cast<const sockaddr*>(peerAddress.GetRawAddress()),
		peerAddress.GetSize(),
		NULL,
		NULL );

	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
	else
	{
		iRet = (int)dwBytesSend;
	}
#elif defined( CCS_LINUX)		// linux  实现
	msghdr msgData;
	msgData.msg_iov = (iovec*)pszIov;
	msgData.msg_iovlen = dwCount;	
	msgData.msg_name = (struct sockaddr*)peerAddress.GetRawAddress();
	msgData.msg_namelen = peerAddress.GetSize();
	msgData.msg_control = 0;
	msgData.msg_controllen = 0;
	msgData.msg_flags = 0;

	iResult = ::sendmsg(
		Handle, 
		&msgData, 
		0 );
#endif

	return iRet;
}

extern CCS_API int CCS_OS::RedvUDP( 
	HANDLE handle,
	char* pBuffer, 
	DWORD dwLength,
	CCCSInetAddress& peerAddress,
	int iFlag /*= 0 */ )
{
	int iSize = (int)peerAddress.GetSize();

#ifdef CCS_WIN32
	int iRet = ::recvfrom(
		(CSSOCKET)handle,
		pBuffer,
		dwLength,
		iFlag,
		reinterpret_cast<sockaddr*>( const_cast<CCSSOCKADDR*>(peerAddress.GetRawAddress())),
		&iSize );

	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
#elif defined( CCS_LINUX)		// linux  实现
	int iRet = ::recvfrom(
		(CSSOCKET)handle,
		pBuffer,
		dwLength,
		iFlag,
		reinterpret_cast<sockaddr*>( const_cast<CCSSOCKADDR*>(peerAddress.GetRawAddress())),
		reinterpret_cast<socklen_t*>( &iSize ) );
#endif

	return iRet;
}

extern CCS_API int CCS_OS::Connect( 
	HANDLE handle,
	const CCCSInetAddress& peerAddress )
{
	int iRet = ::connect(
		(CSSOCKET)handle,
		reinterpret_cast<const struct sockaddr*>( peerAddress.GetRawAddress()),
		(int)peerAddress.GetSize() );
#ifdef CCS_WIN32
	if ( SOCKET_ERROR == iRet )
	{
		errno = ::WSAGetLastError();
	}
#elif defined( CCS_LINUX)		// linux  实现
	if ( SOCKET_ERROR == iRet )
	{
		if ( EINPROGRESS == errno )
		{
			errno = EWOULDBLOCK;
		}
	}
#endif
	
	return iRet;
}

extern CCS_API int CCS_OS::Listen( 
	HANDLE handle,
	const CCCSInetAddress& peerAddress )
{
	int iRet = ::listen(
		(CSSOCKET)handle,
		SOMAXCONN );

#ifdef CCS_WIN32
	if ( SOCKET_ERROR == iRet )
	{
		errno == ::WSAGetLastError();
	}
#elif defined( CCS_LINUX)		// linux  实现
	if ( SOCKET_ERROR == iRet )
	{
		if ( EINPROGRESS == errno )
		{
			errno = EWOULDBLOCK;
		}
	}
#endif
	
	return iRet;
}

extern CCS_API HANDLE CCS_OS::Accept( 
	HANDLE handle,
	CCCSInetAddress& peerAddress )
{
	int iSize = peerAddress.GetSize();
#ifdef CCS_WIN32
	handle = (HANDLE)::accept(
		(CSSOCKET)handle,
		reinterpret_cast<sockaddr*>(const_cast<CCSSOCKADDR*>(peerAddress.GetRawAddress())),
		&iSize );

	if ( CCS_INVALID_HANDLE == handle )
	{
		errno == ::WSAGetLastError();
	}

#elif defined( CCS_LINUX)		// linux  实现
	handle = (HANDLE)::accept(
		(CSSOCKET)handle,
		reinterpret_cast<sockaddr*>(const_cast<CCSSOCKADDR*>(peerAddress.GetRawAddress())),
		reinterpret_cast<socklen_t*>( &iSize ) );

	if ( CCS_INVALID_HANDLE == handle &&
		EINPROGRESS == errno )
	{
		errno == EWOULDBLOCK;
	}
#endif

	return handle;
}
