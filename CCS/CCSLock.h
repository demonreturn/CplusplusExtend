
#ifndef _CCS_LOCK_H_
#define _CCS_LOCK_H_

#include "CCSBase.h"
#include "CCSTimeStamp.h"

typedef enum tag_MutexAddr
{
	MUTEX_PROCESS,
	MUTEX_THREAD,
} MutexAddr;

typedef THREAD_HANDLE CCSThreadMutex;

typedef struct tag_CCSMutex
{
	int type;
	union 
	{
		CCSThreadMutex thread_mutex;
		CCS_HANDLE proc_mutex;
	};
} CCSMutex;

namespace CCS_OS
{
	int InitMutex( CCSMutex* pMutex,
		int locktype = MUTEX_THREAD,
		const char* pszName = 0,
		int* mutextype = 0,
		LPSECURITY_ATTRIBUTES sa = 0 );

	int DestoryMutex( CCSMutex* pMutex );

	int LockMutex( CCSMutex* pMutex );

	int LockMutex( CCSMutex* pMutex, int& abandoned );

	int LockMutex( CCSMutex* pMutex, const CCCSTimeStamp& timeout );

	int LockMutex( CCSMutex* pMutex, const CCCSTimeStamp* timeout );

	int TryLockMutex( CCSMutex* pMutex );

	int TryLockMutex( CCSMutex* pMutex, int& abandoned );

	int UnLockMutex( CCSMutex* pMutex );

/*****************************************************************************/
// A set of wrappers for mutex locks end
/*****************************************************************************/



/*****************************************************************************/
// A set of wrappers for critical section begin
/*****************************************************************************/

	// win32 下是关键段， LINUX下是互斥量
	int ThreadMutexDestroy( CCSThreadMutex* pThreadMutex );

	int ThreadMutexInit( CCSThreadMutex* pThreadMutex,
		int lockType = 0,
		const char* pszName = 0,
		int* mutexType = 0 );

	int ThreadMutexLock( CCSThreadMutex* pThreadMutex );

	int ThreadMutexLock( CCSThreadMutex* pThreadMutex,
		const CCCSTimeStamp& timeout );

	int ThreadMutexLock( CCSThreadMutex* pThreadMutex,
		const CCCSTimeStamp* timeout );

	int ThreadMutexTryLock( CCSThreadMutex* pThreadMutex );

	int ThreadMutexUnLock( CCSThreadMutex* pThreadMutex );

/*****************************************************************************/
// A set of wrappers for critical section end
/*****************************************************************************/


/*****************************************************************************/
// A set of wrappers for event start
/*****************************************************************************/

	int EventDestroy( CCS_HANDLE* event );

	int EventInit( CCS_HANDLE* event,
		int manualReset = 0,
		int initialState = 0,
		const char* pszName = 0,
		void* pArg = 0,
		LPSECURITY_ATTRIBUTES sa = 0 );

	int EventPulse( CCS_HANDLE* event );

	int EventReset( CCS_HANDLE* event );

	int EventSignal( CCS_HANDLE* event );

	int EventTimeWait( CCS_HANDLE* event );

	int EventTimeWait( CCS_HANDLE* event,
		const CCCSTimeStamp& timeout );
	
/*****************************************************************************/
// A set of wrappers for event end
/*****************************************************************************/
}

#endif // _CCS_LOCK_H_
