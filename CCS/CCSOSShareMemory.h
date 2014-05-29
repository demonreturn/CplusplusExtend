
#ifndef _CCS_OS_SHAREMEMORY_H_
#define _CCS_OS_SHAREMEMORY_H_

#include "CCSBase.h"

namespace CCS_OS
{
	extern CCS_API HANDLE CreateShareMemory(
		HANDLE hFile,
		DWORD dwSize,
		const char* szName );

	extern CCS_API HANDLE OpenShareMemory(
		const char* szName,
		const char* szRegularFileName = NULL );

	extern CCS_API void* MapViewShareMemory(
		HANDLE hShareMemory,
		DWORD dwSize );

	extern CCS_API BOOL FlushShareMemory(
		void* lpDataToFlush,
		DWORD dwLength );

	/*
	* 参数说明:
	*	hShareMemory	: 要关闭的句柄，是由ShareMemoryOpen或者ShareMemoryCreate
	*					  返回的，可以为NULL，表示不需任何共享内存句柄
	*	bMapToFile		: 是否映射到用户指定的文件(windows下忽略)，hShareMemory不为NULL
	*					  时生效
	*	pHeader			: 要解除映射的内存空间头指针位置，可以为NULL，表示不需解除操作
	*	dwLen			: 要关闭的长度(windows下忽略),pHeader不为NULL时生效
	*/
	extern CCS_API int CloseShareMemory(
		HANDLE hShareMemory,
		bool bMapToFile,
		void* pHeader,
		DWORD dwLength );

	extern CCS_API void UnLinkShareMemory( const char* szName );
}

#endif // _CCS_OS_SHAREMEMORY_H_