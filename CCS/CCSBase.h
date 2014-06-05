

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
typedef DWORD CCS_THREAD_ID;
#define CCS_INVALID_HANDLE		INVALID_HANDLE_VALUE

struct iovec
{
	DWORD iov_len;	
	char* iov_base;
};

// fileoperation define
#define CCS_DEFAULT_FILE_MODE ( FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE)

// 文件seek操作定义
#define CCS_SEEK_BEGIN		FILE_BEGIN
#define CCS_SEEK_CUR		FILE_CURRENT
#define CCS_SEEK_END		FILE_END

#define CCS_IOV_MAX 64

#elif defined( CCS_LINUX)
typedef void* THREAD_FUNC_RETURN;
typedef void* THREAD_RETURN_TYPE;
typedef int CCS_HANDLE;
typedef int CSSOCKET;
typedef sem_t SEM_HANDLE;
typedef pthread_mutex_t THREAD_HANDLE;

typedef pthread_t CCS_THREAD_ID;

#define CCS_INVALID_HANDLE		-1


typedef struct tagSECURITY_ATTRIBUTES
{
	DWORD nLength;
	void* lpSecurityDescriptor;
	BOOL bInheritHandle;
}SECURITY_ATTRIBUTES, *PSECURITY_ATTRIBUTES, *LPSECURITY_ATTRIBUTES;

// fileoperation define
#define CCS_DEFAULT_FILE_MODE 0644

// 文件seek操作定义
#define CCS_SEEK_BEGIN		SEEK_SET
#define CCS_SEEK_CUR		SEEK_CUR
#define CCS_SEEK_END		SEEK_END

#endif

typedef THREAD_RETURN_TYPE (_stdcall * THREAD_FUNC)(void*);
typedef std::string CCSString;
typedef LONGLONG CCS_OFFSET;

typedef long CCSResult;
typedef long long LONGLONG;

#ifdef SUPPORT_IPV6
typedef sockaddr_in6 CCSSOCKADDR
#else
typedef sockaddr_in CCSSOCKADDR;
#endif

typedef struct tag_FileAttribute
{
	LONGLONG				llFlesize;
	LONGLONG				llCreateTime;
	LONGLONG				llModifyTime;
} FileAttribute;

#define  MAX_FILENAMELEN			260

#endif // _CCS_BASE_H_

