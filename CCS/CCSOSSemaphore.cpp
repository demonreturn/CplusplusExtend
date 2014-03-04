#include "CCSOSSemaphore.h"

int CCS_OS::InitSemaphore( SEM_HANDLE*& pSemaphore, DWORD dwInitCount, DWORD dwMaxCount /*= OS_MAX_SEMAPHORE_COUNT*/, const char* pszName /*= NULL */ )
{
#ifdef CCS_WIN32
	pSemaphore = new SEM_HANDLE;
	if ( NULL == pSemaphore )
	{
		return CCS_ERROR_OUT_OF_MEMORY;
	}

	*pSemaphore = ::CreateSemaphoreA(
		NULL,
		dwInitCount,
		dwMaxCount,
		pszName );

	if ( NULL == *pSemaphore )
	{
		return -1;
	}

	return 0;

#elif defined( CCS_LINUX)		// linux  实现
	if ( NULL == pSemaphore )
	{
		int ret = ::sem_init( pSemaphore, FALSE, dwInitCount );

		return ret;
	}
	else
	{
		pSemaphore = ::sem_open( pszName, O_CREAT, OS_SEMAPHORE_MODE, dwInitCount );

		if ( SEM_FAILED == pSemaphore )
		{
			return -1;
		}
	}
#endif

	return 0;
}

int CCS_OS::UnInitSemaphore( SEM_HANDLE* pSemaphore, const char* pszName /*= NULL */ )
{
	if ( NULL == pSemaphore )
	{
		return CCS_ERROR_NULL_POINTER;
	}

#ifdef CCS_WIN32
	::CloseHandle( *pSemaphore );
#elif defined( CCS_LINUX)		// linux  实现
	int ret = -1;

	if ( NULL == pszName )
	{

	}
#endif
}
