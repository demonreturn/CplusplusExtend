
/*
	CCS	: C++ Common Frameworks
*/

#ifndef _CCS_UTIL_DEFINES_H_
#define _CCS_UTIL_DEFINES_H_

#include "CCSPlantform.h"
#include "CCSErrorDefines.h"

/* 设定select等函数最大处理句柄数为2048 - 原64 */
#ifdef CCS_WIN32

#ifdef FD_SETSIZE
	#define FD_SETSIZE
#endif // FD_SETSIZE

#define FD_SETSIZE 2048
#include <WinSock2.h>

#endif // CCS_WIN32


// 头文件引用定义
#ifdef CCS_WIN32
	#include <string.h>
	#include <direct.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <limits.h>
	#include <stddef.h>
	#include <stdarg.h>
	#include <signal.h>
	#include <errno.h>
	#include <wchar.h>

	#include <crtdbg.h>
	#include <process.h>
#elif defined( CCS_LINUX )
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <unistd.h>
	#include <errno.h>
	#include <limits.h>
	#include <stdarg.h>
	#include <time.h>
	#include <signal.h>
	#include <sys/stat.h>
	#include <sys/fcntl.h>
	#include <pthread.h>
	#include <fcntl.h>
	#include <sys/types.h>
	#include <sys/ioctl.h>
	#include <sys/socket.h>
	#include <sys/time.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <ctype.h>
	#include <assert.h>
	#include <netinet/tcp.h>
	#include <semaphore.h>
	#include <dlfcn.h>
#endif

// 公用头文件引用
#include <fcntl.h>
#include <memory>
#include <utility>
#include <algorithm>
#include <utility>
#include <set> 
#include <map>
#include <vector>
#include <list>
#include <queue>
#include <stack>

// export import defines
#ifdef CCS_WIN32
	#if( defined( _USERDLL) || defined(CCS_EXPORTS) )
		#define CCS_API __declspec( dllexport )
	#else
		#define CCS_API __declspec( dllimport )
	#endif
#else
	#define CCS_EXPORT
#endif // CCS_WIN32

/*
 * 分隔符定义
 */
#ifdef CCS_WIN32
#define CCS_OS_SEPARATE	'\\'
#elif defined( CCS_LINUX)		// linux  实现
#define CCS_OS_SEPARATE	'/'	
#endif

// 常用检测宏定义
/* 检查某bit有没有被设置 */
#ifndef CCS_BIT_ENABLED
#define CCS_BIT_ENABLED( dword, bit ) ( ((dword) & (bit)) != 0 )
#endif	// CCS_BIT_ENABLED

/* 检查某bit有没有被屏蔽 */
#ifndef CCS_BIT_DISABLED
#define CCS_BIT_DISABLED( dword, bit ) ( ((dword) & (bit)) == 0 )
#endif	// CCS_BIT_DISABLED

/* 检查某bit的值是否与<mask>相等 */
#ifndef CCS_BIT_CMP_MASK
#define CCS_BIT_CMP_MASK( dword, bit, mask ) ( ((dword) & (bit)) == mask )
#endif	// CCS_BIT_CMP_MASK

/* 设置某bit */
#ifndef CCS_SET_BITS
#define CCS_SET_BITS( dword, bits ) ( dword |= (bits) )
#endif	// CCS_SET_BITS

/* 屏蔽某bit */
#ifndef CCS_CLR_BITS
#define CCS_CLR_BITS( dword, bits ) ( dword &= ~(bits) )
#endif	// CCS_CLR_BITS

/* 删除一个指针并置为NULL */
#ifndef CCS_DELETE
#define CCS_DELETE( p )			\
	do								\
	{								\
	if ( NULL != p )			\
		{							\
		delete p;				\
		p = NULL;				\
		}							\
	} while ( 0 )
#endif	// CCS_DELETE

/* 删除一个指针数组并置为NULL */
#ifndef CCS_ARRAY_DELETE
#define CCS_ARRAY_DELETE( pArray )	\
	do									\
	{									\
	if ( NULL != pArray )			\
		{								\
		delete []pArray;			\
		pArray = NULL;				\
		}								\
	} while( 0 )
#endif	// CCS_ARRAY_DELETE

/* 判断当前值是否为“失败” */
#define CCS_FAILED( rResult ) ( rResult != CCS_OK )

/* 判断当前值是否为“成功” */
#define CCS_SUCCEEDED( rResult ) ( rResult == CCS_OK )

/* 填充<length>个'0' */
#define CCS_ZERO( psz, length ) memset( psz, 0, length )

#endif	//_CCS_UTIL_DEFINES_H_

