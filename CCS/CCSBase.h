

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
#define CCS_INVALID_HANDLE		INVALID_HANDLE_VALUE

struct iovec
{
	DWORD iov_len;	
	char* iov_base;
};

#define CCS_IOV_MAX 64

#elif defined( CCS_LINUX)
typedef void* THREAD_FUNC_RETURN;
typedef void* THREAD_RETURN_TYPE;
typedef int CCS_HANDLE;
typedef int CSSOCKET;
typedef sem_t SEM_HANDLE;
typedef pthread_mutex_t THREAD_HANDLE;
#define CCS_INVALID_HANDLE		-1

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

#ifdef SUPPORT_IPV6
typedef sockaddr_in6 CCSSOCKADDR
#else
typedef sockaddr_in CCSSOCKADDR;
#endif



#endif // _CCS_BASE_H_

