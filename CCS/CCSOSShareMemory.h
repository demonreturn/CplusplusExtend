
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
	* ����˵��:
	*	hShareMemory	: Ҫ�رյľ��������ShareMemoryOpen����ShareMemoryCreate
	*					  ���صģ�����ΪNULL����ʾ�����κι����ڴ���
	*	bMapToFile		: �Ƿ�ӳ�䵽�û�ָ�����ļ�(windows�º���)��hShareMemory��ΪNULL
	*					  ʱ��Ч
	*	pHeader			: Ҫ���ӳ����ڴ�ռ�ͷָ��λ�ã�����ΪNULL����ʾ����������
	*	dwLen			: Ҫ�رյĳ���(windows�º���),pHeader��ΪNULLʱ��Ч
	*/
	extern CCS_API int CloseShareMemory(
		HANDLE hShareMemory,
		bool bMapToFile,
		void* pHeader,
		DWORD dwLength );

	extern CCS_API void UnLinkShareMemory( const char* szName );
}

#endif // _CCS_OS_SHAREMEMORY_H_