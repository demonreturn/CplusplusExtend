

#ifndef _CCS_SEMAPHORE_H_
#define _CCS_SEMAPHORE_H_

#include "CCSBase.h"

namespace CCS_OS
{
	const DWORD OS_MAX_SEMAPHORE_COUNT = 0x7fffffff;
	const DWORD OS_SEMAPHORE_MODE = 438;		// ÎÄ¼þÊôÐÔrw-r--r--

	int InitSemaphore(
		SEM_HANDLE*& pSemaphore,
		DWORD dwInitCount,
		DWORD dwMaxCount = OS_MAX_SEMAPHORE_COUNT,
		const char* pszName = NULL );

	int UnInitSemaphore( 
		SEM_HANDLE* pSemaphore, const char* pszName = NULL );

	int LockSemaphore( SEM_HANDLE* pSemaphore );

	int UnLockSemaphore( SEM_HANDLE* pSemaphore );

	int PostNSemphore( SEM_HANDLE* pSemaphore, DWORD dwCount );
}

#endif	// _CCS_SEMAPHORE_H_


