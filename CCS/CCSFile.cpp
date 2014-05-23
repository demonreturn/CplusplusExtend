#include "CCSFile.h"

#ifdef CCS_WIN32
#include <io.h>
#include <sys/stat.h>
#elif defined( CCS_LINUX)		// linux  ʵ��
#include <sys/statfs.h>
#endif



extern CCS_API HANDLE CCS_OS::OpenFile( 
	const char* pFullPath,
	DWORD dwFlags /*= O_RDONLY */,
	DWORD dwMode /*= CCS_DEFAULT_FILE_MODE*/,
	DWORD dwFileAttributes /*= FILE_ATTRIBUTE_NORMAL */,
	LPSECURITY_ATTRIBUTES pSapSecurity /*= NULL */ )
{
	if ( NULL == pFullPath )
	{
		return CCS_INVALID_HANDLE;
	}

#ifdef CCS_WIN32
	DWORD dwAccess = GENERIC_READ;
	DWORD dwShareMode = dwMode;
	DWORD dwCreation = OPEN_EXISTING;
	DWORD dwFlagsAndAttributes = dwFileAttributes;

	//���ļ��ķ���Ȩ�ޱ�־
	if ( CCS_BIT_ENABLED( dwFlags, O_WRONLY ) )
	{
		dwAccess = GENERIC_WRITE;
	}
	else if ( CCS_BIT_ENABLED( dwFlags, O_RDWR ) )
	{
		dwAccess = GENERIC_READ | GENERIC_WRITE;
	}
	//�ļ���/������־
	if ( CCS_BIT_CMP_MASK(dwFlags, ( O_CREAT | O_EXCL ), ( O_CREAT | O_EXCL ) ) )
		//if ( (nFlags & (_O_CREAT | _O_EXCL) ) == (_O_CREAT | _O_EXCL) )
	{
		//�ļ�������,����һ�����ļ�
		//�ļ��Ѵ���,����ʧ��
		dwCreation = CREATE_NEW;
	}
	else if( CCS_BIT_CMP_MASK(dwFlags, ( O_CREAT | O_TRUNC ), ( O_CREAT | O_TRUNC ) ) )
		//else if ( (nFlags & (_O_CREAT | _O_TRUNC) ) == ((_O_CREAT | _O_TRUNC)) )
	{
		//�ļ��Ѵ���,���سɹ� �ļ������
		//�ļ�������,����һ�����ļ�
		dwCreation = CREATE_ALWAYS;
	}
	else if ( CCS_BIT_ENABLED (dwFlags, O_CREAT) )
	{
		//�ļ��Ѵ���,���سɹ�
		//�ļ�������,����һ�����ļ�
		dwCreation = OPEN_ALWAYS;
	}
	else if ( CCS_BIT_ENABLED (dwFlags, O_TRUNC) )
	{
		//�ļ�������,����ʧ��
		dwCreation = TRUNCATE_EXISTING;
	}

	if ( CCS_BIT_ENABLED( dwFlags, O_TEMPORARY ) )
	{
		//��ʱ�ļ�����
		dwFlagsAndAttributes |= FILE_ATTRIBUTE_TEMPORARY | FILE_FLAG_DELETE_ON_CLOSE;
	}

	HANDLE handle = ::CreateFileA(
		pFullPath,
		dwAccess,
		dwShareMode,
		pSapSecurity,
		dwCreation,
		dwFlagsAndAttributes,
		NULL );

	if ( INVALID_HANDLE_VALUE == handle )
	{
		return CCS_INVALID_HANDLE;
	}
	else
	{
		if ( CCS_BIT_ENABLED( dwFlags, O_APPEND ))
		{
			::SetFilePointer( handle,
				0,
				0,
				FILE_END );
		}
	}

	return handle;
#elif defined( CCS_LINUX)		// linux  ʵ��
	return (::open(pFullPath,
		dwFlags,
		dwMode ));
#endif
}

extern CCS_API int CCS_OS::ReadFile( 
	HANDLE fileHandle,
	LPVOID pBuffer,
	DWORD dwReadSize,
	LPDWORD dwHaveRead )
{
	if ( NULL == pBuffer )
	{
		return -1;
	}

#ifdef CCS_WIN32
	if ( ::ReadFile( fileHandle,
		pBuffer,
		dwReadSize,
		dwHaveRead,
		NULL ))
	{
		return 0;
	}
#elif defined( CCS_LINUX)		// linux  ʵ��
	ssize_t sz = ::read( fileHandle,
		pBuffer,
		dwReadSize );
	if ( sz >= 0 )
	{
		*dwHaveRead = sz;
		return 0;
	}
#endif
	return -1;
}

extern CCS_API int CCS_OS::WriteFile(
	HANDLE handle,
	const LPVOID pBuffer,
	DWORD dwWriteSize,
	LPDWORD dwHaveWrite )
{
	if ( NULL == dwHaveWrite )
	{
		return -1;
	}
#ifdef CCS_WIN32
	if ( ::WriteFile( handle,
		pBuffer,
		dwWriteSize,
		dwHaveWrite,
		NULL ))
	{
		return 0;
	}
#elif defined( CCS_LINUX)		// linux  ʵ��
	ssize_t sz = ::write( handle,
		pBuf,
		dwWriteSize );
	if ( sz >= 0 )
	{
		*dwHaveWrite = sz;
		return 0;
	}
#endif

	return -1;
}

extern CCS_API int CCS_OS::SeekFile( 
	HANDLE handle,
	CCS_OFFSET lDistance,
	DWORD nMoveMethod )
{
#ifdef CCS_WIN32
	LARGE_INTEGER lgDistance;
	lgDistance.QuadPart = lDistance;

	DWORD dwRet = ::SetFilePointer( handle, 
		lgDistance.LowPart,
		&(lgDistance.HighPart),
		nMoveMethod );
	if ( dwRet == INVALID_SET_FILE_POINTER 
		&& GetLastError() != NO_ERROR )
	{
		return -1;
	}

	return 0;
#elif defined( CCS_LINUX)		// linux  ʵ��
	CCS_OFFSET lRet = ::lseek( handle,
		lDistance,
		nMoveMethod );

	if ( -1 != lRet )
	{
		return 0;
	}
#endif

	return -1;
}

extern CCS_API int CCS_OS::FlushFile( HANDLE handle )
{
#ifdef CCS_WIN32
	if ( ::FlushFileBuffers( handle ))
	{
		return 0;
	}

	return -1;
#elif defined( CCS_LINUX)		// linux  ʵ��
	return ::fsync( handle );
#endif

	return -1;
}

extern CCS_API int CCS_OS::CloseFile( HANDLE handle )
{
#ifdef CCS_WIN32
	if ( ::CloseHandle( handle ))
	{
		return 0;
	}

	return -1;
#elif defined( CCS_LINUX)		// linux  ʵ��
	return ::close(handle);
#endif

	return -1;
}
