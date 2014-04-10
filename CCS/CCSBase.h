

#ifndef _CCS_BASE_H_
#define _CCS_BASE_H_

#include "CCSPlantform.h"
#include "CCSErrorDefines.h"
#include "CCSUtilDefines.h"

#ifdef CCS_WIN32
typedef DWORD THREAD_FUNC_RETURN;
typedef unsigned int THREAD_RETURN_TYPE;
typedef HANDLE CCS_HANDLE;
typedef SOCKET CSSOCKET;
typedef HANDLE SEM_HANDLE;
typedef CRITICAL_SECTION THREAD_HANDLE;

#elif defined( CCS_LINUX)
typedef void* THREAD_FUNC_RETURN;
typedef void* THREAD_RETURN_TYPE;
typedef int CCS_HANDLE;
typedef int CSSOCKET;
typedef sem_t SEM_HANDLE;
typedef pthread_mutex_t THREAD_HANDLE;

typedef struct tagSECURITY_ATTRIBUTES
{
	DWORD nLength;
	void* lpSecurityDescriptor;
	BOOL bInheritHandle;
}SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

#endif

typedef THREAD_RETURN_TYPE (_stdcall * THREAD_FUNC)(void*);
typedef std::string CCSString;

typedef long CCSResult;
typedef sockaddr_in CCSSOCKADDR;


#endif // _CCS_BASE_H_

