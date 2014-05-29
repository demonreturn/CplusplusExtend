#include "CCSOSShareMemory.h"

#ifdef CCS_LINUX
#include <sys/mman.h>
#endif



extern CCS_API HANDLE CCS_OS::CreateShareMemory(
	HANDLE hFile,
	DWORD dwSize,
	const char* szName )
{
	if ( NULL == szName )
	{
		return CCS_INVALID_HANDLE;
	}

	HANDLE hRet = CCS_INVALID_HANDLE;
#ifdef CCS_WIN32
	hRet = ::CreateFileMappingA(
		hFile,
		NULL,
		PAGE_READWRITE,
		0,
		dwSize,
		szName );

	if ( NULL == hRet )
	{
		return CCS_INVALID_HANDLE;
	}

	return hRet;
#elif defined( CCS_LINUX)		// linux  ʵ��
	// ��Linux��˵��������ļ�������ǹ����ڴ�ľ��
	hRet = hFile;
	if ( CCS_INVALID_HANDLE == hRet )
	{
		// ����������CCS_INVALID_HANDLE(-1)��˵��û��ָ��ӳ���ļ�·������ʱʹ��ϵͳĬ�ϵ�
		hRet = ::shm_open(
			szName,
			O_CREAT|O_RDWR,
			-1 );

		if ( CCS_INVALID_HANDLE != hRet )
		{
			// ���ù����ڴ��Сʧ��
			if ( -1 == ::ftruncate(hResult, dwSize))
			{
				::close( hRet );

				hRet = CCS_INVALID_HANDLE;
			}
		}
	}
#endif

	return hRet;
}

extern CCS_API HANDLE CCS_OS::OpenShareMemory(
	const char* szName,
	const char* szRegularFileName /*= NULL */ )
{
	if ( NULL == szName )
	{
		return CCS_INVALID_HANDLE;
	}

	HANDLE hRet = CCS_INVALID_HANDLE;
#ifdef CCS_WIN32
	hRet = ::OpenFileMappingA(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		szName );

	if ( NULL == hRet )
	{
		hRet = CCS_INVALID_HANDLE;
	}
#elif defined( CCS_LINUX)		// linux  ʵ��
	if ( NULL != szRegularFileName)
	{
		// ʹ����ͨ�ļ���Ϊӳ�������
		hRet = ::open( szRegularFileName, O_RDWR, -1 );
	}
	else
	{
		// ʹ��ϵͳĿ¼��һ������/dev/shmĿ¼��
		hRet = ::shm_open( szName, O_RDWR, -1 );
	}
#endif

	return hRet;
}

extern CCS_API void* CCS_OS::MapViewShareMemory( 
	HANDLE hShareMemory,
	DWORD dwSize )
{
	if ( CCS_INVALID_HANDLE == hShareMemory )
	{
		return NULL;
	}

	void* pRet = NULL;
#ifdef CCS_WIN32
	pRet = ::MapViewOfFile(
		hShareMemory,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		dwSize );

#elif defined( CCS_LINUX)		// linux  ʵ��
	pRet = ::mmap(
		NULL,
		dwSize,
		PROT_READ | PROT_WRITE,
		MAP_SHARED,
		hShareMemory,
		0 );

	if ( MAP_FAILED == pRet )
	{
		pRet = NULL;
	}
#endif

	return pRet;
}

extern CCS_API BOOL CCS_OS::FlushShareMemory( 
	void* lpDataToFlush, 
	DWORD dwLength )
{
	if ( NULL == lpDataToFlush )
	{
		return FALSE;
	}

	BOOL bRet = FALSE;
#ifdef CCS_WIN32
	bRet = ::FlushViewOfFile(
		lpDataToFlush,
		dwLength );

#elif defined( CCS_LINUX)		// linux  ʵ��
	int iRet = ::msync(
		lpDataToFlush,
		dwLength,
		MS_SYNC );

	bRet = (-1 == iRet) ? FALSE : TRUE;
#endif

	return bRet;
}

extern CCS_API int CCS_OS::CloseShareMemory( 
	HANDLE hShareMemory,
	bool bMapToFile,
	void* pHeader,
	DWORD dwLength )
{
	int iRet = CCS_OK;
#ifdef CCS_WIN32
	if ( NULL != pHeader 
		&& !::UnmapViewOfFile( pHeader)
		&& CCS_INVALID_HANDLE != hShareMemory 
		&& !::CloseHandle( hShareMemory ) )
	{
		iRet = CCS_ERROR_FAILURE;
	}

#elif defined( CCS_LINUX)		// linux  ʵ��
	if ( CCS_INVALID_HANDLE != hShareMemory
		&& !bMapToFile
		&&  -1 != close(hShareMemory)
		&& NULL != NULL 
		&& -1 == ::munmap( pHeader, dwLength))
	{
		iRet = CCS_ERROR_FAILURE;
	}

#endif

	return iRet;
}

extern CCS_API void CCS_OS::UnLinkShareMemory( 
	const char* szName )
{
#ifdef CCS_LINUX
	::shm_unlink( szName );
#endif
}
