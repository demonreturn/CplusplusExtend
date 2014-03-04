

#ifndef _CCS_OS_THREAD_H_
#define _CCS_OS_THREAD_H_

#include "CCSBase.h"
#include "CCSTimeStamp.h"

namespace CCS_OS
{
	inline int OSCreateThread(
		LPVOID pparms,
		THREAD_FUNC func,
		long flags,
		DWORD* pthreadID,
		CCS_HANDLE* pthreadHandle = 0,
		long npriority = 0,
		LPVOID stack = NULL,
		DWORD stacksize = 0 )
	{
#ifdef CCS_WIN32
		*pthreadHandle = (HANDLE)_beginthreadex(
			NULL,
			stacksize,
			func,
			pparms,
			flags,
			(unsigned int*) *pthreadID );

		if ( INVALID_HANDLE_VALUE == *pthreadHandle )
		{
			return -1;
		}

#elif defined( CCS_LINUX)		// linux  实现
		pthread_attr_t attr;
		int iresult = ::pthread_attr_init( &attr );
		if ( 0 != iresult )
		{
			return -1;
		}

		iresult = ::pthread_attr_setdetachstate(
			&attr,
			PTHREAD_CREATE_JOINABLE );

		if ( 0 != iresult )
		{
			::pthread_attr_destroy( &attr );
			return -1;
		}

		iresult = ::pthread_create(
			pthreadID,
			&attr,
			func,
			pparms );

		if ( 0 != iresult )
		{
			::pthread_attr_destroy( &attr );
			return -1;
		}

		::pthread_attr_destroy( &attr );

		*pthreadHandle = (*pthreadID);
#endif

		return 0;
	}

	inline DWORD GetSelfThreadID()
	{
#ifdef CCS_WIN32
		return ::GetCurrentThreadId();
#elif defined( CCS_LINUX)		// linux  实现
		return ::pthread_self();
#endif
	}

	inline CCS_HANDLE GetSelfThreadHandle()
	{
#ifdef CCS_WIN32
		return ::GetCurrentThread();
#elif defined( CCS_LINUX)		// linux  实现
		return ::pthread_self();
#endif
	}

	inline bool IsThreadEqual( DWORD tid1, DWORD tid2 )
	{
#ifdef CCS_WIN32
		return tid1 == tid2;
#elif defined( CCS_LINUX)		// linux  实现
		return ::pthread_equal( tid1, tid2 );
#endif
	}

	inline bool IsThreadEqual( CCS_HANDLE h1, CCS_HANDLE h2 )
	{
#ifdef CCS_WIN32
		return h1 == h2;
#elif defined( CCS_LINUX)		// linux  实现
		return ::pthread_equal( h1, h2 );
#endif
	}

	inline int OSSuspendThread( CCS_HANDLE th )
	{
#ifdef CCS_WIN32
		if ( INVALID_HANDLE_VALUE == th )
		{
			return -1;
		}

		DWORD dwRet = ::SuspendThread( th );

		if ( dwRet == (DWORD)(-1) )
		{
			return -1;
		}
#elif defined( CCS_LINUX)		// linux  实现
		return -1;
#endif

		return 0;
	}

	inline int OSResumeThread( CCS_HANDLE th )
	{
#ifdef CCS_WIN32
		if ( INVALID_HANDLE_VALUE == th )
		{
			return -1;
		}

		DWORD dwRet = ::ResumeThread( th );

		if ( dwRet == (DWORD)(-1) )
		{
			return -1;
		}
#elif defined( CCS_LINUX)		// linux  实现
		return -1;
#endif

		return 0;
	}

	inline int OSJoinThread( CCS_HANDLE th, THREAD_FUNC_RETURN* pstatus )
	{
#ifdef CCS_WIN32

		if ( INVALID_HANDLE_VALUE == th )
		{
			return -1;
		}

		THREAD_FUNC_RETURN localStatus = 0;
		if ( 0 == pstatus )
		{
			pstatus = &localStatus;
		}

		if ( WAIT_OBJECT_0 == ::WaitForSingleObject( th, INFINITE ) 
			&& FALSE != ::GetExitCodeThread( th, pstatus ) )
		{
			::CloseHandle( th );
			return 0;
		}

		return -1;
#elif defined( CCS_LINUX)		// linux  实现
		int iRet = ::pthread_join( th, NULL );

		return iRet;
#endif
	}

	inline int OSWaitThread( CCS_HANDLE th, const CCCSTimeStamp& ts )
	{
#ifdef CCS_WIN32
		DWORD ret;

		ret = ::WaitForSingleObject( th, ts.GetMicroseconds() / 1000 );

		switch ( ret )
		{
		case WAIT_OBJECT_0:
			{
				::CloseHandle( th );

				return 0;
			}
			break;

		case WAIT_TIMEOUT:
			return -1;
			break;

		default:
			return -1;
		}
#elif defined( CCS_LINUX)		// linux  实现
		int ret = ::pthread_join( th, NULL );

		return ret;
#endif

		return 0;
	}

	inline int OSTerminateThread( CCS_HANDLE th, DWORD dwExitCode )
	{
#ifdef CCS_WIN32
		BOOL bflag = FALSE;
		bflag = ::TerminateThread( th, dwExitCode );

		if ( FALSE == bflag )
		{
			return -1;
		}

		::CloseHandle( th );

		return 0;
#elif defined( CCS_LINUX)		// linux  实现
		int ret = ::pthread_detach( th );

		return ret;
#endif
	}

	inline int GetThreadPriority( CCS_HANDLE th, int& priority )
	{
#ifdef CCS_WIN32
		priority = ::GetThreadPriority( th );

		return 0;
#elif defined( CCS_LINUX)		// linux  实现
		return -1;
#endif
	}

	inline int SetThreadPriority( CCS_HANDLE th, int priority )
	{
#ifdef CCS_WIN32
		return ::SetThreadPriority( th, priority );
#elif defined( CCS_LINUX)		// linux  实现
		return -1;
#endif
	}
}

#endif // _CCS_OS_THREAD_H_

