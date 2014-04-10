#include "CCSLock.h"

int CCS_OS::DestoryMutex( CCSMutex* pMutex )
{
	if ( NULL == pMutex )
	{
		return -1;
	}

#ifdef CCS_WIN32
	switch ( pMutex->type )
	{
	case MUTEX_PROCESS:
		{
			BOOL bClose = ::CloseHandle( pMutex->proc_mutex );
			return bClose ? 0 : -1;
		}
		break;
	case MUTEX_THREAD:
		{
			return ThreadMutexDestroy( &(pMutex->thread_mutex) );
		}
		break;
	default:
		return -1;
		break;
	}
#elif defined( CCS_LINUX)		// linux  实现
	return ThreadMutexDestroy(& (pMutex->thread_mutex) );
#endif
}

int CCS_OS::InitMutex( CCSMutex* pMutex, int locktype /*= MUTEX_THREAD*/, const char* pszName /*= 0*/, int* mutextype /*= 0*/, LPSECURITY_ATTRIBUTES sa /*= 0 */ )
{
	if ( NULL == pMutex )
	{
		return -1;
	}

#ifdef CCS_WIN32
	pMutex->type = locktype;
	switch ( locktype )
	{
	case MUTEX_PROCESS:
		{
			pMutex->proc_mutex = ::CreateMutexA( sa,
				FALSE,
				pszName );

			return ( 0 == pMutex->proc_mutex ) ? -1 : 0;
		}
		break;
	case MUTEX_THREAD:
		{
			return ThreadMutexInit(
				&(pMutex->thread_mutex),
				locktype,
				pszName );
		}
		break;
	default:
		return -1;
		break;
	}
#elif defined( CCS_LINUX)		// linux  实现
	return ThreadMutexInit( &(pMutex->thread_mutex),
		0,
		pszName );
#endif
}

int CCS_OS::LockMutex( CCSMutex* pMutex )
{
	if ( NULL == pMutex )
	{
		return -1;
	}

#ifdef CCS_WIN32
	switch ( pMutex->type )
	{
	case MUTEX_PROCESS:
		{
			DWORD ret = ::WaitForSingleObject( pMutex->proc_mutex, INFINITE );
			switch ( ret )
			{
			case WAIT_OBJECT_0:
			case WAIT_ABANDONED:
				{

					return 0;
				}
			default:
				{
					return -1;
				}
				break;
			}
		}
		break;
	case MUTEX_THREAD:
		{
			return ThreadMutexLock( &(pMutex->thread_mutex) );
		}
		break;
	default:
		return -1;
		break;
	}
#elif defined( CCS_LINUX)		// linux  实现
	return ThreadMutexLock( &(pMutex->thread_mutex) );
#endif
}

int CCS_OS::LockMutex( CCSMutex* pMutex, int& abandoned )
{
	if ( NULL == pMutex )
	{
		return -1;
	}

	abandoned = 0;
#ifdef CCS_WIN32
	switch ( pMutex->type )
	{
	case MUTEX_PROCESS:
		{
			DWORD ret = ::WaitForSingleObject(
				pMutex->proc_mutex, INFINITE );
			switch ( ret )
			{
			case WAIT_OBJECT_0:
				return 0;

			case WAIT_ABANDONED:
				{
					abandoned = 1;
					return 0;
				}
			default:
				return -1;
				break;
			}
		}
		break;
	case MUTEX_THREAD:
		{
			return ThreadMutexLock( &(pMutex->thread_mutex ));
		}
		break;
	default:
		return -1;
		break;
	}
#elif defined( CCS_LINUX)		// linux  实现
	return ThreadMutexLock( &(pMutex->thread_mutex ));
#endif
}

int CCS_OS::LockMutex( CCSMutex* pMutex, const CCCSTimeStamp& timeout )
{
	if ( NULL == pMutex )
	{
		return -1;
	}

	// timeout这个时间传入的是相对时间，在windows下等待用的是相对时间
	// 但是在linux下等待使用的时绝对时间，在这里不需要转换，在linux实现中需要转换。
#ifdef CCS_WIN32
	switch ( pMutex->type )
	{
	case MUTEX_PROCESS:
		{
			DWORD ret = ::WaitForSingleObject( pMutex->proc_mutex,
				timeout.GetMSSeconds() );

			switch ( ret )
			{
			case WAIT_OBJECT_0:
			case WAIT_ABANDONED:
				{
					return 0;
				}

			case WAIT_TIMEOUT:
				return -1;
				break;
			default:
				return -1;
				break;
			}
		}
		break;
	case MUTEX_THREAD:
		{
			return -1;
		}
		break;
	default:
		return -1;
		break;
	}
#elif defined( CCS_LINUX)		// linux  实现
	return ThreadMutexLock( &(pMutex->thread_mutex),
		timeout );
#endif
}

int CCS_OS::LockMutex( CCSMutex* pMutex, const CCCSTimeStamp* timeout )
{
	if ( NULL == pMutex )
	{
		return -1;
	}

#ifdef CCS_WIN32
	return -1;
#elif defined( CCS_LINUX)		// linux  实现
	return ThreadMutexLock( &(pMutex->thread_mutex),
		timeout );
#endif
}

int CCS_OS::TryLockMutex( CCSMutex* pMutex )
{
	if ( NULL == pMutex )
	{
		return -1;
	}

#ifdef CCS_WIN32
	switch ( pMutex->type )
	{
	case MUTEX_PROCESS:
		{
			DWORD ret = ::WaitForSingleObject( pMutex->proc_mutex, 0 );
			switch ( ret )
			{
			case WAIT_OBJECT_0:
			case WAIT_ABANDONED:
				return 0;

			case WAIT_TIMEOUT:
				return -1;
			default:
				return -1;
				break;
			}
		}
		break;
	case MUTEX_THREAD:
		{
			return ThreadMutexTryLock( &(pMutex->thread_mutex) );
		}
		break;
	default:
		return -1;
		break;
	}
#elif defined( CCS_LINUX)		// linux  实现
	return ThreadMutexTryLock( &(pMutex->thread_mutex) );
#endif
}

int CCS_OS::TryLockMutex( CCSMutex* pMutex, int& abandoned )
{
	if ( NULL == pMutex )
	{
		return -1;
	}

	abandoned = 0;
#ifdef CCS_WIN32
	switch ( pMutex->type )
	{
	case MUTEX_PROCESS:
		{
			DWORD ret = ::WaitForSingleObject( pMutex->proc_mutex, 0 );
			switch ( ret )
			{
			case WAIT_OBJECT_0:
				return 0;
			case WAIT_ABANDONED:
				abandoned = 1;
				return 0;

			case WAIT_TIMEOUT:
				return -1;
			default:
				return -1;
				break;
			}
		}
		break;
	case MUTEX_THREAD:
		{
			return ThreadMutexTryLock( &(pMutex->thread_mutex) );
		}
		break;
	default:
		return -1;
		break;
	}
#elif defined( CCS_LINUX)		// linux  实现
	return ThreadMutexTryLock( &(pMutex->thread_mutex) );
#endif
}

int CCS_OS::UnLockMutex( CCSMutex* pMutex )
{
	if ( NULL == pMutex )
	{
		return -1;
	}

#ifdef CCS_WIN32
	switch ( pMutex->type )
	{
	case MUTEX_PROCESS:
		{
			DWORD ret = ::ReleaseMutex( pMutex->proc_mutex );
			return (0 == ret) ? 0 : -1;
		}
		break;
	case MUTEX_THREAD:
		{
			return ThreadMutexUnLock( &(pMutex->thread_mutex) );
		}
		break;
	default:
		return -1;
		break;
	}
#elif defined( CCS_LINUX)		// linux  实现
	return ThreadMutexUnLock( &(pMutex->thread_mutex) );
#endif
}

int CCS_OS::ThreadMutexDestroy( CCSThreadMutex* pThreadMutex )
{
	if ( NULL == pThreadMutex )
	{
		return -1;
	}

#ifdef CCS_WIN32
	::DeleteCriticalSection( pThreadMutex );
#elif defined( CCS_LINUX)		// linux  实现
	::pthread_mutex_destroy( pThreadMutex );
#endif

	return 0;
}

int CCS_OS::ThreadMutexInit( 
	CCSThreadMutex* pThreadMutex,
	int lockType /*= 0*/,
	const char* pszName /*= 0*/,
	int* mutexType /*= 0 */ )
{
	if ( NULL == pThreadMutex )
	{
		return -1;
	}

#ifdef CCS_WIN32
	::InitializeCriticalSection( pThreadMutex );
#elif defined( CCS_LINUX)		// linux  实现
	pthread_mutexattr_t MutexAttr;

	int iResult = ::pthread_mutexattr_init( &MutexAttr );
	SC_ASSERTE( 0 == iResult );

	// 设置mutex类型为回旋锁
	iResult = ::pthread_mutexattr_settype(
		&MutexAttr, 
		PTHREAD_MUTEX_RECURSIVE);

	SC_ASSERTE( 0 == iResult );

	iResult = ::pthread_mutex_init( 
		pThreadMutex, 
		&MutexAttr );

	if ( 0 != iResult )
	{
		ThreadMutexDestroy( pThreadMutex );

		return -1;
	}
#endif

	return 0;
}

int CCS_OS::ThreadMutexLock( CCSThreadMutex* pThreadMutex )
{
	if ( NULL == pThreadMutex )
	{
		return -1;
	}

#ifdef CCS_WIN32

	::EnterCriticalSection( pThreadMutex );

	return 0;

#elif defined( CCS_LINUX)		// linux  实现
	int ret = ::pthread_mutex_lock( pThreadMutex );

	return ( 0 == ret ) ? 0 : -1;
#endif
}

int CCS_OS::ThreadMutexLock(
	CCSThreadMutex* pThreadMutex,
	const CCCSTimeStamp& timeout )
{
	if ( NULL == pThreadMutex )
	{
		return -1;
	}

#ifdef CCS_WIN32
	return -1;
#elif defined( CCS_LINUX)		// linux  实现
	struct timespec tsBuf;
	CCCSTimeStamp tvAbs = CCCSTimeStamp::GetCurTime() + timeout;
	tsBuf.tv_sec = tvAbs.GetSecond();
	tsBuf.tv_nsec = tvAbs.GetUSecond() * 1000;

	return ::pthread_mutex_timedlock(
		pThreadMutex,
		&tsBuf );
#endif

	return 0;
}

int CCS_OS::ThreadMutexTryLock( CCSThreadMutex* pThreadMutex )
{
#ifdef CCS_WIN32

#elif defined( CCS_LINUX)		// linux  实现
	
#endif

	return 0;
}

int CCS_OS::ThreadMutexUnLock( CCSThreadMutex* pThreadMutex )
{
#ifdef CCS_WIN32

#elif defined( CCS_LINUX)		// linux  实现
	
#endif

	return 0;
}
